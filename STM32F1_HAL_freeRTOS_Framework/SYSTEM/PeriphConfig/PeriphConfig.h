#ifndef __PERIPHCONFIG_H
#define __PERIPHCONFIG_H

#include "sys.h"
#include "sys_menu.h"


/*STEP1:���嶼��ʲô����*/
enum devicesIndex_enum
{
	TestLED_Index = 0,
	KEY_Index,
	LCD_Index,
	
	ALL_Index		//�������̶��Ĳ�Ҫɾ
};

/*STEP3.5:��д�����ⲿ�жϵ�IO���жϱ�־λ*/
extern u8 key_Up_Interrupted;
extern u8 key_Down_Interrupted;


/*STEP5:����IO���Ƶĺ�͸ı����ģʽ�ĺ�*/
#define key_Up_ReadIn	HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_1)
#define key_Down_ReadIn	HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_2)

#define	SPI1_CS PAout(4)  		//SPI1��Ƭѡ�ź�
#define	SPI2_CS PBout(12)  		//SPI2��Ƭѡ�ź�

#define TestLED_Ctrl	PAout(7)



/*___________________________________���²��ö�_________________________________________________*/
/*����IO�ڳ�ʼ���ṹ��*/
typedef struct
{
	GPIO_InitTypeDef GPIO_Initure;		//IO��ʼ���ṹ��
	GPIO_TypeDef* GPIOx;				//ѡ��GPIO��
	GPIO_PinState defaultState;			//��ʼ����Ϻ��Ĭ��״̬
										//���pinModeѡ��IT������EXTI�����16��EXTI����PA0��PB0����EXTI0
	uint32_t PreemptPriority;			//�ⲿ�ж���ռ���ȼ�����ʹ���ⲿ�ж�ʱ������Ч��
	u8 isEnableExit;					//�Ƿ�ʹ���ⲿ�жϣ���ʹ���ⲿ�ж�ʱ������Ч��
	
}GPIO_Init_Struct;


/*����������Ϣ�ĳ�ʼ���ṹ��*/
typedef struct
{
	GPIO_Init_Struct* deviceIO_Struct;		//��������IO�ṹ��
	
	enum devicesIndex_enum deviceIndex;		//������������
	char* deviceName;						//������������
	const u8 device_IOnum;					//���������õ�IO������
}Devices_Init_Struct;

void Devices_Init(Devices_Init_Struct* Devices , enum devicesIndex_enum device2Init);
void deviceIO_Init(Devices_Init_Struct* Devices , enum devicesIndex_enum device2Init);
extern Devices_Init_Struct UserDevices[];

/*____________________IO�����������λ����д������ı��������___________________________________*/
/*Author:	����ԭ��@ALIENTEK*/
//IO�ڲ����궨��
#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 
//IO�ڵ�ַӳ��
#define GPIOA_ODR_Addr    (GPIOA_BASE+12) //0x4001080C 
#define GPIOB_ODR_Addr    (GPIOB_BASE+12) //0x40010C0C 
#define GPIOC_ODR_Addr    (GPIOC_BASE+12) //0x4001100C 
#define GPIOD_ODR_Addr    (GPIOD_BASE+12) //0x4001140C 
#define GPIOE_ODR_Addr    (GPIOE_BASE+12) //0x4001180C 
#define GPIOF_ODR_Addr    (GPIOF_BASE+12) //0x40011A0C    
#define GPIOG_ODR_Addr    (GPIOG_BASE+12) //0x40011E0C    

#define GPIOA_IDR_Addr    (GPIOA_BASE+8) //0x40010808 
#define GPIOB_IDR_Addr    (GPIOB_BASE+8) //0x40010C08 
#define GPIOC_IDR_Addr    (GPIOC_BASE+8) //0x40011008 
#define GPIOD_IDR_Addr    (GPIOD_BASE+8) //0x40011408 
#define GPIOE_IDR_Addr    (GPIOE_BASE+8) //0x40011808 
#define GPIOF_IDR_Addr    (GPIOF_BASE+8) //0x40011A08 
#define GPIOG_IDR_Addr    (GPIOG_BASE+8) //0x40011E08 
 
/*____________________________________________________________�û�ʹ��____________*/
//IO�ڲ���,ֻ�Ե�һ��IO��!ȷ��n��ֵС��16!
#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //��� 
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)  //���� 

