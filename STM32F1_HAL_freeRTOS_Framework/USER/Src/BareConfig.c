#include "BareConfig.h"



void Bare_Begin(void)
{
	static u8 RunTimeFaultCheck_ENABLE = 0;		/*ʹ�ܹ���Ѳ�죬300ms����*/
	static u8 RunTimeFaultCheck_TtemNow = 1;	/*����Ѳ�쵱ǰ������Ŀ�����Զ�λ*/
	const u8 RunTimeFaultCheck_TtemMaxNum = 3;	/*����Ѳ��������Ŀ����*/
	
	for(;;)
	{
		/*ע�⣺���ﾡ����Ҫ��10�����жϱ�־������ֻ��100���롢300���롢1���һ���ӵ��жϱ�־��������*/
		
		/*100ms����ִ�У�����Ϊ�������ʹ����*/
		if(Timer_IT_flags._100msec_flag == TRUE)
        {
            Timer_IT_flags._100msec_flag = FALSE;
		}
		/*300ms����ִ�У�ͨ��Ϊ����ʱ�����Լ��Լ�����ˢ����*/
		if(Timer_IT_flags._300msec_flag == TRUE)
		{
			Timer_IT_flags._300msec_flag = FALSE;
			/*���й���Ѳ��START*/
			if(RunTimeFaultCheck_ENABLE)
			{
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
			}
			/*���й���Ѳ��END*/
			
			/*����������Ϣ*/
			
			/*ˢ�½�����Ϣ*/
			
		}
		
		if(Timer_IT_flags._1sec_flag == TRUE)
		{
			Timer_IT_flags._1sec_flag = FALSE;
			
		}
		
		if(Timer_IT_flags._1min_flag == TRUE)
		{
			Timer_IT_flags._1min_flag = FALSE;
			
		}
	}
}


