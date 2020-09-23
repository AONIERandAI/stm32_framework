#ifndef __SYS_H
#define __SYS_H

#include "sysVar.h"								/*����ϵͳ�����õı������������ͺͶ����Ʊ�ʾ��*/
#include "stm32f1xx.h"
#include "stm32f1xx_hal.h"						/*�������stm32f1xx_hal_conf.h����ѡ������Щ�����HAL�⡪����������������Ҫ�����޸ģ�*/
#include "PeriphConfig.h"
#include "FIFO.h"								/*��Github�����һ����Դ�ֿ⣬
												һ��ʵ�ֶ��κ���ʽ���ݵĻ��λ��棬Ĭ���Ѿ����ڴ��ڽ��գ��ο�����.h�ļ���
												��Դ�ֿ��ַ��https://github.com/geekfactory/FIFO.git*/
#include "malloc.h"								/*�������ԭ�ӵ� �ڴ���� �½ڵ�Դ������ʵ�ֵ�malloc��free*/				
												
												
												
/*�û��豸������APP�ļ�����*/
#include "TFTLCD.h"
												
												

/*
��̹淶��
	No.1�����գ�ͨ�ã��ɵ��������ھ۵���ϣ��㷺���

*/

/*
�����淶������ʱ��
	0��������������Ϊ����ʲô��ʲô��ʲô�����磺sys_irq_disable()
	1��ϵͳʹ�����蹦�ܵ����������ú궨��SYSTEM_SUPPORT_XX
	2��RTOS��������ʹ��xx_task()����
	3������������������һ�£����������뺯��һ�£�ֻ��task���ּ�дΪt
	4������ע�͹淶���£�*/
	
	/*__________��������_____________*/
	/********************************
	*������������ϸ����������������������Ҫ�����޸ģ�
	*������		1��...
				2��...
	*����ֵ��	1��NULL
	********************************/
	
	/*
	5����������ֵ0��ʾ�ɹ�����0��ʾʧ�ܣ��˷��������Ա�ʾ�������
	6��һ�����һ��ģ���ڵı��������ýṹ�������������ݾ��ýṹ������
	7��MCU����ͳ��"����"����Periph���û���MCU��ΧоƬ���豸ͳ��"����"��"�豸",��devices
	*/
	
/*Ӧ�ù淶������ʱ��������
	00�����������Ѿ�����string��stdio��stdlib�Ȳ��ʺ�����mcuƽ̨��ͷ�ļ����Ѿ����ÿ�Դ���̰߳�ȫ���������ʵ���滻
	0���ж����ȼ�����ѡ�÷���4����16����ռ���ȼ���0����Ӧ���ȼ��������ã�
	1��IO�������Ϊ�͵�ƽ��Ч���ߵ�ƽ��ֹ������IO����ʹ���ⲿ�жϡ�
	2��ʹ��C99ģʽ���룡
	3��I2Cʹ�����ʵ��
	4��FreeRTOS�������ʼ��ʹ�ö�̬�����ڴ棻FreeRTOS�������ļ������û�����������򣬾�����Ҫ����һ�㲻ʹ�������ʱ������Ӳ����ʱ������������ʱ�������
	5�������������ݴ�������еĿ���������ָ�롢�ṹ��ָ�뵱��������
	6�����ú�����������NULLʵ�Σ�������һ�������ֵ
	7�������紮�ڡ�PWM�ȵ�IO��ʼ�������ʼ�������ڣ����õ����ٳ�ʼ��
	8����������ֵ��0����ȷ����������󲢴�������Ϣ����������HAL���ͷ���ֵ�磺
		  HAL_OK       = 0x00U,
		  HAL_ERROR    = 0x01U,
		  HAL_BUSY     = 0x02U,
		  HAL_TIMEOUT  = 0x03U
	9��FSMC�Ŀ�1����3����4�ֱ������ⲿRAM��LCD����ģ��Ĭ�ϵģ�����
	10���ѱ�ģ�����������Ĭ�ϵĶ���������������
		
*/

/*��˵����
	1��������ʷ����ԭ�򣬱�MDK���̱���λGB2312���������ⲿ�ļ�д����ʱ��ѡ��GB2312������д
		��������Ѿ�ʹ��UTF-8�ȱ����д�˺ܶ�����ʱ��ֻ����notepad����½�һ�����ļ���ѡ��GB2312���룬Ȼ����ԭ��UTF-8�ȱ����ʽ��ԭ�Ľ��������Զ�תΪGB2312������
		
		
*/

/*
STM32F10xxϵ�������淶��

STM32F
	  101 = 		������
	  102 = 		USB�����ͣ� USB 2.0ȫ���豸
	  103 = 		��ǿ��
	  105��107 = 	������
			  T = 36��
			  C = 48��
			  R = 64��
			  V = 100��
			  Z = 144��
			  I = 176��
			   4 = 16KB(ld)
			   6 = 32KB(ld)
			   8 = 64KB(md)
			   B = 128KB(md)
			   C = 256KB(hd)
			   D = 384KB(hd)
			   E = 512KB(hd)
			   G = 1024KB(hd)
			    H = BGA��װ
				T = LQFP��װ
				 6 = -40~85��
			FLASH               RAM
			
			16K(ld)				6K			ld:2��USART��3��16λ��ʱ��+1��16λ������ƶ�ʱ����1��SPI��1��I2C��USB��CAN��1���߼���ʱ����2��ADC��DMA1��7ͨ����
			32K(ld)				10K
			
			64K(md)				20K			md:3��USART��4��16λ��ʱ��+1��16λ������ƶ�ʱ����2��SPI��2��I2C��USB��CAN��1���߼���ʱ����2��ADC��ͨ����������
			128K(md)			20K						(x8/xBϵ����1��2��3��4��ʱ��)��DMA1��7ͨ����
			
			256K(hd)			48K��64K	hd:3+2�����ڣ�8������16λ��ʱ��+2������16λ������ƶ�ʱ����2��������ʱ����3��SPI��2��I2S��2��I2C��USB��CAN��
			384K(hd)			64K				2���߼���ʱ����3��ADC��ͨ������������2��12bit DAC��1��SDIO��FSMC(100��144�ŷ�װ)��DMA1��7ͨ������2��5ͨ����
			512K(hd)			64K
*/

/*
������	BOOT1	BOOT0		��������
		  x		  0			FLASH
		  0		  1			ϵͳ������(ISP����)
		  1		  1			SRAM
*/

/*
��Ҫ 256K(hd) ������IC�������б�
	SDIO
	DAC
	FSMC
	DMA2
	
	��STM32F103ϵ��֮���л���������оƬʱ����Ҫ�������¼��
	1���� Device ���оƬ�ͺ�
	2���� C/C++ ����� Symbols ����ӦоƬ�ͺţ���ѡ��
		STM32F103x6 ���� STM32F103xB ���� STM32F103xE ����  STM32F103xG 
	3������һ����ɺ�������Զ����ˣ��ټ��һ�£��� Debug ����� ����Settings ����� Flash Download �������Ӧ��С���д����������㷨
	4���ڵ�ǰ���̵�CORE�ļ����� ֻ���� ��Ӧ��startup.s�ļ�������������Ϊstartup_stm32f103xb.s���Դ�����
*/

#define SYSTEM_SUPPORT_OS		0				/*�����Ƿ�ʹ��FreeRTOS������0����1������������������Ҫ�����޸ģ�
													FreeRTOS�汾��v10.3.1
													Ĭ�����������RAM��ջ��СΪ5KB�������޸ģ�
												ע�⣺��Ҫ��FreeRTOSConfig.h�����SYSTEM_SUPPORT_OS�궨����˴�����һ�£�����ϵͳ�������FreeRTOS�������л�SVC�жϺ������ܲ�������*/

