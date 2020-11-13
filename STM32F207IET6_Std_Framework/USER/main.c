#include "system.h"
#include "led.h"
#include "time.h"
#include "malloc.h" 

//#include "spi.h"
#include "sdio_sdcard.h"
#include "SPI_SDcard.h"

#include "can.h"

#include "ff.h"
/*__________________________________________________________________________

	GPIO��AF���ù����������� ��stm32f207ie.pdf�� �� 59ҳ ��ʼ

	DMAx����������ͨ�������������� ���Ĵ����ֲ�-cd00225773-stm32f205xx-stm32f207xx-stm32f215xx-and-stm32f217xx-advanced-armbased-32bit-mcus-stmicroelectronics��
				�� 180ҳ ��ʼ
	
	
	STM32F207IET6��
		512KB(hd)FLASH��128KB��SRAM1��+112KB+16KB��SRAM2��RAM��176��LQFP��װ��140��GPIO��-40~85��
   	
	CPU�ڲ� FLASH  			��0x0800 0000 - 0x080F FFFF��,����512K(0x80000)�ֽ�
	CPU�ڲ� SRAM1  			��0x2000 0000 - 0x2000 FFFF��,����128K(0x20000)�ֽ�
	
	ʱ�ӷ��䣺
		HSE���8Mhz����LSE���32.768Khz����
		����HSE��8M����LSE��32.768K����LSI��32K�����ر�HSI��16M��
		PLLCLK = SYSCLK = AHBCLK = HCLK ��Ϊ120MHz��APB2����Ϊ60MHz��APB1����Ϊ30Mhz��APB2��ʱ��Ϊ120MHz��APB1��ʱ��Ϊ60Mhz
		
		ETH\RNG\FSMC\USB FS\USB HS\GPIO\DMA ����120M
		RTC ʱ��ȡ�� LSE = 32.768K
		IWDGʱ��ȡ�� LSI = 32K
		DCMI 48 Mbyte/s max
		
		APB2����(60M)��SDIO\USART1\USART6\SPI1\ADC123
		APB2��ʱ��(120M)��TIM1 TIM8 TIM9 TIM10 TIM11
		APB1����(30M)��USART2\USART3\UART4\UART5\SPI2��I2S2\SPI3��I2S3\I2C123\CAN12\DAC12
		APB1��ʱ��(60M)��TIM2 TIM3 TIM4 TIM5 TIM12 TIM13 TIM14
*/

/*
��������STM32F207IE��׼��ĳ����򵥵�ģ�幤�̣����������ճ������ã��ô�ͳ�ı�׼����жϷ���2...

�������ʱ�ӳ�ʼ���� system_stm32f2xx.c�ļ�����ݺ궨���ϵ����� SystemInit() ��������
*/
int main()
{
	SysTick_Init(120);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //�ж����ȼ����� ��2��
	
	my_mem_init(SRAMIN);		//��ʼ���ڲ��ڴ��
	USART1_Init(115200);
	LED_Init();
	
	TIM4_Init(10000-1,6000-1);  //��ʱ1s
	
	
	/*��Ŀ�����ʼ��*/
	FATFS fs[_VOLUMES];		//�����ļ�ϵͳ�豸���
	FIL ftemp;	  			//�ļ�
	u8 fatbuf[512];			//SD�����ݻ�����
	UINT readCount;
	UINT writeCount;
	
	char strbuf[200];		//�ַ�������
	
	delay_ms(500);
	u8 res;
	res = f_mount(&fs[0],"0:",1); //����SDIO������SD��
	if(res != 0)
	{
		printf("����SDIO SDʧ��\r\n");
		while(1);
	}else					//���سɹ�����ʼ����
	{
		printf("����SDIO SD�ɹ�����ʼ����\r\n");
		
		f_open(&ftemp,"0:TEXT/demo.txt",FA_READ);
		f_read(&ftemp,fatbuf,512,&readCount);
		snprintf(strbuf,(size_t)readCount,"demo.txt�������ݣ�\r\n%s\r\n",fatbuf);
		printf("%s",strbuf);
		f_close(&ftemp);
		
		f_open(&ftemp,"0:TEXT/demo01.txt",FA_OPEN_ALWAYS | FA_WRITE);
		f_lseek(&ftemp, f_size(&ftemp));
		f_write(&ftemp,fatbuf,readCount,&writeCount);
		printf("demo01.txt�Ѿ�д�����ݸ��� %d\r\n",writeCount);
		f_close(&ftemp);
		
		
		delay_ms(100);
		f_mount(0, "0:", 1);
		printf("������ϣ�ж��SDIO SD\r\n");
	}
	
	res = f_mount(&fs[1],"1:",1); //����SPI������SD��
	if(res != 0)
	{
		printf("����SPI SDʧ��\r\n");
		while(1);
	}else				//���سɹ�����ʼ����
	{
		printf("����SPI SD�ɹ�����ʼ����\r\n");
		
		f_open(&ftemp,"1:TEXT/demo.txt",FA_READ);
		f_read(&ftemp,fatbuf,512,&readCount);
		snprintf(strbuf,(size_t)readCount,"demo.txt�������ݣ�\r\n%s\r\n",fatbuf);
		printf("%s",strbuf);
		f_close(&ftemp);
		
		f_open(&ftemp,"1:TEXT/demo02.txt",FA_OPEN_ALWAYS | FA_WRITE);
		f_lseek(&ftemp, f_size(&ftemp));
		f_write(&ftemp,fatbuf,readCount,&writeCount);
		printf("demo02.txt�Ѿ�д�����ݸ��� %d\r\n",writeCount);
		f_close(&ftemp);
		
		
		delay_ms(100);
		f_mount(0, "1:", 1);
		printf("������ϣ�ж��SPI SD\r\n");
	}
	
	
	CAN1_Mode_Init(CAN_SJW_1tq,CAN_BS2_7tq,CAN_BS1_6tq,6,CAN_Mode_Normal);//500Kbps������
		
	printf("Go\r\n");
	for(;;)
	{
		if((USART1_RX_STA & 0x8000) == 1)	//���ڽ��յ�����
		{
			switch(USART1_RX_BUF[0])
			{
				case 1:
					break;
				
				case 2:
					break;
				default:
					break;
			}
		}
		
	}
}