#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  //��� 
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  //���� 

#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)  //��� 
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)  //���� 

#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr,n)  //��� 
#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr,n)  //���� 

#define PEout(n)   BIT_ADDR(GPIOE_ODR_Addr,n)  //��� 
#define PEin(n)    BIT_ADDR(GPIOE_IDR_Addr,n)  //����

#define PFout(n)   BIT_ADDR(GPIOF_ODR_Addr,n)  //��� 
#define PFin(n)    BIT_ADDR(GPIOF_IDR_Addr,n)  //����

#define PGout(n)   BIT_ADDR(GPIOG_ODR_Addr,n)  //��� 
#define PGin(n)    BIT_ADDR(GPIOG_IDR_Addr,n)  //����



/*λ��������8λ����16λһͬ�������*/
/*ע��xΪ16λ�������ͣ�
�÷���	u16 data = 0xaaaa;
		data = PBdataIn; 		//16λ����
		PAdataOut(data);		//16λ���
*//*____________________________________________________________�û�ʹ��____________*/
#define PAdataOut(x) 	GPIOA->ODR=x; //�������
#define PAdataIn     	GPIOA->IDR;   //��������

/*____________________________________________________________�û�ʹ��____________*/
#define PAh8dataOut(x)	PAdataOut(((GPIOA->IDR)&0x00ff)|((x<<8)&0xff00));	//PA�߰�λ���
#define PAl8dataOut(x)	PAdataOut(((GPIOA->IDR)&0xff00)|(x&0x00ff));		//PA�Ͱ�λ���
#define PAh8dataIn		(((GPIOA->IDR)>>8)&0x00ff);							//PA�߰�λ��ȡ
#define PAl8dataIn		((GPIOA->IDR)&0x00ff);								//PA�Ͱ�λ��ȡ

/*____________________________________________________________�û�ʹ��____________*/
#define PBdataOut(x) 	GPIOB->ODR=x; //�������
#define PBdataIn     	GPIOB->IDR;   //��������

/*____________________________________________________________�û�ʹ��____________*/
#define PBh8dataOut(x)	PBdataOut(((GPIOB->IDR)&0x00ff)|((x<<8)&0xff00));	//PB�߰�λ���
#define PBl8dataOut(x)	PBdataOut(((GPIOB->IDR)&0xff00)|(x&0x00ff));		//PB�Ͱ�λ���
#define PBh8dataIn		(((GPIOB->IDR)>>8)&0x00ff);							//PB�߰�λ��ȡ
#define PBl8dataIn		((GPIOB->IDR)&0x00ff);								//PB�Ͱ�λ��ȡ

/*�������ģ�л������ṩ�������л���Ӧ�ڳ�ʼ��IOʱ�����������*/
/*�÷���
	PAmodeIn(15); //����PA15��Ϊ��������������
	PAmodeOut(6); //����PA6��Ϊ�������
*/
#define calMove(x)	4*(x-8)
/*�������������ӣ���������*/
//#define PA15in()  {GPIOA->CRH&=0X0FFFFFFF;GPIOA->CRH|=(u32)8<<28;}
//#define PA15out() {GPIOA->CRH&=0X0FFFFFFF;GPIOA->CRH|=(u32)3<<28;}

//�ֱ�ΪPA15~8�ź�PA7~0������Ϊ��������������
#define PAmodeInH(x)	{GPIOA->CRH &= (~(0x0000000F<<(calMove(x))));GPIOA->CRH|=(u32)8<<(calMove(x));}
#define PAmodeInL(x)	{GPIOA->CRL &= (~(0x0000000F<<(calMove(x))));GPIOA->CRL|=(u32)8<<(calMove(x));}
//�ֱ�ΪPA15~8�ź�PA7~0������Ϊ50MHz�������
#define PAmodeOutH(x)	{GPIOA->CRH &= (~(0x0000000F<<(calMove(x))));GPIOA->CRH|=(u32)3<<(calMove(x));}
#define PAmodeOutL(x)	{GPIOA->CRL &= (~(0x0000000F<<(calMove(x))));GPIOA->CRL|=(u32)3<<(calMove(x));}