#define SYSTEM_SUPPORT_Menu		1				/*ģ��̶����䣡�ṩһ���˵�ģ�壬��ϵͳ�����롢�����ִ�й��ܵı�־λ����ȫ�������*/
/*
	�������������Ƽ�100ms��������
	keyProcess(); 	//��ȡ��ֵ���뺯��������RTOS��ֱ�ӷ�һ��100ms�������񣻶��������100ms�������У�������Ѿ����ˣ� ���������Ϊ�����������������AD Key����������������ң�ء���ת��������
	menuProcess();	//�˵��������������ͬ��
*/
#define SYSTEM_SUPPORT_MyString	1				/*�ṩһ��ʵ����string.h�󲿷��ַ����������Ŀ�*/
/*�������ÿ�MyString.c�ļ����ע��
int mystrlen (const char *str);
char * mystrcat (char *dest, const char *src);
char * mystrncat (char *dest, const char *src, int n);
char * mystrcpy (char *dest, const char *src);
char * mystrncpy (char *dest, const char *src, int n);
int mystrcmp (const char *s1, const char *s2);
int mystrncmp (const char *s1, const char *s2, int n);
void * mymemset (void *s, int c, unsigned n);
void *mymemcpy(void *des,const void *src,size_t len);
char *mystrtok(char *s, const char *delim);
*/
int myatoi(const char *str);					/*�ṩһ���ַ���ת���ε�ʵ��*/
u16 sys_GetsysRunTime(u16* mins,u16* secs,u16* _10ms);/*�ṩ��ȡϵͳ����ʱ��ĺ��������忴Դ������ע��*/
#define SYSTEM_SUPPORT_sprintf	1				/*ģ��̶����䣡�����ұ���printf.h��github��Դ�ļ��������������ܱȽ�ȫ��
													Լռ6KB������stm32������������С����MCU�򿴡���������sprintfʵ�֡��ļ��������,��Ҫ�����ˡ�
													��Դ�ֿ��ַ��https://github.com/mpaland/printf
													�ṩAPI��
													int printf(const char* format, ...); 								����
													int printf_uart(unsigned char uart,const char* format, ...); 		�ã���ѡ���ʹ���
																		����ѡ���ѡ��UART1/UART2/UART3����Ҫ��ʹ����ش���
													int sprintf(char* buffer, const char* format, ...); 				�����ֽ���������
													int snprintf(char* buffer, size_t count, const char* format, ...); 	���ֽ��������ƣ�����ȫ
												ע�⣺����SYSTEM�ļ������ṩstrprintf.h�����ܱȽϵ�һ������С��
												*/
#define SYSTEM_SUPPORT_pid		0				/*�ṩһ��pid�㷨ʵ�ֿ⣬�����˻��ַ���ͱ��޻��֣��Լ���ѡ�Ĳ���ȫ΢�ֺ�΢�����У������÷���pid.h����*/
												/*�������ṩһ��һ�׵�ͨ�˲�ʵ�ֺ���*/
												/*һ�׵�ͨ�˲��� float FirstOrderLPF(float NewValue);*/
												

/*����main��ͷ�ļ�����������*/
#if SYSTEM_SUPPORT_OS
	#include "FreeRTOS.h"	//FreeRTOSʹ��,���ﲻҪ�Ҷ�	  
	#include "task.h"
	#include "TaskConfig.h"
#else
	#include "BareConfig.h"
#endif

#if SYSTEM_SUPPORT_Menu
	#include "sys_menu.h"
#endif

#if SYSTEM_SUPPORT_MyString
	#include "MyString.h"
#endif

#if SYSTEM_SUPPORT_sprintf
	#include "printf.h"
#endif

#if SYSTEM_SUPPORT_pid
	#include "pid.h"
#endif

/*_____MCU��������ѡ����_____*/
#define SYSTEM_MCO_PA8_OUT		0				/*����PA8ΪMCO�����Ĭ��ʱ��ԴΪHSE*/

/*����ʹ��RTC��ȷ��LSE������36.768kHz�ľ���ȷ��RTC��VBAT���õ�Դ
˵����	����Ҫ�����ú��������ã�ʱ�䣬���ӣ�����BKP
		Ĭ�Ͽ���RTC�����жϣ�ϵͳ�ڴ���ģʽ�¿�ѡ�����ӻ���
API:
	RTC_Set(2049,10,1,17,7,0); 				//����RTC���ں�ʱ�䣬������ʱ���룬2049��10��1�գ�17��07��0��
	RTC_Alarm_Set(2149,10,1,17,7,0);		//����RTC�������ں�ʱ�䣬������ʱ���룬2149��10��1�գ�17��07��0��
	
	typedef struct //ʱ��ṹ��
	{
		vu8 hour;
		vu8 min;
		vu8 sec;			
		//������������
		vu16 w_year;
		vu8  w_month;
		vu8  w_date;
		vu8  week;	
	}_calendar_obj;					 
	extern _calendar_obj calendar;				//�û��ã�RTC�ṹ�壬ʵ����ʱֻ��Ҫ������ṹ���ȡʱ�伴��
*/
#define SYSTEM_RTC_ENABLE		0				
/*����ʹ��CRCѭ������У��
���CRC����ģ��ʹ�ó����ġ�����̫����ʹ�õļ������ʽ��
X32 + X26 + X23 + X22 + X16 + X12 + X11 + X10 +X8 + X7 + X5 + X4 + X2 + X + 1
д��16���ƾ��ǣ�0x04C11DB7
API��������const uint32_t aDataBuffer[BUFFER_SIZE]; #define BUFFER_SIZE    114
	HAL_CRC_Accumulate(&hcrc, (uint32_t *)aDataBuffer, BUFFER_SIZE); //����ֵΪuint32_t�ļ�����*/
#define SYSTEM_CRC_ENABLE		1
/*
F103ϵ��������8����ʱ��������x8/xBϵ�н���1��2��3��4��ʱ����xE��������ȫ�˸���
�߼���ʱ��1��8����ʱ���жϣ�
	�߼�PWM��7·��������xxx���ţ���ӳ����xxx���ţ���ʽ��HAL F1�ֲ��225ҳ�ı�����
ͨ�ö�ʱ��2-5��2��5Ϊ32λ��
	��4·��������xxx���ţ���ӳ����xxx���ţ�����ʱ�жϣ����벶������Ƚϣ�PWM ����(��Ե���м����ģʽ)��������ģʽ��������������ж�
������ʱ��6��7������ʱ���жϣ���PWM�ȣ�
*/
#define STSTEM_TIM4_ENABLE		1			/*ģ��������ܣ����뿪����ʹ��ͨ�ö�ʱ��4���ṩʱ����Ĭ��10ms�����ж�*/
/*�ṩ����ͬ���ͼ�ʱ��ʱ����
	Timer_IT_flags._10msec_flag		//10�����־
	Timer_IT_flags._100msec_flag	//100�����־
	Timer_IT_flags._300msec_flag	//300�����־
	Timer_IT_flags._1sec_flag		//1���־
	Timer_IT_flags._1min_flag		//1���ӱ�־
	
	Timer_IT_flags._10msec			//10�������
	Timer_IT_flags._100msec			//100�������
	Timer_IT_flags._1sec			//1�����
	Timer_IT_flags._1min			//1���Ӽ���
*/

/*PWM������Ƚϣ�����ԭ����ǣ�ÿ����ʱ������Ψһһ��CNT����ֵ������ʱ��Դ��һ������Periodֵ�ͻ��������жϼ���ʱ�жϣ�
PWM�����ĸ�ͨ�����ĸ������ıȽ�ֵ��ÿ���Ƚ�ֵ�����CNT����ֵ�Ƚϣ��Ӷ�������·������PWM*/
#define STSTEM_TIM3PWM_ENABLE	1			/*ģ��������ܣ����뿪����ʹ��ͨ�ö�ʱ��3��Ĭ�ϲ������жϣ��ṩ��·PWM���*/
											/*����һ·Ĭ�ϸ����������������͵�ƽ��Ч��������������Ҫ�õ�TIM4��������������ͨ��4�ϣ�
											�ı�ռ�ձȿɵ���ȣ��ı�Ƶ�ʿɵ�����*/
											/*Ĭ�ϣ������������������ΪLOW��PWM1ģʽ			(CH1/PA6, CH2/PA7, CH3/PB0, CH4/PB1)*/
		#define STSTEM_TIM3PWM_REMAP_PARTIAL	0	/*��ʱ��3����������ӳ�䣬Partial remap  	(CH1/PB4, CH2/PB5, CH3/PB0, CH4/PB1)*/
		#define STSTEM_TIM3PWM_REMAP_ENABLE		0	/*��ʱ��3ȫ��������ӳ�䣬Full remap     	(CH1/PC6, CH2/PC7, CH3/PC8, CH4/PC9)*/
		#define STSTEM_TIM3PWM_CHANNEL_ENABLE	B0000_1000 /*���ͨ��ѡ�񣬹��ĸ�ͨ����ͨ���ıش�*/
													/*��ѡ  B0000_0001|B0000_0010|B0000_0100|B0000_1000	*/
		#define STSTEM_TIM3PWM_TI_ENABLE		0	/*�Ƿ�����ʱ��3�Ķ�ʱ�жϣ����Ǽ����ã�����һ�㲻��*/
		
		
		#define tim3prsc STSTEM_TIM3PWM_Period_5K		/*ѡ��ʱ�����Ƶ�ʣ�����������������������װֵΪ720��������ѡ��Ԥ��Ƶϵ����*/
			#define STSTEM_TIM3PWM_Period_2K	(50-1)
			#define STSTEM_TIM3PWM_Period_5K	(20-1)
			#define STSTEM_TIM3PWM_Period_10K	(10-1)
			#define STSTEM_TIM3PWM_Period_20K	(5-1)
			#define STSTEM_TIM3PWM_Period_50K	(2-1)
			#define tim3arr 720-1
		/*����API��
					HAL_TIM_PWM_Start(&TIM3_Handler,TIM_CHANNEL_2);		����TIM3��PWMͨ��2
					HAL_TIM_PWM_Stop(&TIM3_Handler,TIM_CHANNEL_2);		�ر�TIM3��PWMͨ��2������Դ�����ʹ����ͨ�����ر��ˣ���ʵ��
					
					����TIM3��PWMͨ��2��ռ�ձȰٷ���Ϊ88.8%��ֵ����0~100.0֮�䡣Ĭ�����ϼ�����Ĭ������Ϊ������ֵС�ڴ�ֵʱ����͵�ƽ��
					TIM3_set_Channel_Pulse(TIM3PWM_Channel_2,88.8);
					
					buzzer_bibi_once;			�û�ʹ�ã��������л�һ��
					define buzzer_bibi_on;		�û�ʹ�ã���������Ъ�л�����
					define buzzer_bibi_off;		�û�ʹ�ã���������Ъ�л��ر�
		*/


