#include "BareConfig.h"

#define RunTimeFaultCheck_ENABLE 0	/*ʹ�ܹ���Ѳ�죬300ms����*/

void Bare_Begin(void)
{
	#if RunTimeFaultCheck_ENABLE
		static u8 RunTimeFaultCheck_TtemNow = 1;	/*����Ѳ�쵱ǰ������Ŀ�����Զ�λ*/
		const u8 RunTimeFaultCheck_TtemMaxNum = 3;	/*����Ѳ��������Ŀ����*/
	#endif
	
	#if (SYSTEM_FSMC_ENABLE) && (SYSTEM_FSMC_use4LCD)
	
	#else
		char* Head_buf = {"For Test!"};
		DrawPageHead((u8*)Head_buf);
	#endif
	BACK_COLOR = BLACK;
	for(;;)
	{
		/*ע�⣺���ﾡ����Ҫ��10�����жϱ�־������ֻ��100���롢300���롢1���һ���ӵ��жϱ�־��������*/
		
		if(Timer_IT_flags._10msec_flag == TRUE)
		{
			Timer_IT_flags._10msec_flag = FALSE;
			
		}
		
		
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
							//��ʽ�ο�-> if( ִ�м��ĺ��� ��= ReturnOK ) FaultASSERT(Init_OK_Num);
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
			
			/*����������Ϣ*/
			
			/*ˢ�½�����Ϣ*/
			
			keyProcess();	//�˵�����������ӹܺͻ�ȡ����
			menuProcess();	//�˵������İ�������ִ�й��ܺ���
			
			//TestLED_Ctrl = !TestLED_Ctrl;
			TestLED2_Ctrl = !TestLED2_Ctrl;	
		}
		
		/*____________________________________1s����ִ�У�ͨ��Ϊ����״ָ̬ʾ���δ��������ѵȵ�__________________________________________*/
		if(Timer_IT_flags._1sec_flag == TRUE)
		{
			Timer_IT_flags._1sec_flag = FALSE;
			
			/*1s����Ҫ��������*/		
			
			//��ʾRTCʱ��
			char RTC_buf[50];
//			#if SYSTEM_RTC_ENABLE
//				RTC_TimeTypeDef RTC_RealTime;
//				RTC_DateTypeDef	RTC_RealDate;
//				HAL_RTC_GetTime(&RTC_Handler, &RTC_RealTime, RTC_FORMAT_BIN);
//				HAL_RTC_GetDate(&RTC_Handler, &RTC_RealDate, RTC_FORMAT_BIN);
//				sprintf(RTC_buf,"%d-%d-%d-%d   %d-%d-%d\r\n",RTC_RealDate.Year + 1970,RTC_RealDate.Month,RTC_RealDate.Date,RTC_RealDate.WeekDay,RTC_RealTime.Hours,RTC_RealTime.Minutes,RTC_RealTime.Seconds);
//				printf_uart(UART1,"%s",RTC_buf);
//			#endif
			
			POINT_COLOR = BLUE;
			sprintf(RTC_buf,"%4ds",sys_GetsysRunTime(NULL,NULL,NULL));
			LCD_ShowString(5,20,16,(u8*)RTC_buf);
//			
//			
//			//��ʾ��������
//			#if SYSTEM_FLASH_IAP_ENABLE
//				sprintf(RTC_buf,"%d",StartUpTimes);
//				LCD_ShowString(35,20,16,(u8*)RTC_buf);
//			#endif
			
		}
		
		if(Timer_IT_flags._1min_flag == TRUE)
		{
			Timer_IT_flags._1min_flag = FALSE;
			
			/*1min����Ҫ��������*/
			
		}
	}
}