/*____________________________________________________________�û�ʹ��____________*/
#define PAmodeIn(x)		{if(x>7){PAmodeInH(x);}else{PAmodeInL(x);}}
#define PAmodeOut(x)	{if(x>7){PAmodeOutH(x);}else{PAmodeOutL(x);}}


/*_______________________________��ʱ��2___________________________________*/
extern TIM_HandleTypeDef TIM2_Handler;
void sys_TIM2_ENABLE(void); //д��Ԥ��������Ϊ���ⲿ�ļ��ܹ�����
#if STSTEM_TIM2_ENABLE
	#if (STSTEM_TIM2_asPWMorCap == 0)
		#define TIM2PWM_Channel_1	1
		#define TIM2PWM_Channel_2	2
		#define TIM2PWM_Channel_3	3
		#define TIM2PWM_Channel_4	4
		extern TIM_OC_InitTypeDef 	TIM2_CH1Handler,TIM2_CH2Handler,TIM2_CH3Handler,TIM2_CH4Handler;
		void TIM2_set_Channel_Pulse(u8 channel,float percent);
	#elif (STSTEM_TIM2_asPWMorCap == 1)
		extern TIM_IC_InitTypeDef TIM2_CHxConfig;
		void Process_TIM2_IC_CallBack_Channel_1(void);
		void Process_TIM2_IC_CallBack_Channel_2(void);
		void Process_TIM2_IC_CallBack_Channel_3(void);
		void Process_TIM2_IC_CallBack_Channel_4(void);
	#elif (STSTEM_TIM2_asPWMorCap == 3)
		extern TIM_Encoder_InitTypeDef sEncoderConfig;
	#endif
#endif

/*���벶��˽�б���*/
extern u8  	TIM2CHx_CAPTURE_STA;	    				
extern u16	TIM2CHx_CAPTURE_VAL;
float Peek_TIM2_Cap_Val(void);

/*��������˽�б���*/
extern int32_t EncoderOverflowCount;//��ʱ���������
float peek_TIM2_Encoder_Speed(void);
int32_t peek_TIM2_Encoder_Value(void);

/*_______________________________ADC1___________________________________*/
extern ADC_HandleTypeDef ADC1_Handler;
void sys_ADC1_ENABLE(void);
u32 Get_Adc_Average(u32 ch,u8 times);
float Get_Temprate(u32 adcx);
#if SYSTEM_ADC1_ENABLE
	void ADC_RegularChannelConfig(ADC_HandleTypeDef *AdcHandle, uint32_t Channel, uint32_t Rank, uint32_t SamplingTime);
	u16 Get_Adc(u32 ch);
	#if SYSTEM_ADC1_useScan
		extern DMA_HandleTypeDef  ADC1rxDMA_Handler;
		void ADC_DMA_Cfg(void);
	#endif
#endif

/*_______________________________SPI1��2________________________________*/

extern SPI_HandleTypeDef SPI1_Handler;  //SPI1���
extern SPI_HandleTypeDef SPI2_Handler;  //SPI2���
void sys_SPI1_ENABLE(void);
void sys_SPI2_ENABLE(void);
void SPI1_SetSpeed(u8 SPI_BaudRatePrescaler);
void SPI2_SetSpeed(u8 SPI_BaudRatePrescaler);

//д��8�ֽ�
u8 SPI1_ReadWriteByte_8Byte(u8 TxData);
//д��16�ֽڣ�����һ������2�ֽڵ�u8*ָ��
u8 SPI1_ReadWriteByte_16Byte(u8* TxData);
//д8�ֽ�
u8 SPI1_WriteByte_8Byte(u8 TxData);
//д16�ֽڣ�����һ������2�ֽڵ�u8*ָ��
u8 SPI1_WriteByte_16Byte(u8* TxData);

u8 SPI2_ReadWriteByte(u8 TxData);

void sys_SPI1_SS_io_Init(void);
void sys_SPI2_SS_io_Init(void);

/*_________________________________�͹���StandbyMode________________________________*/

void sys_StdbyWKUP_ENABLE(void);
void sys_CheckWKUP_4RTOS(void);
#if SYSTEM_StdbyWKUP_ENABLE
	#define WKUP_KD HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0)  //PA0 ����Ƿ��ⲿWK_UP��������
	u8 Check_WKUP(void);  			//���WKUP�ŵ��ź�
	void Sys_Enter_Standby(void);	//ϵͳ�������ģʽ