/*ͨ���ö�ʱ��2��16λ���ĸ�����ͨ�������ڣ����벶������Ƚϡ�PWM�������壬����;������DMA�ж�*/
#define STSTEM_TIM2_ENABLE		0			/*ͨ�ö�ʱ��2�������Զ���Ĭ�Ϸ�Ƶϵ��Ϊ72����ʼ��������PeriphCconfig.c���涨��*/
	#define STSTEM_TIM2_TI_ENABLE	1		/*�Ƿ�����ʱ��2�Ķ�ʱ�ж�*/
	
	#define STSTEM_TIM2_asPWMorCap	2		/*ѡ��ʱ��2��Ϊ...ע��PWM(����Ƚ�)�����벶������������������ܲ��ܹ��ã�*/
											/*д3��Ϊ�����������Ľ���ʹ�ã�ֻ��ʹ��CH1��CH2����PA15��PB3��Ĭ��ʹ����·���ش���������ֵΪ��·�����������ı�
												��������ʹ�õ�TIM2�Ķ�ʱ�жϣ�����򿪣����ڳ�ʼ��ʱ�Ѿ�Ĭ�ϴ�*/
											/*д2��Ϊ��ͨ��ʱ���ж�ʹ��*/
											/*д1��Ϊ���벶�񣺿��Ի�ȡ�ߵ�ƽ���ߵ͵�ƽ��ʱ�䣬Ĭ�ϲ���Ƶ�����˲�
												���벶��ʹ�õ�TIM2�Ķ�ʱ�жϣ�����򿪣����ڳ�ʼ��ʱ�Ѿ�Ĭ�ϴ�*/
											/*д0��ΪPWM��Ĭ��PWM1ģʽ�����ϼ������͵�ƽ��Ч��һ��������ռ�ձ�Խ��͵�ƽʱ��Խ��
												����˵����			û����ӳ��			���ֲ�����ӳ��			��ȫ��ӳ��
												TIM2�ĸ�ͨ����		PA0 PA1 PA2 PA3		����ǰ�������		PA15 PB3 PB10 PB11
												ע�⣺����PA2 PA3����2ռ�ã�PA0 PA1��ADCռ�ã�����TIM2��PWMֻ����ȫ��ӳ�䣡��
														��PB10 PB11����3ռ�ã�Ҫô���ô���3��Ҫô����3��ӳ��
											*/
			/*PWM����ȽϹ���ѡ��*/
			#define tim2arr STSTEM_TIM2PWM_Period_5K			/*ѡ��ʱ�����Ƶ�ʣ�Ԥ��Ƶϵ��Ϊ72������ѡ����װֵ��*/
				#define STSTEM_TIM2PWM_Period_1K	(1000-1)	/*ע�⣺������ѡ����װֵ��Ҳ��ռ�ձȵķֱ��ʣ�Ƶ�ʸ���ֱ��ʵͣ���֮��Ȼ����ѡ*/
				#define STSTEM_TIM2PWM_Period_2K	(500-1)
				#define STSTEM_TIM2PWM_Period_5K	(200-1)
				#define STSTEM_TIM2PWM_Period_10K	(100-1)
				#define STSTEM_TIM2PWM_Period_20K	(50-1)
				#define STSTEM_TIM2PWM_Period_50K	(20-1)
				#define STSTEM_TIM2PWM_Period_100K	(10-1)
				#define STSTEM_TIM2PWM_Period_200K	(5-1)
			#define STSTEM_TIM2PWM_CHANNEL_ENABLE	B0000_0001|B0000_0010 /*���ͨ��ѡ�񣬹��ĸ�ͨ������������򿪶��ͨ����PA15 PB3 PB10 PB11*/
			/*����API��
				HAL_TIM_PWM_Start(&TIM2_Handler,TIM_CHANNEL_2);		����TIM2��PWMͨ��2
				HAL_TIM_PWM_Stop(&TIM2_Handler,TIM_CHANNEL_2);		�ر�TIM2��PWMͨ��2������Դ�����ʹ����ͨ�����ر��ˣ���ʵ��
				
				����TIM2��PWMͨ��2��ռ�ձȰٷ���Ϊ88.8%��ֵ����0~100.0֮�䡣Ĭ�����ϼ�����Ĭ������Ϊ������ֵС�ڴ�ֵʱ����͵�ƽ��
				TIM2_set_Channel_Pulse(TIM2PWM_Channel_2,88.8);
			*/
			
			/*���벶����ѡ��*/
			#define STSTEM_TIM2_Cap_trigV	1			/*д1�ߵ�ƽ����һ�����벶��д0�෴��д2˫���ش���*/
			#define STSTEM_TIM2_Cap_Channel	B0000_0001	/*ѡ�����ĸ�ͨ�������벶��ֻ����ѡһ����*/
			/*����API��
				float Peek_TIM2_Cap_Val();		��ȡ���һ��TIM2���벶�������ʱ�䣬��λ ���룬�������õĲ����ؽ��У�������ʱ��ص��ô˺���
			*/
			
			/*�������빦��ѡ��*/
			// 4 : 			ʹ�ö�ʱ���������ӿڲ���AB��������غ��½��أ�һ������*4
			// ENCODER��	����������(ת��һȦ���������)
			// SPEEDRATIO��	��������ȣ��ڲ����ת��Ȧ�����������ת��Ȧ���ȣ������ٳ��ֱȣ�������һ��͵��ת��һ�£���ֱ�Ӱѱ�������װ��������ϣ�
			#define ENCODER     300    	// ����������
			#define SPEEDRATIO  1   	// ������ٱ�
			#define PPR         (SPEEDRATIO*ENCODER*4) // Pulse/r ÿȦ�ɲ���������������ö���
			/*����API��
				�õ���ǰ����ֵ��int32_t peek_TIM2_Encoder_Value(void); //���ڱ�ʾ��������ǰ�ľ���λ��
				�ٶȣ�ֻ��ȥ��ʱ������жϺ���HAL_TIM_PeriodElapsedCallback��TIM4����һ���ٶȱ������� peek_TIM2_Encoder_Speed()���ص��ٶ�ֵ ��λ ת/��
			*/

