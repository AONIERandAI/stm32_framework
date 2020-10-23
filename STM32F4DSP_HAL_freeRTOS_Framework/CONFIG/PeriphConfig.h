#ifndef __PERIPHCONFIG_H
#define __PERIPHCONFIG_H

#include "PeriphConfigCore.h"
#include "simui2c.h"
#include "simuspi.h"


/*_____________________________________\\\                               ///____________________________________________*
 *_________________________________________________�û�GPIO����_________________________________________________________*
 *_____________________________________///                               \\\____________________________________________*/


/*STEP 1:���嶼��ʲô����*/
enum devicesIndex_enum
{
	TestLED_Index = 0,
	KEY_Index,
	LCD_Index,
//	simuI2C_Index,
	
	ALL_Index		//�������̶��Ĳ�Ҫɾ
};

/*STEP 3.5:��д�����ⲿ�жϵ�IO���жϱ�־λ*/
extern u8 key_Up_Interrupted; 
extern u8 key_Down_Interrupted;

/*STEP 3.75:����IO���Ƶĺ�͸ı����ģʽ�ĺ�*/
#define key_Up_ReadIn	PAin(1)
#define key_Down_ReadIn	PAin(2)
//��������ȥ�ⲿ�жϻص�����HAL_GPIO_EXTI_Callback()����дIO���ⲿ�жϱ�־Ϊ��λ

#define	SPI1_CS PAout(4)  		//SPI1��Ƭѡ�ź�
#define	SPI2_CS PBout(12)  		//SPI2��Ƭѡ�ź�

#define TestLED_Ctrl	PFout(9)
#define TestLED2_Ctrl	PFout(10)

//#define	simuI2C_SCLout 	PEout(2)
//#define	simuI2C_SDAout 	PEout(3)
//#define	simuI2C_SDAin	PEin(3)
//#define simuI2C_SDAinMode	PEinMode(3)
//#define simuI2C_SDAoutMode	PEoutMode(3)


/*_____________________________________\\\                               ///____________________________________________*
 *_________________________________________________���²��ö�___________________________________________________________*
 *_____________________________________///                               \\\____________________________________________*/
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
//void deviceIO_Init(Devices_Init_Struct* Devices , enum devicesIndex_enum device2Init);
extern Devices_Init_Struct UserDevices[];

/*____________________IO�����������λ����д������ı��������___________________________________*/
/*Author:	����ԭ��@ALIENTEK*/
//IO�ڲ����궨��
#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 
//IO�ڵ�ַӳ��
#define GPIOA_ODR_Addr    (GPIOA_BASE+20)
#define GPIOB_ODR_Addr    (GPIOB_BASE+20)
#define GPIOC_ODR_Addr    (GPIOC_BASE+20)
#define GPIOD_ODR_Addr    (GPIOD_BASE+20)
#define GPIOE_ODR_Addr    (GPIOE_BASE+20)
#define GPIOF_ODR_Addr    (GPIOF_BASE+20)  
#define GPIOG_ODR_Addr    (GPIOG_BASE+20)   

#define GPIOA_IDR_Addr    (GPIOA_BASE+16)
#define GPIOB_IDR_Addr    (GPIOB_BASE+16) 
#define GPIOC_IDR_Addr    (GPIOC_BASE+16)
#define GPIOD_IDR_Addr    (GPIOD_BASE+16)
#define GPIOE_IDR_Addr    (GPIOE_BASE+16)
#define GPIOF_IDR_Addr    (GPIOF_BASE+16)
#define GPIOG_IDR_Addr    (GPIOG_BASE+16)
 
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

#define PEinMode(x)		{GPIOE->MODER &= ~(0x00000003 << (x * 2));GPIOE->MODER |= 0x00000000 << (x * 2);}
#define PEoutMode(x)	{GPIOE->MODER &= ~(0x00000003 << (x * 2));GPIOE->MODER |= 0x00000001 << (x * 2);}
//Ĭ��������������죬�ǿ�©

#define DS18B20_IO_IN()  {GPIOG->MODER&=~(3<<(9*2));GPIOG->MODER|=0<<(9*2);}	//PG9����ģʽ
#define DS18B20_IO_OUT() {GPIOG->MODER&=~(3<<(9*2));GPIOG->MODER|=1<<(9*2);} 	//PG9���ģʽ


#endif



