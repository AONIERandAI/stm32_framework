#include "sys.h"

/*
��Ҫ�ĵĵط���

�ִ�BUG:
	LCD_ShowString()�����������ַ�������ȿ���һ�£�����������������ı�Դ�ַ�����Ϣ����ʱ���Ż�һ���������
	sprintf()��������ʱ��ı�MCUִ���ٶȣ����ó����죬�����Ȳ������������һ����Ŀ���������ͻ�һ��С�ɼ򵥵Ŀ�
	

3��д˳��
	���	��ֲ�˵�ģ�壬�����������Ҳ������
	���	FLASH�洢��������
	����	����2��3�����صĽ��չ��ܣ��봮��1һ���ģ���Ԥ��������Ƿ������ش���
	������	���Ʋ˵���ܣ���Ӳ�������������жఴ����LCDʱ�������ƺ�~~
	���	��ʼ���RTOS��ܣ�д������API
	...		Ъ���
			��ʼ����HAL������У����Բο��ģ�ԭ�ӵ�HAL�ֲ������ֱ�Ӹ��ƣ�Ӳʯ��HALÿ��һ��������ࣩܶ��������
	����	�ο����㹤�̿�ܣ���������X-Bot�ȣ����ػ���������ֲ�ġ���������г���
	����	����ӵĸ߼���������Իع飬
							���ּ����㷨��
							��Ƶ����룬
							modbus��
							MQTT��������ܰ���cjson����
							JPEG GIF BMP����+BMP���룬
							��Щ��ӿ⣬
							����������GUI��LWIP��FATFS�����ڵ�ͬһ���ļ������и߼����.c����ͳһ�����Ƿ����ã�
							��Щ�����Դ���򵥶���һ���ļ��з�

*/

/*__________MCU�����ʼ������_____________*/
/********************************
*��������ʼ�����У����г�ʼ��д�������桪����������������Ҫ�����޸ģ�
*������		1��NULL
*����ֵ��	1��NULL
********************************/


u16	StartUpTimes;	/*���ڱ��濪�����������������һ�������ڶ���ҳ*/
uint32_t UIDw[3]; /*����STM32�ڲ�UIDʶ���룬ȫ��Ψһʶ����*/
uint32_t sysCoreClock; /*��ȡHCLKƵ�ʣ�����ʱ�Ӿ����Դ��ٷ�Ƶ*/
u16 adValue[SYSTEM_ADC1_useChanlNum];		  /*DMA1��ADCת��������͵�Ŀ��λ��*/
u8 adValueDone = 0;		/*DMA��ADC1��ֵ���͵�adValue��ɱ�־*/
u8 is_buzzer_once = 0;
u8 is_buzzer_bibi = 0;
uint8_t is_quitFault;
void sys_MCU_Init_Seq(void)
{
	/*����ʱ��,8M * 9 = 72M���漰����ʱ׼ȷ�ԣ���Ҫ�Ҷ���*/
	/*Ĭ��Ϊ��	PLLCLK��AHB��Ϊ72MHz��APB2Ϊ72MHz��APB1Ϊ����ƵΪ36Mhz
				��ʱ��1~8��ʱ��Դ��Ϊ72MHz
				ADC��AHB��Ƶ
				SDIO��FSMC��DMAʱ��Դ��ΪAHB
				SP11ʱ��ԴΪAPB2��SP12ʱ��ԴΪAPB1
				
	*/
	Stm32_Clock_Init(RCC_PLL_MUL9);
	
	/*�ر�JTAG������SWD*/
	__HAL_RCC_AFIO_CLK_ENABLE();
	__HAL_AFIO_REMAP_SWJ_NOJTAG();
	
	/*delay��ʼ��*/
	delay_init();
	/*����MCO*/
	#if SYSTEM_MCO_PA8_OUT
		sys_MCO_Out_Enable();
	#endif
	/*����RTC*/
	#if SYSTEM_RTC_ENABLE
		sys_RTC_Enable();
		//�û����и�������RTC�����ӵ����ں�ʱ�䣬��	sys_RTC_Enable() ����		
	#endif
	/*����CRC*/
	#if SYSTEM_CRC_ENABLE
		sys_CRC_ENABLE();
		if(HAL_CRC_Accumulate(&hcrc, (uint32_t *)aDataBuffer, BUFFER_SIZE) == uwExpectedCRCValue)
		{}else{FaultASSERT("AT : CRC init");}
	#endif

	/*�����趨��ʼ������1��2��3*/
	#if SYSTEM_UART1_ENABLE
		sys_USART1_ENABLE();
		
		/*����1����Э�飺0Ϊֻ������'\r\n'��β�����ݣ�1Ϊ��FIFO�Ƚ��ȳ��Ļ��λ���ʵ�ֽ���������Э��*/
		USART1_SetMode(0);
	#endif
	#if SYSTEM_UART2_ENABLE
		sys_USART2_ENABLE();
	#endif
	#if SYSTEM_UART3_ENABLE
		sys_USART3_ENABLE();
	#endif
	
	printf_uart(UART1,"Author : Staok\r\nEmail : superxhy@qq.com\r\nRepo : https://github.com/Staok/stm32_framework\r\nSystem is starting...\r\n");
	
	/*��ȡHCLKƵ�ʲ���ӡ������1������ʱ�Ӿ����Դ��ٷ�Ƶ*/
	sysCoreClock = HAL_RCC_GetHCLKFreq(); 
	printf_uart(UART1,"sysCoreClock/HCLK : %d\r\n",sysCoreClock);
	/*����STM32�ڲ�UIDʶ���벢��ӡ��ȫ��Ψһʶ����*/
	UIDw[0] = HAL_GetUIDw0();UIDw[1] = HAL_GetUIDw1();UIDw[2] = HAL_GetUIDw2(); 
	printf_uart(UART1,"UID : %d %d %d\r\n",UIDw[0],UIDw[1],UIDw[2]);
	
	#if SYSTEM_FLASH_IAP_ENABLE
		//��ȡ��������
		STMFLASH_Read( 	(0X08000000 + (u32)((STM32_FLASH_SIZE-2)*1024)),	&StartUpTimes,	sizeof(StartUpTimes));
		StartUpTimes += 1;
		STMFLASH_Write( (0X08000000 + (u32)((STM32_FLASH_SIZE-2)*1024)),	&StartUpTimes,	sizeof(StartUpTimes));
		printf_uart(UART1,"StartUpTimes : %d\r\n",StartUpTimes);
	#endif
	
	#if STSTEM_TIM2_ENABLE
	/*˵��TIM2����;*/
	sys_TIM2_ENABLE();
	#endif
	
	#if SYSTEM_ADC1_ENABLE
		/*˵��ADC1����;*/
		sys_ADC1_ENABLE();
	#endif
	
	#if SYSTEM_SPI1_ENABLE
		/*˵��SPI1����;*/
		sys_SPI1_ENABLE();
	#endif
	
	#if SYSTEM_SPI2_ENABLE
		/*˵��SPI2����;*/
		sys_SPI2_ENABLE();
	#endif
	
	#if SYSTEM_StdbyWKUP_ENABLE
		/*ʹ�ܴ���-�͹���ģʽ��Ĭ�ϳ���PA0(WKUP)3��ؿ���*/
		sys_StdbyWKUP_ENABLE();
	#endif
	
	
	/*��ʼ��������TIM4*/
	#if STSTEM_TIM4_ENABLE
		sys_TIM4_ENABLE();
	#endif
	/*��ʼ��������TIM3PWMͨ��*/
	#if STSTEM_TIM3PWM_ENABLE
		sys_TIM3PWM_ENABLE();
	#endif
	/*��ʼ�����Ź�*/
	#if SYSTEM_IWDG_ENABLE
		sys_IWDG_ENABLE();
	#endif
	
	
}

/*__________���������ʼ�����������Լ�_____________*/
/********************************
*����������MCU����Ŀ�������������������IO�������Ե������������ù���������������������Ҫ�����޸ģ�
*������		1��NULL
*����ֵ��	1��NULL
********************************/
void sys_Device_Init_Seq(void)
{
	/*����Ϊ�û�Ӧ�õ�Device��ʼ������*/
	
	/*�û�IO��ʼ������ѡ���ʼ��ĳ���ض�����������������*/
	Devices_Init(UserDevices,ALL);
	
	/*LCD��ʼ��*/
	LCD_Init();
	
	
	buzzer_bibi_once; //��һ����ʾ��ʼ������
	printf_uart(UART1,"System init over\r\n");
}