/*
	ADC��STN32����12λ��αƽ��ͣ���ADC1��2��3������ADC1��ADC2������һ���������ڲ�ͨ������
	�������1MHz��1us����ADʱ��14MHz����ߣ�������ʱ��Ϊ1.5�����ڵõ�������ת��ʱ��Ϊ (����ʱ�� + 12.5������)������ʱ�䳤��������ȸߣ�
	�ο���ѹ Vref-��������VSSA��Vref+������ 2.4V~VDDA��ADC�����ѹ����С��Vref+��Ĭ��Vref+Ϊ3.3V���������и���ת������
	ADC1���ʾ���һ��ADת������16·ѡ����������ADC1ͬһʱ�̲���ֵֻ����һ����������ڹ�������ɨ��ģʽ���޷���֪��ǰ�������һ·�ģ�һ��ADģ��һ��ֵ
	ADC1��ͨ��������ӳ�䣺
	ͨ����	0	1	2	3	4	5	6	7	8	9	10	11	12	13	14	15	   16		     17
	IO	��	A0	A1	A2	A3	A4	A5	A6	A7	B0	B1	C0	C1	C2	C3	C4	C5	�ڲ��¶�	�ڲ��ο���ѹ
*/
#define SYSTEM_ADC1_ENABLE		0			/*����ADC1*/
	#define SYSTEM_ADC1_useScan		1		/*��������������ɨ�裬������ã�������涨�������ͨ�����ŵ����������ʹ��DAM1��ͨ��1��ת������ŵ�Ŀ��λ��
												��������ã���Ϊ��������ĵ���ת��*/
		#define SYSTEM_ADC1_useCircular	1	/*ֻ��ɨ��ģʽ����Ч���������Զ�ѭ��ADCת����ֻ��Ҫ�жϱ�־λ�Ͷ������ɣ�����Ҫ����ֶ���������һ��ADCת��*/
	#define SYSTEM_ADC1_useChanlNum	3		/*���干�ö���·ͨ��*/
	#define SYSTEM_ADC1_useChanl	B1in16|B4in16|B5in16 /*���干����Щͨ������дB1in16~B15in16���ֱ����ͨ��0~14������InrTemp(�ڲ��¶�ͨ��)
														����16��ADC1ͨ�������ڲ��¶ȱ�־���Բ����ã�*/
													/*���ֻ�òɼ��ڲ��¶ȣ�����������ͨ����Ӧ���ã�SYSTEM_ADC1_useChanlNumΪ1  SYSTEM_ADC1_useChanl��ΪInrTemp*/
		#define InrTemp B16in16
		extern u16 adValue[SYSTEM_ADC1_useChanlNum];/*ɨ��ģʽ��DMA1��ADCת��������͵�Ŀ��λ��*/
		extern u8 adValueDone; 						/*ɨ��ģʽ��ת����ɱ�־*/
	/*���õ�API�����صĶ���ԭʼADCֵ
			�������� SYSTEM_ADC1_useScan ɨ��ģʽ��������һ�Σ��Զ�ɨ�����й��������ͨ�����������ʺϿ���
						�Զ���DMA1ͨ��1���͵�adValue[]������λadValueDone
				��ȡ˳��
					���� HAL_ADC_Start_DMA(&ADC1_Handler, (uint32_t*)&adValue,SYSTEM_ADC1_useChanlNum); һ������һ�ι�����ȫ��ͨ����ת��
						����1����ѹ���������ͨ��ת��һ�飬Ȼ���жϱ�־λadValueDone������adValue[]ȡ��������
					��� SYSTEM_ADC1_useCircular �򿪣�ֻ��Ҫִ��һ�Σ�һ�Σ� HAL_ADC_Start_DMA(&ADC1_Handler, (uint32_t*)&adValue,SYSTEM_ADC1_useChanlNum); ����
					
					�ж� adValueDone �Ƿ�Ϊ1������� adValue[x] ��ֵ���ɣ�������� �ڲ��¶� ͨ������ֵ������adValue[SYSTEM_ADC1_useChanlNum-1]
					��ȡ���� adValueDone ����
					ֹͣת��Ϊ HAL_ADC_Stop_DMA(&ADC1_Handler);
					���ӣ�
						char ADC_buf[20];
						if(adValueDone)
						{
							adValueDone = 0;
							//HAL_ADC_Stop_DMA(&ADC1_Handler);
							sprintf(ADC_buf,"adValue:%d %d %d",adValue[0],adValue[1],adValue[2]);
							LCD_ShowString(10,180,16,(u8*)ADC_buf,0);
						}
			����û������ SYSTEM_ADC1_useScan һ�δ���һ��ͨ�����ֶ�ȡ�����������ʺ�����
				��ȡ˳��
					���� u32 Get_Adc_Average(u32 ch,u8 times); ����ֵΪ����ADCֵ
					���� ch ͨ�� �β�ѡ����ת����ͨ������ѡADC_CHANNEL_0~15������ΪADC_CHANNEL_TEMPSENSOR������result[0]���汾�α�ͨ����ת�����
					���ӣ�
						adValue[0] = (u16)Get_Adc_Average(ADC_CHANNEL_0,10);
						adValue[1] = (u16)Get_Adc_Average(ADC_CHANNEL_3,10);
						adValue[2] = (u16)Get_Adc_Average(ADC_CHANNEL_4,10);
						sprintf(ADC_buf,"adValue:%d %d %d",adValue[0],adValue[1],adValue[2]);
						LCD_ShowString(10,180,16,(u8*)ADC_buf,0);
					
			ע�⣺�ɼ��¶�ͨ�����ص���ADC��ԭʼֵ���� float Get_Temprate(u32 adcx) ��ԭʼֵת��Ϊʵ���¶�ֵ(float����)
	*/
		
#define SYSTEM_IWDG_ENABLE		1			/*�����������Ź���Ĭ��1S��ι�����ڣ�Ĭ����TIM4��ʱ�ж���ι������IWDG�ؿ�TIM4*/
											/*ע�����Ź��͵͹��Ĵ���ģʽ����ͬʱ��������Ϊ���Ź����ܹرգ����Ź���λ�ỽ�ѵ͹���״̬*/

/*DMA�÷����о�*/
/*
����ǰ ���Ȳ鿴 ��DMA1��ͨ��һ����
DMA���õ�һ����̣����Դ��������䵽UART1��TXΪ���ӣ�USART1��TX������DMA1��ͨ��4�ϣ�
	��������
		DMA_HandleTypeDef  UART1TxDMA_Handler;      //DMA���
	��ʼ�����У�
		__HAL_RCC_DMA1_CLK_ENABLE();			//DMA1ʱ��ʹ�� 
		
		__HAL_LINKDMA(&UART1_Handler,hdmatx,UART1TxDMA_Handler);    		//��DMA��USART1��ϵ����(����DMA)
		//����˵����������(�����Ƿ��ͷ����ǽ��շ�) �� �������е�DMA_HandleTypeDef���ͱ��� �� DMA1���
		
		UART1TxDMA_Handler.Instance=DMA1_Channel4;                          //ͨ��ѡ��
		UART1TxDMA_Handler.Init.Direction=DMA_MEMORY_TO_PERIPH;             //�洢��������
											//����ѡ �� DMA_PERIPH_TO_MEMORY ���赽�洢�� �� DMA_MEMORY_TO_MEMORY ��������������
		UART1TxDMA_Handler.Init.PeriphInc=DMA_PINC_DISABLE;                 //���������ģʽ ����һ�㶼�Ƿ���������ַ������
		UART1TxDMA_Handler.Init.MemInc=DMA_MINC_ENABLE;                     //�洢������ģʽ ������һ�㶼����������ַҪ����
		UART1TxDMA_Handler.Init.PeriphDataAlignment=DMA_PDATAALIGN_BYTE;    //�������ݳ���:8λ ����16λ ����32λ ���衢�洢��Ҫһ�£������ܽ���
		UART1TxDMA_Handler.Init.MemDataAlignment=DMA_MDATAALIGN_BYTE;       //�洢�����ݳ���:8λ
		UART1TxDMA_Handler.Init.Mode=DMA_NORMAL;                            //��ADCΪ�������ADCѡ������ģʽ��������ѭ�����������������ģʽ������������ģʽ
		UART1TxDMA_Handler.Init.Priority=DMA_PRIORITY_MEDIUM;               //�е����ȼ� ��ߡ��ߡ��С���
		
		HAL_DMA_DeInit(&UART1TxDMA_Handler);   								//DMA��λ
		HAL_DMA_Init(&UART1TxDMA_Handler);									//DMA��ʼ��
	�жϳ�ʼ��������ѡ��
		HAL_NVIC_SetPriority(DMA1_Channel1_IRQn, 3, 0);                     //DMA�ж����ȼ�
		HAL_NVIC_EnableIRQ(DMA1_Channel1_IRQn);                             //ʹ��DMA�ж�
	�жϻص�������
		//DMAͨ��1�жϷ���������ɴ���һ��ʱ���ж�
		void DMA1_Channel1_IRQHandler(void)
		{
			HAL_DMA_IRQHandler(&ADC1rxDMA_Handler); //����жϱ�־���������𶯣�
		}

		//HAL_DMA_IRQHandler�Ļص�������ADCת��������й�����ͨ������жϺ���
		void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
		{
			//Ҫ�ɵĻ�
		}
		
	��ѯ���õ������Ƿ���ɣ���ͨ��4Ϊ������ûʵ�����
		if(__HAL_DMA_GET_FLAG(&UART1TxDMA_Handler,DMA_FLAG_TC4))//�ȴ�DMA1ͨ��4�������
		{
			__HAL_DMA_CLEAR_FLAG(&UART1TxDMA_Handler,DMA_FLAG_TC4);//���DMA1ͨ��4������ɱ�־
			//Ҫ�ɵĻ�
		}
	
����API��
	�õ���ǰ��ʣ�������ݴ�����	u16 pro = HAL_DMA_GET_COUNTER(&UART1TxDMA_Handler); //����һ�δ���count�����ݣ���ȡ������ʣ�µģ� 1-pro/count �ǽ��Ȱٷֱ�
	
	���ڴ��ڣ�	ʹ��DMA����		ԭ�ͣ� HAL_StatusTypeDef HAL_UART_Transmit_DMA(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size)
									���ӣ�HAL_UART_Transmit_DMA(&UART1_Handler,SendBuff,SEND_BUF_SIZE);
				ʹ��DMA����		ԭ�ͣ� HAL_StatusTypeDef HAL_UART_Receive_DMA(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size)
	
	���ڸ������裺	�ο�����ADC�����DMA�÷�ע�⣬��periphconfig.c�����ADC DMA���жϷ��������Լ�����
*/


