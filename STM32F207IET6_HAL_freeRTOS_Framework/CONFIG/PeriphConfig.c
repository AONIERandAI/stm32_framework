#include "PeriphConfig.h"



/*_____________________________________\\\                               ///____________________________________________*
 *_________________________________________________�û�GPIO����_________________________________________________________*
 *_____________________________________///                               \\\____________________________________________*/
/*STEP 1:ȥ.h�ļ��ﶨ�嶼��ʲô����*/

/*STEP 2:����һ���ж��ٸ�����*/
#define devicesNum	3

/*STEP 3:����ÿ���������õ���IO�������ã�ֻ�Ƕ��壬�����Էֱ�ѡ���ʼ�����߲���ʼ����*/
/*����˵�������������������о���ѡ
	PIN��	GPIO_PIN_0~GPIO_PIN_15
	MODE��	����		GPIO_MODE_INPUT��GPIO_MODE_ANALOG							
			���		GPIO_MODE_OUTPUT_PP��GPIO_MODE_OUTPUT_OD��GPIO_MODE_AF_PP��GPIO_MODE_AF_OD		��AF��Ҫ�ã�����IO���������ʼ�����������
			�ⲿ�ж�	GPIO_MODE_IT_RISING��GPIO_MODE_IT_FALLING��GPIO_MODE_IT_RISING_FALLING  		ѡ��IT��ʾ����EXTI�����16��EXTI����PA0��PB0����EXTI0
	��������	GPIO_NOPULL��GPIO_PULLUP��GPIO_PULLDOWN
	��ת�ٶȣ�	GPIO_SPEED_FREQ_LOW��GPIO_SPEED_FREQ_MEDIUM��GPIO_SPEED_FREQ_HIGH��GPIO_SPEED_FREQ_VERY_HIGH
	GPIOx��		GPIOA~GPIOE��GPIOF��GPIOG��GPIOH��GPIOI
	Ĭ��״̬:	GPIO_PIN_SET��1u����GPIO_PIN_RESET��0u��
	EXTI���ȼ���0~15
	����EXTI��	TRUE����FALSE
*/
GPIO_Init_Struct TestLED_IO_Struct[] = 
{	/*	PIN				MODE			  ������		��ת�ٶ�		  	GPIOx 	  Ĭ��״̬     EXTI���ȼ�	����EXTI*/
	{{GPIO_PIN_7, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH},	GPIOA,  GPIO_PIN_RESET,		15,		  FALSE}
};
//���ڲ˵����ⲿ���밴��
GPIO_Init_Struct KEY_IO_Struct[] =
{	/*	PIN				MODE			  ������		��ת�ٶ�		  	GPIOx 	  Ĭ��״̬     EXTI���ȼ�	����EXTI*/
	{{GPIO_PIN_1, GPIO_MODE_IT_FALLING, GPIO_PULLUP, GPIO_SPEED_FREQ_HIGH},	GPIOA,  GPIO_PIN_SET,		2,		  TRUE},
	{{GPIO_PIN_2, GPIO_MODE_IT_FALLING, GPIO_PULLUP, GPIO_SPEED_FREQ_HIGH},	GPIOA,  GPIO_PIN_SET,		2,		  TRUE}
};

GPIO_Init_Struct LCD_IO_Struct[] = 
{	/*	PIN				MODE			  ������		��ת�ٶ�		  	GPIOx 	  Ĭ��״̬     EXTI���ȼ�	����EXTI*/
	{{GPIO_PIN_3, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH},	GPIOB,  GPIO_PIN_SET,		15,		  FALSE},
	{{GPIO_PIN_4, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH},	GPIOB,  GPIO_PIN_SET,		15,		  FALSE},
	{{GPIO_PIN_5, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH},	GPIOB,  GPIO_PIN_SET,		15,		  FALSE},
	{{GPIO_PIN_6, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH},	GPIOB,  GPIO_PIN_SET,		15,		  FALSE},
	{{GPIO_PIN_7, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH},	GPIOB,  GPIO_PIN_SET,		15,		  FALSE},
	
	{{GPIO_PIN_8, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH},	GPIOB,  GPIO_PIN_SET,		15,		  FALSE},
	{{GPIO_PIN_9, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH},	GPIOB,  GPIO_PIN_SET,		15,		  FALSE},
	{{GPIO_PIN_10, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH},	GPIOB,  GPIO_PIN_SET,		15,		  FALSE},
	{{GPIO_PIN_11, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH},	GPIOB,  GPIO_PIN_SET,		15,		  FALSE},
	{{GPIO_PIN_12, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH},	GPIOB,  GPIO_PIN_SET,		15,		  FALSE},
	{{GPIO_PIN_13, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH},	GPIOB,  GPIO_PIN_SET,		15,		  FALSE},
	{{GPIO_PIN_14, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH},	GPIOB,  GPIO_PIN_SET,		15,		  FALSE},
	{{GPIO_PIN_15, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH},	GPIOB,  GPIO_PIN_SET,		15,		  FALSE},
};

/*STEP 3.5:�������ȥ.h�ļ�����д�����ⲿ�жϵ�IO���жϱ�־λ*/
//��IOʹ���ⲿ�ж�ʱ����һ����־λ��¼�ж��Ƿ������ѳ�ʱ��Ĵ������ŵ��ж����棡
u8 key_Up_Interrupted 		= 	FALSE; 
u8 key_Down_Interrupted 	= 	FALSE;


/*STEP 3.75:ȥ.h�ļ��ﶨ��IO���Ƶĺ�͸ı����ģʽ�ĺ�*/


/*STEP4:��������������������"STEP 1:���嶼��ʲô����"�����˳������ÿ����������Ϣ*/
Devices_Init_Struct UserDevices[devicesNum] = 
{
	{	
		.deviceIO_Struct 	= 	TestLED_IO_Struct	,		//����IO���ýṹ��
		.deviceIndex 		= 	TestLED_Index		,		//����enum��ʽ����
		.deviceName 		= 	"TestLED"			,		//��������
		.device_IOnum 		= 	1							//�����ж��ٸ�IO��
	},
	{
		.deviceIO_Struct 	= 	KEY_IO_Struct	,
		.deviceIndex		= 	KEY_Index		,
		.deviceName 		= 	"Menu Key"		,
		.device_IOnum 		= 	2
	},
	{	
		.deviceIO_Struct 	= 	LCD_IO_Struct	,		//����IO���ýṹ��
		.deviceIndex 		= 	LCD_Index		,		//����enum��ʽ����
		.deviceName 		= 	"LCD"			,		//��������
		.device_IOnum 		= 	13						//�����ж��ٸ�IO��
	}
};


/*_____________________________________\\\                               ///____________________________________________*
 *_________________________________________________���²��ö�___________________________________________________________*
 *_____________________________________///                               \\\____________________________________________*/
/*����IO���ú���*/
void deviceIO_Init(Devices_Init_Struct* Devices , enum devicesIndex_enum device2Init)
{
	u8 dIndex,iIndex;
	dIndex = (u8)device2Init;
	for(iIndex = 0;iIndex < Devices[dIndex].device_IOnum;iIndex++)	//����ĳһ������������IO
	{
		//ʱ��
		if(Devices[dIndex].deviceIO_Struct[iIndex].GPIOx == GPIOA)
			__HAL_RCC_GPIOA_CLK_ENABLE();
		else if(Devices[dIndex].deviceIO_Struct[iIndex].GPIOx == GPIOB)
			__HAL_RCC_GPIOB_CLK_ENABLE();
		else if(Devices[dIndex].deviceIO_Struct[iIndex].GPIOx == GPIOC)
			__HAL_RCC_GPIOC_CLK_ENABLE();
		else if(Devices[dIndex].deviceIO_Struct[iIndex].GPIOx == GPIOD)
			__HAL_RCC_GPIOD_CLK_ENABLE();
		else if(Devices[dIndex].deviceIO_Struct[iIndex].GPIOx == GPIOE)
			__HAL_RCC_GPIOE_CLK_ENABLE();
		
		//����IO����
		HAL_GPIO_Init(Devices[dIndex].deviceIO_Struct[iIndex].GPIOx, \
					 &Devices[dIndex].deviceIO_Struct[iIndex].GPIO_Initure);
		
		//���ʹ��EXTI�������ж��ߺ����ȼ�
		if(   (Devices[dIndex].deviceIO_Struct[iIndex].GPIO_Initure.Mode == GPIO_MODE_IT_RISING) \
			||(Devices[dIndex].deviceIO_Struct[iIndex].GPIO_Initure.Mode == GPIO_MODE_IT_FALLING) \
			||(Devices[dIndex].deviceIO_Struct[iIndex].GPIO_Initure.Mode == GPIO_MODE_IT_RISING_FALLING) )
		{		
			if(Devices[dIndex].deviceIO_Struct[iIndex].GPIO_Initure.Pin == GPIO_PIN_0)
			{	
				HAL_NVIC_SetPriority(EXTI0_IRQn, Devices[dIndex].deviceIO_Struct[iIndex].PreemptPriority, 0);
				if(Devices[dIndex].deviceIO_Struct[iIndex].isEnableExit)  HAL_NVIC_EnableIRQ(EXTI0_IRQn); else HAL_NVIC_DisableIRQ(EXTI0_IRQn);
			}else if(Devices[dIndex].deviceIO_Struct[iIndex].GPIO_Initure.Pin == GPIO_PIN_1)
			{
				HAL_NVIC_SetPriority(EXTI1_IRQn, Devices[dIndex].deviceIO_Struct[iIndex].PreemptPriority, 0);
				if(Devices[dIndex].deviceIO_Struct[iIndex].isEnableExit)  HAL_NVIC_EnableIRQ(EXTI1_IRQn); else HAL_NVIC_DisableIRQ(EXTI1_IRQn);
			}else if(Devices[dIndex].deviceIO_Struct[iIndex].GPIO_Initure.Pin == GPIO_PIN_2)
			{
				HAL_NVIC_SetPriority(EXTI2_IRQn, Devices[dIndex].deviceIO_Struct[iIndex].PreemptPriority, 0);
				if(Devices[dIndex].deviceIO_Struct[iIndex].isEnableExit)  HAL_NVIC_EnableIRQ(EXTI2_IRQn); else HAL_NVIC_DisableIRQ(EXTI2_IRQn);
			}else if(Devices[dIndex].deviceIO_Struct[iIndex].GPIO_Initure.Pin == GPIO_PIN_3)
			{
				HAL_NVIC_SetPriority(EXTI3_IRQn, Devices[dIndex].deviceIO_Struct[iIndex].PreemptPriority, 0);
				if(Devices[dIndex].deviceIO_Struct[iIndex].isEnableExit)  HAL_NVIC_EnableIRQ(EXTI3_IRQn); else HAL_NVIC_DisableIRQ(EXTI3_IRQn);
			}else if(Devices[dIndex].deviceIO_Struct[iIndex].GPIO_Initure.Pin == GPIO_PIN_4)
			{
				HAL_NVIC_SetPriority(EXTI4_IRQn, Devices[dIndex].deviceIO_Struct[iIndex].PreemptPriority, 0);
				if(Devices[dIndex].deviceIO_Struct[iIndex].isEnableExit)  HAL_NVIC_EnableIRQ(EXTI4_IRQn); else HAL_NVIC_DisableIRQ(EXTI4_IRQn);
			}else if( (Devices[dIndex].deviceIO_Struct[iIndex].GPIO_Initure.Pin == GPIO_PIN_5) \
					||(Devices[dIndex].deviceIO_Struct[iIndex].GPIO_Initure.Pin == GPIO_PIN_6) \
					||(Devices[dIndex].deviceIO_Struct[iIndex].GPIO_Initure.Pin == GPIO_PIN_7) \
					||(Devices[dIndex].deviceIO_Struct[iIndex].GPIO_Initure.Pin == GPIO_PIN_8) \
					||(Devices[dIndex].deviceIO_Struct[iIndex].GPIO_Initure.Pin == GPIO_PIN_9) )
			{
				HAL_NVIC_SetPriority(EXTI9_5_IRQn, Devices[dIndex].deviceIO_Struct[iIndex].PreemptPriority, 0);
				if(Devices[dIndex].deviceIO_Struct[iIndex].isEnableExit)  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn); else HAL_NVIC_DisableIRQ(EXTI9_5_IRQn);
			}else if( (Devices[dIndex].deviceIO_Struct[iIndex].GPIO_Initure.Pin == GPIO_PIN_10) \
					||(Devices[dIndex].deviceIO_Struct[iIndex].GPIO_Initure.Pin == GPIO_PIN_11) \
					||(Devices[dIndex].deviceIO_Struct[iIndex].GPIO_Initure.Pin == GPIO_PIN_12) \
					||(Devices[dIndex].deviceIO_Struct[iIndex].GPIO_Initure.Pin == GPIO_PIN_13) \
					||(Devices[dIndex].deviceIO_Struct[iIndex].GPIO_Initure.Pin == GPIO_PIN_14) \
					||(Devices[dIndex].deviceIO_Struct[iIndex].GPIO_Initure.Pin == GPIO_PIN_15) )
			{
				HAL_NVIC_SetPriority(EXTI15_10_IRQn, Devices[dIndex].deviceIO_Struct[iIndex].PreemptPriority, 0);
				if(Devices[dIndex].deviceIO_Struct[iIndex].isEnableExit)  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn); else HAL_NVIC_DisableIRQ(EXTI15_10_IRQn);
			}
		}
		
		//����Ĭ��IO״̬
		HAL_GPIO_WritePin(  Devices[dIndex].deviceIO_Struct[iIndex].GPIOx, \
							Devices[dIndex].deviceIO_Struct[iIndex].GPIO_Initure.Pin, \
							Devices[dIndex].deviceIO_Struct[iIndex].defaultState);
	}
}