/*____________���д�����ʾ�ʹ�ӡ______________________________*/
/********************************
*��������ʾĳ�������������⣬������ʾ������ʾ������ʾ
*������		FaultMessage:������ʾ��Ϣ�ַ���
*����ֵ��	1��NULL
********************************/
void FaultASSERT(char* FaultMessage)
{
	/*������1��������*/
	printf_uart(UART1,"Fault Message : %s\r\n",FaultMessage);
	//����ʾ������ʾ
	buzzer_bibi_on;
	while(1){;}
}
/*_____________��ȡϵͳ���е�ʱ��________________________*/
/********************************
*��������ȡϵͳ���е�ʱ��
*������		mins��secs��_10ms:ϵͳ����ʱ��ķ��������ڴ˻����϶�������������ڴ˻����϶����10������
*����ֵ��	1��ϵͳ���е�������
********************************/
u16 sys_GetsysRunTime(u16* mins,u16* secs,u16* _10ms)
{
	*mins = Timer_IT_flags._1min;
	*secs = Timer_IT_flags._1sec;
	*_10ms = Timer_IT_flags._10msec;
	return ((Timer_IT_flags._1min)*60 + Timer_IT_flags._1sec);
}
/*__________ʱ��ϵͳ���ú���_____________*/
/********************************
*�������ϵ�ʱ��Ҫ���е�ʱ�����ã�Ĭ��ʹ���ⲿ�����ź�Դ
*������		1��PLL:ѡ��ı�Ƶ����RCC_PLL_MUL2~RCC_PLL_MUL16
*����ֵ��	1��ReturnOK,�ɹ�
			2��ReturnErr,ʧ��
********************************/
int8_t Stm32_Clock_Init(uint32_t PLL)
{
    HAL_StatusTypeDef ret = HAL_OK;
    RCC_OscInitTypeDef RCC_OscInitStructure; 
    RCC_ClkInitTypeDef RCC_ClkInitStructure;
    
    RCC_OscInitStructure.OscillatorType=RCC_OSCILLATORTYPE_HSE;    	//ʱ��ԴΪHSE
    RCC_OscInitStructure.HSEState=RCC_HSE_ON;                      	//��HSE
    RCC_OscInitStructure.HSEPredivValue=RCC_HSE_PREDIV_DIV1;		//HSEԤ��Ƶ
    RCC_OscInitStructure.PLL.PLLState=RCC_PLL_ON;					//��PLL
    RCC_OscInitStructure.PLL.PLLSource=RCC_PLLSOURCE_HSE;			//PLLʱ��Դѡ��HSE
    RCC_OscInitStructure.PLL.PLLMUL=PLL; 							//��PLL��Ƶ����
    ret=HAL_RCC_OscConfig(&RCC_OscInitStructure);//��ʼ��
	
    if(ret!=HAL_OK) return ReturnErr;
    
    //ѡ��PLL��Ϊϵͳʱ��Դ��������HCLK,PCLK1��PCLK2
    RCC_ClkInitStructure.ClockType=(RCC_CLOCKTYPE_SYSCLK|RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2);
    RCC_ClkInitStructure.SYSCLKSource=RCC_SYSCLKSOURCE_PLLCLK;		//����ϵͳʱ��ʱ��ԴΪPLL
    RCC_ClkInitStructure.AHBCLKDivider=RCC_SYSCLK_DIV1;				//AHB��Ƶϵ��Ϊ1
    RCC_ClkInitStructure.APB1CLKDivider=RCC_HCLK_DIV2; 				//APB1��Ƶϵ��Ϊ2
    RCC_ClkInitStructure.APB2CLKDivider=RCC_HCLK_DIV1; 				//APB2��Ƶϵ��Ϊ1
    ret=HAL_RCC_ClockConfig(&RCC_ClkInitStructure,FLASH_LATENCY_2);	//ͬʱ����FLASH��ʱ����Ϊ2WS��Ҳ����3��CPU���ڡ�
		
    if(ret!=HAL_OK) return ReturnErr;
	
	return ReturnOK;
}


/*__________��ʱ���ײ����ú���_____________*/
/********************************
*��������ʱ���ײ�����������ʱ�ӣ������ж����ȼ����˺����ᱻHAL_TIM_Base_Init()��������
*������		1��NULL
*����ֵ��	1��NULL
********************************/
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
    if(htim->Instance==TIM4)
	{
		__HAL_RCC_TIM4_CLK_ENABLE();            //ʹ��TIM4ʱ��
		HAL_NVIC_SetPriority(TIM4_IRQn,1,0);    //�����ж����ȼ�����ռ���ȼ�1����Ӧ���ȼ�0������Ϊ4
		HAL_NVIC_EnableIRQ(TIM4_IRQn);          //����ITM4�ж�   
	}
	if(htim->Instance==TIM3)
	{
		__HAL_RCC_TIM3_CLK_ENABLE();            //ʹ��TIM3ʱ��
		HAL_NVIC_SetPriority(TIM3_IRQn,3,0);    //�����ж����ȼ�����ռ���ȼ�3�������ȼ�0
		
		//#if STSTEM_TIM3PWM_TI_ENABLE
			HAL_NVIC_EnableIRQ(TIM3_IRQn);      //����ITM3�ж�
		//#endif
	}
	if(htim->Instance==TIM2)
	{
		__HAL_RCC_TIM2_CLK_ENABLE();            //ʹ��TIM2ʱ��
		
		#if STSTEM_TIM2_TI_ENABLE
			__HAL_TIM_CLEAR_IT(&TIM2_Handler, TIM_IT_UPDATE);  // ��������жϱ�־λ
			__HAL_TIM_URS_ENABLE(&TIM2_Handler);               // ���������������Ų��������ж�
			__HAL_TIM_ENABLE_IT(&TIM2_Handler,TIM_IT_UPDATE);  // ʹ�ܸ����ж�
		#endif
		
		HAL_NVIC_SetPriority(TIM2_IRQn,3,0);
		HAL_NVIC_EnableIRQ(TIM2_IRQn);
	}
}

/*__________��ʱ���жϻص�����_____________*/
/********************************
*�������ص���������ʱ���жϷ��������ã���Ҫд��̫�����
*������		1��NULL
*����ֵ��	1��NULL
********************************/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	static u8 is_reversal = 0;
	static u8 is_runOnce4bibi = 0;	//������һ����һ��һ��Ҳû����ʱ����
	static u8 is_runOnce4biOnce = 0;
	
	/*ע�⣺��Ҫд��̫�����Ӷ�ռ��ʱ�䣡*/
    if(htim==(&TIM4_Handler))
    {
		Timer_IT_flags._10msec_flag = TRUE;
		
		/*������ö�ʱ��2���������빦�ܣ����ﶨʱ10ms���ڼ�����������ֵ�����㷵���ٶ� ��λ ת/��*/
		#if (STSTEM_TIM2_ENABLE)&&(STSTEM_TIM2_asPWMorCap == 3)
			//��������ٶȵı�����x���¾�Ӧд�� x = peek_TIM2_Encoder_Speed();
			peek_TIM2_Encoder_Speed();
		#endif
		
		if(++Timer_IT_flags._10msec >= 10)
		{
			Timer_IT_flags._10msec = 0;
			Timer_IT_flags._100msec_flag = TRUE;
			Timer_IT_flags._100msec++;
			
			#if SYSTEM_IWDG_ENABLE
				IWDG_Feed();//1s���ڵĿ��Ź�����ι����
			#endif
			
		}
		
		if(Timer_IT_flags._100msec % 3 == 0)
		{
			Timer_IT_flags._300msec_flag = TRUE;
			
			if(is_buzzer_once)
			{
				TIM3_set_Channel_Pulse(TIM3PWM_Channel_4,80.0); //�򿪷�����
				is_buzzer_once = FALSE;
				is_runOnce4biOnce = TRUE;
			}else{
				if(is_runOnce4biOnce)
				{
					TIM3_set_Channel_Pulse(TIM3PWM_Channel_4,0); //�رշ�����
					is_runOnce4biOnce = FALSE;
				}
			}
			
		}
		
		if(Timer_IT_flags._100msec >= 10)
		{
			Timer_IT_flags._100msec = 0;
			Timer_IT_flags._1sec_flag = TRUE;
			Timer_IT_flags._1sec++;
			
			if(is_buzzer_bibi)
			{
				if(is_reversal) TIM3_set_Channel_Pulse(TIM3PWM_Channel_4,80.0); //�򿪷�����
				else TIM3_set_Channel_Pulse(TIM3PWM_Channel_4,0); //�رշ�����
				is_runOnce4bibi = TRUE;
				is_reversal = ~is_reversal;
			}else{
				if(is_runOnce4bibi)
				{
					TIM3_set_Channel_Pulse(TIM3PWM_Channel_4,0);//�رշ�����
					is_runOnce4bibi = FALSE;
				}
				
			}
		}
		
		if(Timer_IT_flags._1sec >= 60)
		{
            Timer_IT_flags._1sec = 0;
			Timer_IT_flags._1min_flag = TRUE;
			Timer_IT_flags._1min++;
			
			
			if((Timer_IT_flags._1min > 666)){
				Timer_IT_flags._1min = 0;
				
				//����ʱ�䣬�����趨ǿ�ƹر�
				//_OutofTime_Running_flag = 1;
				//CTRL_DCDC_ON_OFF = DCDC_OFF;
			}
		}
    }
	
	/*��ʱ��3���ڻص�*/
	if(htim==(&TIM3_Handler))
    {
        //LED1=!LED1;
    }
	
	/*��ʱ��2���ڻص�*/
	if(htim==(&TIM2_Handler))
    {
//		#if (SYSTEM_ADC1_useScan)
//			HAL_ADC_Start(&ADC1_Handler);               	//����ADת�� 
//		#endif
		
		#if (STSTEM_TIM2_asPWMorCap == 1)					//ʹ�����벶���ܣ���ʱ�����һ�������������һ
			if((TIM2CHx_CAPTURE_STA&0X80)==0)				//��δ�ɹ�����
			{
				if(TIM2CHx_CAPTURE_STA&0X40)				//�Ѿ����񵽸ߵ�ƽ��
				{
					if((TIM2CHx_CAPTURE_STA&0X3F)==0X3F)	//�ߵ�ƽ̫����
					{
						TIM2CHx_CAPTURE_STA|=0X80;			//��ǳɹ�������һ��
						TIM2CHx_CAPTURE_VAL=0XFFFF;
					}else TIM2CHx_CAPTURE_STA++;
				}	 
			}
		#endif
		
		#if (STSTEM_TIM2_asPWMorCap == 3)					//ʹ���������빦�ܣ��������������¼
			if(__HAL_TIM_IS_TIM_COUNTING_DOWN(&TIM2_Handler))
			EncoderOverflowCount--;       //���¼������
			else
			EncoderOverflowCount++;       //���ϼ������
		#endif
    }
}


#if SYSTEM_UART1_ENABLE||SYSTEM_UART2_ENABLE||SYSTEM_UART3_ENABLE

UART_HandleTypeDef UART1_Handler,UART2_Handler,UART3_Handler; //UART���
u8 aRxBuffer1[RXBUFFERSIZE],aRxBuffer2[RXBUFFERSIZE],aRxBuffer3[RXBUFFERSIZE];//HAL��ʹ�õĴ��ڽ��ջ���


/*printf������printf_uart����ô˺������͵����ֽڣ������봮�ڷ��ͣ�ֻ��printf_uart������*/
void _putchar(char character)
{
	// send char to console etc.
	//���ʹ��RTOS�������Ƿ�Ӧ��ֹͣ����������ڽ������ٴ�
	switch(uart2sent)/*uart2sentȫ�ֱ����������жϷ��͵���һ������*/
	{
		case UART1:/*��������1*/
			HAL_UART_Transmit(&UART1_Handler, (uint8_t *)&character, 1, 0x12C); //��ʱʱ��Ϊ0x12C��Ϊ300ms
			break;
		case UART2:/*��������2*/
			HAL_UART_Transmit(&UART2_Handler, (uint8_t *)&character, 1, 0x12C);
			break;
		case UART3:/*��������3*/
			HAL_UART_Transmit(&UART3_Handler, (uint8_t *)&character, 1, 0x12C);
			break;
		default:/*Ĭ�Ϸ�������1*/
			HAL_UART_Transmit(&UART1_Handler, (uint8_t *)&character, 1, 0x12C);
			break;
	}
}