/*�������ڣ�x8/xBϵ�����������ڣ���ò�����2Mλÿ�롣Ĭ�Ͼ�Ϊ��8λ���ݣ�1λֹͣ����У�飬�շ�ģʽ�����������ж�*/
/*���ڷ������API����SYSTEM_SUPPORT_sprintf�궨���ע��*/
/*ע������2��3�Ľ��ջص�����û�в�ȫ����ʱ�ٲ����ʹ���1��ͬ��*/
#define SYSTEM_UART1_ENABLE			1		/*ʹ�ܴ���1	       TX/PA9, RX/PA10		*/
#define SYSTEM_UART1_REMAP_ENABLE	0		/*����1������ӳ�䣺TX/PB6, RX/PB7		*/
#define SYSTEM_UART1_BOUND			115200	/*����1������*/

/*ע������2��Ŀǰ�����ã�û�з�Ӧ����֪����HAL�����⻹��оƬ����*/
#define SYSTEM_UART2_ENABLE			0		/*ʹ�ܴ���2	       TX/PA2, RX/PA3		*/
#define SYSTEM_UART2_REMAP_ENABLE	0		/*����2������ӳ�䣺TX/PD5, RX/PD6���������ã�������C8T6�޴�����*/
#define SYSTEM_UART2_BOUND			115200	/*����2������*/

#define SYSTEM_UART3_ENABLE			0		/*ʹ�ܴ���3	       TX/PB10, RX/PB11		*/
#define SYSTEM_UART3_REMAP_ENABLE	0		/*����3������ӳ�䣺TX/PD8,  RX/PD9���������ã�������C8T6�޴�����*/
#define SYSTEM_UART3_BOUND			115200	/*����3������*/
/*���õ�API�� Ŀǰ���ڽ��յ��������һ��ӿ�����ݹ������������Ǵ洢����ʱջ�����������ʱ�Ҳ��������С����������û������
	���ͣ�	������� SYSTEM_SUPPORT_sprintf ������ã���Ҫ��printf��
				������UART1~UART3
				printf_uart(UART1,"Fault : %d\t",x);
				Ҳ������	sprintf(char* buffer, const char* format, ...); 				�����ֽ���������
							snprintf(char* buffer, size_t count, const char* format, ...); 	���ֽ��������ƣ�����ȫ
			���û������ SYSTEM_SUPPORT_sprintf ����������£�
			������UART1_Handler~UART3_Handler �� �������ݵ��ַ�����ָ�� �� ���ݳ���(�ֽ���} �� ��ʱʱ��
				HAL_UART_Transmit(&UART1_Handler,UART_BUF,12,10); 				���ͺ���
				while(__HAL_UART_GET_FLAG(&UART1_Handler,UART_FLAG_TC)!=SET); 	�ȴ����ͽ���
	���գ�������ֻ��Դ���1˵������һ�ν����ַ���Ҫ����200���ֽڣ������������֮������ݣ�
			����Э������(Ĭ��Э��0)��USART1_SetMode(0);	����1����Э�飺0Ϊֻ������'\r\n'��β�����ݣ�������ȥ��\r\n���棩��1Ϊ��FIFO�Ƚ��ȳ��Ļ��λ���ʵ�ֽ�����������ԭ�����棬��Э��
				����Э�����ÿ�����ʱ�л����л�����շ�ʽҲ�������˵������
			ͳһ���պ����� ����returnOK�������ݿ���ȡ����֮ΪReturnErr��is_print���Ƿ��ӡ���յ������ݣ�buf���ڴ�Ž��յ������ݣ������ȸ����㹻�������
							char sys_USART1_RX_Fetch(u8 is_print, char* buf)
							������
								char buf4uart1[(USART1_RX_BUF_MaxNum > USART1_RX_FIFO_MaxNum) ? (USART1_RX_BUF_MaxNum):(USART1_RX_FIFO_MaxNum)];
								if(sys_USART1_RX_Fetch(FALSE, buf4uart1) == ReturnOK)
								{
									printf_uart(UART1,"%s-",buf4uart1);
									printf_uart(UART1,"%d",mystrlen(buf4uart1));
								}
			����������Э��0��1�Ľ���ϸ�ڣ��Ѿ���sys_USART1_RX_Fetch()��ʵ�֣�һ�㲻�ÿ�
			Э��0��
				�����������С���ã�#define USART1_RX_BUF_MaxNum 200 �����������洮�ں궨��������
				�ж��Ƿ�������һ�Σ�USART1_isDone		�����ж��Ƿ�������һ�� ���ӣ� if(USART1_isDone){��ʾ�������һ��}
				��ѯ���ν������һ�κ���յ����ַ�������USART1_RX_ByteNum u8���� ������"\r\n"�����ַ���
				���ջ�������	USART1_RX_BUF[x] ��x : 0~USART1_RX_ByteNum
				���ܳɹ�һ��֮�󣬴���������֮���������ɱ�־��USART1_SetUnDone;
			Э��1��
				��FIFO���������ձ������ݣ�FIFO��ʼ��������sys.c����Ĵ��ڳ�ʼ��������
				�����������С���ã�#define USART1_RX_FIFO_MaxNum 200 �����������洮�ں궨��������
				while (!fifo_is_empty(Uart1_fifo))
				{
					char/int/float/struct... fifodata;
					fifo_get(Uart1_fifo, &fifodata);	//fifodata����Ϊ�����ַ��͡����Ρ������͡��ṹ���͵ȵ�
					printf_uart(UART1,"%c",fifodata); 
				}
				����û��Э�飬ֻ�Ǵ��棬����û�н�����ɱ�־
				
*/

/*����Ӳ��SPI��x8/xBϵ��������SPI�����18Mλÿ��
Ĭ�ϣ�����ֻ������һ������������ö��SSʹ�ܶˣ����ṩ������ӳ�䣬Ĭ��һ�η��Ͱ�λbits���ݣ�SS�����û��������壡
		masterģʽ��MSB First��SS�͵�ƽѡ������
		SCK����ʱ��Ϊ�ߵ�ƽ(ʱ�Ӽ���CPOL=1)��Ĭ�ϣ���
			��ʹ�õڶ����������ݱ�����(ʱ����λCPHA=1)���������� SCK ��ż�����ز�����Ĭ�ϣ�
			��ʹ�õ�һ���������ݱ�����(ʱ����λCPHA=0)���������� SCK ���������ز���
���ţ�
	SPI1->CS	SPI1->CLK	SPI1->MISO	SPI1->MOSI 	������������ 	SPI2->CS	SPI2->CLK	SPI2->MISO	SPI2->MOSI
	PA4			PA5			PA6			PA7					PB12		PB13		PB14		PB15
*/
#define SYSTEM_SPI1_ENABLE		0		/*ʹ��SPI1*/
#define SYSTEM_SPI2_ENABLE		0		/*ʹ��SPI2*/
/*�ṩAPI��
	�û��Զ�SS���ţ�
		��PeriphConfig.c�����
			sys_SPI1_SS_io_Init();		���и���
			sys_SPI2_SS_io_Init();		���и���
		�Լ� ��PeriphConfig.h�����
			#define	SPI1_CS PAout(4)	���и���
			#define	SPI2_CS PBout(12)	���и���
	д��������(Ŀǰֻд��SPI1��SPI2���Ҫ�õĻ�ͬ��)
		u8 SPI1_ReadWriteByte_8Byte(u8 TxData) 		��дһ���ֽ�
		u8 SPI1_ReadWriteByte_16Byte(u8* TxData) 	��д�����ֽڲ����أ�����һ������2�ֽڵ�u8*ָ��
		u8 SPI1_WriteByte_8Byte(u8 TxData)			дһ���ֽ�
		u8 SPI1_WriteByte_16Byte(u8* TxData)		��д�����ֽڣ�����һ������2�ֽڵ�u8*ָ��
		���ӣ�
			u8 Max7219_adr_data[Max7219_regNum][2] = 
			{
				{0x09,0xFF},
				{0x0A,0x08},
				...
			}
			for(i = 0;i < Max7219_regNum;i++)
				SPI1_WriteByte_16Byte(Max7219_adr_data[i]);
	
	����SPI�ٶȺ����� APB2Ϊ72MHz��APB1Ϊ����ƵΪ36Mhz
		void SPI1_SetSpeed(u8 SPI_BaudRatePrescaler);	//SPI1��APB2��Ƶ����
		void SPI2_SetSpeed(u8 SPI_BaudRatePrescaler);	//SPI2��APB1��Ƶ����
*/