void Devices_Init(Devices_Init_Struct* Devices , enum devicesIndex_enum device2Init)
{
	static u8 dIndex;
	if(device2Init == ALL_Index)
	{
		for(dIndex = 0;dIndex < devicesNum;dIndex++)	//������������
		{
			deviceIO_Init(Devices,(enum devicesIndex_enum)dIndex);
		}
	}else{
		deviceIO_Init(Devices,device2Init);				////�ض�������ʼ��
	}
}




/*�жϷ�����*/
void EXTI0_IRQHandler(void){ HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);}
void EXTI1_IRQHandler(void){ HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_1);}
void EXTI2_IRQHandler(void){ HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_2);}
void EXTI3_IRQHandler(void){ HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_3);}
void EXTI4_IRQHandler(void){ HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_4);}
void EXTI9_5_IRQHandler(void)		//��Ҫ�Լ��жϵģ�
{ 
//	if(PAin(5))		//��ǰ����PA5Ϊ�ⲿ�ж�ʱ
//		HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_5);
//	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_6);
//	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_7);
//	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_8);
//	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_9);
}
void EXTI15_10_IRQHandler(void)		//��Ҫ�Լ��жϵģ�
{ 
//	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_10);
//	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_11);
//	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_12);
//	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_13);
//	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_14);
//	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_15);
}


/*�ⲿ�жϻص�����*/
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    switch(GPIO_Pin)
    {
        case GPIO_PIN_0:
			/*���ʹ��RTOS�򲻳�ʼ��PA0���жϣ�ʹ�������ʹ��PA0���ⲿ�ж�*/
			#if SYSTEM_StdbyWKUP_ENABLE
				if(Check_WKUP())
				{
					Sys_Enter_Standby();//�������ģʽ
				}
			#endif
            break;
		case GPIO_PIN_1:
			/*������GPIOA������1Ϊ�˵��������ϰ���ʱ*/
			key_Up_Interrupted = TRUE;
			break;
        case GPIO_PIN_2:
			/*������GPIOA������2Ϊ�˵��������°���ʱ*/
			key_Down_Interrupted = TRUE;
            break;
        case GPIO_PIN_3:
            break;
        case GPIO_PIN_4:
            break;
    }
}

/*_________________________________________������������������������PeriphConfigCore.h��������_________________________________________________________*/

/*___________________________________________�û�SPI1��2����_______________________________________________*/
#if ((SYSTEM_SPI1_ENABLE)||(SYSTEM_SPI2_ENABLE))


/*��ʼ��SPI1��SS����ѡ������	Ĭ��PA4���û��ɸ�*/
void sys_SPI1_SS_io_Init(void)
{
	GPIO_InitTypeDef GPIO_Initure;
	GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;
    GPIO_Initure.Pull=GPIO_PULLUP;
    GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;
    
	/*��Ҫ��������*/
	__HAL_RCC_GPIOA_CLK_ENABLE();
    GPIO_Initure.Pin=GPIO_PIN_4;
    HAL_GPIO_Init(GPIOA,&GPIO_Initure);
    
	SPI1_CS = IO_High;			                	//SPI1Ĭ�ϲ�ѡ��
}
/*��ʼ��SPI2��SS����ѡ������	Ĭ��PB12���û��ɸ�*/
void sys_SPI2_SS_io_Init(void)
{
	GPIO_InitTypeDef GPIO_Initure;
	GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;
    GPIO_Initure.Pull=GPIO_PULLUP;
    GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;
    
	/*��Ҫ��������*/
	__HAL_RCC_GPIOB_CLK_ENABLE();
    GPIO_Initure.Pin=GPIO_PIN_12;
    HAL_GPIO_Init(GPIOB,&GPIO_Initure);
    
	SPI2_CS = IO_High;			                	//SPI2Ĭ�ϲ�ѡ��
}


//SPI�ײ�������ʱ��ʹ�ܣ���������
//�˺����ᱻHAL_SPI_Init()����
//hspi:SPI���
void HAL_SPI_MspInit(SPI_HandleTypeDef *hspi)
{
    GPIO_InitTypeDef GPIO_Initure;
    /*
	SPI1->CS	SPI1->CLK	SPI1->MISO	SPI1->MOSI 	������������ 	SPI2->CS	SPI2->CLK	SPI2->MISO	SPI2->MOSI
	PA4			PA5			PA6			PA7					PB12		PB13		PB14		PB15
	*/
	if(hspi->Instance == SPI1)
	{
		__HAL_RCC_GPIOA_CLK_ENABLE();       //ʹ��GPIOAʱ��
		__HAL_RCC_SPI1_CLK_ENABLE();        //ʹ��SPI1ʱ��
		//__HAL_RCC_AFIO_CLK_ENABLE();
		
		//PB13,14,15
		GPIO_Initure.Pin=GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
		GPIO_Initure.Mode=GPIO_MODE_AF_PP;              //�������������MISO����Ϊ��������û����
		GPIO_Initure.Pull=GPIO_PULLUP;                  //����
		GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;        //����   
		GPIO_Initure.Alternate=GPIO_AF5_SPI1;
		HAL_GPIO_Init(GPIOA,&GPIO_Initure);
	}else if(hspi->Instance == SPI2)
	{
		__HAL_RCC_GPIOB_CLK_ENABLE();       //ʹ��GPIOBʱ��
		__HAL_RCC_SPI2_CLK_ENABLE();        //ʹ��SPI2ʱ��
		//__HAL_RCC_AFIO_CLK_ENABLE();
		
		//PB13,14,15
		GPIO_Initure.Pin=GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
		GPIO_Initure.Mode=GPIO_MODE_AF_PP;              //�������������MISO����Ϊ��������û����
		GPIO_Initure.Pull=GPIO_PULLUP;                  //����
		GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;        //���� 
		GPIO_Initure.Alternate=GPIO_AF5_SPI1;
		HAL_GPIO_Init(GPIOB,&GPIO_Initure);
	}

}


#if SYSTEM_SPI1_ENABLE

SPI_HandleTypeDef SPI1_Handler;  //SPI1���

void sys_SPI1_ENABLE(void)
{
    SPI1_Handler.Instance=SPI1;                         //SPI1
    SPI1_Handler.Init.Mode=SPI_MODE_MASTER;             //����SPI����ģʽ������Ϊ��ģʽ
    SPI1_Handler.Init.Direction=SPI_DIRECTION_2LINES;   //����SPI�������˫�������ģʽ:SPI����Ϊ˫��ģʽ
    SPI1_Handler.Init.DataSize=SPI_DATASIZE_8BIT;       //����SPI�����ݴ�С:SPI���ͽ���8λ֡�ṹ
    
	SPI1_Handler.Init.CLKPolarity=SPI_POLARITY_HIGH;    //����ͬ��ʱ�ӵĿ���״̬Ϊ�ߵ�ƽ
    SPI1_Handler.Init.CLKPhase=SPI_PHASE_2EDGE;         //����ͬ��ʱ�ӵĵڶ��������أ��������½������ݱ�����
    
	SPI1_Handler.Init.NSS=SPI_NSS_SOFT;                 //NSS�ź���Ӳ����NSS�ܽţ����������ʹ��SSIλ������:�ڲ�NSS�ź���SSIλ����
    SPI1_Handler.Init.BaudRatePrescaler=SPI_BAUDRATEPRESCALER_256;//���岨����Ԥ��Ƶ��ֵ:������Ԥ��ƵֵΪ256
    SPI1_Handler.Init.FirstBit=SPI_FIRSTBIT_MSB;        //ָ�����ݴ����MSBλ����LSBλ��ʼ:���ݴ����MSBλ��ʼ
    SPI1_Handler.Init.TIMode=SPI_TIMODE_DISABLE;        //�ر�TIģʽ
    SPI1_Handler.Init.CRCCalculation=SPI_CRCCALCULATION_DISABLE;//�ر�Ӳ��CRCУ��
    SPI1_Handler.Init.CRCPolynomial=7;                  //CRCֵ����Ķ���ʽ
    HAL_SPI_Init(&SPI1_Handler);//��ʼ��
    
	sys_SPI1_SS_io_Init();
	
    __HAL_SPI_ENABLE(&SPI1_Handler);                    //ʹ��SPI1
	
    //SPI1_ReadWriteByte(0Xff);                           //��������
}

//SPI�ٶ����ú���
//SPI1�ٶ�=APB2/��Ƶϵ��
/*������ѡ��
SPI_BAUDRATEPRESCALER_2 SPI_BAUDRATEPRESCALER_4 SPI_BAUDRATEPRESCALER_8 SPI_BAUDRATEPRESCALER_16 
SPI_BAUDRATEPRESCALER_32 SPI_BAUDRATEPRESCALER_64 SPI_BAUDRATEPRESCALER_128 SPI_BAUDRATEPRESCALER_256
*/
void SPI1_SetSpeed(u8 SPI_BaudRatePrescaler)
{
    assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_BaudRatePrescaler));//�ж���Ч��
    __HAL_SPI_DISABLE(&SPI1_Handler);            //�ر�SPI
    SPI1_Handler.Instance->CR1&=0XFFC7;          //λ3-5���㣬�������ò�����
    SPI1_Handler.Instance->CR1|=SPI_BaudRatePrescaler;//����SPI�ٶ�
    __HAL_SPI_ENABLE(&SPI1_Handler);             //ʹ��SPI
    
}

//SPI1 ��дһ���ֽ�
//TxData:Ҫд����ֽ�
//����ֵ:��ȡ�����ֽ�
u8 SPI1_ReadWriteByte_8Byte(u8 TxData)
{
    u8 Rxdata;
	SPI1_CS = IO_Low;
    HAL_SPI_TransmitReceive(&SPI1_Handler,&TxData,&Rxdata,1, 100);
	SPI1_CS = IO_High;	
 	return Rxdata;          		    //�����յ�������		
}

//����һ������2�ֽڵ�u8*ָ��
u8 SPI1_ReadWriteByte_16Byte(u8* TxData)
{
    u8 Rxdata;
	SPI1_CS = IO_Low;
    HAL_SPI_TransmitReceive(&SPI1_Handler,TxData,&Rxdata, 2, 100);
	SPI1_CS = IO_High;	
 	return Rxdata;          		    //�����յ�������		
}

u8 SPI1_WriteByte_8Byte(u8 TxData)
{
	u8 state;
	SPI1_CS = IO_Low;
	state = (u8)(HAL_SPI_Transmit(&SPI1_Handler, &TxData, 1, 100));	
	SPI1_CS = IO_High;
	return state;
}

//����һ������2�ֽڵ�u8*ָ��
u8 SPI1_WriteByte_16Byte(u8* TxData)
{
	u8 state;
	SPI1_CS = IO_Low;
	state = (u8)(HAL_SPI_Transmit(&SPI1_Handler, TxData, 2, 100));	
	SPI1_CS = IO_High;
	return state;
}

#endif

#if SYSTEM_SPI2_ENABLE

SPI_HandleTypeDef SPI2_Handler;  //SPI2���

void sys_SPI2_ENABLE(void)
{
    SPI2_Handler.Instance=SPI2;                         //SPI2
    SPI2_Handler.Init.Mode=SPI_MODE_MASTER;             //����SPI����ģʽ������Ϊ��ģʽ
    SPI2_Handler.Init.Direction=SPI_DIRECTION_2LINES;   //����SPI�������˫�������ģʽ:SPI����Ϊ˫��ģʽ
    SPI2_Handler.Init.DataSize=SPI_DATASIZE_8BIT;       //����SPI�����ݴ�С:SPI���ͽ���8λ֡�ṹ
    
	SPI2_Handler.Init.CLKPolarity=SPI_POLARITY_HIGH;    //����ͬ��ʱ�ӵĿ���״̬Ϊ�ߵ�ƽ
    SPI2_Handler.Init.CLKPhase=SPI_PHASE_2EDGE;         //����ͬ��ʱ�ӵĵڶ��������أ��������½������ݱ�����
    
	SPI2_Handler.Init.NSS=SPI_NSS_SOFT;                 //NSS�ź���Ӳ����NSS�ܽţ����������ʹ��SSIλ������:�ڲ�NSS�ź���SSIλ����
    SPI2_Handler.Init.BaudRatePrescaler=SPI_BAUDRATEPRESCALER_256;//���岨����Ԥ��Ƶ��ֵ:������Ԥ��ƵֵΪ256
    SPI2_Handler.Init.FirstBit=SPI_FIRSTBIT_MSB;        //ָ�����ݴ����MSBλ����LSBλ��ʼ:���ݴ����MSBλ��ʼ
    SPI2_Handler.Init.TIMode=SPI_TIMODE_DISABLE;        //�ر�TIģʽ
    SPI2_Handler.Init.CRCCalculation=SPI_CRCCALCULATION_DISABLE;//�ر�Ӳ��CRCУ��
    SPI2_Handler.Init.CRCPolynomial=7;                  //CRCֵ����Ķ���ʽ
    HAL_SPI_Init(&SPI2_Handler);//��ʼ��
    
	sys_SPI2_SS_io_Init();
	
    __HAL_SPI_ENABLE(&SPI2_Handler);                    //ʹ��SPI2
	
    //SPI2_ReadWriteByte(0Xff);                           //��������
}

//SPI�ٶ����ú���
//SPI2�ٶ�=APB1/��Ƶϵ��
/*������ѡ��
SPI_BAUDRATEPRESCALER_2 SPI_BAUDRATEPRESCALER_4 SPI_BAUDRATEPRESCALER_8 SPI_BAUDRATEPRESCALER_16 
SPI_BAUDRATEPRESCALER_32 SPI_BAUDRATEPRESCALER_64 SPI_BAUDRATEPRESCALER_128 SPI_BAUDRATEPRESCALER_256
*/
void SPI2_SetSpeed(u8 SPI_BaudRatePrescaler)
{
    assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_BaudRatePrescaler));//�ж���Ч��
    __HAL_SPI_DISABLE(&SPI2_Handler);            //�ر�SPI
    SPI2_Handler.Instance->CR1&=0XFFC7;          //λ3-5���㣬�������ò�����
    SPI2_Handler.Instance->CR1|=SPI_BaudRatePrescaler;//����SPI�ٶ�
    __HAL_SPI_ENABLE(&SPI2_Handler);             //ʹ��SPI
    
}

//SPI2 ��дһ���ֽ�
//TxData:Ҫд����ֽ�
//����ֵ:��ȡ�����ֽ�
u8 SPI2_ReadWriteByte(u8 TxData)
{
    u8 Rxdata;
    HAL_SPI_TransmitReceive(&SPI2_Handler,&TxData,&Rxdata,1, 100); 
 	return Rxdata;          		    //�����յ�������		
}
#endif

#endif

/*________________________________________�û���ʱ��2����_________________________________________________________*/
#if STSTEM_TIM2_ENABLE
TIM_HandleTypeDef TIM2_Handler;

#if (STSTEM_TIM2_asPWMorCap == 0)
	TIM_OC_InitTypeDef 	TIM2_CH1Handler,TIM2_CH2Handler,TIM2_CH3Handler,TIM2_CH4Handler;
#elif (STSTEM_TIM2_asPWMorCap == 1)
	TIM_IC_InitTypeDef TIM2_CHxConfig;
#elif (STSTEM_TIM2_asPWMorCap == 3)
	TIM_Encoder_InitTypeDef sEncoderConfig;
#endif

void sys_TIM2_ENABLE(void)
{
	TIM_ClockConfigTypeDef sClockSourceConfig = {0};
	TIM_MasterConfigTypeDef sMasterConfig = {0};
	
	TIM2_Handler.Instance = 		TIM2;                          	//ͨ�ö�ʱ��2
    TIM2_Handler.Init.Prescaler=	(60-1);                 	   	//��Ƶϵ��
    TIM2_Handler.Init.CounterMode=	TIM_COUNTERMODE_UP;    			//���ϼ�����
    TIM2_Handler.Init.Period=		tim2arr;                       	//�Զ�װ��ֵ
    TIM2_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;			//ʱ�ӷ�Ƶ����
	TIM2_Handler.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
    HAL_TIM_Base_Init(&TIM2_Handler);
	
	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	HAL_TIM_ConfigClockSource(&TIM2_Handler, &sClockSourceConfig);
	
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	HAL_TIMEx_MasterConfigSynchronization(&TIM2_Handler, &sMasterConfig);
	
	#if (STSTEM_TIM2_asPWMorCap == 0)
		/*��ΪPWM*/
		HAL_TIM_PWM_Init(&TIM2_Handler);       //��ʼ��PWM
		if((STSTEM_TIM2PWM_CHANNEL_ENABLE) & B0000_0001)
		{
			TIM2_CH1Handler.OCMode=TIM_OCMODE_PWM1; 		//ģʽѡ��PWM1
			TIM2_CH1Handler.Pulse=tim2arr/2;            	//���ñȽ�ֵ,��ֵ����ȷ��ռ�ձȣ�Ĭ�ϱȽ�ֵΪ�Զ���װ��ֵ��һ��,��ռ�ձ�Ϊ50%
			TIM2_CH1Handler.OCPolarity=TIM_OCPOLARITY_LOW; 	//����Ƚϼ���Ϊ�� 
			HAL_TIM_PWM_ConfigChannel(&TIM2_Handler,&TIM2_CH1Handler,TIM_CHANNEL_1);//����TIM2ͨ��1
			__HAL_TIM_ENABLE_OCxPRELOAD(&TIM2_Handler, TIM_CHANNEL_1);
			HAL_TIM_PWM_Start(&TIM2_Handler,TIM_CHANNEL_1);	//����PWMͨ��1
		}
		if((STSTEM_TIM2PWM_CHANNEL_ENABLE) & B0000_0010)
		{
			TIM2_CH2Handler.OCMode=TIM_OCMODE_PWM1;
			TIM2_CH2Handler.Pulse=tim2arr/2;
			TIM2_CH2Handler.OCPolarity=TIM_OCPOLARITY_LOW;
			HAL_TIM_PWM_ConfigChannel(&TIM2_Handler,&TIM2_CH2Handler,TIM_CHANNEL_2);
			__HAL_TIM_ENABLE_OCxPRELOAD(&TIM2_Handler, TIM_CHANNEL_2);
			HAL_TIM_PWM_Start(&TIM2_Handler,TIM_CHANNEL_2);
		}
		if((STSTEM_TIM2PWM_CHANNEL_ENABLE) & B0000_0100)
		{
			TIM2_CH3Handler.OCMode=TIM_OCMODE_PWM1;
			TIM2_CH3Handler.Pulse=tim2arr/2;
			TIM2_CH3Handler.OCPolarity=TIM_OCPOLARITY_LOW;
			HAL_TIM_PWM_ConfigChannel(&TIM2_Handler,&TIM2_CH3Handler,TIM_CHANNEL_3);
			__HAL_TIM_ENABLE_OCxPRELOAD(&TIM2_Handler, TIM_CHANNEL_3);
			HAL_TIM_PWM_Start(&TIM2_Handler,TIM_CHANNEL_3);
		}
		if((STSTEM_TIM2PWM_CHANNEL_ENABLE) & B0000_1000)
		{
			TIM2_CH4Handler.OCMode=TIM_OCMODE_PWM1;
			TIM2_CH4Handler.Pulse=tim2arr/2;
			TIM2_CH4Handler.OCPolarity=TIM_OCPOLARITY_LOW;
			HAL_TIM_PWM_ConfigChannel(&TIM2_Handler,&TIM2_CH4Handler,TIM_CHANNEL_4);
			__HAL_TIM_ENABLE_OCxPRELOAD(&TIM2_Handler, TIM_CHANNEL_4);
			HAL_TIM_PWM_Start(&TIM2_Handler,TIM_CHANNEL_4);
		}
	#elif (STSTEM_TIM2_asPWMorCap == 1)
		/*��ΪCap*/
		TIM2_Handler.Init.Period=0XFFFF;       //�Զ�װ��ֵ
		HAL_TIM_IC_Init(&TIM2_Handler);			//��ʼ�����벶��ʱ������
		
		if(STSTEM_TIM2_Cap_trigV == 1)
			TIM2_CHxConfig.ICPolarity=TIM_ICPOLARITY_RISING;    //�����ز���
		else if(STSTEM_TIM2_Cap_trigV == 0)
			TIM2_CHxConfig.ICPolarity=TIM_ICPOLARITY_FALLING;    //�½��ز���
		else if(STSTEM_TIM2_Cap_trigV == 2)
			TIM2_CHxConfig.ICPolarity=TIM_ICPOLARITY_BOTHEDGE;    //˫���ز���
		
		TIM2_CHxConfig.ICSelection=TIM_ICSELECTION_DIRECTTI;//ӳ�䵽TI1��
		TIM2_CHxConfig.ICPrescaler=TIM_ICPSC_DIV1;          //���������Ƶ������Ƶ
		TIM2_CHxConfig.ICFilter=0;                          //���������˲��������˲�
		
		switch(STSTEM_TIM2_Cap_Channel)
		{
			case B0000_0001:				//ѡ��ͨ��1��Ϊ���벶��
				HAL_TIM_IC_ConfigChannel(&TIM2_Handler,&TIM2_CHxConfig,TIM_CHANNEL_1);//����TIM2ͨ��1
				HAL_TIM_IC_Start_IT(&TIM2_Handler,TIM_CHANNEL_1);   //����TIM2�Ĳ���ͨ��1�����ҿ��������ж�
				break;
			case B0000_0010:				//ѡ��ͨ��2��Ϊ���벶��
				HAL_TIM_IC_ConfigChannel(&TIM2_Handler,&TIM2_CHxConfig,TIM_CHANNEL_2);
				HAL_TIM_IC_Start_IT(&TIM2_Handler,TIM_CHANNEL_2);
				break;
			case B0000_0100:				//ѡ��ͨ��3��Ϊ���벶��
				HAL_TIM_IC_ConfigChannel(&TIM2_Handler,&TIM2_CHxConfig,TIM_CHANNEL_3);
				HAL_TIM_IC_Start_IT(&TIM2_Handler,TIM_CHANNEL_3);
				break;
			case B0000_1000:				//ѡ��ͨ��4��Ϊ���벶��
				HAL_TIM_IC_ConfigChannel(&TIM2_Handler,&TIM2_CHxConfig,TIM_CHANNEL_4);
				HAL_TIM_IC_Start_IT(&TIM2_Handler,TIM_CHANNEL_4);
				break;
			default:break;
		}
		__HAL_TIM_ENABLE_IT(&TIM2_Handler,TIM_IT_UPDATE);   //ʹ�ܸ����ж�
	#elif (STSTEM_TIM2_asPWMorCap == 3)
		TIM2_Handler.Init.Prescaler=	0;
		TIM2_Handler.Init.Period=		0xFFFF;

	  sEncoderConfig.EncoderMode        = TIM_ENCODERMODE_TI12;
	  sEncoderConfig.IC1Polarity        = TIM_ICPOLARITY_RISING;
	  sEncoderConfig.IC1Selection       = TIM_ICSELECTION_DIRECTTI;
	  sEncoderConfig.IC1Prescaler       = TIM_ICPSC_DIV1;
	  sEncoderConfig.IC1Filter          = 0;

	  sEncoderConfig.IC2Polarity        = TIM_ICPOLARITY_RISING;
	  sEncoderConfig.IC2Selection       = TIM_ICSELECTION_DIRECTTI;
	  sEncoderConfig.IC2Prescaler       = TIM_ICPSC_DIV1;
	  sEncoderConfig.IC2Filter          = 0;
	  __HAL_TIM_SET_COUNTER(&TIM2_Handler,0);
	  
	  HAL_TIM_Encoder_Init(&TIM2_Handler, &sEncoderConfig);
	  
	__HAL_TIM_CLEAR_IT(&TIM2_Handler, TIM_IT_UPDATE);  // ��������жϱ�־λ
	__HAL_TIM_URS_ENABLE(&TIM2_Handler);               // ���������������Ų��������ж�
	__HAL_TIM_ENABLE_IT(&TIM2_Handler,TIM_IT_UPDATE);  // ʹ�ܸ����ж�

	HAL_NVIC_SetPriority(TIM2_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(TIM2_IRQn);

	HAL_TIM_Encoder_Start(&TIM2_Handler, TIM_CHANNEL_ALL);
	
	#endif
	
	#if (STSTEM_TIM2_asPWMorCap == 2)
		#if (!STSTEM_TIM2_TI_ENABLE)
			HAL_TIM_Base_Start(&TIM2_Handler);	//����IT�Ŀ�����ʱ��
		#else
			HAL_TIM_Base_Start_IT(&TIM2_Handler);//��IT�Ŀ�����ʱ��
		#endif
	#endif
}

//��ʱ��2�жϷ�����
void TIM2_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&TIM2_Handler);
}