#if SYSTEM_UART1_ENABLE
void sys_USART1_ENABLE(void)
{
	//UART ��ʼ������
	UART1_Handler.Instance=USART1;					    		//USART1
	UART1_Handler.Init.BaudRate=(uint32_t)SYSTEM_UART1_BOUND;	//������
	
	UART1_Handler.Init.WordLength=UART_WORDLENGTH_8B;   		//�ֳ�Ϊ8λ���ݸ�ʽ
	UART1_Handler.Init.StopBits=UART_STOPBITS_1;	    		//һ��ֹͣλ
	UART1_Handler.Init.Parity=UART_PARITY_NONE;		    		//����żУ��λ
	UART1_Handler.Init.HwFlowCtl=UART_HWCONTROL_NONE;   		//��Ӳ������
	UART1_Handler.Init.Mode=UART_MODE_TX_RX;		    		//�շ�ģʽ
	HAL_UART_Init(&UART1_Handler);					    		//HAL_UART_Init()��ʹ��UART1
	
	HAL_UART_Receive_IT(&UART1_Handler, (u8 *)aRxBuffer1, RXBUFFERSIZE);//�ú����Ὺ�������жϣ���־λUART_IT_RXNE���������ý��ջ����Լ����ջ���������������
	
//	if(fifo_create_static(Uart1_fifo, USART1_RX_FIFO_buf, (uint16_t)USART1_RX_FIFO_MaxNum, sizeof(char)) == NULL)
//	{
//		FaultASSERT("AT:fifo_create_static");
//	}
	Uart1_fifo = fifo_create((uint16_t)USART1_RX_FIFO_MaxNum, sizeof(char));
	if(Uart1_fifo == NULL)
	{
		FaultASSERT("AT:fifo_create");
	}
}

char sys_USART1_RX_Fetch(u8 is_print, char* buf)
{
	char CharData,is_Data;
	u16 i;
	
	if(!(USART1_RX_CONFIG & USART1_RX_MODE_mask))
	{
		/*0Ϊֻ������'\r\n'��β������*/
		if(USART1_isDone)
		{
			if(is_print)
				printf_uart(UART1,"%s",USART1_RX_BUF);
			if(USART1_RX_ByteNum >= USART1_RX_BUF_MaxNum) /*��ֹջ���*/
			{
				mystrncpy(buf,USART1_RX_BUF,USART1_RX_BUF_MaxNum);
			}else{
				mystrncpy(buf,USART1_RX_BUF,USART1_RX_ByteNum);
			}
			//buf = USART1_RX_BUF; /*��fifo���õ�char*�����ﲻ��ֱ�Ӹ���ַ����������\0������\r\n���ַ���*/ 
			USART1_SetUnDone;
			return (char)ReturnOK;
		}else{
			return (char)ReturnErr;
			}
	}else{
		/*1Ϊ��FIFO�Ƚ��ȳ��Ļ��λ���ʵ�ֽ���������Э��*/
		
		is_Data = FALSE;i = 0;
		while(fifo_get(Uart1_fifo, &CharData))
		{
			is_Data = TRUE;
			buf[i++] = CharData;
		}
		
		if(i >= USART1_RX_FIFO_MaxNum) /*��ֹջ���*/
		{
			buf[(USART1_RX_FIFO_MaxNum-1)] = '\0';
		}else{
			buf[i] = '\0';
		}
		
		if(is_print)
			printf_uart(UART1,"%c",CharData);
		
		if(is_Data == TRUE)
		{
			return (char)ReturnOK;
		}else{
			return (char)ReturnErr;
			}
	}
}

#endif
#if SYSTEM_UART2_ENABLE
void sys_USART2_ENABLE(void)
{
	//UART ��ʼ������
	UART2_Handler.Instance=USART2;					    		//USART2
	UART2_Handler.Init.BaudRate=(uint32_t)SYSTEM_UART2_BOUND;	//������
	
	UART2_Handler.Init.WordLength=UART_WORDLENGTH_8B;   		//�ֳ�Ϊ8λ���ݸ�ʽ
	UART2_Handler.Init.StopBits=UART_STOPBITS_1;	    		//һ��ֹͣλ
	UART2_Handler.Init.Parity=UART_PARITY_NONE;		    		//����żУ��λ
	UART2_Handler.Init.HwFlowCtl=UART_HWCONTROL_NONE;   		//��Ӳ������
	UART2_Handler.Init.Mode=UART_MODE_TX_RX;		    		//�շ�ģʽ
	HAL_UART_Init(&UART2_Handler);					    		//HAL_UART_Init()��ʹ��UART2
	
	HAL_UART_Receive_IT(&UART2_Handler, (u8 *)aRxBuffer2, RXBUFFERSIZE);//�ú����Ὺ�������жϣ���־λUART_IT_RXNE���������ý��ջ����Լ����ջ���������������
}
#endif
#if SYSTEM_UART3_ENABLE
void sys_USART3_ENABLE(void)
{
	//UART ��ʼ������
	UART3_Handler.Instance=USART3;					    		//USART3
	UART3_Handler.Init.BaudRate=(uint32_t)SYSTEM_UART3_BOUND;	//������
	
	UART3_Handler.Init.WordLength=UART_WORDLENGTH_8B;   		//�ֳ�Ϊ8λ���ݸ�ʽ
	UART3_Handler.Init.StopBits=UART_STOPBITS_1;	    		//һ��ֹͣλ
	UART3_Handler.Init.Parity=UART_PARITY_NONE;		    		//����żУ��λ
	UART3_Handler.Init.HwFlowCtl=UART_HWCONTROL_NONE;   		//��Ӳ������
	UART3_Handler.Init.Mode=UART_MODE_TX_RX;		    		//�շ�ģʽ
	HAL_UART_Init(&UART3_Handler);					    		//HAL_UART_Init()��ʹ��UART3
	
	HAL_UART_Receive_IT(&UART3_Handler, (u8 *)aRxBuffer3, RXBUFFERSIZE);//�ú����Ὺ�������жϣ���־λUART_IT_RXNE���������ý��ջ����Լ����ջ���������������
}
#endif
//UART�ײ��ʼ����ʱ��ʹ�ܣ��������ã��ж�����
//�˺����ᱻHAL_UART_Init()����
//huart:���ھ��
void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
    //GPIO�˿�����
	GPIO_InitTypeDef GPIO_Initure;
	if(huart->Instance==USART1)//����Ǵ���1�����д���1 MSP��ʼ��
	{
		__HAL_RCC_USART1_CLK_ENABLE();			//ʹ��USART1ʱ��
		__HAL_RCC_AFIO_CLK_ENABLE();
		#if SYSTEM_UART1_REMAP_ENABLE
			__HAL_AFIO_REMAP_USART1_ENABLE();
			__HAL_RCC_GPIOB_CLK_ENABLE();
			GPIO_Initure.Pin=GPIO_PIN_6;			//PB6 TX
			GPIO_Initure.Mode=GPIO_MODE_AF_PP;		//�����������
			GPIO_Initure.Pull=GPIO_PULLUP;			//����
			GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;//����
			HAL_GPIO_Init(GPIOB,&GPIO_Initure);	   	//��ʼ��PB6

			GPIO_Initure.Pin=GPIO_PIN_7;			//PB7 RX
			GPIO_Initure.Mode=GPIO_MODE_AF_INPUT;	//ģʽҪ����Ϊ��������ģʽ��	
			HAL_GPIO_Init(GPIOB,&GPIO_Initure);	   	//��ʼ��PB7
		#else 
			__HAL_RCC_GPIOA_CLK_ENABLE();			//ʹ��GPIOAʱ��
			GPIO_Initure.Pin=GPIO_PIN_9;			//PA9 TX
			GPIO_Initure.Mode=GPIO_MODE_AF_PP;		//�����������
			GPIO_Initure.Pull=GPIO_PULLUP;			//����
			GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;//����
			HAL_GPIO_Init(GPIOA,&GPIO_Initure);	   	//��ʼ��PA9

			GPIO_Initure.Pin=GPIO_PIN_10;			//PA10 RX
			GPIO_Initure.Mode=GPIO_MODE_AF_INPUT;	//ģʽҪ����Ϊ��������ģʽ��	
			HAL_GPIO_Init(GPIOA,&GPIO_Initure);	   	//��ʼ��PA10
		#endif
		
		HAL_NVIC_SetPriority(USART1_IRQn,3,0);			//��ռ���ȼ�3�������ȼ�0
		HAL_NVIC_EnableIRQ(USART1_IRQn);				//ʹ��USART1�ж�ͨ��
	}
	
	if(huart->Instance==USART2)//����Ǵ���2�����д���2 MSP��ʼ��
	{
		__HAL_RCC_USART2_CLK_ENABLE();			//ʹ��USART2ʱ��
		__HAL_RCC_AFIO_CLK_ENABLE();
		#if SYSTEM_UART2_REMAP_ENABLE
			__HAL_AFIO_REMAP_USART2_ENABLE();
			__HAL_RCC_GPIOD_CLK_ENABLE();
			GPIO_Initure.Pin=GPIO_PIN_5;			//PD5 TX
			GPIO_Initure.Mode=GPIO_MODE_AF_PP;		//�����������
			GPIO_Initure.Pull=GPIO_PULLUP;			//����
			GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;//����
			HAL_GPIO_Init(GPIOD,&GPIO_Initure);	   	//��ʼ��PD5

			GPIO_Initure.Pin=GPIO_PIN_6;			//PD6 RX
			GPIO_Initure.Mode=GPIO_MODE_AF_INPUT;	//ģʽҪ����Ϊ��������ģʽ��	
			HAL_GPIO_Init(GPIOD,&GPIO_Initure);	   	//��ʼ��PD6
		#else 
			__HAL_RCC_GPIOA_CLK_ENABLE();			//ʹ��GPIOAʱ��
			GPIO_Initure.Pin=GPIO_PIN_2;			//PA2 TX
			GPIO_Initure.Mode=GPIO_MODE_AF_PP;		//�����������
			GPIO_Initure.Pull=GPIO_PULLUP;			//����
			GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;//����
			HAL_GPIO_Init(GPIOA,&GPIO_Initure);	   	//��ʼ��PA2

			GPIO_Initure.Pin=GPIO_PIN_3;			//PA3 RX
			GPIO_Initure.Mode=GPIO_MODE_AF_INPUT;	//ģʽҪ����Ϊ��������ģʽ��	
			HAL_GPIO_Init(GPIOA,&GPIO_Initure);	   	//��ʼ��PA3
		#endif
		
		HAL_NVIC_SetPriority(USART2_IRQn,4,0);
		HAL_NVIC_EnableIRQ(USART2_IRQn);				//ʹ��USART2�ж�ͨ��
	}
	
	if(huart->Instance==USART3)//����Ǵ���3�����д���3 MSP��ʼ��
	{
		__HAL_RCC_USART3_CLK_ENABLE();			//ʹ��USART3ʱ��
		__HAL_RCC_AFIO_CLK_ENABLE();
		#if SYSTEM_UART3_REMAP_ENABLE
			__HAL_AFIO_REMAP_USART3_ENABLE();
			__HAL_RCC_GPIOD_CLK_ENABLE();
			GPIO_Initure.Pin=GPIO_PIN_8;			//PD8 TX
			GPIO_Initure.Mode=GPIO_MODE_AF_PP;		//�����������
			GPIO_Initure.Pull=GPIO_PULLUP;			//����
			GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;//����
			HAL_GPIO_Init(GPIOD,&GPIO_Initure);	   	//��ʼ��PD8

			GPIO_Initure.Pin=GPIO_PIN_9;			//PD9 RX
			GPIO_Initure.Mode=GPIO_MODE_AF_INPUT;	//ģʽҪ����Ϊ��������ģʽ��	
			HAL_GPIO_Init(GPIOD,&GPIO_Initure);	   	//��ʼ��PD9
		#else 
			__HAL_RCC_GPIOB_CLK_ENABLE();			//ʹ��GPIOBʱ��
			GPIO_Initure.Pin=GPIO_PIN_10;			//PB10 TX
			GPIO_Initure.Mode=GPIO_MODE_AF_PP;		//�����������
			GPIO_Initure.Pull=GPIO_PULLUP;			//����
			GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;//����
			HAL_GPIO_Init(GPIOB,&GPIO_Initure);	   	//��ʼ��PB10

			GPIO_Initure.Pin=GPIO_PIN_11;			//PB11 RX
			GPIO_Initure.Mode=GPIO_MODE_AF_INPUT;	//ģʽҪ����Ϊ��������ģʽ��	
			HAL_GPIO_Init(GPIOB,&GPIO_Initure);	   	//��ʼ��PB11
		#endif
		
		HAL_NVIC_SetPriority(USART3_IRQn,4,0);
		HAL_NVIC_EnableIRQ(USART3_IRQn);				//ʹ��USART3�ж�ͨ��
	}
}




