#include "PeriphConfig.h"

/*
______________________________��PIN MAP��__________________________________________
ע�������紮�ڡ�PWM�ȵ�IO��ʼ�������ʼ�������ڣ����õ����ٳ�ʼ��
		[IO]											[����]
���裺	* PA8										MCO�����Ĭ��ʱ��ԴΪHSE
		* CH1/PA6, CH2/PA7, CH3/PB0, CH4/PB1		TIM3Ĭ��PWM��
		  CH1/PB4, CH2/PB5, CH3/PB0, CH4/PB1		TIM3������ӳ��PWM��
		  CH1/PC6, CH2/PC7, CH3/PC8, CH4/PC9		TIM3��ȫ��ӳ��PWM��
		* TX/PA9, RX/PA10 - TX/PB6, RX/PB7			USART1Ĭ�����ź���ӳ������
		* TX/PA2, RX/PA3 - TX/PD5, RX/PD6			USART2Ĭ�����ź���ӳ������
		* TX/PB10, RX/PB11 - TX/PD8,  RX/PD9		USART3Ĭ�����ź���ӳ������
		* 											SPI1Ĭ�����ź���ӳ������
		*...

�û���	*
*/

/*___________________________����IO����___________________________________________*/

/*STEP1:ȥ.h�ļ����"���嶼��ʲô����"����д������Щ����*/

/*STEP2:����һ���ж��ٸ�����*/
#define devicesNum	2

/*STEP3:����ÿ���������õ���IO��������*/
/*����˵����
	PIN��	GPIO_PIN_0~GPIO_PIN_15��GPIO_PIN_All
	MODE��	GPIO_MODE_INPUT��GPIO_MODE_ANALOG��GPIO_MODE_AF_INPUT							����
			GPIO_MODE_OUTPUT_PP��GPIO_MODE_OUTPUT_OD��GPIO_MODE_AF_PP��GPIO_MODE_AF_OD		���
			GPIO_MODE_IT_RISING��GPIO_MODE_IT_FALLING��GPIO_MODE_IT_RISING_FALLING  		ѡ��IT��ʾ����EXTI�����16��EXTI����PA0��PB0����EXTI0
	��������GPIO_NOPULL��GPIO_PULLUP��GPIO_PULLDOWN
	��ת�ٶȣ�GPIO_SPEED_FREQ_LOW��GPIO_SPEED_FREQ_MEDIUM��GPIO_SPEED_FREQ_HIGH
	GPIOx��GPIOA~GPIOE
	Ĭ��״̬:GPIO_PIN_SET��1u����GPIO_PIN_RESET��0u��
	EXTI���ȼ���0~15
	����EXTI��TRUE����FALSE
*/
GPIO_Init_Struct LCD_IO_Struct[] = 
{	/*	PIN				MODE			  ������		��ת�ٶ�		  	GPIOx 	  Ĭ��״̬     EXTI���ȼ�	����EXTI*/
	{{GPIO_PIN_2, GPIO_MODE_OUTPUT_PP, GPIO_PULLUP, GPIO_SPEED_FREQ_HIGH},	GPIOA,  GPIO_PIN_SET,		2,		  TRUE},
	{{GPIO_PIN_2, GPIO_MODE_OUTPUT_PP, GPIO_PULLUP, GPIO_SPEED_FREQ_HIGH},	GPIOB,  GPIO_PIN_SET,		2,		  TRUE}
};

GPIO_Init_Struct BUCK_IO_Struct[] =
{
	{{GPIO_PIN_2, GPIO_MODE_OUTPUT_PP, GPIO_PULLUP, GPIO_SPEED_FREQ_HIGH},	GPIOA,  GPIO_PIN_SET,		2,		  TRUE},
	{{GPIO_PIN_2, GPIO_MODE_OUTPUT_PP, GPIO_PULLUP, GPIO_SPEED_FREQ_HIGH},	GPIOB,  GPIO_PIN_SET,		2,		  TRUE}
};

/*STEP4:��������������������"���嶼��ʲô����"�����˳������ÿ����������Ϣ*/
Devices_Init_Struct UserDevices[devicesNum] = 
{
	{	
		.deviceIO_Struct 	= 	LCD_IO_Struct	,		//����IO���ýṹ��
		.deviceIndex 		= 	LCD				,		//����enum��ʽ����
		.deviceName 		= 	"LCD device"	,		//��������
		.device_IOnum 		= 	8						//�����ж��ٸ�IO��
	},
	{
		.deviceIO_Struct 	= 	BUCK_IO_Struct	,
		.deviceIndex		= 	BUCK			,
		.deviceName 		= 	"BUCK device"	,
		.device_IOnum 		= 	2
	}
};


/*___________________________����IO���ú���___________________________________________*/
void Devices_Init(Devices_Init_Struct* Devices , enum devicesIndex_enum device2Init)
{
	u8 dIndex;
	if(device2Init == ALL)
	{
		for(dIndex = 0;dIndex < devicesNum;dIndex++)	//������������
		{
			deviceIO_Init(Devices,(enum devicesIndex_enum)dIndex);
		}
	}else{
		switch(device2Init)								//�ض�������ʼ������������		
		{
			case LCD:	deviceIO_Init(Devices,LCD);
				break;
			case BUCK:	deviceIO_Init(Devices,BUCK);
			default:break;
		}
	}
}

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
		if( (Devices[dIndex].deviceIO_Struct[iIndex].GPIO_Initure.Mode == GPIO_MODE_IT_RISING) \
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
			}else if((Devices[dIndex].deviceIO_Struct[iIndex].GPIO_Initure.Pin == GPIO_PIN_5) \
					||(Devices[dIndex].deviceIO_Struct[iIndex].GPIO_Initure.Pin == GPIO_PIN_6) \
					||(Devices[dIndex].deviceIO_Struct[iIndex].GPIO_Initure.Pin == GPIO_PIN_7) \
					||(Devices[dIndex].deviceIO_Struct[iIndex].GPIO_Initure.Pin == GPIO_PIN_8) \
					||(Devices[dIndex].deviceIO_Struct[iIndex].GPIO_Initure.Pin == GPIO_PIN_9) )
			{
				HAL_NVIC_SetPriority(EXTI9_5_IRQn, Devices[dIndex].deviceIO_Struct[iIndex].PreemptPriority, 0);
				if(Devices[dIndex].deviceIO_Struct[iIndex].isEnableExit)  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn); else HAL_NVIC_DisableIRQ(EXTI9_5_IRQn);
			}else if((Devices[dIndex].deviceIO_Struct[iIndex].GPIO_Initure.Pin == GPIO_PIN_10) \
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
		HAL_GPIO_WritePin(Devices[dIndex].deviceIO_Struct[iIndex].GPIOx, \
			Devices[dIndex].deviceIO_Struct[iIndex].GPIO_Initure.Pin, \
			Devices[dIndex].deviceIO_Struct[iIndex].defaultState);
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
            break;
		case GPIO_PIN_1:
			break;
        case GPIO_PIN_2:
            break;
        case GPIO_PIN_3:
            break;
        case GPIO_PIN_4:
            break;
    }
}