#if (STSTEM_TIM2_asPWMorCap == 3)				//���ʹ����������
void HAL_TIM_Encoder_MspInit(TIM_HandleTypeDef* htim_base)
{
  GPIO_InitTypeDef GPIO_InitStruct;
  if(htim_base->Instance==TIM2)
  {
    /* ������ʱ������ʱ��ʹ�� */
    __HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_TIM2_CLK_ENABLE();
    //__HAL_AFIO_REMAP_TIM2_ENABLE();
	  
	/*PA15 PB3*/
	  
    /* ��ʱ��ͨ��1��������IO��ʼ�� */
    GPIO_InitStruct.Pin = GPIO_PIN_15;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull=GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF1_TIM2;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* ��ʱ��ͨ��2��������IO��ʼ�� */
    GPIO_InitStruct.Pin = GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF1_TIM2;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
  }
}

/*�ڶ�ʱ������жϻص�����������мӼ�����*/
int32_t EncoderOverflowCount = 0;//��ʱ���������

/*��ȡһ�α������ĵ�ǰ����ֵ�����ڱ�ʾ��������ǰ�ľ���λ��*/
int32_t peek_TIM2_Encoder_Value(void)
{
	return ( int32_t )__HAL_TIM_GET_COUNTER(&TIM2_Handler);
}

/*��ȡһ����������������ת�ٶ� ��λ ת/�룬�������ŵ�TIM4��10ms��ʱ�ж���*/
float peek_TIM2_Encoder_Speed(void)
{
	float Speed = 0;
	int32_t CaptureNumber = 0;     // ���벶����
	
	/* �ٶȶ�ʱ���������ӿڲ���ֵ */
	CaptureNumber = ( int32_t )__HAL_TIM_GET_COUNTER(&TIM2_Handler) + EncoderOverflowCount*65536;
	
	Speed = ((float)CaptureNumber / (float)PPR);
	Speed *= 100.0;	//������10ms����һ�Σ����ﻻ���1��
	
	/* ��������,�ȴ���һ�����¼�¼���� */
	EncoderOverflowCount = 0;
	__HAL_TIM_SET_COUNTER(&TIM2_Handler,0);
	
	return Speed;
}

#endif

#if (STSTEM_TIM2_asPWMorCap == 1)				//���ʹ��Cap����

//��ʱ��2��IC���ܵײ�������ʱ��ʹ�ܣ���������
//�˺����ᱻHAL_TIM_IC_Init()����
//htim:��ʱ�����
void HAL_TIM_IC_MspInit(TIM_HandleTypeDef *htim)
{
	GPIO_InitTypeDef GPIO_Initure;
	if(htim->Instance==TIM2)
	{
		__HAL_RCC_TIM2_CLK_ENABLE();            //ʹ��TIM2ʱ��
		//__HAL_AFIO_REMAP_TIM2_ENABLE();			/*TIM2ͨ��������ȫ��ӳ��ʹ�� (CH1/ETR/PA15, CH2/PB3, CH3/PB10, CH4/PB11)*/
		
		if(STSTEM_TIM2_Cap_trigV == 1)				//�����ز���
			GPIO_Initure.Pull=GPIO_PULLDOWN;        //����
		else if(STSTEM_TIM2_Cap_trigV == 0)			//�½��ز���
			GPIO_Initure.Pull=GPIO_PULLUP;        	//����
		else if(STSTEM_TIM2_Cap_trigV == 2)			//˫���ز���
			GPIO_Initure.Pull=GPIO_NOPULL;        	//����
		
		GPIO_Initure.Mode=GPIO_MODE_AF_PP; 			//��������
		GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;	//����
		GPIO_Initure.Alternate = GPIO_AF1_TIM2;
		
		switch(STSTEM_TIM2_Cap_Channel)
		{
			case B0000_0001:					//ѡ��ͨ��1��Ϊ���벶��
				__HAL_RCC_GPIOA_CLK_ENABLE();	//����GPIOAʱ��
				GPIO_Initure.Pin=GPIO_PIN_15;            //PA15
				HAL_GPIO_Init(GPIOA,&GPIO_Initure);
				break;
			case B0000_0010:					//ѡ��ͨ��2��Ϊ���벶��
				__HAL_RCC_GPIOB_CLK_ENABLE();
				GPIO_Initure.Pin=GPIO_PIN_3;            //PB3
				HAL_GPIO_Init(GPIOB,&GPIO_Initure);
				break;
			case B0000_0100:					//ѡ��ͨ��3��Ϊ���벶��
				__HAL_RCC_GPIOB_CLK_ENABLE();
				GPIO_Initure.Pin=GPIO_PIN_10;            //PB10
				HAL_GPIO_Init(GPIOB,&GPIO_Initure);
				break;
			case B0000_1000:					//ѡ��ͨ��4��Ϊ���벶��
				__HAL_RCC_GPIOB_CLK_ENABLE();
				GPIO_Initure.Pin=GPIO_PIN_11;            //PB11
				HAL_GPIO_Init(GPIOB,&GPIO_Initure);
				break;
			default:break;
		}
		
		HAL_NVIC_SetPriority(TIM2_IRQn,2,0);    //�����ж����ȼ�����ռ���ȼ�2�������ȼ�0
		HAL_NVIC_EnableIRQ(TIM2_IRQn);          //����ITM2�ж�ͨ��  
	}
}

//����״̬
//[7]:0,û�гɹ��Ĳ���;1,�ɹ�����һ��.
//[6]:0,��û���񵽵͵�ƽ;1,�Ѿ����񵽵͵�ƽ��.
//[5:0]:����͵�ƽ������Ĵ���
u8  TIM2CHx_CAPTURE_STA=0;							//���벶��״̬		    				
u16	TIM2CHx_CAPTURE_VAL;							//���벶��ֵ

/*��ȡ���һ��TIM2���벶�������ʱ�䣬��λ ���룬�������õĲ����ؽ��У�������ʱ��ص��ô˺���*/
float Peek_TIM2_Cap_Val(void)
{
	u8 Tim2overFlowTimes = 0;
	float temp = 0;
	if(TIM2CHx_CAPTURE_STA&0X80)        			//�ɹ�������һ�θߵ�ƽ
	{
		Tim2overFlowTimes = TIM2CHx_CAPTURE_STA & 0X3F;
		temp = (float)Tim2overFlowTimes;
		temp *= 65536.0;		 	    			//���ʱ���ܺ�
		temp += (float)TIM2CHx_CAPTURE_VAL;      	//���ϵ�ǰ����ֵ�õ��ܵĸߵ�ƽʱ��
		TIM2CHx_CAPTURE_STA = 0;          			//������һ�β���
		temp /= 1000.0;								//��λ ����
		return temp;
	}else{
		return 0.0;
	}
}

//��ʱ�����벶���жϴ���ص��������ú�����HAL_TIM_IRQHandler�лᱻ����
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)//�����жϷ���ʱִ��
{
	if(htim==(&TIM2_Handler))
	{
			switch(STSTEM_TIM2_Cap_Channel)
			{
				case B0000_0001: //ͨ��1
					Process_TIM2_IC_CallBack_Channel_1();
					break;
				case B0000_0010: //ͨ��2
					Process_TIM2_IC_CallBack_Channel_2();
					break;
				case B0000_0100: //ͨ��3
					Process_TIM2_IC_CallBack_Channel_3();
					break;
				case B0000_1000: //ͨ��4
					Process_TIM2_IC_CallBack_Channel_4();
					break;
				default:break;
			}
	}	
}

void Process_TIM2_IC_CallBack_Channel_1(void)
{
	if((STSTEM_TIM2_Cap_trigV == 1)||(STSTEM_TIM2_Cap_trigV == 0))				//�����ػ����½��ز���
	{
		if((TIM2CHx_CAPTURE_STA&0X80)==0)				//��δ�ɹ�����
		{
			if(TIM2CHx_CAPTURE_STA&0X40)				//����һ���½��� 		
			{	  			
				TIM2CHx_CAPTURE_STA|=0X80;				//��ǳɹ�����һ�θߵ�ƽ����
				TIM2CHx_CAPTURE_VAL=HAL_TIM_ReadCapturedValue(&TIM2_Handler,TIM_CHANNEL_1);//��ȡ��ǰ�Ĳ���ֵ.
				TIM_RESET_CAPTUREPOLARITY(&TIM2_Handler,TIM_CHANNEL_1);   //һ��Ҫ�����ԭ�������ã���
				if(STSTEM_TIM2_Cap_trigV == 1)	//�������Ϊ�����ز���
				{
					TIM_SET_CAPTUREPOLARITY(&TIM2_Handler,TIM_CHANNEL_1,TIM_ICPOLARITY_RISING);//����TIM2ͨ��1�����ز���
				}else{
					TIM_SET_CAPTUREPOLARITY(&TIM2_Handler,TIM_CHANNEL_1,TIM_ICPOLARITY_FALLING);//��ʱ��2ͨ��1����Ϊ�½��ز���
				}
				
			}else  										//��δ��ʼ,��һ�β���������
			{
				TIM2CHx_CAPTURE_STA=0;					//���
				TIM2CHx_CAPTURE_VAL=0;
				TIM2CHx_CAPTURE_STA|=0X40;				//��ǲ�����������
				__HAL_TIM_DISABLE(&TIM2_Handler);      	//�رն�ʱ��2
				__HAL_TIM_SET_COUNTER(&TIM2_Handler,0);
				TIM_RESET_CAPTUREPOLARITY(&TIM2_Handler,TIM_CHANNEL_1);   //һ��Ҫ�����ԭ�������ã���
				
				if(STSTEM_TIM2_Cap_trigV == 1)	//�������Ϊ�����ز���
				{
					TIM_SET_CAPTUREPOLARITY(&TIM2_Handler,TIM_CHANNEL_1,TIM_ICPOLARITY_FALLING);//��ʱ��2ͨ��1����Ϊ�½��ز���
				}else{
					TIM_SET_CAPTUREPOLARITY(&TIM2_Handler,TIM_CHANNEL_1,TIM_ICPOLARITY_RISING);//��ʱ��2ͨ��1����Ϊ�����ز���
				}
				
				__HAL_TIM_ENABLE(&TIM2_Handler);		//ʹ�ܶ�ʱ��2
			}		    
		}
	}else if(STSTEM_TIM2_Cap_trigV == 2)				//˫�ز���
	{
		if((TIM2CHx_CAPTURE_STA&0X80)==0)				//��δ�ɹ�����
		{
			if(TIM2CHx_CAPTURE_STA&0X40)				//�Ѿ�����һ����
			{
				TIM2CHx_CAPTURE_STA|=0X80;				//��ǳɹ�����һ������
				TIM2CHx_CAPTURE_VAL=HAL_TIM_ReadCapturedValue(&TIM2_Handler,TIM_CHANNEL_1);//��ȡ��ǰ�Ĳ���ֵ
			}else										//��δ����һ����
			{
				TIM2CHx_CAPTURE_STA=0;					//���
				TIM2CHx_CAPTURE_VAL=0;
				TIM2CHx_CAPTURE_STA|=0X40;				//��ǲ�����һ����
				__HAL_TIM_DISABLE(&TIM2_Handler);      	//�رն�ʱ��2
				__HAL_TIM_SET_COUNTER(&TIM2_Handler,0);
				__HAL_TIM_ENABLE(&TIM2_Handler);		//ʹ�ܶ�ʱ��2
			}
		}
	}
}