char USART1_RX_BUF[USART1_RX_BUF_MaxNum]; 		/*����1��ģʽ1���ݽ�����*/

//	fifo_t Test_fifo;
//	fifo_t Test2_fifo;
	fifo_t Uart1_fifo;
//char USART1_RX_FIFO_buf[USART1_RX_FIFO_MaxNum] = "0"; 	/*����1��ģʽ0��FIFO���ݽ���������̬����ʱ����*/
/*�������з�����sys.h����*/
//#define USART1_RX_DONE_mask 0x8000
//#define USART1_RX_MODE_mask 0x4000
//#define USART1_RX_Rec_r_mask 0x2000
//#define USART1_RX_Num_mask 0x1fff /*0001 1111 1111 1111*/

u16 USART1_RX_CONFIG = 0;	/*    x            x           x        x xxxx xxxx xxxx      */
							/*(�������) (Э��ģʽ0/1) (���յ�\r)   ����1���������ֽڼ��� */
							/*����1����Э�飺0Ϊֻ������'\r\n'��β�����ݣ�1Ϊ��FIFO�Ƚ��ȳ��Ļ��λ���ʵ�ֽ���������Э��*/
/*
FIFO�Ƚ��ȳ����ζ���ʾ�⣺	ͷָ���ֻ������βָ���ֻд�롣
							 *		*		*		*		*	...
							 0ͷ	1		2		3		4β����������ݴ���βָ���ϣ����Ŵ洢��βָ������ƶ���
							�ж�ͷ�����ݴ������˺󣬡�0����ַ�ռ�����ݽ����ͷŵ����ж�ͷָ����һ�����Դ������ݵĵ�ַ��1�����Դ�����
							��һ���ڴ��ڣ�βָ��һֱ�ƶ��������ʱ���0��ַ���У����βָ��ָ��0���Ӷ��γɻ���
*/
/*�������з�����sys.h����*/
//#define USART1_SetMode(x) 	USART1_RX_CONFIG |= (((u16)x)<<14) /*�û����ã������������ô���1����Э��*/
//#define USART1_isDone 		(USART1_RX_CONFIG & USART1_RX_DONE_mask)/*�û��ã������ж��Ƿ�������һ��*/
//#define USART1_RX_ByteNum 	(USART1_RX_CONFIG & USART1_RX_Num_mask)/*�û����ã����ؽ��յ��ַ�����*/
//#define USART1_SetDone 		USART1_RX_CONFIG |= USART1_RX_DONE_mask /*���ô���1������ɱ�־λ*/
//#define USART1_SetUnDone 		USART1_RX_CONFIG &= USART1_RX_MODE_mask /*�û����ã��������д������Դ���1��־λ���и�λ������modeλ������λ��д0*/

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance==USART1)//����Ǵ���1
	{	
		if(!(USART1_RX_CONFIG & USART1_RX_MODE_mask)) /*Э��0��ֻ������'\r\n'��β�����ݣ���USART1_RX_BUF[]��������*/
		{ 
			if(!(USART1_RX_CONFIG & USART1_RX_DONE_mask)) /*�������δ���*/
			{
				if(USART1_RX_CONFIG & USART1_RX_Rec_r_mask) /*������յ���\r*/
				{
					if(aRxBuffer1[0] == '\n') /*������ܵ���\r\n*/
					{
						USART1_RX_BUF[USART1_RX_ByteNum] = '\0'; /*�Ӹ�������\0*/
						USART1_SetDone;
						//USART1_RX_CONFIG++; 
						/*������ɺ�� ���������ֽڼ��� ������ '\r\n' ����*/
					}else{USART1_Set_r_UnDone;} /*û�н��յ�\n�������µȵ�\r����*/
				}else
				{
					if(aRxBuffer1[0] == '\r') {USART1_RX_CONFIG |= USART1_RX_Rec_r_mask;
												//USART1_RX_CONFIG++; /*������ɺ�� ���������ֽڼ��� ������ '\r\n' ����*/
					}
					else{
						USART1_RX_BUF[USART1_RX_CONFIG & USART1_RX_Num_mask] = aRxBuffer1[0];
						USART1_RX_CONFIG++;
						if((USART1_RX_CONFIG & USART1_RX_Num_mask) >= (USART1_RX_BUF_MaxNum)) USART1_SetDone; 
					}

				}
			}
		}else 		/*Э��1����FIFO�Ƚ��ȳ��Ļ��λ���ʵ�ֽ���������Э�飬��Ҫ��ʱ���ߣ���������������������ݶ�ʧ*/
		{
			if(!fifo_is_full(Uart1_fifo))
				fifo_add(Uart1_fifo, &aRxBuffer1[0]);
		}
	}else if(huart->Instance==USART2)//����Ǵ���2
	{
		
	}else if(huart->Instance==USART3)//����Ǵ���3
	{
		
	}
}

#if SYSTEM_UART1_ENABLE
void USART1_IRQHandler(void)	//����1�жϷ������
{ 
	u32 timeout=0;
	#if SYSTEM_SUPPORT_OS	 	//ʹ��OS
		//OSIntEnter();  
		taskENTER_CRITICAL();           //�����ٽ���
	#endif
	
	HAL_UART_IRQHandler(&UART1_Handler);	//����HAL���жϴ����ú���
	
	timeout=0;
    while (HAL_UART_GetState(&UART1_Handler) != HAL_UART_STATE_READY)//�ȴ�����
	{
	 timeout++;////��ʱ����
     if(timeout>HAL_MAX_DELAY) break;		
	
	}
     
	timeout=0;
	while(HAL_UART_Receive_IT(&UART1_Handler, (u8 *)aRxBuffer1, RXBUFFERSIZE) != HAL_OK)//һ�δ������֮�����¿����жϲ�����RxXferCountΪ1
	{
	 timeout++; //��ʱ����
	 if(timeout>HAL_MAX_DELAY) break;	
	}
	#if SYSTEM_SUPPORT_OS	 	//ʹ��OS
		//OSIntExit();  	
		taskEXIT_CRITICAL();            //�˳��ٽ���
	#endif
}
#endif

#if SYSTEM_UART2_ENABLE
void USART2_IRQHandler(void)	//����2�жϷ������
{ 
	u32 timeout=0;
	#if SYSTEM_SUPPORT_OS	 	//ʹ��OS
		//OSIntEnter();    
		taskENTER_CRITICAL();           //�����ٽ���
	#endif
	
	HAL_UART_IRQHandler(&UART2_Handler);	//����HAL���жϴ����ú���
	
	timeout=0;
    while (HAL_UART_GetState(&UART2_Handler) != HAL_UART_STATE_READY)//�ȴ�����
	{
	 timeout++;////��ʱ����
     if(timeout>HAL_MAX_DELAY) break;		
	
	}
     
	timeout=0;
	while(HAL_UART_Receive_IT(&UART2_Handler, (u8 *)aRxBuffer2, RXBUFFERSIZE) != HAL_OK)//һ�δ������֮�����¿����жϲ�����RxXferCountΪ1
	{
	 timeout++; //��ʱ����
	 if(timeout>HAL_MAX_DELAY) break;	
	}
	#if SYSTEM_SUPPORT_OS	 	//ʹ��OS
		//OSIntExit();  			
		taskEXIT_CRITICAL();            //�˳��ٽ���	
	#endif
}
#endif

