#include "PeriphConfig.h"

/*STEP 1:ȥ.h�ļ��ﶨ�嶼��ʲô����*/

/*STEP 2:����һ���ж��ٸ�����*/
#define devicesNum	3
.
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


/*___________________________________���²��ö�_________________________________________________*/
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


#endif