void Process_TIM2_IC_CallBack_Channel_2(void)
{
	if((STSTEM_TIM2_Cap_trigV == 1)||(STSTEM_TIM2_Cap_trigV == 0))
	{
		if((TIM2CHx_CAPTURE_STA&0X80)==0)
		{
			if(TIM2CHx_CAPTURE_STA&0X40)	
			{	  			
				TIM2CHx_CAPTURE_STA|=0X80;	
				TIM2CHx_CAPTURE_VAL=HAL_TIM_ReadCapturedValue(&TIM2_Handler,TIM_CHANNEL_2);
				TIM_RESET_CAPTUREPOLARITY(&TIM2_Handler,TIM_CHANNEL_2); 
				if(STSTEM_TIM2_Cap_trigV == 1)
				{
					TIM_SET_CAPTUREPOLARITY(&TIM2_Handler,TIM_CHANNEL_2,TIM_ICPOLARITY_RISING);
				}else{
					TIM_SET_CAPTUREPOLARITY(&TIM2_Handler,TIM_CHANNEL_2,TIM_ICPOLARITY_FALLING);
				}
				
			}else 
			{
				TIM2CHx_CAPTURE_STA=0;
				TIM2CHx_CAPTURE_VAL=0;
				TIM2CHx_CAPTURE_STA|=0X40;
				__HAL_TIM_DISABLE(&TIM2_Handler);
				__HAL_TIM_SET_COUNTER(&TIM2_Handler,0);
				TIM_RESET_CAPTUREPOLARITY(&TIM2_Handler,TIM_CHANNEL_2); 
				
				if(STSTEM_TIM2_Cap_trigV == 1)	
				{
					TIM_SET_CAPTUREPOLARITY(&TIM2_Handler,TIM_CHANNEL_2,TIM_ICPOLARITY_FALLING);
				}else{
					TIM_SET_CAPTUREPOLARITY(&TIM2_Handler,TIM_CHANNEL_2,TIM_ICPOLARITY_RISING);
				}
				
				__HAL_TIM_ENABLE(&TIM2_Handler);
			}		    
		}
	}else if(STSTEM_TIM2_Cap_trigV == 2)				//˫�ز���
	{
		if((TIM2CHx_CAPTURE_STA&0X80)==0)				//��δ�ɹ�����
		{
			if(TIM2CHx_CAPTURE_STA&0X40)				//�Ѿ�����һ����
			{
				TIM2CHx_CAPTURE_STA|=0X80;				//��ǳɹ�����һ������
				TIM2CHx_CAPTURE_VAL=HAL_TIM_ReadCapturedValue(&TIM2_Handler,TIM_CHANNEL_2);//��ȡ��ǰ�Ĳ���ֵ
			}else										//��δ����һ����
			{
				TIM2CHx_CAPTURE_STA=0;					//���
				TIM2CHx_CAPTURE_VAL=0;
				TIM2CHx_CAPTURE_STA|=0X40;				//��ǲ�����һ����
				__HAL_TIM_DISABLE(&TIM2_Handler);      	//�رն�ʱ��2
				__HAL_TIM_SET_COUNTER(&TIM2_Handler,0);
				__HAL_TIM_ENABLE(&TIM2_Handler);		//ʹ�ܶ�ʱ��2
			}
		}
	}
}

void Process_TIM2_IC_CallBack_Channel_3(void)
{
	if((STSTEM_TIM2_Cap_trigV == 1)||(STSTEM_TIM2_Cap_trigV == 0))
	{
		if((TIM2CHx_CAPTURE_STA&0X80)==0)
		{
			if(TIM2CHx_CAPTURE_STA&0X40)	
			{	  			
				TIM2CHx_CAPTURE_STA|=0X80;	
				TIM2CHx_CAPTURE_VAL=HAL_TIM_ReadCapturedValue(&TIM2_Handler,TIM_CHANNEL_3);
				TIM_RESET_CAPTUREPOLARITY(&TIM2_Handler,TIM_CHANNEL_3); 
				if(STSTEM_TIM2_Cap_trigV == 1)
				{
					TIM_SET_CAPTUREPOLARITY(&TIM2_Handler,TIM_CHANNEL_3,TIM_ICPOLARITY_RISING);
				}else{
					TIM_SET_CAPTUREPOLARITY(&TIM2_Handler,TIM_CHANNEL_3,TIM_ICPOLARITY_FALLING);
				}
				
			}else 
			{
				TIM2CHx_CAPTURE_STA=0;
				TIM2CHx_CAPTURE_VAL=0;
				TIM2CHx_CAPTURE_STA|=0X40;
				__HAL_TIM_DISABLE(&TIM2_Handler);
				__HAL_TIM_SET_COUNTER(&TIM2_Handler,0);
				TIM_RESET_CAPTUREPOLARITY(&TIM2_Handler,TIM_CHANNEL_3); 
				
				if(STSTEM_TIM2_Cap_trigV == 1)	
				{
					TIM_SET_CAPTUREPOLARITY(&TIM2_Handler,TIM_CHANNEL_3,TIM_ICPOLARITY_FALLING);
				}else{
					TIM_SET_CAPTUREPOLARITY(&TIM2_Handler,TIM_CHANNEL_3,TIM_ICPOLARITY_RISING);
				}
				
				__HAL_TIM_ENABLE(&TIM2_Handler);
			}		    
		}
	}else if(STSTEM_TIM2_Cap_trigV == 2)				//˫�ز���
	{
		if((TIM2CHx_CAPTURE_STA&0X80)==0)				//��δ�ɹ�����
		{
			if(TIM2CHx_CAPTURE_STA&0X40)				//�Ѿ�����һ����
			{
				TIM2CHx_CAPTURE_STA|=0X80;				//��ǳɹ�����һ������
				TIM2CHx_CAPTURE_VAL=HAL_TIM_ReadCapturedValue(&TIM2_Handler,TIM_CHANNEL_3);//��ȡ��ǰ�Ĳ���ֵ
			}else										//��δ����һ����
			{
				TIM2CHx_CAPTURE_STA=0;					//���
				TIM2CHx_CAPTURE_VAL=0;
				TIM2CHx_CAPTURE_STA|=0X40;				//��ǲ�����һ����
				__HAL_TIM_DISABLE(&TIM2_Handler);      	//�رն�ʱ��2
				__HAL_TIM_SET_COUNTER(&TIM2_Handler,0);
				__HAL_TIM_ENABLE(&TIM2_Handler);		//ʹ�ܶ�ʱ��2
			}
		}
	}
}
void Process_TIM2_IC_CallBack_Channel_4(void)
{
	if((STSTEM_TIM2_Cap_trigV == 1)||(STSTEM_TIM2_Cap_trigV == 0))
	{
		if((TIM2CHx_CAPTURE_STA&0X80)==0)
		{
			if(TIM2CHx_CAPTURE_STA&0X40)	
			{	  			
				TIM2CHx_CAPTURE_STA|=0X80;	
				TIM2CHx_CAPTURE_VAL=HAL_TIM_ReadCapturedValue(&TIM2_Handler,TIM_CHANNEL_4);
				TIM_RESET_CAPTUREPOLARITY(&TIM2_Handler,TIM_CHANNEL_4); 
				if(STSTEM_TIM2_Cap_trigV == 1)
				{
					TIM_SET_CAPTUREPOLARITY(&TIM2_Handler,TIM_CHANNEL_4,TIM_ICPOLARITY_RISING);
				}else{
					TIM_SET_CAPTUREPOLARITY(&TIM2_Handler,TIM_CHANNEL_4,TIM_ICPOLARITY_FALLING);
				}
				
			}else 
			{
				TIM2CHx_CAPTURE_STA=0;
				TIM2CHx_CAPTURE_VAL=0;
				TIM2CHx_CAPTURE_STA|=0X40;
				__HAL_TIM_DISABLE(&TIM2_Handler);
				__HAL_TIM_SET_COUNTER(&TIM2_Handler,0);
				TIM_RESET_CAPTUREPOLARITY(&TIM2_Handler,TIM_CHANNEL_4); 
				
				if(STSTEM_TIM2_Cap_trigV == 1)	
				{
					TIM_SET_CAPTUREPOLARITY(&TIM2_Handler,TIM_CHANNEL_4,TIM_ICPOLARITY_FALLING);
				}else{
					TIM_SET_CAPTUREPOLARITY(&TIM2_Handler,TIM_CHANNEL_4,TIM_ICPOLARITY_RISING);
				}
				
				__HAL_TIM_ENABLE(&TIM2_Handler);
			}		    
		}
	}else if(STSTEM_TIM2_Cap_trigV == 2)				//˫�ز���
	{
		if((TIM2CHx_CAPTURE_STA&0X80)==0)				//��δ�ɹ�����
		{
			if(TIM2CHx_CAPTURE_STA&0X40)				//�Ѿ�����һ����
			{
				TIM2CHx_CAPTURE_STA|=0X80;				//��ǳɹ�����һ������
				TIM2CHx_CAPTURE_VAL=HAL_TIM_ReadCapturedValue(&TIM2_Handler,TIM_CHANNEL_4);//��ȡ��ǰ�Ĳ���ֵ
			}else										//��δ����һ����
			{
				TIM2CHx_CAPTURE_STA=0;					//���
				TIM2CHx_CAPTURE_VAL=0;
				TIM2CHx_CAPTURE_STA|=0X40;				//��ǲ�����һ����
				__HAL_TIM_DISABLE(&TIM2_Handler);      	//�رն�ʱ��2
				__HAL_TIM_SET_COUNTER(&TIM2_Handler,0);
				__HAL_TIM_ENABLE(&TIM2_Handler);		//ʹ�ܶ�ʱ��2
			}
		}
	}
}


#endif
#if (STSTEM_TIM2_asPWMorCap == 0)				//���ʹ��PWM
	//����TIM2ͨ����ռ�ձ�
	//percent:ռ�ձȰٷ���
	void TIM2_set_Channel_Pulse(u8 channel,float percent)
	{
		float compare;
		if(percent < 0) percent = 0;
		if(percent > 100) percent = 100.0;
		percent /= 100.0;
		compare = ((float)tim2arr) * percent;
		switch(channel)
		{
			case TIM2PWM_Channel_1: TIM2->CCR1=(u32)compare;break;
			case TIM2PWM_Channel_2: TIM2->CCR2=(u32)compare;break;
			case TIM2PWM_Channel_3: TIM2->CCR3=(u32)compare;break;
			case TIM2PWM_Channel_4: TIM2->CCR4=(u32)compare;break;
			default:break;
		}
	}
#endif

#endif


/*________________________________________�û���ʱ��6����_________________________________________________________*/

#if STSTEM_TIM6_ENABLE

TIM_HandleTypeDef TIM6_Handler;
void sys_TIM6_ENABLE(void)
{
	TIM_MasterConfigTypeDef sMasterConfig = {0};
	
	TIM6_Handler.Instance=TIM6;                          		//������ʱ��6
    TIM6_Handler.Init.Prescaler = (60-1);                     	//��Ƶϵ��
    TIM6_Handler.Init.CounterMode=TIM_COUNTERMODE_UP;    		//���ϼ�����
    TIM6_Handler.Init.Period = tim6arr;                        	//�Զ�װ��ֵ
    TIM6_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;		//ʱ�ӷ�Ƶ����
	TIM6_Handler.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
    HAL_TIM_Base_Init(&TIM6_Handler);
	
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	HAL_TIMEx_MasterConfigSynchronization(&TIM6_Handler, &sMasterConfig);
	
    HAL_TIM_Base_Start_IT(&TIM6_Handler); //ʹ�ܶ�ʱ��6�Ͷ�ʱ��6�����жϣ�TIM_IT_UPDATE 
}


//��ʱ��6�жϷ�����
void TIM6_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&TIM6_Handler);
}

#endif

/*________________________________________�û���ʱ��7����_________________________________________________________*/
#if STSTEM_TIM7_ENABLE

TIM_HandleTypeDef TIM7_Handler;
void sys_TIM7_ENABLE(void)
{
	TIM_MasterConfigTypeDef sMasterConfig = {0};
	
	TIM7_Handler.Instance=TIM7;                          		//������ʱ��7
    TIM7_Handler.Init.Prescaler = (60-1);                     	//��Ƶϵ��
    TIM7_Handler.Init.CounterMode=TIM_COUNTERMODE_UP;    		//���ϼ�����
    TIM7_Handler.Init.Period = tim7arr;                        	//�Զ�װ��ֵ
    TIM7_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;		//ʱ�ӷ�Ƶ����
	TIM7_Handler.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
    HAL_TIM_Base_Init(&TIM7_Handler);
	
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	HAL_TIMEx_MasterConfigSynchronization(&TIM7_Handler, &sMasterConfig);
    
    HAL_TIM_Base_Start_IT(&TIM7_Handler); //ʹ�ܶ�ʱ��6�Ͷ�ʱ��7�����жϣ�TIM_IT_UPDATE 
}


//��ʱ��7�жϷ�����
void TIM7_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&TIM7_Handler);
}

#endif




/*__________________________________�͹���StandbyMode__________________________________________*/
#if SYSTEM_StdbyWKUP_ENABLE

void sys_StdbyWKUP_ENABLE(void)
{
	#if !SYSTEM_SUPPORT_OS
    GPIO_InitTypeDef GPIO_Initure;
    __HAL_RCC_GPIOA_CLK_ENABLE();			//����GPIOAʱ��
	
    GPIO_Initure.Pin=GPIO_PIN_0;            //PA0
    GPIO_Initure.Mode=GPIO_MODE_IT_RISING;  //�ж�,������
    GPIO_Initure.Pull=GPIO_PULLDOWN;        //����
    GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;//����
    HAL_GPIO_Init(GPIOA,&GPIO_Initure);
	
	/*PA0�ⲿ�жϺ����� HAL_GPIO_EXTI_Callback ��*/
    
//    //����Ƿ�����������
//    if(Check_WKUP()==0)
//    {
//        Sys_Enter_Standby();//���ǿ������������ģʽ
//    }

    HAL_NVIC_SetPriority(EXTI0_IRQn,2,0);
    HAL_NVIC_EnableIRQ(EXTI0_IRQn);
	
	#else
	
    GPIO_InitTypeDef GPIO_Initure;
    __HAL_RCC_GPIOA_CLK_ENABLE();			//����GPIOAʱ��
	
    GPIO_Initure.Pin=GPIO_PIN_0;            //PA0
    GPIO_Initure.Mode=GPIO_MODE_INPUT;  //������
    GPIO_Initure.Pull=GPIO_PULLDOWN;        //����
    GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;//����
    HAL_GPIO_Init(GPIOA,&GPIO_Initure);
	
	#endif
}