#if SYSTEM_UART3_ENABLE
void USART3_IRQHandler(void)	//����3�жϷ������
{ 
	u32 timeout=0;
	#if SYSTEM_SUPPORT_OS	 	//ʹ��OS
		//OSIntEnter();    
		taskENTER_CRITICAL();           //�����ٽ���
	#endif
	
	HAL_UART_IRQHandler(&UART3_Handler);	//����HAL���жϴ����ú���
	
	timeout=0;
    while (HAL_UART_GetState(&UART3_Handler) != HAL_UART_STATE_READY)//�ȴ�����
	{
	 timeout++;////��ʱ����
     if(timeout>HAL_MAX_DELAY) break;		
	
	}
     
	timeout=0;
	while(HAL_UART_Receive_IT(&UART3_Handler, (u8 *)aRxBuffer3, RXBUFFERSIZE) != HAL_OK)//һ�δ������֮�����¿����жϲ�����RxXferCountΪ1
	{
	 timeout++; //��ʱ����
	 if(timeout>HAL_MAX_DELAY) break;	
	}
	#if SYSTEM_SUPPORT_OS	 	//ʹ��OS
		//OSIntExit();  			
		taskEXIT_CRITICAL();            //�˳��ٽ���
	#endif
}
#endif

#endif

#if STSTEM_TIM4_ENABLE

struct TIM4_IT_FLAGS Timer_IT_flags = 
{
	._10msec_flag = 0,
	._10msec = 0,
	._100msec_flag = 0,
	._100msec = 0,
	._300msec_flag = 0,
	._1sec_flag  = 0,
	._1sec = 0,
	._1min_flag = 0,
	._1min = 0
};

//ͨ�ö�ʱ��4�жϳ�ʼ����arr���Զ���װֵ��psc��ʱ��Ԥ��Ƶ������ʱ�����ʱ����㷽��:Tout=((arr+1)*(psc+1))/Ft us
//�˴�Ĭ��Ƶ��Ϊ100Hz��10ms����һ���ж�
TIM_HandleTypeDef TIM4_Handler;
void sys_TIM4_ENABLE(void)
{
	TIM4_Handler.Instance=TIM4;                          		//ͨ�ö�ʱ��4
    TIM4_Handler.Init.Prescaler=(360-1);                     	//��Ƶϵ��
    TIM4_Handler.Init.CounterMode=TIM_COUNTERMODE_UP;    		//���ϼ�����
    TIM4_Handler.Init.Period=(2000-1);                        	//�Զ�װ��ֵ
    TIM4_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;		//ʱ�ӷ�Ƶ����
    HAL_TIM_Base_Init(&TIM4_Handler);
    
    HAL_TIM_Base_Start_IT(&TIM4_Handler); //ʹ�ܶ�ʱ��4�Ͷ�ʱ��4�����жϣ�TIM_IT_UPDATE 
}

//��ʱ��4�жϷ�����
void TIM4_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&TIM4_Handler);
}

#endif


#if STSTEM_TIM3PWM_ENABLE

TIM_HandleTypeDef 	TIM3_Handler;      	//��ʱ�����
TIM_OC_InitTypeDef 	TIM3_CH1Handler,TIM3_CH2Handler,TIM3_CH3Handler,TIM3_CH4Handler;	//��ʱ��3ͨ��1-4���
void sys_TIM3PWM_ENABLE(void)
{
	TIM3_Handler.Instance=TIM3;          	//��ʱ��3
	TIM3_Handler.Init.Prescaler=tim3prsc;       //��ʱ����Ƶ
	TIM3_Handler.Init.CounterMode=TIM_COUNTERMODE_UP;//���ϼ���ģʽ
	TIM3_Handler.Init.Period=tim3arr;          //�Զ���װ��ֵ
	TIM3_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;
	
	
	/*���Ҫ������ʱ�жϣ�ȡ���������ע�ͺ�HAL_TIM_Base_MspInit�е�TIM3��IRQע��*/
	#if STSTEM_TIM3PWM_TI_ENABLE
		HAL_TIM_Base_Init(&TIM3_Handler);
		HAL_TIM_Base_Start_IT(&TIM3_Handler); //ʹ�ܶ�ʱ��3�Ͷ�ʱ��3�����жϣ�TIM_IT_UPDATE
	#endif
	
	HAL_TIM_PWM_Init(&TIM3_Handler);       //��ʼ��PWM
    
	if(STSTEM_TIM3PWM_CHANNEL_ENABLE & B0000_0010)
	{
		TIM3_CH2Handler.OCMode=TIM_OCMODE_PWM1; //ģʽѡ��PWM1
		TIM3_CH2Handler.Pulse=tim3arr/2;            //���ñȽ�ֵ,��ֵ����ȷ��ռ�ձȣ�Ĭ�ϱȽ�ֵΪ�Զ���װ��ֵ��һ��,��ռ�ձ�Ϊ50%
		/*����Ƚϼ���Ϊ�ͣ�����PWM1ģʽʱ��������ֵС�ڱȽ�ֵʱ����͵�ƽ��PWM2��PWM1�����෴��ע��淶����͵�ƽ��Ч���ߵ�ƽ��ֹ*/
		/*��������ֵС�ڱȽ�ֵʱ�����Ч���������Թ�����������Ƚ�ֵԽ����������ʱ��Խ������ ռ�ձ� Խ��*/
		TIM3_CH2Handler.OCPolarity=TIM_OCPOLARITY_LOW;
		HAL_TIM_PWM_ConfigChannel(&TIM3_Handler,&TIM3_CH2Handler,TIM_CHANNEL_2);//����TIM3ͨ��2
		HAL_TIM_PWM_Start(&TIM3_Handler,TIM_CHANNEL_2);//����PWMͨ��2
	}
	if(STSTEM_TIM3PWM_CHANNEL_ENABLE & B0000_0001)
	{
		TIM3_CH1Handler.OCMode=TIM_OCMODE_PWM1; //ģʽѡ��PWM1
		TIM3_CH1Handler.Pulse=tim3arr/2;            //���ñȽ�ֵ,��ֵ����ȷ��ռ�ձȣ�Ĭ�ϱȽ�ֵΪ�Զ���װ��ֵ��һ��,��ռ�ձ�Ϊ50%
		TIM3_CH1Handler.OCPolarity=TIM_OCPOLARITY_LOW; //����Ƚϼ���Ϊ�� 
		HAL_TIM_PWM_ConfigChannel(&TIM3_Handler,&TIM3_CH1Handler,TIM_CHANNEL_1);//����TIM3ͨ��1
		HAL_TIM_PWM_Start(&TIM3_Handler,TIM_CHANNEL_1);//����PWMͨ��1
	}
	if(STSTEM_TIM3PWM_CHANNEL_ENABLE & B0000_0100)
	{
		TIM3_CH3Handler.OCMode=TIM_OCMODE_PWM1; //ģʽѡ��PWM1
		TIM3_CH3Handler.Pulse=tim3arr/2;            //���ñȽ�ֵ,��ֵ����ȷ��ռ�ձȣ�Ĭ�ϱȽ�ֵΪ�Զ���װ��ֵ��һ��,��ռ�ձ�Ϊ50%
		TIM3_CH3Handler.OCPolarity=TIM_OCPOLARITY_LOW; //����Ƚϼ���Ϊ�� 
		HAL_TIM_PWM_ConfigChannel(&TIM3_Handler,&TIM3_CH3Handler,TIM_CHANNEL_3);//����TIM3ͨ��3
		HAL_TIM_PWM_Start(&TIM3_Handler,TIM_CHANNEL_3);//����PWMͨ��3
	}
	if(STSTEM_TIM3PWM_CHANNEL_ENABLE & B0000_1000)
	{
		TIM3_CH4Handler.OCMode=TIM_OCMODE_PWM1; //ģʽѡ��PWM1
		TIM3_CH4Handler.Pulse=tim3arr/2;            //���ñȽ�ֵ,��ֵ����ȷ��ռ�ձȣ�Ĭ�ϱȽ�ֵΪ�Զ���װ��ֵ��һ��,��ռ�ձ�Ϊ50%
		TIM3_CH4Handler.OCPolarity=TIM_OCPOLARITY_LOW; //����Ƚϼ���Ϊ�� 
		HAL_TIM_PWM_ConfigChannel(&TIM3_Handler,&TIM3_CH4Handler,TIM_CHANNEL_4);//����TIM3ͨ��4
		HAL_TIM_PWM_Start(&TIM3_Handler,TIM_CHANNEL_4);//����PWMͨ��4
	}

}
//void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)�Ѿ�д������

//��ʱ���ײ�������ʱ��ʹ�ܣ���������
//�˺����ᱻHAL_TIM_PWM_Init()����
//htim:��ʱ�����
void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)
{
	GPIO_InitTypeDef GPIO_Initure;
	
    if(htim->Instance==TIM3)
	{
		__HAL_RCC_TIM3_CLK_ENABLE();			//ʹ�ܶ�ʱ��3
		
		if(STSTEM_TIM3PWM_REMAP_ENABLE)	//���ȫ����ӳ��
		{
			__HAL_AFIO_REMAP_TIM3_ENABLE();			//TIM3ͨ������ȫ����ӳ��ʹ�ܣ�������ôӳ�俴�⺯��ע�ͻ�sys.h��
			__HAL_RCC_GPIOC_CLK_ENABLE();			//����GPIOCʱ��
			if(STSTEM_TIM3PWM_CHANNEL_ENABLE & B0000_0001)	GPIO_Initure.Pin=GPIO_PIN_6;	//�������ͨ��1��PC6
			if(STSTEM_TIM3PWM_CHANNEL_ENABLE & B0000_0010)	GPIO_Initure.Pin=GPIO_PIN_7;	//�������ͨ��2��PC7
			if(STSTEM_TIM3PWM_CHANNEL_ENABLE & B0000_0100)	GPIO_Initure.Pin=GPIO_PIN_8;	//�������ͨ��3��PC8
			if(STSTEM_TIM3PWM_CHANNEL_ENABLE & B0000_1000)	GPIO_Initure.Pin=GPIO_PIN_6;	//�������ͨ��4��PC9
			GPIO_Initure.Mode=GPIO_MODE_AF_PP;  	//�����������
			GPIO_Initure.Pull=GPIO_PULLUP;          //����������Ӳ������õ͵�ƽ��Ч���ߵ�ƽ��ֹ
			GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;//����
			HAL_GPIO_Init(GPIOC,&GPIO_Initure); 
		}else if(STSTEM_TIM3PWM_REMAP_PARTIAL)	//���������ӳ��
		{
			__HAL_AFIO_REMAP_TIM3_PARTIAL();		//TIM3ͨ�����Ų�����ӳ��ʹ�ܣ�������ôӳ�俴�⺯��ע�ͻ�sys.h��
			__HAL_RCC_GPIOB_CLK_ENABLE();			//����GPIOBʱ��
			if(STSTEM_TIM3PWM_CHANNEL_ENABLE & B0000_0001)	GPIO_Initure.Pin=GPIO_PIN_4;	//�������ͨ��1��PB4
			if(STSTEM_TIM3PWM_CHANNEL_ENABLE & B0000_0010)	GPIO_Initure.Pin=GPIO_PIN_5;	//�������ͨ��2��PB5
			if(STSTEM_TIM3PWM_CHANNEL_ENABLE & B0000_0100)	GPIO_Initure.Pin=GPIO_PIN_0;	//�������ͨ��3��PB0
			if(STSTEM_TIM3PWM_CHANNEL_ENABLE & B0000_1000)	GPIO_Initure.Pin=GPIO_PIN_1;	//�������ͨ��4��PB1
			GPIO_Initure.Mode=GPIO_MODE_AF_PP;  	//�����������
			GPIO_Initure.Pull=GPIO_PULLUP;          //����������Ӳ������õ͵�ƽ��Ч���ߵ�ƽ��ֹ
			GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;//����
			HAL_GPIO_Init(GPIOB,&GPIO_Initure); 			
		}else{									//û����ӳ��
			
			GPIO_Initure.Mode=GPIO_MODE_AF_PP;  	//�����������
			GPIO_Initure.Pull=GPIO_PULLUP;          //����������Ӳ������õ͵�ƽ��Ч���ߵ�ƽ��ֹ
			GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;//����
			
			if(STSTEM_TIM3PWM_CHANNEL_ENABLE & B0000_0001)	
			{
				__HAL_RCC_GPIOA_CLK_ENABLE();GPIO_Initure.Pin=GPIO_PIN_6;	//�������ͨ��1��PA6
				HAL_GPIO_Init(GPIOA,&GPIO_Initure); 
			}
			if(STSTEM_TIM3PWM_CHANNEL_ENABLE & B0000_0010)
			{
				__HAL_RCC_GPIOA_CLK_ENABLE();GPIO_Initure.Pin=GPIO_PIN_7;	//�������ͨ��2��PA7
				HAL_GPIO_Init(GPIOA,&GPIO_Initure); 
			}
			if(STSTEM_TIM3PWM_CHANNEL_ENABLE & B0000_0100)
			{
				__HAL_RCC_GPIOB_CLK_ENABLE();GPIO_Initure.Pin=GPIO_PIN_0;	//�������ͨ��3��PB0
				HAL_GPIO_Init(GPIOB,&GPIO_Initure); 
			}
			if(STSTEM_TIM3PWM_CHANNEL_ENABLE & B0000_1000)
			{
				__HAL_RCC_GPIOB_CLK_ENABLE();GPIO_Initure.Pin=GPIO_PIN_1;	//�������ͨ��4��PB1
				HAL_GPIO_Init(GPIOB,&GPIO_Initure);
			}
		}
	}
	
	if(htim->Instance==TIM2)
	{
		__HAL_RCC_TIM2_CLK_ENABLE();			//ʹ�ܶ�ʱ��2
		__HAL_AFIO_REMAP_TIM2_ENABLE();			/*TIM2ͨ��������ȫ��ӳ��ʹ�� (CH1/ETR/PA15, CH2/PB3, CH3/PB10, CH4/PB11)*/
		
		GPIO_Initure.Mode=GPIO_MODE_AF_PP;  	//�����������
		GPIO_Initure.Pull=GPIO_PULLUP;          //����������Ӳ������õ͵�ƽ��Ч���ߵ�ƽ��ֹ
		GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;//����
		
		if(STSTEM_TIM2PWM_CHANNEL_ENABLE & B0000_0001)	//CH1/ETR/PA15
		{
			__HAL_RCC_GPIOA_CLK_ENABLE();
			GPIO_Initure.Pin=GPIO_PIN_15;
			HAL_GPIO_Init(GPIOA,&GPIO_Initure);
		}
		if(STSTEM_TIM2PWM_CHANNEL_ENABLE & B0000_0010)	//CH2/PB3
		{
			__HAL_RCC_GPIOB_CLK_ENABLE();
			GPIO_Initure.Pin=GPIO_PIN_3;
			HAL_GPIO_Init(GPIOB,&GPIO_Initure);
		}
		if(STSTEM_TIM2PWM_CHANNEL_ENABLE & B0000_0100)	//CH3/PB10
		{
			__HAL_RCC_GPIOB_CLK_ENABLE();
			GPIO_Initure.Pin=GPIO_PIN_10;
			HAL_GPIO_Init(GPIOB,&GPIO_Initure);
		}
		if(STSTEM_TIM2PWM_CHANNEL_ENABLE & B0000_1000)	//CH4/PB11
		{
			__HAL_RCC_GPIOB_CLK_ENABLE();
			GPIO_Initure.Pin=GPIO_PIN_11;
			HAL_GPIO_Init(GPIOB,&GPIO_Initure);
		}
	}
}

//����TIM3ͨ����ռ�ձ�
//percent:ռ�ձȰٷ���
void TIM3_set_Channel_Pulse(u8 channel,float percent)
{
	float compare;
	if(percent < 0) percent = 0;
	if(percent > 100) percent = 100.0;
	percent /= 100.0;
	compare = (float)tim3arr * percent;
	switch(channel)
	{
		case TIM3PWM_Channel_1: TIM3->CCR1=(u32)compare;break;
		case TIM3PWM_Channel_2: TIM3->CCR2=(u32)compare;break;
		case TIM3PWM_Channel_3: TIM3->CCR3=(u32)compare;break;
		case TIM3PWM_Channel_4: TIM3->CCR4=(u32)compare;break;
		default:break;
	}
}

//��ʱ��3�жϷ�����
void TIM3_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&TIM3_Handler);
}

//�ص���������ʱ���жϷ��������õ�void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)������
#endif

#if SYSTEM_IWDG_ENABLE
	IWDG_HandleTypeDef IWDG_Handler; //�������Ź����
	//��ʼ���������Ź�
	//prer:��Ƶ��:IWDG_PRESCALER_4~IWDG_PRESCALER_256
	//rlr:�Զ���װ��ֵ,0~0XFFF.
	//ʱ�����(���):Tout=((4*2^prer)*rlr)/32 (ms)
	void sys_IWDG_ENABLE(void)
	{
		IWDG_Handler.Instance=IWDG;
		IWDG_Handler.Init.Prescaler=IWDG_PRESCALER_64;	//����IWDG��Ƶϵ��
		IWDG_Handler.Init.Reload=500;		//��װ��ֵ
		HAL_IWDG_Init(&IWDG_Handler);		//��ʼ��IWDG,Ĭ�ϻῪ���������Ź�	
	}
	//ι�������Ź�
	void IWDG_Feed(void)
	{   
		HAL_IWDG_Refresh(&IWDG_Handler); 	//ι��
	}
#endif
#if SYSTEM_MCO_PA8_OUT
void sys_MCO_Out_Enable(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	HAL_RCC_MCOConfig(RCC_MCO, RCC_MCO1SOURCE_HSE, RCC_MCODIV_1); 
	HAL_RCC_EnableCSS(); // ʹ��CSS���ܣ�����ʹ���ⲿ�����ڲ�ʱ��ԴΪ����
	GPIO_InitStruct.Pin = GPIO_PIN_8;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}
#endif

#if SYSTEM_RTC_ENABLE
/*__________RTC��ʼ��_____________*/
RTC_HandleTypeDef RTC_Handler;		//RTC���
_calendar_obj calendar;				//RTC�ṹ��
/*��ʼ��RTCʱ��,ͬʱ���ʱ���Ƿ�������
BKP->DR1���ڱ����Ƿ��һ�����õ�����*/
char sys_RTC_Enable(void)
{
	RTC_Handler.Instance=RTC; 
	RTC_Handler.Init.AsynchPrediv=32767; 	//ʱ����������(�д��۲�,���Ƿ�������?)����ֵ��32767	
	if(HAL_RTC_Init(&RTC_Handler)!=HAL_OK) return (char)ReturnErr;
	
	if(HAL_RTCEx_BKUPRead(&RTC_Handler,RTC_BKP_DR1)!=0X5050)//�Ƿ��һ������
	{
		RTC_Set(2049,10,1,17,7,0); //�������ں�ʱ�䣬2049��10��1�գ�17��07��0��
		RTC_Alarm_Set(2149,10,1,17,7,0); //����RTC�������ں�ʱ�䣬������ʱ���룬2149��10��1�գ�17��07��0��
		HAL_RTCEx_BKUPWrite(&RTC_Handler,RTC_BKP_DR1,0X5050);//����Ѿ���ʼ������
	 	//printf("FIRST TIME\n");
	}
	
	__HAL_RTC_ALARM_ENABLE_IT(&RTC_Handler,RTC_IT_SEC); 	//�������ж�
	__HAL_RTC_ALARM_ENABLE_IT(&RTC_Handler,RTC_IT_ALRA); 	//���������ж�
    HAL_NVIC_SetPriority(RTC_IRQn,2,0); 				//��ռ���ȼ�2
    HAL_NVIC_EnableIRQ(RTC_IRQn);	 
	
	RTC_Get();//����ʱ��
	return (char)ReturnOK;
}