/*�͹���ģʽ��
˯�ߣ� WFI�������룬�����жϻָ���CPUʱ�ӹأ���������ʱ��ά��																		�������ã�
ֹͣ��HSI��HSEʱ�ӹأ���ѹ���������������ã���һ�ⲿ�жϻ��ѣ����͵���ֵΪ20uA														�������ã�
������HSI��HSEʱ�ӹأ���ѹ�������أ�SRAM�ͼĴ������ݶ�ʧ������Դ���ƼĴ����ͱ���������Ӱ��
		����������WKUP���������أ�RTC�����¼�����λ���������Ź���λ�����������͵���ֵΪ2uA��Ϊ����ģʽ����� 	�����ڿ��ػ�		�����ã�
		WKUP ��PA0
*/
#define SYSTEM_StdbyWKUP_ENABLE	0		/*ʹ�ô���-�͹���ģʽ��ռ��0���ⲿ�жϣ�*/
										/*ע�����Ź��͵͹��Ĵ���ģʽ����ͬʱ��������Ϊ���Ź����ܹرգ����Ź���λ�ỽ�ѵ͹���״̬*/
/*������ SYSTEM_StdbyWKUP_ENABLE ��PA0��ΪWKUP������Ĭ�ϳ���3��������״̬���ٴΰ�����ָ����������ģʽ������PA0���ⲿ�ж���*/
//����PA0������Ϊ�ߵ�ƽ������3s���ɿ�����ʱһ�루��ʱ�����������ݵȹػ�ǰ��׼������������״̬���ػ������ٴΰ��¿���
/*WKUP IO��������������裬������ʱSTM32�ڲ��Ѿ�����*/

/*��ͬ������FLASH��֯��ʽ��
С������32��	1K�ֽ�/ҳ
��������128��	1K�ֽ�/ҳ
��������256��	2K�ֽ�/ҳ
*/
#define SYSTEM_FLASH_IAP_ENABLE	0		/*���ö��ڲ�FLASH����ռ���*/
	#define STM32_FLASH_WREN	1		/*����д���ܣ�����ֻ����д*/
	#define STM32_FLASH_SIZE 	64 		/*��ѡSTM32��FLASH������С(��λΪKB)*/
	#define FLASH_SAVE_ADDR  0X0800F000					//����FLASH �����ַ(����Ϊҳ���׵�ַ���ұ���Ϊ2�ı���������ֵҪ���ڴ�����ռ��FLASH�Ĵ�С+0X08000000)
	#define FLASH_SAVE_ADDR1 (0X08000000 + (u32)(60*1024))
/*����API�������س���ʱ��Ҫ���� ����оƬFLASH��ֻ�����г����������
	ע�������ñ����ܺ���ϵͳ��ʼ�������н�������濪��������һ��������һ��u16�ı����ᴢ�������һ�������ڶ���ҳ
	����	const u8 TEXT_Buffer[]={"STM32F103 FLASH TEST"};	//���ڴ��������
			u8 datatemp[sizeof(TEXT_Buffer)];					//���ڽӶ���������
	д����һ��д�볤�����Ϊһ��ҳ���ֽ�����������С������Ϊ1KB�����ڴ�������Ϊ2KB���������һ�����������ֽ�Ϊ��λ��
		STMFLASH_Write(	FLASH_SAVE_ADDR1,	(u16*)TEXT_Buffer,	sizeof(TEXT_Buffer));
	����STMFLASH_Read(	FLASH_SAVE_ADDR1,	(u16*)datatemp,		sizeof(TEXT_Buffer));
*/

/*hdϵ�����裬DAC�������ͨ�� PA4��PA5��Ĭ�ϳ�ʼ��Ϊ12λ�Ҷ��룬�ٶ����Ϊ250K���ң������Χ 0~Vref+��Ĭ��Vref+Ϊ3.3V���������и���ת������*/
/*��ѡ��� �������� �� ���ǲ����� ��Ĭ�ϲ������ⲿ��������ѡ����Դ�ڳ�ʼ���������޸ģ��ж�ʱ���жϺ��ⲿ�ж���9��*/
#define SYSTEM_DAC_OUT1_ENABLE	0
#define SYSTEM_DAC_OUT2_ENABLE	0
/*����API:
	����ͨ��1�����ѹ,vol:0~3.30V
		void DAC_Set_Ch1_Vol(float vol)
	����ͨ��2�����ѹ,vol:0~3.30V
		void DAC_Set_Ch2_Vol(float vol)
*/

/*hdϵ�����裬�����ߣ���λ�����ߣ�ʱ���ߺ������ߣ���SDIO��ߴ����ٶ�12M�ֽ�ÿ�룬Ŀǰֻ֧������SD��*/
/*֧�ֵ����ֿ���SD2.0 ����������SDHC�����32G����SD2.0 ��׼��������SDSC����� 2G����SD1.x ���� MMC ����*/
/*
��ʼ�����ȡ���Ŀ���Ϣ���ڣ�
	HAL_SD_CardInfoTypeDef  SDCardInfo;	//SD����Ϣ�ṹ��
	��Ա��
		uint32_t CardType;             			�����ͣ�						Specifies the card Type
														CARD_SDSC					SD Standard Capacity
														CARD_SDHC_SDXC				SD High Capacity <32Go, SD Extended Capacity <2To
														CARD_SECURED
		uint32_t CardVersion;                 	���汾��CARD_V1_X��CARD_V2_X	Specifies the card version
		uint32_t Class;                        	������							Specifies the class of the card class 
		uint32_t RelCardAdd;                  	����Ե�ַ						Specifies the Relative Card Address
		uint32_t BlockNbr;                     	���������洢���ڲ����£�		Specifies the Card Capacity in blocks
		uint32_t BlockSize;                   	���С���洢���ڲ����£�		Specifies one block size in bytes
		uint32_t LogBlockNbr;                 	�߼�������						Specifies the Card logical Capacity in blocks
		uint32_t LogBlockSize;                	�߼����С��������Ŀ��			Specifies logical block size in bytes
		ע������ֻ��Ҫ��ע�߼�����߼����С���ɣ�������SD���ڲ������飬�߼�����߼�����һ���£�һ���߼���Ϊ�˱�֤���ݶ���512�ֽڴ�С
			BLOCK SIZE �� 8 ��ÿ��BLOCK��8������������Ǵ洢���ڲ����£��û������ģ�
			Ҳ��������ֻ���ģ�
				SECTOR SIZE ��һ��Ϊ512�ֽ�
				SECTOR COUNT�������������ֽ���/512
	
	HAL_SD_CardCIDTypeDef SDCard_CID;  //SD������CID
	��Ա��
		__IO uint8_t  ManufacturerID;  ������ID		Manufacturer ID
		__IO uint16_t OEM_AppliID;     OEM/Application ID
		__IO uint32_t ProdName1;       Product Name part1
		__IO uint8_t  ProdName2;       Product Name part2
		__IO uint8_t  ProdRev;         Product Revision
		__IO uint32_t ProdSN;          Product Serial Number
		__IO uint8_t  Reserved1;       Reserved1
		__IO uint16_t ManufactDate;    Manufacturing Date
		__IO uint8_t  CID_CRC;         CID CRC
		__IO uint8_t  Reserved2;       Always 1
*/
/*
���ţ�
PC8			SDIO_D0
PC9			SDIO/D1
PC10		SDIO_D2
PC11		SDIO_D3
PC12		SDIO_CK
PD2			SDIO_CMD
*/
/*��ע�����ÿ�����DMA��дSD����������ʡʱ�䣬��д��ʱ��Ͳ��ù��ж���*/
#define SYSTEM_SDIO_SD_ENABLE	0
/*�ײ�API�������Ƽ�ֱ�Ӷ�д��Ҫ���ļ�ϵͳFATFS�����ļ���д������SDIO��SD��ʼ������FATFS��ʼ���
	һ����Ĵ�С��SDCardInfo.LogBlockSize
	SD�����������SDCardInfo.LogBlockNbr
	u8 SD_ReadDisk(buf,secaddr,seccnt);			//��ȡ�ӵ�secaddr�鿪ʼ��seccnt��������ݣ����ص�ַ��buf�������һ����Ϊ512KB��buf������׼�����㹻�ռ䣩
												//���� HAL_OK ��ֵΪ0�� Ϊ�ɹ�������Ϊʧ��
														
	u8 SD_WriteDisk(buf,secaddr,seccnt);		//��buf�ڵ����ݴ�secaddr�鿪ʼд�룬����дseccnt����
												//���� HAL_OK ��ֵΪ0�� Ϊ�ɹ�������Ϊʧ��
	
	void show_sdcard_info(void);				//ͨ������1��ӡSD�������Ϣ
	
	����SD���ݣ���λΪ�ֽڣ���
		uint64_t CardCap = (uint64_t)(SDCardInfo.LogBlockNbr)*(uint64_t)(SDCardInfo.LogBlockSize);	 //����SD����������λΪ�ֽڣ�
		CardCap>>20 //��Ϊת��ΪMB��λ
*/