//ϵͳ�������ģʽ
void Sys_Enter_Standby(void)
{
	while(WKUP_KD == 1){;} //WKUP�����ɿ����������ʱ1s������׼���ʹ���ػ�ǰ������
	HAL_Delay(500);
	while(WKUP_KD == 1){;}
	HAL_Delay(500);
    //__HAL_RCC_APB2_FORCE_RESET();       //��λ����IO�� 
	__HAL_RCC_PWR_CLK_ENABLE();         //ʹ��PWRʱ��
    __HAL_PWR_CLEAR_FLAG(PWR_FLAG_WU);                  //���Wake_UP��־
    HAL_PWR_EnableWakeUpPin(PWR_WAKEUP_PIN1);           //����WKUP���ڻ���
    HAL_PWR_EnterSTANDBYMode();                         //�������ģʽ     
}

//���WKUP�ŵ��ź�
//����ֵ1:��������3s����
//      0:����Ĵ���	
u8 Check_WKUP(void) 
{
	u8 t=0;	//��¼���µ�ʱ��
	while(1)
	{
		if(WKUP_KD)
		{
			t++;			//�Ѿ������� 
			HAL_Delay(30);
			if(t>=100)		//���³���3����
			{
				return 1; 	//����3s������
			}
		}else 
		{ 
			return 0; //���²���3��
		}
	}
}

void sys_CheckWKUP_4RTOS(void)
{
	static u8 t=0;	//��¼���µ�ʱ��
	if(WKUP_KD)
	{
		t++;			//�Ѿ������� 
		HAL_Delay(30);
		if(t>=100)		//���³���3����
		{
			Sys_Enter_Standby();//����3s�����ˣ��������ģʽ
		}
	}else 
	{} //���²���3��
}

#endif



/*________________________________________�û�ADC1����_________________________________________________________*/
#if SYSTEM_ADC1_ENABLE


void ADC_RegularChannelConfig(ADC_HandleTypeDef *AdcHandle, uint32_t Channel, uint32_t Rank, uint32_t SamplingTime)
{
    ADC_ChannelConfTypeDef ADC1_ChanConf;      
    ADC1_ChanConf.Channel      = Channel;                      		//ͨ��
    ADC1_ChanConf.Rank         = Rank;                          	//�ڼ�������
    ADC1_ChanConf.SamplingTime = SamplingTime;                  	//����ʱ�� 
    HAL_ADC_ConfigChannel(AdcHandle,&ADC1_ChanConf);              	//ͨ������
}

ADC_HandleTypeDef ADC1_Handler;		//ADC���
void sys_ADC1_ENABLE(void)
{
	u8 i;
	i = 1;
	
	#if SYSTEM_ADC1_useScan
		/*�ȳ�ʼ��DMA���ٳ�ʼ��ADC*/
		ADC_DMA_Cfg();
		//HAL_ADC_Start_DMA(&ADC1_Handler, (uint32_t*)&adValue,12);	//��ʼDMA��ָ���������飬���һ������Ϊ���ݳ��ȣ�Ҫ�����ٴΣ�
	#endif
	
    ADC1_Handler.Instance=ADC1;
	ADC1_Handler.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2; //Ҳ��֪����ʱ���Ƕ���
    ADC1_Handler.Init.DataAlign=ADC_DATAALIGN_RIGHT;             //�Ҷ���
	ADC1_Handler.Init.Resolution = ADC_RESOLUTION_12B;
	
	if(!SYSTEM_ADC1_useScan)
	{
		ADC1_Handler.Init.ScanConvMode=DISABLE;                  //��ɨ��ģʽ
		ADC1_Handler.Init.ContinuousConvMode=DISABLE,
		ADC1_Handler.Init.DMAContinuousRequests = DISABLE;
		ADC1_Handler.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
	}else{
		ADC1_Handler.Init.ScanConvMode=ENABLE;					 //ɨ��ģʽ
		
		if(SYSTEM_ADC1_useCircular)
		{	ADC1_Handler.Init.ContinuousConvMode=ENABLE;               //����ת�� ����������ת�������ͨ����ȫ��ͨ�������Զ�������һ��ת����������������һ��ת��һ�Σ�
			ADC1_Handler.Init.DMAContinuousRequests = ENABLE;
			ADC1_Handler.Init.EOCSelection = ADC_EOC_SEQ_CONV;
		}
		else{
			ADC1_Handler.Init.ContinuousConvMode=DISABLE;
			ADC1_Handler.Init.DMAContinuousRequests = DISABLE;
			ADC1_Handler.Init.EOCSelection = ADC_EOC_SEQ_CONV;
		}
	}
	
	if(SYSTEM_ADC1_useScan)
		ADC1_Handler.Init.NbrOfConversion=SYSTEM_ADC1_useChanlNum;   	//n��ת���ڹ���������
	else ADC1_Handler.Init.NbrOfConversion=1;							//ֻת����������1
	
    ADC1_Handler.Init.DiscontinuousConvMode=DISABLE;             //��ֹ����������ģʽ
    ADC1_Handler.Init.NbrOfDiscConversion=0;                     //����������ͨ����Ϊ0
	ADC1_Handler.Init.ExternalTrigConv=ADC_SOFTWARE_START;  	 //�������
	ADC1_Handler.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
    HAL_ADC_Init(&ADC1_Handler);                                 //��ʼ�� 
	
	//HAL_ADCEx_Calibration_Start(&ADC1_Handler);					 //У׼ADC
	
	if(SYSTEM_ADC1_useScan)		//�������ɨ�裬�������ͨ�������뵽��������
	{               
		if((SYSTEM_ADC1_useChanl) & B1in16) 	ADC_RegularChannelConfig(&ADC1_Handler, ADC_CHANNEL_0, (uint32_t)(i++), ADC_SAMPLETIME_56CYCLES);
		if((SYSTEM_ADC1_useChanl) & B2in16) 	ADC_RegularChannelConfig(&ADC1_Handler, ADC_CHANNEL_1, (uint32_t)(i++), ADC_SAMPLETIME_56CYCLES);
		if((SYSTEM_ADC1_useChanl) & B3in16) 	ADC_RegularChannelConfig(&ADC1_Handler, ADC_CHANNEL_2, (uint32_t)(i++), ADC_SAMPLETIME_56CYCLES);
		if((SYSTEM_ADC1_useChanl) & B4in16) 	ADC_RegularChannelConfig(&ADC1_Handler, ADC_CHANNEL_3, (uint32_t)(i++), ADC_SAMPLETIME_56CYCLES);
		if((SYSTEM_ADC1_useChanl) & B5in16) 	ADC_RegularChannelConfig(&ADC1_Handler, ADC_CHANNEL_4, (uint32_t)(i++), ADC_SAMPLETIME_56CYCLES);
		if((SYSTEM_ADC1_useChanl) & B6in16) 	ADC_RegularChannelConfig(&ADC1_Handler, ADC_CHANNEL_5, (uint32_t)(i++), ADC_SAMPLETIME_56CYCLES);
		if((SYSTEM_ADC1_useChanl) & B7in16) 	ADC_RegularChannelConfig(&ADC1_Handler, ADC_CHANNEL_6, (uint32_t)(i++), ADC_SAMPLETIME_56CYCLES);
		if((SYSTEM_ADC1_useChanl) & B8in16) 	ADC_RegularChannelConfig(&ADC1_Handler, ADC_CHANNEL_7, (uint32_t)(i++), ADC_SAMPLETIME_56CYCLES);
		if((SYSTEM_ADC1_useChanl) & B9in16) 	ADC_RegularChannelConfig(&ADC1_Handler, ADC_CHANNEL_8, (uint32_t)(i++), ADC_SAMPLETIME_56CYCLES);
		if((SYSTEM_ADC1_useChanl) & B10in16)	ADC_RegularChannelConfig(&ADC1_Handler, ADC_CHANNEL_9, (uint32_t)(i++), ADC_SAMPLETIME_56CYCLES);
		if((SYSTEM_ADC1_useChanl) & B11in16)	ADC_RegularChannelConfig(&ADC1_Handler, ADC_CHANNEL_10, (uint32_t)(i++), ADC_SAMPLETIME_56CYCLES);
		if((SYSTEM_ADC1_useChanl) & B12in16)	ADC_RegularChannelConfig(&ADC1_Handler, ADC_CHANNEL_11, (uint32_t)(i++), ADC_SAMPLETIME_56CYCLES);
		if((SYSTEM_ADC1_useChanl) & B13in16)	ADC_RegularChannelConfig(&ADC1_Handler, ADC_CHANNEL_12, (uint32_t)(i++), ADC_SAMPLETIME_56CYCLES);
		if((SYSTEM_ADC1_useChanl) & B14in16)	ADC_RegularChannelConfig(&ADC1_Handler, ADC_CHANNEL_13, (uint32_t)(i++), ADC_SAMPLETIME_56CYCLES);
		if((SYSTEM_ADC1_useChanl) & B15in16) 	ADC_RegularChannelConfig(&ADC1_Handler, ADC_CHANNEL_14, (uint32_t)(i++), ADC_SAMPLETIME_56CYCLES);
		//if((SYSTEM_ADC1_useChanl) & 0x10) 	ADC_RegularChannelConfig(&ADC1_Handler, ADC_CHANNEL_15, (uint32_t)(i++), ADC_SAMPLETIME_56CYCLES);
		
		if((SYSTEM_ADC1_useChanl) & B16in16) 	ADC_RegularChannelConfig(&ADC1_Handler, ADC_CHANNEL_TEMPSENSOR, (uint32_t)(i++), ADC_SAMPLETIME_56CYCLES);
	}
}

//�˺����ᱻHAL_ADC_Init()����
//hadc:ADC���
void HAL_ADC_MspInit(ADC_HandleTypeDef* hadc)
{
/*	
	ͨ����	0	1	2	3	4	5	6	7	8	9	10	11	12	13	14	15	   16		     17
	IO	��	A0	A1	A2	A3	A4	A5	A6	A7	B0	B1	C0	C1	C2	C3	C4	C5	�ڲ��¶�	�ڲ��ο���ѹ
*/
	if(hadc->Instance == ADC1)
	{
		GPIO_InitTypeDef GPIO_Initure;
		__HAL_RCC_ADC1_CLK_ENABLE();            //ʹ��ADC1ʱ��
		__HAL_RCC_GPIOA_CLK_ENABLE();			//����GPIOAʱ��
		__HAL_RCC_GPIOB_CLK_ENABLE();
		
		GPIO_Initure.Mode=GPIO_MODE_ANALOG;     //ģ��
		GPIO_Initure.Pull=GPIO_NOPULL;          //����������
		               
		if((SYSTEM_ADC1_useChanl) & B1in16) {
			GPIO_Initure.Pin=GPIO_PIN_0; 
			HAL_GPIO_Init(GPIOA,&GPIO_Initure);
			}
		if((SYSTEM_ADC1_useChanl) & B2in16) {
			GPIO_Initure.Pin=GPIO_PIN_1; 
			HAL_GPIO_Init(GPIOA,&GPIO_Initure);
			}
		if((SYSTEM_ADC1_useChanl) & B3in16) {
			GPIO_Initure.Pin=GPIO_PIN_2; 
			HAL_GPIO_Init(GPIOA,&GPIO_Initure);
			}
		if((SYSTEM_ADC1_useChanl) & B4in16) {
			GPIO_Initure.Pin=GPIO_PIN_3; 
			HAL_GPIO_Init(GPIOA,&GPIO_Initure);
			}
		if((SYSTEM_ADC1_useChanl) & B5in16) {GPIO_Initure.Pin=GPIO_PIN_4; HAL_GPIO_Init(GPIOA,&GPIO_Initure);}
		if((SYSTEM_ADC1_useChanl) & B6in16) {GPIO_Initure.Pin=GPIO_PIN_5; HAL_GPIO_Init(GPIOA,&GPIO_Initure);}
		if((SYSTEM_ADC1_useChanl) & B7in16) {GPIO_Initure.Pin=GPIO_PIN_6; HAL_GPIO_Init(GPIOA,&GPIO_Initure);}
		if((SYSTEM_ADC1_useChanl) & B8in16) {GPIO_Initure.Pin=GPIO_PIN_7; HAL_GPIO_Init(GPIOA,&GPIO_Initure);}
		if((SYSTEM_ADC1_useChanl) & B9in16) {GPIO_Initure.Pin=GPIO_PIN_0; HAL_GPIO_Init(GPIOB,&GPIO_Initure);}
		if((SYSTEM_ADC1_useChanl) & B10in16) {GPIO_Initure.Pin=GPIO_PIN_1; HAL_GPIO_Init(GPIOB,&GPIO_Initure);}
		if((SYSTEM_ADC1_useChanl) & B11in16) {GPIO_Initure.Pin=GPIO_PIN_0; HAL_GPIO_Init(GPIOC,&GPIO_Initure);}
		if((SYSTEM_ADC1_useChanl) & B12in16) {GPIO_Initure.Pin=GPIO_PIN_1; HAL_GPIO_Init(GPIOC,&GPIO_Initure);}
		if((SYSTEM_ADC1_useChanl) & B13in16) {GPIO_Initure.Pin=GPIO_PIN_2; HAL_GPIO_Init(GPIOC,&GPIO_Initure);}
		if((SYSTEM_ADC1_useChanl) & B14in16) {GPIO_Initure.Pin=GPIO_PIN_3; HAL_GPIO_Init(GPIOC,&GPIO_Initure);}
		if((SYSTEM_ADC1_useChanl) & B15in16) {GPIO_Initure.Pin=GPIO_PIN_4; HAL_GPIO_Init(GPIOC,&GPIO_Initure);}
		//if((SYSTEM_ADC1_useChanl) & B166in16) {GPIO_Initure.Pin=GPIO_PIN_5; HAL_GPIO_Init(GPIOC,&GPIO_Initure);}  �����ڲ��¶�ͨ������16��ADC1ͨ��������
	}
}