/*RTC�ײ�������ʱ������
�˺����ᱻHAL_RTC_Init()����
hrtc:RTC���*/
void HAL_RTC_MspInit(RTC_HandleTypeDef* hrtc)
{
    RCC_OscInitTypeDef RCC_OscInitStruct;
    RCC_PeriphCLKInitTypeDef PeriphClkInitStruct;

    __HAL_RCC_PWR_CLK_ENABLE();	//ʹ�ܵ�Դʱ��PWR
	HAL_PWR_EnableBkUpAccess();	//ȡ����������д����
	__HAL_RCC_BKP_CLK_ENABLE();	//ʹ��BSPʱ��
	
	RCC_OscInitStruct.OscillatorType=RCC_OSCILLATORTYPE_LSE;//LSE����
    RCC_OscInitStruct.PLL.PLLState=RCC_PLL_NONE;
    RCC_OscInitStruct.LSEState=RCC_LSE_ON;                  //RTCʹ��LSE
    HAL_RCC_OscConfig(&RCC_OscInitStruct);

    PeriphClkInitStruct.PeriphClockSelection=RCC_PERIPHCLK_RTC;//����ΪRTC
    PeriphClkInitStruct.RTCClockSelection=RCC_RTCCLKSOURCE_LSE;//RTCʱ��ԴΪLSE
    HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct);
        
    __HAL_RCC_RTC_ENABLE();//RTCʱ��ʹ��
}
/*__________RTC����_____________*/

//RTC�����жϵĻص�����
void HAL_RTC_AlarmAEventCallback(RTC_HandleTypeDef *hrtc)
{
	if(hrtc->Instance == RTC)
	{
		//ptintf("RTC_AlarmIRQ!!!");
	}
	
}
//RTCʱ���ж�
//ÿ�봥��һ��  	 
void RTC_IRQHandler(void)
{		 
	if(__HAL_RTC_ALARM_GET_FLAG(&RTC_Handler,RTC_FLAG_SEC)!=RESET)  //���ж�
	{
	 	__HAL_RTC_ALARM_CLEAR_FLAG(&RTC_Handler,RTC_FLAG_SEC); 		//������ж�
		RTC_Get();				//����ʱ��   
		//LED1=!LED1;													//LED1��ת
	}		

	if(__HAL_RTC_ALARM_GET_FLAG(&RTC_Handler,RTC_FLAG_SEC)!=RESET)  //�����ж�
	{
		__HAL_RTC_ALARM_CLEAR_FLAG(&RTC_Handler,RTC_FLAG_ALRAF); 	//��������ж�   
		RTC_Get();				//����ʱ��   
		//printf("ALARM A!\r\n");
	}	
	__HAL_RTC_ALARM_CLEAR_FLAG(&RTC_Handler,RTC_FLAG_OW); 		//������  	    						 	   	 
}

//�ж��Ƿ������꺯��
//�·�   1  2  3  4  5  6  7  8  9  10 11 12
//����   31 29 31 30 31 30 31 31 30 31 30 31
//������ 31 28 31 30 31 30 31 31 30 31 30 31
//year:���
//����ֵ:������ǲ�������.1,��.0,����
u8 Is_Leap_Year(u16 year)
{			  
	if(year%4==0) //�����ܱ�4����
	{ 
		if(year%100==0) 
		{ 
			if(year%400==0)return 1;//�����00��β,��Ҫ�ܱ�400���� 	   
			else return 0;   
		}else return 1;   
	}else return 0;	
}	

//����ʱ��
//�������ʱ��ת��Ϊ����
//��1970��1��1��Ϊ��׼
//1970~2099��Ϊ�Ϸ����
//����ֵ:0,�ɹ�;����:�������.
//�·����ݱ�											 
u8 const table_week[12]={0,3,3,6,1,4,6,2,5,0,3,5}; //���������ݱ�	  
//ƽ����·����ڱ�
const u8 mon_table[12]={31,28,31,30,31,30,31,31,30,31,30,31};
//syear,smon,sday,hour,min,sec��������ʱ����
//����ֵ�����ý����0���ɹ���1��ʧ�ܡ�
u8 RTC_Set(u16 syear,u8 smon,u8 sday,u8 hour,u8 min,u8 sec)
{
	u16 t;
	u32 seccount=0;
//	RTC_DateTypeDef RTC_DateStructure;
//	RTC_TimeTypeDef RTC_TimeStructure;
	
	if(syear<1970||syear>2099)return 1;	   
	for(t=1970;t<syear;t++)	//��������ݵ��������
	{
		if(Is_Leap_Year(t))seccount+=31622400;//�����������
		else seccount+=31536000;			  //ƽ���������
	}
	smon-=1;
	for(t=0;t<smon;t++)	   //��ǰ���·ݵ����������
	{
		seccount+=(u32)mon_table[t]*86400;//�·����������
		if(Is_Leap_Year(syear)&&t==1)seccount+=86400;//����2�·�����һ���������	   
	}
	seccount+=(u32)(sday-1)*86400;//��ǰ�����ڵ���������� 
	seccount+=(u32)hour*3600;//Сʱ������
    seccount+=(u32)min*60;	 //����������
	seccount+=sec;//�������Ӽ���ȥ
	
//	RTC_DateStructure.Year=syear;
//	RTC_DateStructure.Month=smon;
//	RTC_DateStructure.Date=sday;
//	HAL_RTC_SetDate(&RTC_Handler,&RTC_DateStructure,RTC_FORMAT_BIN);
//	
//	RTC_TimeStructure.Hours=hour;
//	RTC_TimeStructure.Minutes=min;
//	RTC_TimeStructure.Seconds=sec;
//	HAL_RTC_SetTime(&RTC_Handler,&RTC_TimeStructure,RTC_FORMAT_BIN);
	

	//����ʱ��
    RCC->APB1ENR|=1<<28;//ʹ�ܵ�Դʱ��
    RCC->APB1ENR|=1<<27;//ʹ�ܱ���ʱ��
	PWR->CR|=1<<8;    //ȡ��������д����
	//���������Ǳ����!
	RTC->CRL|=1<<4;   //�������� 
	RTC->CNTL=seccount&0xffff;
	RTC->CNTH=seccount>>16;
	RTC->CRL&=~(1<<4);//���ø���
	while(!(RTC->CRL&(1<<5)));//�ȴ�RTC�Ĵ���������� 
	
	RTC_Get();//������֮�����һ������ 	
	return 0;	    
}
//��ʼ������		  
//��1970��1��1��Ϊ��׼
//1970~2099��Ϊ�Ϸ����
//syear,smon,sday,hour,min,sec�����ӵ�������ʱ����   
//����ֵ:0,�ɹ�;����:�������.
u8 RTC_Alarm_Set(u16 syear,u8 smon,u8 sday,u8 hour,u8 min,u8 sec)
{
	u16 t;
	u32 seccount=0;
	if(syear<1970||syear>2099)return 1;	   
	for(t=1970;t<syear;t++)	//��������ݵ��������
	{
		if(Is_Leap_Year(t))seccount+=31622400;//�����������
		else seccount+=31536000;			  //ƽ���������
	}
	smon-=1;
	for(t=0;t<smon;t++)	   //��ǰ���·ݵ����������
	{
		seccount+=(u32)mon_table[t]*86400;//�·����������
		if(Is_Leap_Year(syear)&&t==1)seccount+=86400;//����2�·�����һ���������	   
	}
	seccount+=(u32)(sday-1)*86400;//��ǰ�����ڵ���������� 
	seccount+=(u32)hour*3600;//Сʱ������
    seccount+=(u32)min*60;	 //����������
	seccount+=sec;//�������Ӽ���ȥ 			    
	//����ʱ��
    RCC->APB1ENR|=1<<28;//ʹ�ܵ�Դʱ��
    RCC->APB1ENR|=1<<27;//ʹ�ܱ���ʱ��
	PWR->CR|=1<<8;    //ȡ��������д����
	//���������Ǳ����!
	RTC->CRL|=1<<4;   //�������� 
	RTC->ALRL=seccount&0xffff;
	RTC->ALRH=seccount>>16;
	RTC->CRL&=~(1<<4);//���ø���
	while(!(RTC->CRL&(1<<5)));//�ȴ�RTC�Ĵ����������  
	return 0;	    
}
//�õ���ǰ��ʱ�䣬���������calendar�ṹ������
//����ֵ:0,�ɹ�;����:�������.
u8 RTC_Get(void)
{
	static u16 daycnt=0;
	u32 timecount=0; 
	u32 temp=0;
	u16 temp1=0;	  
 	timecount=RTC->CNTH;//�õ��������е�ֵ(������)
	timecount<<=16;
	timecount+=RTC->CNTL;			 

 	temp=timecount/86400;   //�õ�����(��������Ӧ��)
	if(daycnt!=temp)//����һ����
	{	  
		daycnt=temp;
		temp1=1970;	//��1970�꿪ʼ
		while(temp>=365)
		{				 
			if(Is_Leap_Year(temp1))//������
			{
				if(temp>=366)temp-=366;//�����������
				else break;  
			}
			else temp-=365;	  //ƽ�� 
			temp1++;  
		}   
		calendar.w_year=temp1;//�õ����
		temp1=0;
		while(temp>=28)//������һ����
		{
			if(Is_Leap_Year(calendar.w_year)&&temp1==1)//�����ǲ�������/2�·�
			{
				if(temp>=29)temp-=29;//�����������
				else break; 
			}
			else 
			{
				if(temp>=mon_table[temp1])temp-=mon_table[temp1];//ƽ��
				else break;
			}
			temp1++;  
		}
		calendar.w_month=temp1+1;	//�õ��·�
		calendar.w_date=temp+1;  	//�õ����� 
	}
	temp=timecount%86400;     		//�õ�������   	   
	calendar.hour=temp/3600;     	//Сʱ
	calendar.min=(temp%3600)/60; 	//����	
	calendar.sec=(temp%3600)%60; 	//����
	calendar.week=RTC_Get_Week(calendar.w_year,calendar.w_month,calendar.w_date);//��ȡ����   
	return 0;
}	 
//������������ڼ�
//��������:���빫�����ڵõ�����(ֻ����1901-2099��)
//year,month,day������������ 
//����ֵ�����ں�																						 
u8 RTC_Get_Week(u16 year,u8 month,u8 day)
{	
	u16 temp2;
	u8 yearH,yearL;
	
	yearH=year/100;	yearL=year%100; 
	// ���Ϊ21����,�������100  
	if (yearH>19)yearL+=100;
	// ����������ֻ��1900��֮���  
	temp2=yearL+yearL/4;
	temp2=temp2%7; 
	temp2=temp2+day+table_week[month-1];
	if (yearL%4==0&&month<3)temp2--;
	return(temp2%7);
}