#endif

/*____________________________FLASH���___________________________________*/
void STMFLASH_Read(		u32 ReadAddr,	u16 *pBuffer,	u16 NumToRead);		//����API
void STMFLASH_Write(	u32 WriteAddr,	u16 *pBuffer,	u16 NumToWrite);	//����API
#if SYSTEM_FLASH_IAP_ENABLE
	
	#if STM32_FLASH_WREN	//���ʹ����д   
		extern void FLASH_PageErase(uint32_t PageAddress);
		void STMFLASH_Write_NoCheck(u32 WriteAddr,u16 *pBuffer,u16 NumToWrite);
	#endif

	u16 STMFLASH_ReadHalfWord(u32 faddr);
#endif

/*_____________________________________DAC________________________________________*/

#if ((SYSTEM_DAC_OUT1_ENABLE) || (SYSTEM_DAC_OUT2_ENABLE)) && ((STM32F103xG) || (STM32F103xE))
extern DAC_HandleTypeDef DAC1_Handler;//DAC���
void sys_DAC_ENABLE(void);
void HAL_DAC_MspInit(DAC_HandleTypeDef* hdac);
void DAC_Set_Ch1_Vol(float vol);
void DAC_Set_Ch2_Vol(float vol);

#endif



/*____________________SDIO SD_____________________________________________*/

u8 SD_Init(void);
u8 SD_ReadDisk(u8* buf,u32 sector,u32 cnt);
u8 SD_WriteDisk(u8 *buf,u32 sector,u32 cnt);
void show_sdcard_info(void);						//ͨ������1��ӡSD�������Ϣ
#if (SYSTEM_SDIO_SD_ENABLE) && ((STM32F103xG) || (STM32F103xE))

extern HAL_SD_CardInfoTypeDef  	SDCardInfo;              	//SD����Ϣ
extern HAL_SD_CardCIDTypeDef	SDCard_CID;					//SD��CID��Ϣ
extern SD_HandleTypeDef        	SDCARD_Handler;     		//SD�����
#define SD_TIMEOUT 			((uint32_t)100000000)  			//��ʱʱ��

#endif

/*____________________________FSMC for SARM_____________________________________________*/
void sys_FSMC_SRAM_ENABLE(void);
void FSMC_SRAM_WriteBuffer(u8 *pBuffer,u32 WriteAddr,u32 n);
void FSMC_SRAM_ReadBuffer(u8 *pBuffer,u32 ReadAddr,u32 n);
#if ((SYSTEM_FSMC_ENABLE) && (SYSTEM_FSMC_use4SRAM)) && ((STM32F103xG) || (STM32F103xE))

extern SRAM_HandleTypeDef SRAM_Handler;    //SRAM���
//ʹ��NOR/SRAM�� Bank1.sector3,��ַλHADDR[27,26]=10 
//��IS61LV25616/IS62WV25616,��ַ�߷�ΧΪA0~A17 
//��IS61LV51216/IS62WV51216,��ַ�߷�ΧΪA0~A18
#define SRAM1_BANK3_ADDR    ((u32)(0x68000000))	//���㣺 (0x6000 0000 | ((u32)64*1024*1024*(3 - 1)))

#endif


/*____________________________FSMC for LCD_____________________________________________*/
void LCD_with_FSMC_init_FSMC(void);
//LCD��ַ�ṹ��
typedef struct
{
	vu16 LCD_REG;
	vu16 LCD_RAM;
} LCD_TypeDef;
//ʹ��NOR/SRAM�� Bank1.sector4,��ַλHADDR[27,26]=11 A10��Ϊ�������������� 
//ע������ʱSTM32�ڲ�������һλ����! 			    
#define LCD_BASE        ((u32)(0x6C000000 | 0x000007FE))
#define LCD             ((LCD_TypeDef *) LCD_BASE)
#if ((SYSTEM_FSMC_ENABLE) && (SYSTEM_FSMC_use4LCD)) && ((STM32F103xG) || (STM32F103xE))

extern SRAM_HandleTypeDef TFTSRAM_Handler;    //SRAM���(���ڿ���LCD)

#endif


#endif