u16 adValue[SYSTEM_ADC1_useChanlNum];		  /*DMA1��ADCת��������͵�Ŀ��λ��*/
u8 adValueDone = 0;			/*DMA��ADC1��ֵ���͵�adValue��ɱ�־*/

//���ADCֵ
//ch: ͨ��ֵ 0~16��ȡֵ��ΧΪ��ADC_CHANNEL_0~ADC_CHANNEL_16
//����ֵ:ת�����
u16 Get_Adc(u32 ch)   
{
	ADC_ChannelConfTypeDef ADC1_ChanConf;
	if (!SYSTEM_ADC1_useScan)
	{	
		ADC1_ChanConf.Channel=ch;                                   //ͨ��
		ADC1_ChanConf.Rank=1;                                       //��1�����У�����1
		ADC1_ChanConf.SamplingTime=ADC_SAMPLETIME_480CYCLES;      	//����ʱ��               
		HAL_ADC_ConfigChannel(&ADC1_Handler,&ADC1_ChanConf);        //ͨ������
		
		HAL_ADC_Start(&ADC1_Handler);                               //����ADC
		HAL_ADC_PollForConversion(&ADC1_Handler,2);                 //����
		return (u16)HAL_ADC_GetValue(&ADC1_Handler);	        	//�������һ��ADC1�������ת�����
	}else
	{
		return 2333;
	}
}

u32 Get_Adc_Average(u32 ch,u8 times)
{
	u32 temp_val = 0;
	u8 t;
	
	for(t=0;t < times;t++)
	{
		temp_val += Get_Adc(ch);
		HAL_Delay(1);
	}
	return (temp_val/times);
}

/*��AD�ɼ��¶�ͨ����ԭʼֵ��ת��Ϊ�¶�ֵ*/
float Get_Temprate(u32 adcx)
{
 	float temperate;
	temperate = ((float)adcx)*(3.3/4096.0);				//��ѹֵ
	temperate = (1.43-temperate)/0.0043 + 25.0;				//ת��Ϊ�¶�ֵ 	 
	return temperate;
}

#if SYSTEM_ADC1_useScan
DMA_HandleTypeDef  ADC1rxDMA_Handler; //DMA���

//DMA1�ĸ�ͨ������
//����Ĵ�����ʽ�ǹ̶���,���Ҫ���ݲ�ͬ��������޸�
//�Ӵ洢��->����ģʽ/8λ���ݿ��/�洢������ģʽ
void ADC_DMA_Cfg(void)
{
	__HAL_RCC_DMA2_CLK_ENABLE();

    ADC1rxDMA_Handler.Instance = DMA2_Stream0;                                 //DMA Stream0
	ADC1rxDMA_Handler.Init.Channel = DMA_CHANNEL_0;
    ADC1rxDMA_Handler.Init.Direction=DMA_PERIPH_TO_MEMORY;                     //���赽�洢��
    ADC1rxDMA_Handler.Init.PeriphInc=DMA_PINC_DISABLE;                        //���������ģʽ
    ADC1rxDMA_Handler.Init.MemInc=DMA_MINC_ENABLE;                             //�洢������ģʽ
    ADC1rxDMA_Handler.Init.PeriphDataAlignment=DMA_PDATAALIGN_HALFWORD;        //�������ݳ���:16λ
    ADC1rxDMA_Handler.Init.MemDataAlignment=DMA_MDATAALIGN_HALFWORD;          //�洢�����ݳ���:16λ
	
	if(SYSTEM_ADC1_useCircular)
		ADC1rxDMA_Handler.Init.Mode=DMA_CIRCULAR;                                 	//���ADCѡ������ģʽ��������ѭ�����������������ģʽ������������ģʽ
	else ADC1rxDMA_Handler.Init.Mode=DMA_NORMAL;
   
	ADC1rxDMA_Handler.Init.Priority=DMA_PRIORITY_MEDIUM;                       //���ȼ�

    //ADC1rxDMA_Handler.XferCpltCallback = HAL_DMA_IRQHandler;
	ADC1rxDMA_Handler.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    
	HAL_DMA_DeInit(&ADC1rxDMA_Handler);                                      //DMA��λ
    HAL_DMA_Init(&ADC1rxDMA_Handler);                                        //DMA��ʼ�� 
        
		/*			����Դ   ����Դ����е�DMA����	  ʹ�õ�DMA���*/
	__HAL_LINKDMA(&ADC1_Handler,DMA_Handle,ADC1rxDMA_Handler);               //��DMA��ADC��ϵ����(����DMA)
	/*��DMA���ADC1rxDMA_Handler����ADC1_Handler��DMA_Handle*/
        
    HAL_NVIC_SetPriority(DMA2_Stream0_IRQn, 2, 0);                          //DMA�ж����ȼ� ���뿪���𶯣�
    HAL_NVIC_EnableIRQ(DMA2_Stream0_IRQn);                                  //ʹ��DMA�ж�
}

//DMA2 Stream0�жϷ���������ɴ���һ��ʱ���жϣ����ã���ΪҪ��ADȫ������ͨ��ת������ٲ���һ���ж�
void DMA2_Stream0_IRQHandler(void)
{
	HAL_DMA_IRQHandler(&ADC1rxDMA_Handler); /*����жϱ�־�����ж��Ƿ����ȫ��ת�����𶯣�*/
}

//HAL_DMA_IRQHandler�Ļص�������ADCת��������й�����ͨ������жϺ���
/*HAL_ADC_Start_DMA���������HAL_ADC_ConvCpltCallback��ΪADC1rxDMA_Handler���DMA����Ļص������ˣ�
�Զ��ģ�����ֻ�迪DMA���жϣ�����Ҫ��ADC�жϣ�������ͨ����ת���ú�DMA�жϾͻ�ص��������*/
/*TODO������һ�£���ADC1rxDMA_Handler.XferCpltCallback = HAL_DMA_IRQHandler;��仰ע�͵���Ӧ�ò�Ӱ��Ч����
��ΪHAL_ADC_Start_DMA�����������Ҫ�����ã�����DMA�Ļص������������ˣ�*/
/*��֮����ADC1rxDMA_Handler.XferCpltCallback = HAL_DMA_IRQHandler;ע�͵���ʣ�µĲ��־������׼��д�������*/
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
	adValueDone = 1; /*��־���ι�����ͨ��ȫ��ת����ɣ��𶯣�*/
}

#endif

#endif


/*_________________________________________________DAC_________________________________________________________*/
#if ((SYSTEM_DAC_OUT1_ENABLE) || (SYSTEM_DAC_OUT2_ENABLE))

DAC_HandleTypeDef DAC1_Handler;//DAC���

void sys_DAC_ENABLE(void)
{
	DAC_ChannelConfTypeDef DACCH1_Config;
	DAC_ChannelConfTypeDef DACCH2_Config;
	
	DAC1_Handler.Instance=DAC;
	HAL_DAC_Init(&DAC1_Handler);                 			//��ʼ��DAC
    
		/*ͨ��1����*/
		DACCH1_Config.DAC_Trigger=DAC_TRIGGER_NONE;             		//��ʹ�ô�������
							/*��ѡ��
								DAC_TRIGGER_T6_TRGO
								DAC_TRIGGER_T7_TRGO
								DAC_TRIGGER_T8_TRGO
								DAC_TRIGGER_T2_TRGO
								DAC_TRIGGER_T4_TRGO
								DAC_TRIGGER_EXT_IT9
								DAC_TRIGGER_SOFTWARE*/
		DACCH1_Config.DAC_OutputBuffer=DAC_OUTPUTBUFFER_ENABLE;		//DAC1�������
		/*ͨ��2����*/
		DACCH2_Config.DAC_Trigger=DAC_TRIGGER_NONE;             	//��ʹ�ô�������
		DACCH2_Config.DAC_OutputBuffer=DAC_OUTPUTBUFFER_ENABLE;		//DAC1�������
		
		if(SYSTEM_DAC_OUT1_ENABLE)
			HAL_DAC_ConfigChannel(&DAC1_Handler,&DACCH1_Config,DAC_CHANNEL_1);//DACͨ��1����
			HAL_DAC_Start(&DAC1_Handler,DAC_CHANNEL_1);  			//����DACͨ��1
		if(SYSTEM_DAC_OUT2_ENABLE)
			HAL_DAC_ConfigChannel(&DAC1_Handler,&DACCH2_Config,DAC_CHANNEL_2);//DACͨ��2����
			HAL_DAC_Start(&DAC1_Handler,DAC_CHANNEL_2);  			//����DACͨ��2
    
    
}

//DAC�ײ�������ʱ�����ã����� ����
//�˺����ᱻHAL_DAC_Init()����
//hdac:DAC���
void HAL_DAC_MspInit(DAC_HandleTypeDef* hdac)
{      
	if(SYSTEM_DAC_OUT1_ENABLE)
	{
		GPIO_InitTypeDef GPIO_Initure;
		__HAL_RCC_DAC_CLK_ENABLE();             //ʹ��DACʱ��
		__HAL_RCC_GPIOA_CLK_ENABLE();			//����GPIOAʱ��
		
		GPIO_Initure.Pin=GPIO_PIN_4;            //PA4
		GPIO_Initure.Mode=GPIO_MODE_ANALOG;     //ģ��
		GPIO_Initure.Pull=GPIO_NOPULL;          //����������
		HAL_GPIO_Init(GPIOA,&GPIO_Initure);
	}
	
	if(SYSTEM_DAC_OUT2_ENABLE)
	{
		GPIO_InitTypeDef GPIO_Initure;
		__HAL_RCC_DAC_CLK_ENABLE();             //ʹ��DACʱ��
		__HAL_RCC_GPIOA_CLK_ENABLE();			//����GPIOAʱ��
		
		GPIO_Initure.Pin=GPIO_PIN_5;            //PA5
		GPIO_Initure.Mode=GPIO_MODE_ANALOG;     //ģ��
		GPIO_Initure.Pull=GPIO_NOPULL;          //����������
		HAL_GPIO_Init(GPIOA,&GPIO_Initure);
	}
}

//����ͨ��1�����ѹ
//vol:0~3.30V
void DAC_Set_Ch1_Vol(float vol)
{
	float temp = vol;
	temp = (temp/3.30)*4096.0;
    HAL_DAC_SetValue(&DAC1_Handler,DAC_CHANNEL_1,DAC_ALIGN_12B_R,(uint32_t)temp);//12λ�Ҷ������ݸ�ʽ����DACֵ
}

//����ͨ��2�����ѹ
//vol:0~3.30V
void DAC_Set_Ch2_Vol(float vol)
{
	float temp = vol;
	temp = (temp/3.30)*4096.0;
    HAL_DAC_SetValue(&DAC1_Handler,DAC_CHANNEL_2,DAC_ALIGN_12B_R,(uint32_t)temp);//12λ�Ҷ������ݸ�ʽ����DACֵ
}


#endif


/*________________________________________________FSMC_________________________________________________________*/
#if ((SYSTEM_FSMC_ENABLE) && (SYSTEM_FSMC_use4SRAM))