#endif


#if SYSTEM_CRC_ENABLE
CRC_HandleTypeDef hcrc;
void sys_CRC_ENABLE(void)
{
	hcrc.Instance = CRC;
	HAL_CRC_Init(&hcrc);
}
void HAL_CRC_MspInit(CRC_HandleTypeDef* hcrc)
{
	if(hcrc->Instance==CRC)
	{
	/* ����ʱ��ʹ�� */
	__HAL_RCC_CRC_CLK_ENABLE();
	}
}
/* ˽�б��� ------------------------------------------------------------------*/
const uint32_t aDataBuffer[BUFFER_SIZE] =
  {
    0x00001021, 0x20423063, 0x408450a5, 0x60c670e7, 0x9129a14a, 0xb16bc18c,
    0xd1ade1ce, 0xf1ef1231, 0x32732252, 0x52b54294, 0x72f762d6, 0x93398318,
    0xa35ad3bd, 0xc39cf3ff, 0xe3de2462, 0x34430420, 0x64e674c7, 0x44a45485,
    0xa56ab54b, 0x85289509, 0xf5cfc5ac, 0xd58d3653, 0x26721611, 0x063076d7,
    0x569546b4, 0xb75ba77a, 0x97198738, 0xf7dfe7fe, 0xc7bc48c4, 0x58e56886,
    0x78a70840, 0x18612802, 0xc9ccd9ed, 0xe98ef9af, 0x89489969, 0xa90ab92b,
    0x4ad47ab7, 0x6a961a71, 0x0a503a33, 0x2a12dbfd, 0xfbbfeb9e, 0x9b798b58,
    0xbb3bab1a, 0x6ca67c87, 0x5cc52c22, 0x3c030c60, 0x1c41edae, 0xfd8fcdec,
    0xad2abd0b, 0x8d689d49, 0x7e976eb6, 0x5ed54ef4, 0x2e321e51, 0x0e70ff9f,
    0xefbedfdd, 0xcFFCbf1b, 0x9f598f78, 0x918881a9, 0xb1caa1eb, 0xd10cc12d,
    0xe16f1080, 0x00a130c2, 0x20e35004, 0x40257046, 0x83b99398, 0xa3fbb3da,
    0xc33dd31c, 0xe37ff35e, 0x129022f3, 0x32d24235, 0x52146277, 0x7256b5ea,
    0x95a88589, 0xf56ee54f, 0xd52cc50d, 0x34e224c3, 0x04817466, 0x64475424,
    0x4405a7db, 0xb7fa8799, 0xe75ff77e, 0xc71dd73c, 0x26d336f2, 0x069116b0,
    0x76764615, 0x5634d94c, 0xc96df90e, 0xe92f99c8, 0xb98aa9ab, 0x58444865,
    0x78066827, 0x18c008e1, 0x28a3cb7d, 0xdb5ceb3f, 0xfb1e8bf9, 0x9bd8abbb,
    0x4a755a54, 0x6a377a16, 0x0af11ad0, 0x2ab33a92, 0xed0fdd6c, 0xcd4dbdaa,
    0xad8b9de8, 0x8dc97c26, 0x5c644c45, 0x3ca22c83, 0x1ce00cc1, 0xef1fff3e,
    0xdf7caf9b, 0xbfba8fd9, 0x9ff86e17, 0x7e364e55, 0x2e933eb2, 0x0ed11ef0
  };
/* Expected CRC Value */
uint32_t uwExpectedCRCValue = 0x379E9F06;
#endif


#if SYSTEM_SUPPORT_OS

extern void xPortSysTickHandler(void);
//systick�жϷ�����
void SysTick_Handler(void)
{
	HAL_IncTick();
	
    if(xTaskGetSchedulerState()!=taskSCHEDULER_NOT_STARTED)//ϵͳ�Ѿ�����
    {
        xPortSysTickHandler();	
    }
}
#endif

/*__________��ʱ����_____________*/
/********************************
*��������ʱ�������壬�Զ������Ƿ�ʹ��RTOS����
********************************/
static u32 fac_us=0;							//us��ʱ������.
#if SYSTEM_SUPPORT_OS
	static u16 fac_ms=0;							//ms��ʱ������,��ucos��,����ÿ�����ĵ�ms��
#endif

#if SYSTEM_SUPPORT_OS		/*ʹ��FreeRTOS�����*/
//��ʼ���ӳٺ���
//SYSTICK��ʱ�ӹ̶�ΪAHBʱ�ӣ�������������SYSTICKʱ��Ƶ��ΪAHB/8
//����Ϊ�˼���FreeRTOS�����Խ�SYSTICK��ʱ��Ƶ�ʸ�ΪAHB��Ƶ�ʣ�
//SYSCLK:ϵͳʱ��Ƶ��
void delay_init(void)
{
	u32 reload;
	HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);//SysTickƵ��ΪHCLK
	fac_us=SystemCoreClock/1000000;				//�����Ƿ�ʹ��OS,fac_us����Ҫʹ��
	reload=SystemCoreClock/1000000;				//ÿ���ӵļ������� ��λΪM  
	reload*=1000000/configTICK_RATE_HZ;			//����configTICK_RATE_HZ�趨���ʱ��
												//reloadΪ24λ�Ĵ���,���ֵ:16777216,��72M��,Լ��0.233s����	
	fac_ms=1000/configTICK_RATE_HZ;				//����OS������ʱ�����ٵ�λ	   

	SysTick->CTRL|=SysTick_CTRL_TICKINT_Msk;   	//����SYSTICK�ж�
	SysTick->LOAD=reload; 						//ÿ1/configTICK_RATE_HZ���ж�һ��	
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk;   	//����SYSTICK    
}								    


//��ʱnus
//nus:Ҫ��ʱ��us��.	
//nus:0~204522252(���ֵ��2^32/fac_us@fac_us=168)	    								   
void delay_us(uint32_t nus)
{	
	u32 ticks;
	u32 told,tnow,tcnt=0;
	u32 reload=SysTick->LOAD;				//LOAD��ֵ	    	 
	ticks=nus*fac_us; 						//��Ҫ�Ľ����� 
	told=SysTick->VAL;        				//�ս���ʱ�ļ�����ֵ
	while(1)
	{
		tnow=SysTick->VAL;	
		if(tnow!=told)
		{	    
			if(tnow<told)tcnt+=told-tnow;	//����ע��һ��SYSTICK��һ���ݼ��ļ������Ϳ�����.
			else tcnt+=reload-tnow+told;	    
			told=tnow;
			if(tcnt>=ticks)break;			//ʱ�䳬��/����Ҫ�ӳٵ�ʱ��,���˳�.
		}  
	};										    
}  
//��ʱnms
//nms:Ҫ��ʱ��ms��
//nms:0~65535
void delay_ms(uint16_t nms)
{	
	if(xTaskGetSchedulerState()!=taskSCHEDULER_NOT_STARTED)//ϵͳ�Ѿ�����
	{		
		if(nms>=fac_ms)						//��ʱ��ʱ�����OS������ʱ������ 
		{ 
   			vTaskDelay(nms/fac_ms);	 		//FreeRTOS��ʱ������ǰ��������ʽ��ʱ
		}
		nms%=fac_ms;						//OS�Ѿ��޷��ṩ��ôС����ʱ��,������ͨ��ʽ��ʱ    
	}
	delay_us((u32)(nms*1000));				//��ͨ��ʽ��ʱ
}

//��ʱnms,���������������
//nms:Ҫ��ʱ��ms��
void delay_xms(uint16_t nms)
{
	u32 i;
	for(i=0;i<nms;i++) delay_us(1000);
}


#else						/*��ʹ��FreeRTOS�����*/

void delay_init(void)
{
    HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);//SysTickƵ��ΪHCLK
	fac_us=72;						//�����Ƿ�ʹ��OS,fac_us����Ҫʹ��
}
//��ʱnus
//nusΪҪ��ʱ��us��.	
//nus:0~190887435(���ֵ��2^32/fac_us@fac_us=22.5)	 
void delay_us(uint32_t nus)
{		
	u32 ticks;
	u32 told,tnow,tcnt=0;
	u32 reload=SysTick->LOAD;				//LOAD��ֵ	    	 
	ticks=nus*fac_us; 						//��Ҫ�Ľ����� 
	told=SysTick->VAL;        				//�ս���ʱ�ļ�����ֵ
	while(1)
	{
		tnow=SysTick->VAL;	
		if(tnow!=told)
		{	    
			if(tnow<told)tcnt+=told-tnow;	//����ע��һ��SYSTICK��һ���ݼ��ļ������Ϳ�����.
			else tcnt+=reload-tnow+told;	    
			told=tnow;
			if(tcnt>=ticks)break;			//ʱ�䳬��/����Ҫ�ӳٵ�ʱ��,���˳�.
		}  
	};
}

//��ʱnms
//nms:Ҫ��ʱ��ms��
void delay_ms(uint16_t nms)
{
	u32 i;
	for(i=0;i<nms;i++) delay_us(1000);
}
#endif

/*�ַ���ת���Σ�stm32��֧�ֱ�׼��atoi,�����Լ�ʵ��*/
int myatoi(const char *str)
{
	int s=0;
	uint8_t falg=0;
	
	while(*str==' ')
	{
		str++;
	}

	if(*str=='-'||*str=='+')
	{
		if(*str=='-')
		falg=1;
		str++;
	}

	while(*str>='0'&&*str<='9')
	{
		s=s*10+*str-'0';
		str++;
		if(s<0)
		{
			s=2147483647;
			break;
		}
	}
	return s*(falg?-1:1);
}




//THUMBָ�֧�ֻ������
//�������·���ʵ��ִ�л��ָ��WFI  
void WFI_SET(void)
{
	__ASM volatile("wfi");		  
}
//�ر������ж�
void INTX_DISABLE(void)
{		  
	__ASM volatile("cpsid i");
}
//���������ж�
void INTX_ENABLE(void)
{
	__ASM volatile("cpsie i");		  
}
//����ջ����ַ
//addr:ջ����ַ
__asm void MSR_MSP(uint32_t addr) 
{
    MSR MSP, r0 			//set Main Stack value
    BX r14
}


