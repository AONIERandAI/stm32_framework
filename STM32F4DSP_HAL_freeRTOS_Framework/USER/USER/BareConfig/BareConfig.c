#include "BareConfig.h"

#define RunTimeFaultCheck_ENABLE 0	/*ʹ�ܹ���Ѳ�죬300ms����*/

void Bare_Begin(void)
{
	#if RunTimeFaultCheck_ENABLE
		static u8 RunTimeFaultCheck_TtemNow = 1;	/*����Ѳ�쵱ǰ������Ŀ�����Զ�λ*/
		const u8 RunTimeFaultCheck_TtemMaxNum = 3;	/*����Ѳ��������Ŀ����*/
	#endif
	
	/*LCD������ҳ*/
	#if (SYSTEM_FSMC_ENABLE) && (SYSTEM_FSMC_use4LCD)
	
	#else
		char* Head_buf = {"stm32_framework"};
		DrawPageHead((u8*)Head_buf);
	#endif
	
	/*������ADCʱ��Ҫ����HAL_ADC_Start_DMA*/
	#if (SYSTEM_ADC1_ENABLE) && (SYSTEM_ADC1_useScan) && (SYSTEM_ADC1_useCircular)
		HAL_ADC_Start_DMA(&ADC1_Handler, (uint32_t*)&adValue,SYSTEM_ADC1_useChanlNum);
	#endif
	BACK_COLOR = BLACK;
	
	for(;;)
	{
		#if SYS_SUPPORT_LWIP && NO_SYS	//����LWIP��������ʱ�ŵ���
			lwip_periodic_handle();
		#endif
		
		/*ע�⣺���ﾡ����Ҫ��10�����жϱ�־������ֻ��100���롢300���롢1���һ���ӵ��жϱ�־��������*/
		if(Timer_IT_flags._10msec_flag == TRUE)
		{
			Timer_IT_flags._10msec_flag = FALSE;
			
			#if SYSTEM_RNG_ENABLE
				HAL_RNG_GenerateRandomNumber_IT(&RNG_Handle);
			#endif
		}
		
		#if SYSTEM_RNG_ENABLE
			char RNG_buf[20];
			if(GenerateRNG_Ready)
			{
				GenerateRNG_Ready = 0;
				sprintf_(RNG_buf,"RNG:%d",randomNum32bit);
				POINT_COLOR = RED;
				LCD_ShowString(5,lcddev.height - 80,16,(u8*)RNG_buf);
			}
		#endif
		
		/*____________________________________100ms����ִ�У�����Ϊ�������ʹ����________________________________________*/
		if(Timer_IT_flags._100msec_flag == TRUE)
        {
            Timer_IT_flags._100msec_flag = FALSE;
			
			/*100ms����Ҫ��������*/
			
			/*���ڻ���*/
//			u16 num4uart1;
//			char* buf4uart1 = mymalloc(InrRAM,(USART1_RX_BUF_MaxNum > USART1_RX_FIFO_MaxNum ? USART1_RX_BUF_MaxNum : USART1_RX_FIFO_MaxNum));
//			if(buf4uart1 != NULL)
//			{
//				if(sys_USART1_RX_Fetch(FALSE, buf4uart1,&num4uart1) == HAL_OK)
//				{
//					printf_uart(UART1,"%s-%d",buf4uart1,num4uart1);
//				}
//			}
//			myfree(InrRAM,buf4uart1);
			
			
			/*����������Ϣ*/
			keyProcess();	//�˵�����������ӹܺͻ�ȡ����
			
			/*ˢ�½�����Ϣ*/
			menuProcess();	//�˵������İ�������ִ�й��ܺ���
			
		}
		/*____________________________________300ms����ִ�У�ͨ��Ϊ����ʱ�����Լ��Լ�����ˢ����__________________________________________*/
		if(Timer_IT_flags._300msec_flag == TRUE)
		{
			Timer_IT_flags._300msec_flag = FALSE;
			
			/*���й���Ѳ��START*/
			#if RunTimeFaultCheck_ENABLE
				switch(RunTimeFaultCheck_TtemNow)
				{
					case 1:	
							//��ʽ�ο�-> if( ִ�м��ĺ��� ��= ReturnOK ) FaultASSERT("1",1,flag_Warning);
							break;
					case 2:	
							break;
					case 3:	
							break;
					default:break;
				}
				if(++RunTimeFaultCheck_TtemNow > RunTimeFaultCheck_TtemMaxNum)
					RunTimeFaultCheck_TtemNow = 1;
			#endif
			/*���й���Ѳ��END*/
			
			/*300ms����Ҫ��������*/
			
			//TestLED_Ctrl = !TestLED_Ctrl;
			TestLED2_Ctrl = !TestLED2_Ctrl;	
			
			/*��ʾADCֵ*/
			#if SYSTEM_ADC1_ENABLE
				char ADC_buf[20];
				if(adValueDone)
				{
					adValueDone = 0;
					//HAL_ADC_Stop_DMA(&ADC1_Handler);
					sprintf_(ADC_buf,"adValue:%d %d %d %5.2f",adValue[0],adValue[1],adValue[2],Get_Temprate(adValue[3]));
					LCD_Fill(0,lcddev.height - 60,lcddev.width,lcddev.height - 40,BLACK);
					Gui_StrCenter(0,lcddev.height - 60,RED,BLACK,(u8*)ADC_buf,16,0);
				}
			#endif
			
//				POINT_COLOR = RED;
//				char str_buf[200];
//				short MPU6050_Gyro[3];
//				short MPU6050_Accel[3];
//				float mpu_temp = MPU_Get_Temperature();
//				MPU6050ReadAcc(MPU6050_Accel);
//				MPU6050ReadGyro(MPU6050_Gyro);
//				sprintf_(str_buf,"MPU6050_Accel-%d-%d-%d-%5.2f-%d",MPU6050_Accel[0],MPU6050_Accel[1],MPU6050_Accel[2],mpu_temp,Timer_IT_flags._100msec);
//				LCD_ShowString(5,lcddev.height - 60,16,(u8*)str_buf);
			
		}
		
		/*____________________________________1s����ִ�У�ͨ��Ϊ����״ָ̬ʾ���δ��������ѵȵ�__________________________________________*/
		if(Timer_IT_flags._1sec_flag == TRUE)
		{
			Timer_IT_flags._1sec_flag = FALSE;
			
			/*1s����Ҫ��������*/

			#if SYSTEM_FSMC_ENABLE
				POINT_COLOR = RED;
				char* str_buf = mymalloc(ExRAM1,20000);
				char* str_buf2 = "mymalloc fault";
				if(str_buf == NULL)
					LCD_ShowString(5,lcddev.height - 80,16,(u8*)str_buf2);
				else
					sprintf_(str_buf,"%6.3f-%6.3f%%\0",Timer_IT_flags._100msec/3.3f,my_mem_perused(ExRAM1)*100.0f),
					LCD_ShowString(5,lcddev.height - 80,16,(u8*)str_buf);
				myfree(ExRAM1,str_buf);
			#endif
			
			/*��ʾRTCʱ��*/
			char RTC_buf[50];
			#if SYSTEM_RTC_ENABLE
				RTC_TimeTypeDef RTC_RealTime;
				RTC_DateTypeDef	RTC_RealDate;
				HAL_RTC_GetTime(&RTC_Handler, &RTC_RealTime, RTC_FORMAT_BIN);
				HAL_RTC_GetDate(&RTC_Handler, &RTC_RealDate, RTC_FORMAT_BIN);
				sprintf_(RTC_buf,"%4d-%2d-%2d-%1d %2d-%2d-%2d\r\n",RTC_RealDate.Year + 1970,RTC_RealDate.Month,RTC_RealDate.Date,RTC_RealDate.WeekDay,RTC_RealTime.Hours,RTC_RealTime.Minutes,RTC_RealTime.Seconds);
				Gui_StrCenter(0,lcddev.height - 40,BRRED,BLACK,(u8*)RTC_buf,16,0);
				//printf_uart(UART1,"%s",RTC_buf);
			#endif
			
			/*��ʾ����ʱ�䣨�룩*/
			POINT_COLOR = BLUE;
			sprintf_(RTC_buf,"%4ds",sys_GetsysRunTime(NULL,NULL,NULL));
			LCD_ShowString(5,20,16,(u8*)RTC_buf);
			
			/*��ʾ��������*/
			#if SYSTEM_FLASH_IAP_ENABLE
				POINT_COLOR = RED;
				sprintf_(RTC_buf,"%d",StartUpTimes);
				LCD_ShowString(lcddev.width - 20,20,16,(u8*)RTC_buf);
			#endif
			
		}
		
		if(Timer_IT_flags._1min_flag == TRUE)
		{
			Timer_IT_flags._1min_flag = FALSE;
			
			/*1min����Ҫ��������*/
			
		}
	}
}