SRAM_HandleTypeDef SRAM_Handler;    //SRAM���

//SRAM��ʼ��
void sys_FSMC_SRAM_ENABLE(void)
{	
	FSMC_NORSRAM_TimingTypeDef FSMC_ReadWriteTim;
	
	SRAM_Handler.Instance=FSMC_NORSRAM_DEVICE;                
	SRAM_Handler.Extended=FSMC_NORSRAM_EXTENDED_DEVICE;    
    
	SRAM_Handler.Init.NSBank=FSMC_NORSRAM_BANK3;     					//ʹ��NE3
	SRAM_Handler.Init.DataAddressMux=FSMC_DATA_ADDRESS_MUX_DISABLE; 	//��ַ/�����߲�����
	SRAM_Handler.Init.MemoryType=FSMC_MEMORY_TYPE_SRAM;   				//SRAM
	SRAM_Handler.Init.MemoryDataWidth=FSMC_NORSRAM_MEM_BUS_WIDTH_16; 	//16λ���ݿ��
	SRAM_Handler.Init.BurstAccessMode=FSMC_BURST_ACCESS_MODE_DISABLE; 	//�Ƿ�ʹ��ͻ������,����ͬ��ͻ���洢����Ч,�˴�δ�õ�
	SRAM_Handler.Init.WaitSignalPolarity=FSMC_WAIT_SIGNAL_POLARITY_LOW;	//�ȴ��źŵļ���,����ͻ��ģʽ����������
	SRAM_Handler.Init.WrapMode = FSMC_WRAP_MODE_DISABLE; 
	SRAM_Handler.Init.WaitSignalActive=FSMC_WAIT_TIMING_BEFORE_WS;   	//�洢�����ڵȴ�����֮ǰ��һ��ʱ�����ڻ��ǵȴ������ڼ�ʹ��NWAIT
	SRAM_Handler.Init.WriteOperation=FSMC_WRITE_OPERATION_ENABLE;    	//�洢��дʹ��
	SRAM_Handler.Init.WaitSignal=FSMC_WAIT_SIGNAL_DISABLE;           	//�ȴ�ʹ��λ,�˴�δ�õ�
	SRAM_Handler.Init.ExtendedMode=FSMC_EXTENDED_MODE_DISABLE;        	//��дʹ����ͬ��ʱ��
	SRAM_Handler.Init.AsynchronousWait=FSMC_ASYNCHRONOUS_WAIT_DISABLE;	//�Ƿ�ʹ��ͬ������ģʽ�µĵȴ��ź�,�˴�δ�õ�
	SRAM_Handler.Init.WriteBurst=FSMC_WRITE_BURST_DISABLE;           	//��ֹͻ��д
  
	//FMC��ʱ����ƼĴ���
	FSMC_ReadWriteTim.AddressSetupTime=0x00;       	//��ַ����ʱ�䣨ADDSET��Ϊ1��HCLK 1/72M=13.8ns
	FSMC_ReadWriteTim.AddressHoldTime=0x00;			//��ַ����ʱ�䣨ADDHLD��ģʽAδ�õ�
	FSMC_ReadWriteTim.DataSetupTime=0x01;			//���ݱ���ʱ��Ϊ3��HCLK	=4*13.8=55ns
	FSMC_ReadWriteTim.BusTurnAroundDuration=0X00;
	FSMC_ReadWriteTim.AccessMode=FSMC_ACCESS_MODE_A;//ģʽA
	HAL_SRAM_Init(&SRAM_Handler,&FSMC_ReadWriteTim,&FSMC_ReadWriteTim);	
}

//��ָ����ַ(WriteAddr+Bank1_SRAM3_ADDR)��ʼ,����д��n���ֽ�.
//pBuffer:�ֽ�ָ��
//WriteAddr:Ҫд��ĵ�ַ
//n:Ҫд����ֽ���
void FSMC_SRAM_WriteBuffer(u8 *pBuffer,u32 WriteAddr,u32 n)
{
	for(;n!=0;n--)
	{
		*(vu8*)(SRAM1_BANK3_ADDR + WriteAddr) = *pBuffer;
		WriteAddr++;
		pBuffer++;
	}
}

//��ָ����ַ((WriteAddr+Bank1_SRAM3_ADDR))��ʼ,��������n���ֽ�.
//pBuffer:�ֽ�ָ��
//ReadAddr:Ҫ��������ʼ��ַ
//n:Ҫд����ֽ���
void FSMC_SRAM_ReadBuffer(u8 *pBuffer,u32 ReadAddr,u32 n)
{
	for(;n!=0;n--)
	{
		*pBuffer++ = *(vu8*)(SRAM1_BANK3_ADDR + ReadAddr);
		ReadAddr++;
	}
}

#endif

#if SYSTEM_FSMC_ENABLE

//SRAM�ײ�������ʱ��ʹ�ܣ����ŷ���
//�˺����ᱻHAL_SRAM_Init()����
//hsram:SRAM���
void HAL_SRAM_MspInit(SRAM_HandleTypeDef *hsram)
{	
	/*���������TFT��FSMC*/
	if(&TFTSRAM_Handler == hsram)
	{
		GPIO_InitTypeDef GPIO_Initure;
		
		__HAL_RCC_FSMC_CLK_ENABLE();			//ʹ��FSMCʱ��
		__HAL_RCC_GPIOD_CLK_ENABLE();			//ʹ��GPIODʱ��
		__HAL_RCC_GPIOE_CLK_ENABLE();			//ʹ��GPIOEʱ��
		__HAL_RCC_GPIOG_CLK_ENABLE();			//ʹ��GPIOGʱ��
		
		//��ʼ��PD0,1,4,5,8,9,10,14,15
		GPIO_Initure.Pin=GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_8|\
						 GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_14|GPIO_PIN_15;
		GPIO_Initure.Mode=GPIO_MODE_AF_PP; 		//���츴��
		GPIO_Initure.Pull=GPIO_NOPULL;			//
		GPIO_Initure.Speed=GPIO_SPEED_FREQ_VERY_HIGH;//����
		GPIO_Initure.Alternate = GPIO_AF12_FSMC;
		HAL_GPIO_Init(GPIOD,&GPIO_Initure);     //��ʼ��
		
		//��ʼ��PE7,8,9,10,11,12,13,14,15
		GPIO_Initure.Pin=GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11|\
						 GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
		HAL_GPIO_Init(GPIOE,&GPIO_Initure);
		
		//��ʼ��PG0,12
		GPIO_Initure.Pin=GPIO_PIN_0|GPIO_PIN_12;
		HAL_GPIO_Init(GPIOG,&GPIO_Initure);
	}
	
	/*���������SRAM��FSMC*/
	if(&SRAM_Handler == hsram)
	{
		GPIO_InitTypeDef GPIO_Initure;
		
		__HAL_RCC_FSMC_CLK_ENABLE();                //ʹ��FSMCʱ��
		__HAL_RCC_GPIOD_CLK_ENABLE();               //ʹ��GPIODʱ��
		__HAL_RCC_GPIOE_CLK_ENABLE();               //ʹ��GPIOEʱ��
		__HAL_RCC_GPIOF_CLK_ENABLE();               //ʹ��GPIOFʱ��
		__HAL_RCC_GPIOG_CLK_ENABLE();               //ʹ��GPIOGʱ��
		
		//PD0,1,4,5,8~15
		GPIO_Initure.Pin=GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_8|\
						 GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|\
						 GPIO_PIN_14|GPIO_PIN_15;  
		GPIO_Initure.Mode=GPIO_MODE_AF_PP;          //���츴��
		GPIO_Initure.Pull=GPIO_NOPULL;              //
		GPIO_Initure.Speed=GPIO_SPEED_FREQ_VERY_HIGH;    //���� 
		GPIO_Initure.Alternate = GPIO_AF12_FSMC;
		HAL_GPIO_Init(GPIOD,&GPIO_Initure);     	
		
		//PE0,1,7~15
		GPIO_Initure.Pin=GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9|\
						 GPIO_PIN_10| GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|\
						 GPIO_PIN_15;    
		HAL_GPIO_Init(GPIOE,&GPIO_Initure);    
		
		//PF0~5,12~15
		GPIO_Initure.Pin=GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|\
						 GPIO_PIN_5|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;              
		HAL_GPIO_Init(GPIOF,&GPIO_Initure);     
		
		//PG0~5,10
		GPIO_Initure.Pin=GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_10;              
		HAL_GPIO_Init(GPIOG,&GPIO_Initure);  
	}

}

#endif

#if ((SYSTEM_FSMC_ENABLE) && (SYSTEM_FSMC_use4LCD))

SRAM_HandleTypeDef TFTSRAM_Handler;    //SRAM���(���ڿ���LCD)

void LCD_with_FSMC_init_FSMC(void)
{
	FSMC_NORSRAM_TimingTypeDef FSMC_ReadWriteTim;
	FSMC_NORSRAM_TimingTypeDef FSMC_WriteTim;
	
	TFTSRAM_Handler.Instance=FSMC_NORSRAM_DEVICE;                
	TFTSRAM_Handler.Extended=FSMC_NORSRAM_EXTENDED_DEVICE;    
    
	TFTSRAM_Handler.Init.NSBank=FSMC_NORSRAM_BANK4;     				//ʹ��NE4
	TFTSRAM_Handler.Init.DataAddressMux=FSMC_DATA_ADDRESS_MUX_DISABLE; 	//��ַ/�����߲�����
	TFTSRAM_Handler.Init.MemoryType=FSMC_MEMORY_TYPE_SRAM;   			//SRAM
	TFTSRAM_Handler.Init.MemoryDataWidth=FSMC_NORSRAM_MEM_BUS_WIDTH_16; //16λ���ݿ��
	TFTSRAM_Handler.Init.BurstAccessMode=FSMC_BURST_ACCESS_MODE_DISABLE; //�Ƿ�ʹ��ͻ������,����ͬ��ͻ���洢����Ч,�˴�δ�õ�
	TFTSRAM_Handler.Init.WaitSignalPolarity=FSMC_WAIT_SIGNAL_POLARITY_LOW;//�ȴ��źŵļ���,����ͻ��ģʽ����������
	TFTSRAM_Handler.Init.WrapMode = FSMC_WRAP_MODE_DISABLE;
	TFTSRAM_Handler.Init.WaitSignalActive=FSMC_WAIT_TIMING_BEFORE_WS;   //�洢�����ڵȴ�����֮ǰ��һ��ʱ�����ڻ��ǵȴ������ڼ�ʹ��NWAIT
	TFTSRAM_Handler.Init.WriteOperation=FSMC_WRITE_OPERATION_ENABLE;    //�洢��дʹ��
	TFTSRAM_Handler.Init.WaitSignal=FSMC_WAIT_SIGNAL_DISABLE;           //�ȴ�ʹ��λ,�˴�δ�õ�
	TFTSRAM_Handler.Init.ExtendedMode=FSMC_EXTENDED_MODE_ENABLE;        //��дʹ�ò�ͬ��ʱ��
	TFTSRAM_Handler.Init.AsynchronousWait=FSMC_ASYNCHRONOUS_WAIT_DISABLE;//�Ƿ�ʹ��ͬ������ģʽ�µĵȴ��ź�,�˴�δ�õ�
	TFTSRAM_Handler.Init.WriteBurst=FSMC_WRITE_BURST_DISABLE;           //��ֹͻ��д
    
	//FMC��ʱ����ƼĴ���
	FSMC_ReadWriteTim.AddressSetupTime=0x06;       	//��ַ����ʱ�䣨ADDSET��Ϊ7��HCLK 13.8ns*7=96.6ns
	FSMC_ReadWriteTim.AddressHoldTime=0;
	FSMC_ReadWriteTim.DataSetupTime=26;				//���ݱ���ʱ��Ϊ27��HCLK	=13.8*27=372.6ns
	FSMC_ReadWriteTim.AccessMode=FSMC_ACCESS_MODE_A;//ģʽA
	//FMCдʱ����ƼĴ���
	FSMC_WriteTim.BusTurnAroundDuration=0;			//������ת�׶γ���ʱ��Ϊ0���˱�������ֵ�Ļ���Ī��������Զ��޸�Ϊ4�����³�����������
	FSMC_WriteTim.AddressSetupTime=3;          		//��ַ����ʱ�䣨ADDSET��Ϊ4��HCLK =55.2ns 
	FSMC_WriteTim.AddressHoldTime=0;
	FSMC_WriteTim.DataSetupTime=0x06;              	//���ݱ���ʱ��Ϊ13.8ns*7��HCLK=96.6ns
	FSMC_WriteTim.AccessMode=FSMC_ACCESS_MODE_A;    //ģʽA
	HAL_SRAM_Init(&TFTSRAM_Handler,&FSMC_ReadWriteTim,&FSMC_WriteTim);	
	
	HAL_Delay(50); // delay 50 ms 
}

#endif