/*ʹ��FATFS�ļ�ϵͳ����SD����FATSF֧��FAT12/FAT16/FAT32/exFAT����������API˵������http://elm-chan.org/fsw/ff/00index_e.html*/
/*������أ��� ffconf.h �ļ���
	ע�⣺	Ĭ��û��֧�����·�����������FATFS�����ļ��ڴ�
			Ĭ������֧��4���ļ��豸��Ĭ��ʹ��UTF-8����
	���ã�	��������Щ�豸������DEV_ExFLASH���ⲿFLASH��MMC/NAND/SPI FLASH�ȣ���DEV_SD��DEV_InrFlash���ڲ�FLASH����DEV_USB�ȵ�
			��diskio.c���涨���д������Щ�豸�ĵײ㺯�������ײ㺯����Ӧ�ò㲻Ӧ���ã�
				DSTATUS disk_initialize (BYTE pdrv);
				DSTATUS disk_status (BYTE pdrv);	//���ڴ洢�豸�Լ�ʵ�ֵĶ�д�����ڲ�����æ�жϣ����������ȡ�豸״̬��������
				DRESULT disk_read (BYTE pdrv, BYTE* buff, LBA_t sector, UINT count);
				DRESULT disk_write (BYTE pdrv, const BYTE* buff, LBA_t sector, UINT count);
				DRESULT disk_ioctl (BYTE pdrv, BYTE cmd, void* buff);
	���ã�	��ffsystem.c�����Ѿ�����ʵ�ֵ��ڴ������ͷź�����Ĭ����STM32�ڲ���RAM����Ҫʹ���ⲿRAM��ȥ�ֶ���Ϊ ExRAM1
	���ã�	FATFS�������ļ�����һ��û����ȫ���úã�ffconf.h��������RTOS֧��
*/
#define SYSTEM_FATFS_ENABLE	0
/*��ʼ�����裺
	Ҫ���ģ��ڳ�ʼ��ϵ�������FATFS��ʼ��SD��
			��Ϊÿ���ļ��豸�������ռ�
			����
			
			�����ļ��������òο�ԭ��FATFS������� fattester.c �� exfuns.c ����Ļ�ȡʣ��ռ䡢ʶ���ļ����͡��õ��ļ��д�С���ļ����ļ��и��Ƶ����õ�API�ȵ�
			
			FATFS����API���ο�ԭ�ӵģ���������API���ο��ٷ��ĵ���
*/


/*hdϵ�����裬FSMC*/
/*FSMCΪ16λ�����ߣ���Ϊ�ĸ�256MB�Ŀ飨28����ַ�ߣ�����ַ��0x6000 0000��ʼ���ڶ����鿪ʼ��0x7000 0000���Դ����ƣ���ÿһ���Ϊ�ĸ�64MB������BANK1~4��*/
/*��һ��������NOR/SRAM���ڶ�������������NAND�����ĸ�������PC������һ����NOR FLASH�����������������������NAND FLASH������*/
/*
һ��ӷ�����CEǰ���һ��N����ʾCE����Ч������ͬ��
	FSMC			SRAM					LCD
	NEx				NCE����ѡ�У�			CS����ѡ�У�
	NOE				NOE����ʹ�������		RD���Ͷ���
	NWE				NWE���߶���д��			WR����д��
											RS�������ݵ���������ɽ���FSMC��һ����ַ����A10
	NUB				NUB����ѡ�߰�λ��
	NLB				NLB����ѡ�Ͱ�λ��
	A[x:0]			A[x:0]����ַ��������
	D[15:0]									D[15:0]�����ݣ�
*/
/*ԭ�ӵ�FSMC����LCD���̵Ľ��ͣ�ʱ��ѡ��ģʽA��RS���ӵ���A10
	typedef struct
	{
		vu16 LCD_REG;	//0111 1111 1110 0X7FE
		vu16 LCD_RAM;	//1000 0000 0000 0X7FE+0x02
	}LCD_TypeDef;
	#define LCD_BASE        ((u32)(0x6C000000 | 0x000007FE))
	#define LCD             ((LCD_TypeDef *) LCD_BASE)
	
	0x7FEΪ��	0111 1111 1110����ΪFSMCѡ����16λģʽ��ʵ�ʵ�ַ��Ϊ0x7FE������1��
	����֮��  0011 1111 1111 ��ΪLCD->LCD_REG�� ʵ�ʵ�ַ�� �������ʱA10Ϊ0��LCD->LCD_RAM�ĵ�ַΪLCD->LCD_REG��ַ+2
	LCD->LCD_REG �ĵ�ַ�� 0011 1111 1111		A10Ϊ0 	RS�͵�ַ
	LCD->LCD_RAM �ĵ�ַ�� 0100 0000 0001		A10Ϊ1	RS������
	������������ݾ����ֿ���
	
	Ȼ���д������д��ص�CS��WR��RD�ŵȵĵ�ƽ��FSMC�Զ����ã�
		д��	LCD->LCD_REG = LCD_Reg;				//Ҫд�ļĴ�����ַ 
				LCD->LCD_RAM = LCD_RegValue;		//д��һ��16λ����
		����	LCD_WR_REG(LCD_Reg);				//��д�Ĵ�����ַ
				vu16 LCD_RegValue = LCD->LCD_RAM;	//�ٶ���һ��16λ����
*/
/*������FSMCͬʱ����LCD��SRAM������MCU��˵���ⲿFLASH������SPI��FLASH�����ļ�ϵͳʹ�ã����ͼ����USB U�̻���IAP�ȵȣ���������NOR/NAND֮�������Ƕ�MPU�ģ�
	���Ƕ��ڲ���LTDC LCD�������STM32F429���µ���STM32F1��STM32F40xϵ�ж���
  ����STM32F429��������LTDC LCD��������LCD
*/
/*
  ���ʵ��ʹ���˴�����ϵ�к�100������ϵ�е�Ƭ�ӵ���û��LTDC���Ƽ���FSMCͬʱ����LCD��SRAM*/
#define SYSTEM_FSMC_ENABLE	0				//�Ƿ�����FSMC
	#define SYSTEM_FSMC_use4LCD		0		//����FSMC��������LCD������ش��뱻���룬���API����
	#define SYSTEM_FSMC_use4SRAM	0		//����FSMC��������SRAM������ش��뱻���룬���API����
/*
����LCD�Ĳ��֣�
	  Ҫ���ģ�	LCD����ش��뻹û����ֲ��LCD������������ȫ����ԭ�ӵ�LCD����
				���ǻ��������ڵ�LCD��������Ԥ����������ƣ���˵���������𣬵��õ�ʱ��úø�

����SRAM�Ĳ��֣�
	����Ĭ���õ� ��1��NORSRAM�飩������3������4����LCD�~������1����3����4�ֱ������ⲿRAM��LCD����ģ��Ĭ�ϣ����򻹵øĵ�ַ��
	Ĭ����������IS62WV51216����ַ�߷�ΧΪA0~A18�������߷�ΧD0~D15����NUB��NLB��NWE��NOE��NCE��������߶���Ӧ�Ӻã�
	�ײ�API�������Ƽ�ֱ�ӵ��ã�ʹ����ʵ�ֵ�malloc��free�������ֽ�Ϊ��λ��
		u32 testsram[250000] __attribute__((at(SRAM1_BANK3_ADDR))); 	//��ַ�������ⲿSRAM��
		void FSMC_SRAM_WriteBuffer(u8 *pBuffer,u32 WriteAddr,u32 n); 	//д ����������ָ�룬�ⲿSRAM�ڵĵ�ַ(��0��ʼ)��д����ֽ���
		void FSMC_SRAM_ReadBuffer(u8 *pBuffer,u32 ReadAddr,u32 n);   	//�� ������
*/
/*
�ڴ�����ȵ�malloc.h���涨���м���RAM��RAM�ı�־λ���͸���RAM���ڴ�������Ŀռ�
	Ӧ�ò�API���������ڴ���������ֽ�Ϊ��λ��
		my_mem_init(InrRAM);				//��ʼ���ڲ��ڴ�أ�ϵͳ�Դ���
		my_mem_init(ExRAM1);				//��ʼ���ⲿ�ڴ�أ����������SYSTEM_FSMC_use4SRAM��û����仰��
		
		void myfree(u8 memx,void *ptr);  			//�ڴ��ͷ�
		void *mymalloc(u8 memx,u32 size);			//�ڴ����
		void *myrealloc(u8 memx,void *ptr,u32 size);//���·����ڴ�
*/



/*_____________ϵͳ����_______________*/
extern u16	StartUpTimes;			/*���ڱ��濪�����������������һ�������ڶ���ҳ*/
extern uint32_t UIDw[3]; /*����STM32�ڲ�UIDʶ���룬ȫ��Ψһʶ����*/
extern uint32_t sysCoreClock; /*��ȡHCLKƵ�ʣ�����ʱ�Ӿ����Դ��ٷ�Ƶ*/

