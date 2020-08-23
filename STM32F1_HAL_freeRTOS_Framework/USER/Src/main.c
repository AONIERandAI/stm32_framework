/*
*��Ŀ˵����STM32F1��̿��
*���ߣ�Staok�����䣺superxhy@qq.com
*��Դ��ַ���ֿ��ַ https://github.com/Staok/stm32_framework
*������ú��ã���ע����Դ�ֿ��ַ�������Ժ��о��¿�ԴЭ���ټ��Ͽ�ԴЭ��ٺ�
*/

#include "sys.h" /*����ͷ�ļ�������������*/

int main(void)
{
	/*ѡ���Ƿ���FreeRTOS��д��ʼ����������sys.c��*/
	/*FreeRTOS�����д��TaskConfig.c��*/
	/*������������д��BareConfig.c��*/
	HAL_Init();                    	/*��ʼ��HAL��*/
	sys_MCU_Init_Seq();					/*MCU�����ʼ�����У����г�ʼ��д�������桪����������������Ҫ�����޸ģ�*/
	delay_ms(66);
	sys_Device_Init_Seq();				/*���������ʼ�����������Լ졪����������������Ҫ�����޸ģ�*/
	delay_ms(234);
	while(1)
	{
		#if SYSTEM_SUPPORT_OS
			Task_Begin(); 			/*��ʼ��FreeRTOS*/
		#else
			Bare_Begin();			/*��ʼ�����*/
		#endif
	}
}