void sys_MCU_Init_Seq(void);				/*MCU�����ʼ�����У����г�ʼ��д��������*/
void sys_Device_Init_Seq(void);				/*���������ʼ�����������Լ�*/

extern uint8_t is_quitFault;
void FaultASSERT(char* FaultMessage);				/*��ʾ��ʼ�������⣬������ʾ��ָʾ�ƻ��߷�����������ʾ*/
int8_t Stm32_Clock_Init(uint32_t PLL);		/*ʱ��ϵͳ����*/

#if SYSTEM_UART1_ENABLE||SYSTEM_UART2_ENABLE||SYSTEM_UART3_ENABLE
	
	#define USART1_RX_BUF_MaxNum 	500 	/*������Э��0ֻ������'\r\n'��β������ʱ���Դ����ַ��������������ֽ���Ŀ*/
	#define USART1_RX_FIFO_MaxNum	200		/*������Э��1��FIFO�洢����ʱ���Դ������ֽ���Ŀ*/
	
	#define UART1	1
	#define UART2	2
	#define UART3	3
	#define RXBUFFERSIZE   1 					//�����С
	extern u8 aRxBuffer1[RXBUFFERSIZE],aRxBuffer2[RXBUFFERSIZE],aRxBuffer3[RXBUFFERSIZE];//HAL��ʹ�õĴ��ڽ��ջ���
	extern UART_HandleTypeDef UART1_Handler,UART2_Handler,UART3_Handler; //UART���
	void sys_USART1_ENABLE(void);
	void sys_USART2_ENABLE(void);
	void sys_USART3_ENABLE(void);
	
	
	#define USART1_RX_DONE_mask 0x8000
	#define USART1_RX_MODE_mask 0x4000
	#define USART1_RX_Rec_r_mask 0x2000
	#define USART1_RX_Num_mask 0x1fff /*0001 1111 1111 1111*/
	

	extern char USART1_RX_BUF[USART1_RX_BUF_MaxNum]; /*����1��ģʽ1���ݽ�����*/
	extern u16 USART1_RX_CONFIG;	/*    x            x           x        x xxxx xxxx xxxx      */
									/*(�������) (Э��ģʽ0/1) (���յ�\r)   ����1���������ֽڼ��� */
									/*����1����Э�飺0Ϊֻ������'\r\n'��β�����ݣ�1Ϊ��FIFO�Ƚ��ȳ�ʵ�ֽ���������Э��*/
									
	#define USART1_SetDone 		USART1_RX_CONFIG |= USART1_RX_DONE_mask /*���ô���1������ɱ�־λ*/
	#define USART1_SetUnDone 	USART1_RX_CONFIG &= USART1_RX_MODE_mask /*�������д������Դ���1��־λ���и�λ������modeλ������λ��д0*/
	#define USART1_Set_r_UnDone	USART1_RX_CONFIG &= (!USART1_RX_Rec_r_mask)
	#define USART1_SetMode(x) 	USART1_RX_CONFIG |= (((u16)x)<<14) 		/*�û����ã������������ô���1����Э��*/
	#define USART1_isDone 		(USART1_RX_CONFIG & USART1_RX_DONE_mask)/*�û��ã������ж��Ƿ�������һ��*/
	#define USART1_RX_ByteNum 	(USART1_RX_CONFIG & USART1_RX_Num_mask)/*�û����ã����ؽ��յ��ַ�����*/
	
//	extern char USART1_RX_FIFO_buf[USART1_RX_FIFO_MaxNum]; /*����1��ģʽ0��FIFO���ݽ�����*/
//	extern fifo_t Test_fifo;
//	extern fifo_t Test2_fifo;
	extern fifo_t Uart1_fifo;
	char sys_USART1_RX_Fetch(u8 is_print, char* buf);
	
	
#endif

#if SYSTEM_MCO_PA8_OUT
	void sys_MCO_Out_Enable(void);				/*MCO��PA8�����������Ĭ��ʱ��ԴHSE*/
#endif

#if STSTEM_TIM4_ENABLE

	__packed struct TIM4_IT_FLAGS
	{
		u8 _10msec_flag;	//10�����־�ͼ���
		u16 _10msec;
		
		u8 _100msec_flag;	//100�����־�ͼ���
		u16 _100msec;
		
		u8 _300msec_flag;	//300�����־
		
		u8 _1sec_flag;		//1���־�ͼ���
		u16 _1sec;
		
		u8 _1min_flag;		//1���ӱ�־�ͼ���
		u16 _1min;
	};
	extern struct TIM4_IT_FLAGS Timer_IT_flags;
	extern TIM_HandleTypeDef TIM4_Handler;      //ͨ�ö�ʱ��4��� 
	void sys_TIM4_ENABLE(void);
#endif
	
#if STSTEM_TIM3PWM_ENABLE
	/*������������ͨ��4��*/
	extern u8 is_buzzer_once;
	extern u8 is_buzzer_bibi;
	#define buzzer_bibi_once	is_buzzer_once = 1;  //�û�ʹ�ã��������л�һ��
	#define buzzer_bibi_on		is_buzzer_bibi = 1;  //�û�ʹ�ã���������Ъ�л�����
	#define buzzer_bibi_off		is_buzzer_bibi = 0;  //�û�ʹ�ã���������Ъ�л��ر�
	extern TIM_HandleTypeDef 	TIM3_Handler;      	//��ʱ��3���
	extern TIM_OC_InitTypeDef 	TIM3_CH1Handler,TIM3_CH2Handler,TIM3_CH3Handler,TIM3_CH4Handler;	//��ʱ��3ͨ��1-4���
	#define TIM3PWM_Channel_1	1
	#define TIM3PWM_Channel_2	2
	#define TIM3PWM_Channel_3	3
	#define TIM3PWM_Channel_4	4
	void sys_TIM3PWM_ENABLE(void);
	void TIM3_set_Channel_Pulse(u8 channel,float percent);
#endif

#if SYSTEM_IWDG_ENABLE
	extern IWDG_HandleTypeDef IWDG_Handler; //�������Ź����
	void sys_IWDG_ENABLE(void);
	void IWDG_Feed(void);
#endif

#if SYSTEM_CRC_ENABLE
	#define BUFFER_SIZE    114
	extern CRC_HandleTypeDef hcrc;
	extern const uint32_t aDataBuffer[BUFFER_SIZE];
	extern uint32_t uwExpectedCRCValue;
	void sys_CRC_ENABLE(void);
	void HAL_CRC_MspInit(CRC_HandleTypeDef* hcrc);
#endif

#if SYSTEM_RTC_ENABLE
	extern RTC_HandleTypeDef RTC_Handler;  //RTC���
	//ʱ��ṹ��
	typedef struct 
	{
		vu8 hour;
		vu8 min;
		vu8 sec;			
		//������������
		vu16 w_year;
		vu8  w_month;
		vu8  w_date;
		vu8  week;	
	}_calendar_obj;					 
	extern _calendar_obj calendar;				//�û��ã�RTC�ṹ�壬ʵ����ʱֻ��Ҫ������ṹ���ȡʱ�伴��
	char sys_RTC_Enable(void);						/*RTC����*/
	u8 Is_Leap_Year(u16 year);					//ƽ��,�����ж�
	u8 RTC_Get(void);         					//��ȡʱ�䣬��RTC���ж���ִ�У��Զ�����calendarʱ�䣬�û����ù�
	u8 RTC_Get_Week(u16 year,u8 month,u8 day);
	u8 RTC_Set(u16 syear,u8 smon,u8 sday,u8 hour,u8 min,u8 sec);		//�û��ã�����ʱ��	
	u8 RTC_Alarm_Set(u16 syear,u8 smon,u8 sday,u8 hour,u8 min,u8 sec);	//�û��ã���������
	//HAL_StatusTypeDef HAL_RTC_SetAlarm_IT (RTC_HandleTypeDef * hrtc, RTC_AlarmTypeDef * sAlarm,uint32_t Format);
#endif


void delay_init(void);
void delay_ms(uint16_t nms);
void delay_xms(uint16_t nms);
void delay_us(uint32_t nus);


/*Author:		MaxwellXyao*/
#define BIT(n) 					(1 << n) 				//λmask
#define bit_SetTrue(x,mask) 	(x |= mask)				//��λ����Ϊ��
#define bit_SetFalse(x,mask)	(x &= ~mask)			//��λ����Ϊ��
#define bit_Toggle(x,mask) 		(x ^= mask)				//λ�л�
#define bit_IsTrue(x,mask) 		((x & mask) != 0)		//��λ�Ƿ���
#define bit_IsFalse(x,mask) 	((x & mask) == 0)		//��λ�Ƿ��

//����Ϊ��ຯ��
void WFI_SET(void);		//ִ��WFIָ��
void INTX_DISABLE(void);//�ر������ж�
void INTX_ENABLE(void);	//���������ж�
void MSR_MSP(uint32_t addr);	//���ö�ջ��ַ

#endif


