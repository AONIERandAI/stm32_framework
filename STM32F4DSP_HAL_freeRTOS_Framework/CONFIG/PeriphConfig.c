#include "PeriphConfig.h"


/*_____________________________________\\\                               ///____________________________________________*
 *_________________________________________________�û�GPIO����_________________________________________________________*
 *_____________________________________///                               \\\____________________________________________*/
/*STEP 1:ȥ.h�ļ��ﶨ�嶼��ʲô����*/

/*STEP 2:����һ���ж��ٸ�����*/
#define devicesNum	3

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
/*ָʾ��IO����*/
GPIO_Init_Struct TestLED_IO_Struct[] = 
{	/*	PIN				MODE			  ������		��ת�ٶ�		  		GPIOx 	  Ĭ��״̬     EXTI���ȼ�	����EXTI*/
	{{GPIO_PIN_9, 	GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH},	GPIOF,  GPIO_PIN_SET,		15,		  FALSE},
	{{GPIO_PIN_10, 	GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH},	GPIOF,  GPIO_PIN_SET,		15,		  FALSE}
};
/*���ڲ˵����ⲿ���밴������*/
GPIO_Init_Struct KEY_IO_Struct[] =
{	/*	PIN				MODE			  ������		��ת�ٶ�		  	GPIOx 	  Ĭ��״̬     EXTI���ȼ�	����EXTI*/
	{{GPIO_PIN_1, GPIO_MODE_IT_FALLING, GPIO_PULLUP, GPIO_SPEED_FREQ_HIGH},	GPIOA,  GPIO_PIN_SET,		2,		  TRUE},	//key_Up
	{{GPIO_PIN_2, GPIO_MODE_IT_FALLING, GPIO_PULLUP, GPIO_SPEED_FREQ_HIGH},	GPIOA,  GPIO_PIN_SET,		2,		  TRUE}		//key_Down
};
/*LCD IO����ʱ��IO����*/
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

///*I2C��IO����*/
//GPIO_Init_Struct simuI2C_IO_Struct[] =
//{	/*	PIN				MODE			  ������		��ת�ٶ�		  	GPIOx 	  Ĭ��״̬     EXTI���ȼ�	����EXTI*/
//	{{GPIO_PIN_2, GPIO_MODE_OUTPUT_PP, GPIO_PULLUP, GPIO_SPEED_FREQ_HIGH},	GPIOE,  GPIO_PIN_SET,		2,		  TRUE},	//MPU6050 SCL
//	{{GPIO_PIN_3, GPIO_MODE_OUTPUT_PP, GPIO_PULLUP, GPIO_SPEED_FREQ_HIGH},	GPIOE,  GPIO_PIN_SET,		2,		  TRUE} 	//MPU6050 SDA
//};

/*STEP 3.5:�������ȥ.h�ļ�����д�����ⲿ�жϵ�IO���жϱ�־λ*/
//��IOʹ���ⲿ�ж�ʱ����һ����־λ��¼�ж��Ƿ������ѳ�ʱ��Ĵ������ŵ��ж����棡
u8 key_Up_Interrupted 		= 	FALSE; 
u8 key_Down_Interrupted 	= 	FALSE;


/*STEP 3.75:ȥ.h�ļ��ﶨ��IO���Ƶĺ�͸ı����ģʽ�ĺ�*/


/*STEP4:��������������������"STEP 1:���嶼��ʲô����"�����˳������ÿ����������Ϣ*/
Devices_Init_Struct UserDevices[devicesNum] = 
{
	{	
		.deviceIO_Struct 	= 	TestLED_IO_Struct	,	//����IO���ýṹ��
		.deviceIndex 		= 	TestLED_Index		,	//����enum��ʽ����
		.deviceName 		= 	"TestLED"			,	//��������
		.device_IOnum 		= 	2						//�����ж��ٸ�IO��
	},
	{
		.deviceIO_Struct 	= 	KEY_IO_Struct	,
		.deviceIndex		= 	KEY_Index		,
		.deviceName 		= 	"Menu Key"		,
		.device_IOnum 		= 	2
	},
	{	
		.deviceIO_Struct 	= 	LCD_IO_Struct	,
		.deviceIndex 		= 	LCD_Index		,
		.deviceName 		= 	"LCD"			,
		.device_IOnum 		= 	13				
	},
//	{	
//		.deviceIO_Struct 	= 	simuI2C_IO_Struct	,
//		.deviceIndex 		= 	simuI2C_Index		,
//		.deviceName 		= 	"simuI2C"			,
//		.device_IOnum 		= 	2					
//	}
};


/*_____________________________________\\\                               ///____________________________________________*
 *_________________________________________________���²��ö�___________________________________________________________*
 *_____________________________________///                               \\\____________________________________________*/
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
		else if(Devices[dIndex].deviceIO_Struct[iIndex].GPIOx == GPIOF)
			__HAL_RCC_GPIOF_CLK_ENABLE();
		else if(Devices[dIndex].deviceIO_Struct[iIndex].GPIOx == GPIOG)
			__HAL_RCC_GPIOG_CLK_ENABLE();
		
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
			key_Up_Interrupted = TRUE;
			break;
        case GPIO_PIN_2:
			key_Down_Interrupted = TRUE;
            break;
        case GPIO_PIN_3:
            break;
        case GPIO_PIN_4:
            break;
    }
}

/*_________________________________________������������������������PeriphConfigCore.h��������_________________________________________________________*/
#if SYSTEM_CAN1_ENABLE


CAN_TxHeaderTypeDef	TxHeader;      //����
CAN_RxHeaderTypeDef	RxHeader;      //����

CAN_HandleTypeDef CAN1_Handler;

/* CAN1 init function */
void MX_CAN1_Init(void)
{

  CAN1_Handler.Instance = CAN1;
  CAN1_Handler.Init.Prescaler = 3; 					//1~1024����Ƶ��APB1 30MHZ
  CAN1_Handler.Init.Mode = CAN_MODE_NORMAL;			//���趯
  CAN1_Handler.Init.SyncJumpWidth = CAN_SJW_2TQ;	//CAN_SJW_1TQ ~ CAN_SJW_4TQ
  CAN1_Handler.Init.TimeSeg1 = CAN_BS1_10TQ;		//CAN_BS1_1TQ ~ CAN_BS1_16TQ
  CAN1_Handler.Init.TimeSeg2 = CAN_BS2_8TQ;			//CAN_BS2_1TQ ~ CAN_BS2_8TQ
	//CAN1������ 500Kbps
	
  CAN1_Handler.Init.TimeTriggeredMode = DISABLE;	//��ʱ�䴥��ͨ��ģʽ
  CAN1_Handler.Init.AutoBusOff = DISABLE;			//����Զ����߹���
  CAN1_Handler.Init.AutoWakeUp = DISABLE;			//˯��ģʽͨ���������
  CAN1_Handler.Init.AutoRetransmission = ENABLE;	//�����Զ�����
  CAN1_Handler.Init.ReceiveFifoLocked = DISABLE;	//���Ĳ�����,�µĸ��Ǿɵ�
  CAN1_Handler.Init.TransmitFifoPriority = DISABLE;//���ȼ��ɱ��ı�ʶ������
  
  HAL_CAN_Init(&CAN1_Handler);
  
}
void CAN_Config(void);
void HAL_CAN_MspInit(CAN_HandleTypeDef* canHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(canHandle->Instance==CAN1)
  {
  /* USER CODE BEGIN CAN1_MspInit 0 */

  /* USER CODE END CAN1_MspInit 0 */
    /* CAN1 clock enable */
    __HAL_RCC_CAN1_CLK_ENABLE();

    __HAL_RCC_GPIOI_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**CAN1 GPIO Configuration
    PB8     ------> CAN1_RX
    PB9     ------> CAN1_TX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_CAN1;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_8;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_CAN1;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* CAN1 interrupt Init */
//    HAL_NVIC_SetPriority(CAN1_RX0_IRQn, 2, 0);
//    HAL_NVIC_EnableIRQ(CAN1_RX0_IRQn);
//    HAL_NVIC_SetPriority(CAN1_RX1_IRQn, 2, 0);
//    HAL_NVIC_EnableIRQ(CAN1_RX1_IRQn);
	
	CAN_Config();
  }
}

//void CAN1_RX0_IRQHandler(void)
//{
//  HAL_CAN_IRQHandler(&CAN1_Handler);
//}
//void CAN1_RX1_IRQHandler(void)
//{
//  HAL_CAN_IRQHandler(&CAN1_Handler);
//}

void CAN_Config(void)
{
  CAN_FilterTypeDef  sFilterConfig;

  /*����CAN������*/
  sFilterConfig.FilterBank = 0;                     //������0
  sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
  sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
  sFilterConfig.FilterIdHigh = 0x0000;              //32λID
  sFilterConfig.FilterIdLow = 0x0000;
  sFilterConfig.FilterMaskIdHigh = 0x0000;          //32λMASK
  sFilterConfig.FilterMaskIdLow = 0x0000;
  sFilterConfig.FilterFIFOAssignment = CAN_RX_FIFO0;//������0������FIFO0
  sFilterConfig.FilterActivation = ENABLE;          //�����˲���0
  sFilterConfig.SlaveStartFilterBank = 14;
  
  //����������
  if (HAL_CAN_ConfigFilter(&CAN1_Handler, &sFilterConfig) != HAL_OK)
  {
	  FaultASSERT("HAL_CAN_ConfigFilter",1,flag_Fault);
  }

  //����CAN��Χ�豸
  if (HAL_CAN_Start(&CAN1_Handler) != HAL_OK)
  {
    FaultASSERT("HAL_CAN_Start",1,flag_Fault);
  }

  //�������RX֪ͨ
  if (HAL_CAN_ActivateNotification(&CAN1_Handler, CAN_IT_RX_FIFO0_MSG_PENDING) != HAL_OK)
  {
    FaultASSERT("HAL_CAN_ActivateNotification",1,flag_Fault);
  }
  
  /*���ô������*/
  TxHeader.StdId = 0x321;
  TxHeader.ExtId = 0x01;
  TxHeader.RTR = CAN_RTR_DATA;
  TxHeader.IDE = CAN_ID_STD;
  TxHeader.DLC = 2;
  TxHeader.TransmitGlobalTime = DISABLE;
}
//can����һ������(�̶���ʽ:IDΪ0X12,��׼֡,����֡)	
//len:���ݳ���(���Ϊ8)				     
//msg:����ָ��,���Ϊ8���ֽ�.
//����ֵ:0,�ɹ�;
//		 ����,ʧ��;
u8 CAN1_Send_Msg(u8* msg,u8 len)
{	
    u8 i=0;
	u32 TxMailbox;
	u8 message[8];
    TxHeader.StdId=0X12;        //��׼��ʶ��
    TxHeader.ExtId=0x12;        //��չ��ʶ��(29λ)
    TxHeader.IDE=CAN_ID_STD;    //ʹ�ñ�׼֡
    TxHeader.RTR=CAN_RTR_DATA;  //����֡
    TxHeader.DLC=len;                
    for(i=0;i<len;i++)
    {
		message[i]=msg[i];
	}
    if(HAL_CAN_AddTxMessage(&CAN1_Handler, &TxHeader, message, &TxMailbox) != HAL_OK)//����
	{
		return HAL_ERROR;
	}
	while(HAL_CAN_GetTxMailboxesFreeLevel(&CAN1_Handler) != 3) {}
    return HAL_OK;
}

//can�ڽ������ݲ�ѯ
//buf:���ݻ�����;	 
//����ֵ:0,�����ݱ��յ�;
//		 ����,���յ����ݳ���;
u8 CAN1_Receive_Msg(u8 *buf)
{
 	u32 i;
	u8	RxData[8];

	if(HAL_CAN_GetRxFifoFillLevel(&CAN1_Handler, CAN_RX_FIFO0) != 1)
	{
		return 0xF1;
	}

	if(HAL_CAN_GetRxMessage(&CAN1_Handler, CAN_RX_FIFO0, &RxHeader, RxData) != HAL_OK)
	{
		return 0xF2;
	}
    for(i=0;i<RxHeader.DLC;i++)
    buf[i]=RxData[i];
	return RxHeader.DLC;
}

#endif
/*________________________________________�û���ʱ��1PWM����_________________________________________________________*/
#if STSTEM_TIM1PWM_ENABLE
TIM_HandleTypeDef TIM1_Handler;

void sys_TIM1PWM_ENABLE(void)
{

  TIM_ClockConfigTypeDef sClockSourceConfig;
  TIM_MasterConfigTypeDef sMasterConfig;
  TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig;
  TIM_OC_InitTypeDef sConfigOC;
  
  TIM1_Handler.Instance = TIM1;
  TIM1_Handler.Init.Prescaler = tim1prsc;
  TIM1_Handler.Init.CounterMode = TIM_COUNTERMODE_CENTERALIGNED1; //���Ķ���
  TIM1_Handler.Init.Period = tim1arr;							  //��װ��ֵ��16λ
  TIM1_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;
  TIM1_Handler.Init.RepetitionCounter = 0;
  TIM1_Handler.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  HAL_TIM_Base_Init(&TIM1_Handler);

  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;	//ʱ��Դ�����ڲ����������ⲿETR������Ϊʱ��Դ��
  HAL_TIM_ConfigClockSource(&TIM1_Handler, &sClockSourceConfig);

  HAL_TIM_PWM_Init(&TIM1_Handler);
  
   /*���Ҫ�����Ӷ�ʱ�����ο�https://my.oschina.net/u/4315748/blog/3220499*/
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;			//������źŸ���������
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;	//��ʹ�ö�ʱ�����ӹ��ܣ�������TIM1�Ķ�ʱ�ж���Ϊ������ʱ���ļ���Դ
  HAL_TIMEx_MasterConfigSynchronization(&TIM1_Handler, &sMasterConfig);
  
  sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;		//Ĭ��disable����
  sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;		//Ĭ��disable
  sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_3;				//��������������������Ȳ������ٱ�Ļ��Ͱ�LOCK������߼�
  /*����ʱ����ƣ�DeadTime��8��bits�������£�DTΪ����ʱ�䣬TdtsΪ1/72M~13.9ns
	DTG[7:5]=0xx	=>	DT = DTG[7:0] x Tdtg,        Tdtg  = Tdts; 		���1.764us
	DTG[7:5]=10x	=>	DT = (64+DTG[5:0]) x Tdtg,   Tdtg  = 2 x Tdts;	���3.5288us
	DTG[7:5]=110	=>	DT = (32+DTG[4:0]) x Tdtg,   Tdtg  = 8 x Tdts; 	���7us
	DTG[7:5]=111	=>	DT = (32+DTG[4:0]) x Tdtg,   Tdtg  = 16 x Tdts;	���14us����ʱֵΪ0xff��
																		Ҫ3us����Ϊ0xab
	*/
  sBreakDeadTimeConfig.DeadTime = 0xab;							//����ʱ������ 0x00~0xff
  #if STSTEM_TIM1PWM_useBreak
	sBreakDeadTimeConfig.BreakState = TIM_BREAK_ENABLE;			//ʹ�ܻ�ʧ��TIMxɲ������
  #else
	sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
  #endif
  sBreakDeadTimeConfig.BreakFilter = 0xa;						//ɲ�������˲���0x0~0xF
  sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_LOW;	//ɲ������ż���
  sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;	//Ĭ��
  HAL_TIMEx_ConfigBreakDeadTime(&TIM1_Handler, &sBreakDeadTimeConfig);

  sConfigOC.OCMode = TIM_OCMODE_PWM1;							//���ϼ���ʱ��PWM1ģʽ���Ǽ���С��ռ�ձ�ֵ��TIMx_CNT<TIMx_CCR1����IO��Ϊ��Ч���ԣ������෴
  sConfigOC.Pulse = tim1arr/2;									//ռ�ձ�ֵ������Ƚ�ֵ��16λ��
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;					//��ѡ��ͨ������Ч����Ϊ�߻��ǵ�
  sConfigOC.OCNPolarity = TIM_OCNPOLARITY_LOW;					//��ѡ����ͨ������Ч����
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;					//disable�ͺ�
  sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;				//���е�ƽ����ѡ��û������ʱ�ĵ�ƽ�������޸ģ���Ҳ�п�����ɲ��ʱ�ĵ�ƽ��
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_SET;
  HAL_TIM_PWM_ConfigChannel(&TIM1_Handler, &sConfigOC, TIM_CHANNEL_1);
  __HAL_TIM_ENABLE_OCxPRELOAD(&TIM1_Handler, TIM_CHANNEL_1);

  sConfigOC.Pulse = tim1arr/2;
  HAL_TIM_PWM_ConfigChannel(&TIM1_Handler, &sConfigOC, TIM_CHANNEL_2);
  __HAL_TIM_ENABLE_OCxPRELOAD(&TIM1_Handler, TIM_CHANNEL_2);

  sConfigOC.Pulse = tim1arr/2;
  HAL_TIM_PWM_ConfigChannel(&TIM1_Handler, &sConfigOC, TIM_CHANNEL_3);
  __HAL_TIM_ENABLE_OCxPRELOAD(&TIM1_Handler, TIM_CHANNEL_3);

  sConfigOC.Pulse = tim1arr/2;
  HAL_TIM_PWM_ConfigChannel(&TIM1_Handler, &sConfigOC, TIM_CHANNEL_4);
  __HAL_TIM_ENABLE_OCxPRELOAD(&TIM1_Handler, TIM_CHANNEL_4);
}


void TIM1_set_Channel_Pulse(u8 channel,float percent)
{
	float compare;
	if(percent < 0) percent = 0f;
	if(percent > 100) percent = 100.0f;
	percent /= 100.0f;
	compare = ((float)tim1arr) * percent;
	switch(channel)
	{
		case TIM1PWM_Channel_1: TIM1->CCR1=(u32)compare;break;
		case TIM1PWM_Channel_2: TIM1->CCR2=(u32)compare;break;
		case TIM1PWM_Channel_3: TIM1->CCR3=(u32)compare;break;
		case TIM1PWM_Channel_4: TIM1->CCR4=(u32)compare;break;
		default:break;
	}
}


#endif

/*________________________________________�û���ʱ��8PWM����_________________________________________________________*/
#if STSTEM_TIM8PWM_ENABLE
TIM_HandleTypeDef TIM8_Handler;

void sys_TIM8PWM_ENABLE(void)
{

  TIM_ClockConfigTypeDef sClockSourceConfig;
  TIM_MasterConfigTypeDef sMasterConfig;
  TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig;
  TIM_OC_InitTypeDef sConfigOC;
  
  TIM8_Handler.Instance = TIM8;
  TIM8_Handler.Init.Prescaler = tim8prsc;
  TIM8_Handler.Init.CounterMode = TIM_COUNTERMODE_CENTERALIGNED1;
  TIM8_Handler.Init.Period = tim8arr;							//��װ��ֵ��16λ
  TIM8_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;
  TIM8_Handler.Init.RepetitionCounter = 0;
  TIM8_Handler.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  HAL_TIM_Base_Init(&TIM8_Handler);

  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;	//ʱ��Դ�����ڲ����������ⲿETR������Ϊʱ��Դ��
  HAL_TIM_ConfigClockSource(&TIM8_Handler, &sClockSourceConfig);

  HAL_TIM_PWM_Init(&TIM8_Handler);
  
   /*���Ҫ�����Ӷ�ʱ�����ο�https://my.oschina.net/u/4315748/blog/3220499*/
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;			//������źŸ���������
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;	//��ʹ�ö�ʱ�����ӹ��ܣ�������TIM1�Ķ�ʱ�ж���Ϊ������ʱ���ļ���Դ
  HAL_TIMEx_MasterConfigSynchronization(&TIM8_Handler, &sMasterConfig);
  
  sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;		//Ĭ��disable����
  sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;		//Ĭ��disable
  sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_3;				//��������������������Ȳ������ٱ�Ļ��Ͱ�LOCK������߼�
  /*����ʱ����ƣ�DeadTime��8��bits�������£�DTΪ����ʱ�䣬TdtsΪ1/72M~13.9ns
	DTG[7:5]=0xx	=>	DT = DTG[7:0] x Tdtg,        Tdtg  = Tdts; 		���1.764us
	DTG[7:5]=10x	=>	DT = (64+DTG[5:0]) x Tdtg,   Tdtg  = 2 x Tdts;	���3.5288us
	DTG[7:5]=110	=>	DT = (32+DTG[4:0]) x Tdtg,   Tdtg  = 8 x Tdts; 	���7us
	DTG[7:5]=111	=>	DT = (32+DTG[4:0]) x Tdtg,   Tdtg  = 16 x Tdts;	���14us����ʱֵΪ0xff��
																		Ҫ3us����Ϊ0xab
	*/
  sBreakDeadTimeConfig.DeadTime = 0xab;							//����ʱ������ 0x00~0xff
  #if STSTEM_TIM8PWM_useBreak
	sBreakDeadTimeConfig.BreakState = TIM_BREAK_ENABLE;			//ʹ�ܻ�ʧ��TIMxɲ������
  #else
	sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
  #endif
  sBreakDeadTimeConfig.BreakFilter = 0xa;						//ɲ�������˲���0x0~0xF
  sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_LOW;	//ɲ������ż���
  sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;	//Ĭ��
  HAL_TIMEx_ConfigBreakDeadTime(&TIM8_Handler, &sBreakDeadTimeConfig);

  sConfigOC.OCMode = TIM_OCMODE_PWM1;							//���ϼ���ʱ��PWM1ģʽ���Ǽ���С��ռ�ձ�ֵ��TIMx_CNT<TIMx_CCR1����IO��Ϊ��Ч���ԣ������෴
  sConfigOC.Pulse = tim8arr/2;									//ռ�ձ�ֵ������Ƚ�ֵ��16λ��
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;					//��ѡ��ͨ������Ч����Ϊ�߻��ǵ�
  sConfigOC.OCNPolarity = TIM_OCNPOLARITY_LOW;					//��ѡ����ͨ������Ч����
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;					//disable�ͺ�
  sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;				//���е�ƽ����ѡ��û������ʱ�ĵ�ƽ�������޸ģ���Ҳ�п�����ɲ��ʱ�ĵ�ƽ��
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_SET;
  HAL_TIM_PWM_ConfigChannel(&TIM8_Handler, &sConfigOC, TIM_CHANNEL_1);
  __HAL_TIM_ENABLE_OCxPRELOAD(&TIM8_Handler, TIM_CHANNEL_1);

  sConfigOC.Pulse = tim8arr/2;
  HAL_TIM_PWM_ConfigChannel(&TIM8_Handler, &sConfigOC, TIM_CHANNEL_2);
  __HAL_TIM_ENABLE_OCxPRELOAD(&TIM8_Handler, TIM_CHANNEL_2);

  sConfigOC.Pulse = tim8arr/2;
  HAL_TIM_PWM_ConfigChannel(&TIM8_Handler, &sConfigOC, TIM_CHANNEL_3);
  __HAL_TIM_ENABLE_OCxPRELOAD(&TIM8_Handler, TIM_CHANNEL_3);

  sConfigOC.Pulse = tim8arr/2;
  HAL_TIM_PWM_ConfigChannel(&TIM8_Handler, &sConfigOC, TIM_CHANNEL_4);
  __HAL_TIM_ENABLE_OCxPRELOAD(&TIM8_Handler, TIM_CHANNEL_4);
}


void TIM8_set_Channel_Pulse(u8 channel,float percent)
{
	float compare;
	if(percent < 0) percent = 0f;
	if(percent > 100) percent = 100.0f;
	percent /= 100.0f;
	compare = ((float)tim8arr) * percent;
	switch(channel)
	{
		case TIM8PWM_Channel_1: TIM8->CCR1=(u32)compare;break;
		case TIM8PWM_Channel_2: TIM8->CCR2=(u32)compare;break;
		case TIM8PWM_Channel_3: TIM8->CCR3=(u32)compare;break;
		case TIM8PWM_Channel_4: TIM8->CCR4=(u32)compare;break;
		default:break;
	}
}


#endif


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


//SPI�ײ�������ʱ��ʹ�ܣ���������
//�˺����ᱻHAL_SPI_Init()����
//hspi:SPI���
void HAL_SPI_MspInit(SPI_HandleTypeDef *hspi)
{
    GPIO_InitTypeDef GPIO_Initure;
    /*
	SPI1->CS	SPI1->CLK	SPI1->MISO	SPI1->MOSI 	������������ 	SPI2->CS	SPI2->CLK	SPI2->MISO	SPI2->MOSI
	PA4			PA5			PA6			PA7					PB12		PB13		PB14		PB15
	*/
	if(hspi->Instance == SPI1)
	{
		__HAL_RCC_GPIOA_CLK_ENABLE();       //ʹ��GPIOAʱ��
		__HAL_RCC_SPI1_CLK_ENABLE();        //ʹ��SPI1ʱ��
		//__HAL_RCC_AFIO_CLK_ENABLE();
		
		//PB13,14,15
		GPIO_Initure.Pin=GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
		GPIO_Initure.Mode=GPIO_MODE_AF_PP;              //�������������MISO����Ϊ��������û����
		GPIO_Initure.Pull=GPIO_PULLUP;                  //����
		GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;        //����   
		GPIO_Initure.Alternate=GPIO_AF5_SPI1;
		HAL_GPIO_Init(GPIOA,&GPIO_Initure);
	}else if(hspi->Instance == SPI2)
	{
		__HAL_RCC_GPIOB_CLK_ENABLE();       //ʹ��GPIOBʱ��
		__HAL_RCC_SPI2_CLK_ENABLE();        //ʹ��SPI2ʱ��
		//__HAL_RCC_AFIO_CLK_ENABLE();
		
		//PB13,14,15
		GPIO_Initure.Pin=GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
		GPIO_Initure.Mode=GPIO_MODE_AF_PP;              //�������������MISO����Ϊ��������û����
		GPIO_Initure.Pull=GPIO_PULLUP;                  //����
		GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;        //���� 
		GPIO_Initure.Alternate=GPIO_AF5_SPI1;
		HAL_GPIO_Init(GPIOB,&GPIO_Initure);
	}

}


#if SYSTEM_SPI1_ENABLE

SPI_HandleTypeDef SPI1_Handler;  //SPI1���

void sys_SPI1_ENABLE(void)
{
    SPI1_Handler.Instance=SPI1;                         //SPI1
    SPI1_Handler.Init.Mode=SPI_MODE_MASTER;             //����SPI����ģʽ������Ϊ��ģʽ
    SPI1_Handler.Init.Direction=SPI_DIRECTION_2LINES;   //����SPI�������˫�������ģʽ:SPI����Ϊ˫��ģʽ
    SPI1_Handler.Init.DataSize=SPI_DATASIZE_8BIT;       //����SPI�����ݴ�С:SPI���ͽ���8λ֡�ṹ
    
	SPI1_Handler.Init.CLKPolarity=SPI_POLARITY_HIGH;    //����ͬ��ʱ�ӵĿ���״̬Ϊ�ߵ�ƽ
    SPI1_Handler.Init.CLKPhase=SPI_PHASE_2EDGE;         //����ͬ��ʱ�ӵĵڶ��������أ��������½������ݱ�����
    
	SPI1_Handler.Init.NSS=SPI_NSS_SOFT;                 //NSS�ź���Ӳ����NSS�ܽţ����������ʹ��SSIλ������:�ڲ�NSS�ź���SSIλ����
    SPI1_Handler.Init.BaudRatePrescaler=SPI_BAUDRATEPRESCALER_256;//���岨����Ԥ��Ƶ��ֵ:������Ԥ��ƵֵΪ256
    SPI1_Handler.Init.FirstBit=SPI_FIRSTBIT_MSB;        //ָ�����ݴ����MSBλ����LSBλ��ʼ:���ݴ����MSBλ��ʼ
    SPI1_Handler.Init.TIMode=SPI_TIMODE_DISABLE;        //�ر�TIģʽ
    SPI1_Handler.Init.CRCCalculation=SPI_CRCCALCULATION_DISABLE;//�ر�Ӳ��CRCУ��
    SPI1_Handler.Init.CRCPolynomial=7;                  //CRCֵ����Ķ���ʽ
    HAL_SPI_Init(&SPI1_Handler);//��ʼ��
    
	sys_SPI1_SS_io_Init();
	
    __HAL_SPI_ENABLE(&SPI1_Handler);                    //ʹ��SPI1
	
    //SPI1_ReadWriteByte(0Xff);                           //��������
}

//SPI�ٶ����ú���
//SPI1�ٶ�=APB2/��Ƶϵ��
/*������ѡ��
SPI_BAUDRATEPRESCALER_2 SPI_BAUDRATEPRESCALER_4 SPI_BAUDRATEPRESCALER_8 SPI_BAUDRATEPRESCALER_16 
SPI_BAUDRATEPRESCALER_32 SPI_BAUDRATEPRESCALER_64 SPI_BAUDRATEPRESCALER_128 SPI_BAUDRATEPRESCALER_256
*/
void SPI1_SetSpeed(u8 SPI_BaudRatePrescaler)
{
    assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_BaudRatePrescaler));//�ж���Ч��
    __HAL_SPI_DISABLE(&SPI1_Handler);            //�ر�SPI
    SPI1_Handler.Instance->CR1&=0XFFC7;          //λ3-5���㣬�������ò�����
    SPI1_Handler.Instance->CR1|=SPI_BaudRatePrescaler;//����SPI�ٶ�
    __HAL_SPI_ENABLE(&SPI1_Handler);             //ʹ��SPI
    
}

//SPI1 ��дһ���ֽ�
//TxData:Ҫд����ֽ�
//����ֵ:��ȡ�����ֽ�
u8 SPI1_ReadWriteByte_8Byte(u8 TxData)
{
    u8 Rxdata;
	SPI1_CS = IO_Low;
    HAL_SPI_TransmitReceive(&SPI1_Handler,&TxData,&Rxdata,1, 100);
	SPI1_CS = IO_High;	
 	return Rxdata;          		    //�����յ�������		
}

//����һ������2�ֽڵ�u8*ָ��
u8 SPI1_ReadWriteByte_16Byte(u8* TxData)
{
    u8 Rxdata;
	SPI1_CS = IO_Low;
    HAL_SPI_TransmitReceive(&SPI1_Handler,TxData,&Rxdata, 2, 100);
	SPI1_CS = IO_High;	
 	return Rxdata;          		    //�����յ�������		
}

u8 SPI1_WriteByte_8Byte(u8 TxData)
{
	u8 state;
	SPI1_CS = IO_Low;
	state = (u8)(HAL_SPI_Transmit(&SPI1_Handler, &TxData, 1, 100));	
	SPI1_CS = IO_High;
	return state;
}

//����һ������2�ֽڵ�u8*ָ��
u8 SPI1_WriteByte_16Byte(u8* TxData)
{
	u8 state;
	SPI1_CS = IO_Low;
	state = (u8)(HAL_SPI_Transmit(&SPI1_Handler, TxData, 2, 100));	
	SPI1_CS = IO_High;
	return state;
}

#endif

#if SYSTEM_SPI2_ENABLE

SPI_HandleTypeDef SPI2_Handler;  //SPI2���

void sys_SPI2_ENABLE(void)
{
    SPI2_Handler.Instance=SPI2;                         //SPI2
    SPI2_Handler.Init.Mode=SPI_MODE_MASTER;             //����SPI����ģʽ������Ϊ��ģʽ
    SPI2_Handler.Init.Direction=SPI_DIRECTION_2LINES;   //����SPI�������˫�������ģʽ:SPI����Ϊ˫��ģʽ
    SPI2_Handler.Init.DataSize=SPI_DATASIZE_8BIT;       //����SPI�����ݴ�С:SPI���ͽ���8λ֡�ṹ
    
	SPI2_Handler.Init.CLKPolarity=SPI_POLARITY_HIGH;    //����ͬ��ʱ�ӵĿ���״̬Ϊ�ߵ�ƽ
    SPI2_Handler.Init.CLKPhase=SPI_PHASE_2EDGE;         //����ͬ��ʱ�ӵĵڶ��������أ��������½������ݱ�����
    
	SPI2_Handler.Init.NSS=SPI_NSS_SOFT;                 //NSS�ź���Ӳ����NSS�ܽţ����������ʹ��SSIλ������:�ڲ�NSS�ź���SSIλ����
    SPI2_Handler.Init.BaudRatePrescaler=SPI_BAUDRATEPRESCALER_256;//���岨����Ԥ��Ƶ��ֵ:������Ԥ��ƵֵΪ256
    SPI2_Handler.Init.FirstBit=SPI_FIRSTBIT_MSB;        //ָ�����ݴ����MSBλ����LSBλ��ʼ:���ݴ����MSBλ��ʼ
    SPI2_Handler.Init.TIMode=SPI_TIMODE_DISABLE;        //�ر�TIģʽ
    SPI2_Handler.Init.CRCCalculation=SPI_CRCCALCULATION_DISABLE;//�ر�Ӳ��CRCУ��
    SPI2_Handler.Init.CRCPolynomial=7;                  //CRCֵ����Ķ���ʽ
    HAL_SPI_Init(&SPI2_Handler);//��ʼ��
    
	sys_SPI2_SS_io_Init();
	
    __HAL_SPI_ENABLE(&SPI2_Handler);                    //ʹ��SPI2
	
    //SPI2_ReadWriteByte(0Xff);                           //��������
}

//SPI�ٶ����ú���
//SPI2�ٶ�=APB1/��Ƶϵ��
/*������ѡ��
SPI_BAUDRATEPRESCALER_2 SPI_BAUDRATEPRESCALER_4 SPI_BAUDRATEPRESCALER_8 SPI_BAUDRATEPRESCALER_16 
SPI_BAUDRATEPRESCALER_32 SPI_BAUDRATEPRESCALER_64 SPI_BAUDRATEPRESCALER_128 SPI_BAUDRATEPRESCALER_256
*/
void SPI2_SetSpeed(u8 SPI_BaudRatePrescaler)
{
    assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_BaudRatePrescaler));//�ж���Ч��
    __HAL_SPI_DISABLE(&SPI2_Handler);            //�ر�SPI
    SPI2_Handler.Instance->CR1&=0XFFC7;          //λ3-5���㣬�������ò�����
    SPI2_Handler.Instance->CR1|=SPI_BaudRatePrescaler;//����SPI�ٶ�
    __HAL_SPI_ENABLE(&SPI2_Handler);             //ʹ��SPI
    
}

//SPI2 ��дһ���ֽ�
//TxData:Ҫд����ֽ�
//����ֵ:��ȡ�����ֽ�
u8 SPI2_ReadWriteByte(u8 TxData)
{
    u8 Rxdata;
    HAL_SPI_TransmitReceive(&SPI2_Handler,&TxData,&Rxdata,1, 100); 
 	return Rxdata;          		    //�����յ�������		
}
#endif

#endif

/*________________________________________�û���ʱ��2����_________________________________________________________*/
#if STSTEM_TIM2_ENABLE
TIM_HandleTypeDef TIM2_Handler;

#if (STSTEM_TIM2_asPWMorCap == 0)
	TIM_OC_InitTypeDef 	TIM2_CH1Handler,TIM2_CH2Handler,TIM2_CH3Handler,TIM2_CH4Handler;
#elif (STSTEM_TIM2_asPWMorCap == 1)
	TIM_IC_InitTypeDef TIM2_CHxConfig;
#elif (STSTEM_TIM2_asPWMorCap == 3)
	TIM_Encoder_InitTypeDef sEncoderConfig;
#endif

void sys_TIM2_ENABLE(void)
{
	TIM_ClockConfigTypeDef sClockSourceConfig = {0};
	TIM_MasterConfigTypeDef sMasterConfig = {0};
	
	TIM2_Handler.Instance = 		TIM2;                          	//ͨ�ö�ʱ��2
    TIM2_Handler.Init.Prescaler=	(84-1);                 	   	//��Ƶϵ��
    TIM2_Handler.Init.CounterMode=	TIM_COUNTERMODE_UP;    			//���ϼ�����
    TIM2_Handler.Init.Period=		tim2arr;                       	//�Զ�װ��ֵ
    TIM2_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;			//ʱ�ӷ�Ƶ����
	TIM2_Handler.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
    HAL_TIM_Base_Init(&TIM2_Handler);
	
	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	HAL_TIM_ConfigClockSource(&TIM2_Handler, &sClockSourceConfig);
	
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	HAL_TIMEx_MasterConfigSynchronization(&TIM2_Handler, &sMasterConfig);
	
	#if (STSTEM_TIM2_asPWMorCap == 0)
		/*��ΪPWM*/
		HAL_TIM_PWM_Init(&TIM2_Handler);       //��ʼ��PWM
		if((STSTEM_TIM2PWM_CHANNEL_ENABLE) & B0000_0001)
		{
			TIM2_CH1Handler.OCMode=TIM_OCMODE_PWM1; 		//ģʽѡ��PWM1
			TIM2_CH1Handler.Pulse=tim2arr/2;            	//���ñȽ�ֵ,��ֵ����ȷ��ռ�ձȣ�Ĭ�ϱȽ�ֵΪ�Զ���װ��ֵ��һ��,��ռ�ձ�Ϊ50%
			TIM2_CH1Handler.OCPolarity=TIM_OCPOLARITY_LOW; 	//����Ƚϼ���Ϊ�� 
			HAL_TIM_PWM_ConfigChannel(&TIM2_Handler,&TIM2_CH1Handler,TIM_CHANNEL_1);//����TIM2ͨ��1
			__HAL_TIM_ENABLE_OCxPRELOAD(&TIM2_Handler, TIM_CHANNEL_1);
			HAL_TIM_PWM_Start(&TIM2_Handler,TIM_CHANNEL_1);	//����PWMͨ��1
		}
		if((STSTEM_TIM2PWM_CHANNEL_ENABLE) & B0000_0010)
		{
			TIM2_CH2Handler.OCMode=TIM_OCMODE_PWM1;
			TIM2_CH2Handler.Pulse=tim2arr/2;
			TIM2_CH2Handler.OCPolarity=TIM_OCPOLARITY_LOW;
			HAL_TIM_PWM_ConfigChannel(&TIM2_Handler,&TIM2_CH2Handler,TIM_CHANNEL_2);
			__HAL_TIM_ENABLE_OCxPRELOAD(&TIM2_Handler, TIM_CHANNEL_2);
			HAL_TIM_PWM_Start(&TIM2_Handler,TIM_CHANNEL_2);
		}
		if((STSTEM_TIM2PWM_CHANNEL_ENABLE) & B0000_0100)
		{
			TIM2_CH3Handler.OCMode=TIM_OCMODE_PWM1;
			TIM2_CH3Handler.Pulse=tim2arr/2;
			TIM2_CH3Handler.OCPolarity=TIM_OCPOLARITY_LOW;
			HAL_TIM_PWM_ConfigChannel(&TIM2_Handler,&TIM2_CH3Handler,TIM_CHANNEL_3);
			__HAL_TIM_ENABLE_OCxPRELOAD(&TIM2_Handler, TIM_CHANNEL_3);
			HAL_TIM_PWM_Start(&TIM2_Handler,TIM_CHANNEL_3);
		}
		if((STSTEM_TIM2PWM_CHANNEL_ENABLE) & B0000_1000)
		{
			TIM2_CH4Handler.OCMode=TIM_OCMODE_PWM1;
			TIM2_CH4Handler.Pulse=tim2arr/2;
			TIM2_CH4Handler.OCPolarity=TIM_OCPOLARITY_LOW;
			HAL_TIM_PWM_ConfigChannel(&TIM2_Handler,&TIM2_CH4Handler,TIM_CHANNEL_4);
			__HAL_TIM_ENABLE_OCxPRELOAD(&TIM2_Handler, TIM_CHANNEL_4);
			HAL_TIM_PWM_Start(&TIM2_Handler,TIM_CHANNEL_4);
		}
	#elif (STSTEM_TIM2_asPWMorCap == 1)
		/*��ΪCap*/
		TIM2_Handler.Init.Period=0XFFFF;       //�Զ�װ��ֵ
		HAL_TIM_IC_Init(&TIM2_Handler);			//��ʼ�����벶��ʱ������
		
		if(STSTEM_TIM2_Cap_trigV == 1)
			TIM2_CHxConfig.ICPolarity=TIM_ICPOLARITY_RISING;    //�����ز���
		else if(STSTEM_TIM2_Cap_trigV == 0)
			TIM2_CHxConfig.ICPolarity=TIM_ICPOLARITY_FALLING;    //�½��ز���
		else if(STSTEM_TIM2_Cap_trigV == 2)
			TIM2_CHxConfig.ICPolarity=TIM_ICPOLARITY_BOTHEDGE;    //˫���ز���
		
		TIM2_CHxConfig.ICSelection=TIM_ICSELECTION_DIRECTTI;//ӳ�䵽TI1��
		TIM2_CHxConfig.ICPrescaler=TIM_ICPSC_DIV1;          //���������Ƶ������Ƶ
		TIM2_CHxConfig.ICFilter=0;                          //���������˲��������˲�
		
		switch(STSTEM_TIM2_Cap_Channel)
		{
			case B0000_0001:				//ѡ��ͨ��1��Ϊ���벶��
				HAL_TIM_IC_ConfigChannel(&TIM2_Handler,&TIM2_CHxConfig,TIM_CHANNEL_1);//����TIM2ͨ��1
				HAL_TIM_IC_Start_IT(&TIM2_Handler,TIM_CHANNEL_1);   //����TIM2�Ĳ���ͨ��1�����ҿ��������ж�
				break;
			case B0000_0010:				//ѡ��ͨ��2��Ϊ���벶��
				HAL_TIM_IC_ConfigChannel(&TIM2_Handler,&TIM2_CHxConfig,TIM_CHANNEL_2);
				HAL_TIM_IC_Start_IT(&TIM2_Handler,TIM_CHANNEL_2);
				break;
			case B0000_0100:				//ѡ��ͨ��3��Ϊ���벶��
				HAL_TIM_IC_ConfigChannel(&TIM2_Handler,&TIM2_CHxConfig,TIM_CHANNEL_3);
				HAL_TIM_IC_Start_IT(&TIM2_Handler,TIM_CHANNEL_3);
				break;
			case B0000_1000:				//ѡ��ͨ��4��Ϊ���벶��
				HAL_TIM_IC_ConfigChannel(&TIM2_Handler,&TIM2_CHxConfig,TIM_CHANNEL_4);
				HAL_TIM_IC_Start_IT(&TIM2_Handler,TIM_CHANNEL_4);
				break;
			default:break;
		}
		__HAL_TIM_ENABLE_IT(&TIM2_Handler,TIM_IT_UPDATE);   //ʹ�ܸ����ж�
	#elif (STSTEM_TIM2_asPWMorCap == 3)
		TIM2_Handler.Init.Prescaler=	0;
		TIM2_Handler.Init.Period=		0xFFFF;

	  sEncoderConfig.EncoderMode        = TIM_ENCODERMODE_TI12;
	  sEncoderConfig.IC1Polarity        = TIM_ICPOLARITY_RISING;
	  sEncoderConfig.IC1Selection       = TIM_ICSELECTION_DIRECTTI;
	  sEncoderConfig.IC1Prescaler       = TIM_ICPSC_DIV1;
	  sEncoderConfig.IC1Filter          = 0;

	  sEncoderConfig.IC2Polarity        = TIM_ICPOLARITY_RISING;
	  sEncoderConfig.IC2Selection       = TIM_ICSELECTION_DIRECTTI;
	  sEncoderConfig.IC2Prescaler       = TIM_ICPSC_DIV1;
	  sEncoderConfig.IC2Filter          = 0;
	  __HAL_TIM_SET_COUNTER(&TIM2_Handler,0);
	  
	  HAL_TIM_Encoder_Init(&TIM2_Handler, &sEncoderConfig);
	  
	__HAL_TIM_CLEAR_IT(&TIM2_Handler, TIM_IT_UPDATE);  // ��������жϱ�־λ
	__HAL_TIM_URS_ENABLE(&TIM2_Handler);               // ���������������Ų��������ж�
	__HAL_TIM_ENABLE_IT(&TIM2_Handler,TIM_IT_UPDATE);  // ʹ�ܸ����ж�

	HAL_NVIC_SetPriority(TIM2_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(TIM2_IRQn);

	HAL_TIM_Encoder_Start(&TIM2_Handler, TIM_CHANNEL_ALL);
	
	#endif
	
	#if (STSTEM_TIM2_asPWMorCap == 2)
		#if (!STSTEM_TIM2_TI_ENABLE)
			HAL_TIM_Base_Start(&TIM2_Handler);	//����IT�Ŀ�����ʱ��
		#else
			HAL_TIM_Base_Start_IT(&TIM2_Handler);//��IT�Ŀ�����ʱ��
		#endif
	#endif
}

//��ʱ��2�жϷ�����
void TIM2_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&TIM2_Handler);
}

#if (STSTEM_TIM2_asPWMorCap == 3)				//���ʹ����������
void HAL_TIM_Encoder_MspInit(TIM_HandleTypeDef* htim_base)
{
  GPIO_InitTypeDef GPIO_InitStruct;
  if(htim_base->Instance==TIM2)
  {
    /* ������ʱ������ʱ��ʹ�� */
    __HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_TIM2_CLK_ENABLE();
    //__HAL_AFIO_REMAP_TIM2_ENABLE();
	  
	/*PA15 PB3*/
	  
    /* ��ʱ��ͨ��1��������IO��ʼ�� */
    GPIO_InitStruct.Pin = GPIO_PIN_15;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull=GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF1_TIM2;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* ��ʱ��ͨ��2��������IO��ʼ�� */
    GPIO_InitStruct.Pin = GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF1_TIM2;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
  }
}

/*�ڶ�ʱ������жϻص�����������мӼ�����*/
int32_t EncoderOverflowCount = 0;//��ʱ���������

/*��ȡһ�α������ĵ�ǰ����ֵ�����ڱ�ʾ��������ǰ�ľ���λ��*/
int32_t peek_TIM2_Encoder_Value(void)
{
	return ( int32_t )__HAL_TIM_GET_COUNTER(&TIM2_Handler);
}

/*��ȡһ����������������ת�ٶ� ��λ ת/�룬�������ŵ�TIM4��10ms��ʱ�ж���*/
float peek_TIM2_Encoder_Speed(void)
{
	float Speed = 0;
	int32_t CaptureNumber = 0;     // ���벶����
	
	/* �ٶȶ�ʱ���������ӿڲ���ֵ */
	CaptureNumber = ( int32_t )__HAL_TIM_GET_COUNTER(&TIM2_Handler) + EncoderOverflowCount*65536;
	
	Speed = ((float)CaptureNumber / (float)PPR);
	Speed *= 100.0f;	//������10ms����һ�Σ����ﻻ���1��
	
	/* ��������,�ȴ���һ�����¼�¼���� */
	EncoderOverflowCount = 0;
	__HAL_TIM_SET_COUNTER(&TIM2_Handler,0);
	
	return Speed;
}

#endif

#if (STSTEM_TIM2_asPWMorCap == 1)				//���ʹ��Cap����

//��ʱ��2��IC���ܵײ�������ʱ��ʹ�ܣ���������
//�˺����ᱻHAL_TIM_IC_Init()����
//htim:��ʱ�����
void HAL_TIM_IC_MspInit(TIM_HandleTypeDef *htim)
{
	GPIO_InitTypeDef GPIO_Initure;
	if(htim->Instance==TIM2)
	{
		__HAL_RCC_TIM2_CLK_ENABLE();            //ʹ��TIM2ʱ��
		//__HAL_AFIO_REMAP_TIM2_ENABLE();			/*TIM2ͨ��������ȫ��ӳ��ʹ�� (CH1/ETR/PA15, CH2/PB3, CH3/PB10, CH4/PB11)*/
		
		if(STSTEM_TIM2_Cap_trigV == 1)				//�����ز���
			GPIO_Initure.Pull=GPIO_PULLDOWN;        //����
		else if(STSTEM_TIM2_Cap_trigV == 0)			//�½��ز���
			GPIO_Initure.Pull=GPIO_PULLUP;        	//����
		else if(STSTEM_TIM2_Cap_trigV == 2)			//˫���ز���
			GPIO_Initure.Pull=GPIO_NOPULL;        	//����
		
		GPIO_Initure.Mode=GPIO_MODE_AF_PP; 			//��������
		GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;	//����
		GPIO_Initure.Alternate = GPIO_AF1_TIM2;
		
		switch(STSTEM_TIM2_Cap_Channel)
		{
			case B0000_0001:					//ѡ��ͨ��1��Ϊ���벶��
				__HAL_RCC_GPIOA_CLK_ENABLE();	//����GPIOAʱ��
				GPIO_Initure.Pin=GPIO_PIN_15;            //PA15
				HAL_GPIO_Init(GPIOA,&GPIO_Initure);
				break;
			case B0000_0010:					//ѡ��ͨ��2��Ϊ���벶��
				__HAL_RCC_GPIOB_CLK_ENABLE();
				GPIO_Initure.Pin=GPIO_PIN_3;            //PB3
				HAL_GPIO_Init(GPIOB,&GPIO_Initure);
				break;
			case B0000_0100:					//ѡ��ͨ��3��Ϊ���벶��
				__HAL_RCC_GPIOB_CLK_ENABLE();
				GPIO_Initure.Pin=GPIO_PIN_10;            //PB10
				HAL_GPIO_Init(GPIOB,&GPIO_Initure);
				break;
			case B0000_1000:					//ѡ��ͨ��4��Ϊ���벶��
				__HAL_RCC_GPIOB_CLK_ENABLE();
				GPIO_Initure.Pin=GPIO_PIN_11;            //PB11
				HAL_GPIO_Init(GPIOB,&GPIO_Initure);
				break;
			default:break;
		}
		
		HAL_NVIC_SetPriority(TIM2_IRQn,2,0);    //�����ж����ȼ�����ռ���ȼ�2�������ȼ�0
		HAL_NVIC_EnableIRQ(TIM2_IRQn);          //����ITM2�ж�ͨ��  
	}
}

//����״̬
//[7]:0,û�гɹ��Ĳ���;1,�ɹ�����һ��.
//[6]:0,��û���񵽵͵�ƽ;1,�Ѿ����񵽵͵�ƽ��.
//[5:0]:����͵�ƽ������Ĵ���
u8  TIM2CHx_CAPTURE_STA=0;							//���벶��״̬		    				
u16	TIM2CHx_CAPTURE_VAL;							//���벶��ֵ

/*��ȡ���һ��TIM2���벶�������ʱ�䣬��λ ���룬�������õĲ����ؽ��У�������ʱ��ص��ô˺���*/
float Peek_TIM2_Cap_Val(void)
{
	u8 Tim2overFlowTimes = 0;
	float temp = 0;
	if(TIM2CHx_CAPTURE_STA&0X80)        			//�ɹ�������һ�θߵ�ƽ
	{
		Tim2overFlowTimes = TIM2CHx_CAPTURE_STA & 0X3F;
		temp = (float)Tim2overFlowTimes;
		temp *= 65536.0f;		 	    			//���ʱ���ܺ�
		temp += (float)TIM2CHx_CAPTURE_VAL;      	//���ϵ�ǰ����ֵ�õ��ܵĸߵ�ƽʱ��
		TIM2CHx_CAPTURE_STA = 0;          			//������һ�β���
		temp /= 1000.0f;							//��λ ����
		return temp;
	}else{
		return 0.0f;
	}
}

//��ʱ�����벶���жϴ���ص��������ú�����HAL_TIM_IRQHandler�лᱻ����
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)//�����жϷ���ʱִ��
{
	if(htim==(&TIM2_Handler))
	{
			switch(STSTEM_TIM2_Cap_Channel)
			{
				case B0000_0001: //ͨ��1
					Process_TIM2_IC_CallBack_Channel_1();
					break;
				case B0000_0010: //ͨ��2
					Process_TIM2_IC_CallBack_Channel_2();
					break;
				case B0000_0100: //ͨ��3
					Process_TIM2_IC_CallBack_Channel_3();
					break;
				case B0000_1000: //ͨ��4
					Process_TIM2_IC_CallBack_Channel_4();
					break;
				default:break;
			}
	}	
}

void Process_TIM2_IC_CallBack_Channel_1(void)
{
	if((STSTEM_TIM2_Cap_trigV == 1)||(STSTEM_TIM2_Cap_trigV == 0))				//�����ػ����½��ز���
	{
		if((TIM2CHx_CAPTURE_STA&0X80)==0)				//��δ�ɹ�����
		{
			if(TIM2CHx_CAPTURE_STA&0X40)				//����һ���½��� 		
			{	  			
				TIM2CHx_CAPTURE_STA|=0X80;				//��ǳɹ�����һ�θߵ�ƽ����
				TIM2CHx_CAPTURE_VAL=HAL_TIM_ReadCapturedValue(&TIM2_Handler,TIM_CHANNEL_1);//��ȡ��ǰ�Ĳ���ֵ.
				TIM_RESET_CAPTUREPOLARITY(&TIM2_Handler,TIM_CHANNEL_1);   //һ��Ҫ�����ԭ�������ã���
				if(STSTEM_TIM2_Cap_trigV == 1)	//�������Ϊ�����ز���
				{
					TIM_SET_CAPTUREPOLARITY(&TIM2_Handler,TIM_CHANNEL_1,TIM_ICPOLARITY_RISING);//����TIM2ͨ��1�����ز���
				}else{
					TIM_SET_CAPTUREPOLARITY(&TIM2_Handler,TIM_CHANNEL_1,TIM_ICPOLARITY_FALLING);//��ʱ��2ͨ��1����Ϊ�½��ز���
				}
				
			}else  										//��δ��ʼ,��һ�β���������
			{
				TIM2CHx_CAPTURE_STA=0;					//���
				TIM2CHx_CAPTURE_VAL=0;
				TIM2CHx_CAPTURE_STA|=0X40;				//��ǲ�����������
				__HAL_TIM_DISABLE(&TIM2_Handler);      	//�رն�ʱ��2
				__HAL_TIM_SET_COUNTER(&TIM2_Handler,0);
				TIM_RESET_CAPTUREPOLARITY(&TIM2_Handler,TIM_CHANNEL_1);   //һ��Ҫ�����ԭ�������ã���
				
				if(STSTEM_TIM2_Cap_trigV == 1)	//�������Ϊ�����ز���
				{
					TIM_SET_CAPTUREPOLARITY(&TIM2_Handler,TIM_CHANNEL_1,TIM_ICPOLARITY_FALLING);//��ʱ��2ͨ��1����Ϊ�½��ز���
				}else{
					TIM_SET_CAPTUREPOLARITY(&TIM2_Handler,TIM_CHANNEL_1,TIM_ICPOLARITY_RISING);//��ʱ��2ͨ��1����Ϊ�����ز���
				}
				
				__HAL_TIM_ENABLE(&TIM2_Handler);		//ʹ�ܶ�ʱ��2
			}		    
		}
	}else if(STSTEM_TIM2_Cap_trigV == 2)				//˫�ز���
	{
		if((TIM2CHx_CAPTURE_STA&0X80)==0)				//��δ�ɹ�����
		{
			if(TIM2CHx_CAPTURE_STA&0X40)				//�Ѿ�����һ����
			{
				TIM2CHx_CAPTURE_STA|=0X80;				//��ǳɹ�����һ������
				TIM2CHx_CAPTURE_VAL=HAL_TIM_ReadCapturedValue(&TIM2_Handler,TIM_CHANNEL_1);//��ȡ��ǰ�Ĳ���ֵ
			}else										//��δ����һ����
			{
				TIM2CHx_CAPTURE_STA=0;					//���
				TIM2CHx_CAPTURE_VAL=0;
				TIM2CHx_CAPTURE_STA|=0X40;				//��ǲ�����һ����
				__HAL_TIM_DISABLE(&TIM2_Handler);      	//�رն�ʱ��2
				__HAL_TIM_SET_COUNTER(&TIM2_Handler,0);
				__HAL_TIM_ENABLE(&TIM2_Handler);		//ʹ�ܶ�ʱ��2
			}
		}
	}
}

void Process_TIM2_IC_CallBack_Channel_2(void)
{
	if((STSTEM_TIM2_Cap_trigV == 1)||(STSTEM_TIM2_Cap_trigV == 0))
	{
		if((TIM2CHx_CAPTURE_STA&0X80)==0)
		{
			if(TIM2CHx_CAPTURE_STA&0X40)	
			{	  			
				TIM2CHx_CAPTURE_STA|=0X80;	
				TIM2CHx_CAPTURE_VAL=HAL_TIM_ReadCapturedValue(&TIM2_Handler,TIM_CHANNEL_2);
				TIM_RESET_CAPTUREPOLARITY(&TIM2_Handler,TIM_CHANNEL_2); 
				if(STSTEM_TIM2_Cap_trigV == 1)
				{
					TIM_SET_CAPTUREPOLARITY(&TIM2_Handler,TIM_CHANNEL_2,TIM_ICPOLARITY_RISING);
				}else{
					TIM_SET_CAPTUREPOLARITY(&TIM2_Handler,TIM_CHANNEL_2,TIM_ICPOLARITY_FALLING);
				}
				
			}else 
			{
				TIM2CHx_CAPTURE_STA=0;
				TIM2CHx_CAPTURE_VAL=0;
				TIM2CHx_CAPTURE_STA|=0X40;
				__HAL_TIM_DISABLE(&TIM2_Handler);
				__HAL_TIM_SET_COUNTER(&TIM2_Handler,0);
				TIM_RESET_CAPTUREPOLARITY(&TIM2_Handler,TIM_CHANNEL_2); 
				
				if(STSTEM_TIM2_Cap_trigV == 1)	
				{
					TIM_SET_CAPTUREPOLARITY(&TIM2_Handler,TIM_CHANNEL_2,TIM_ICPOLARITY_FALLING);
				}else{
					TIM_SET_CAPTUREPOLARITY(&TIM2_Handler,TIM_CHANNEL_2,TIM_ICPOLARITY_RISING);
				}
				
				__HAL_TIM_ENABLE(&TIM2_Handler);
			}		    
		}
	}else if(STSTEM_TIM2_Cap_trigV == 2)				//˫�ز���
	{
		if((TIM2CHx_CAPTURE_STA&0X80)==0)				//��δ�ɹ�����
		{
			if(TIM2CHx_CAPTURE_STA&0X40)				//�Ѿ�����һ����
			{
				TIM2CHx_CAPTURE_STA|=0X80;				//��ǳɹ�����һ������
				TIM2CHx_CAPTURE_VAL=HAL_TIM_ReadCapturedValue(&TIM2_Handler,TIM_CHANNEL_2);//��ȡ��ǰ�Ĳ���ֵ
			}else										//��δ����һ����
			{
				TIM2CHx_CAPTURE_STA=0;					//���
				TIM2CHx_CAPTURE_VAL=0;
				TIM2CHx_CAPTURE_STA|=0X40;				//��ǲ�����һ����
				__HAL_TIM_DISABLE(&TIM2_Handler);      	//�رն�ʱ��2
				__HAL_TIM_SET_COUNTER(&TIM2_Handler,0);
				__HAL_TIM_ENABLE(&TIM2_Handler);		//ʹ�ܶ�ʱ��2
			}
		}
	}
}

void Process_TIM2_IC_CallBack_Channel_3(void)
{
	if((STSTEM_TIM2_Cap_trigV == 1)||(STSTEM_TIM2_Cap_trigV == 0))
	{
		if((TIM2CHx_CAPTURE_STA&0X80)==0)
		{
			if(TIM2CHx_CAPTURE_STA&0X40)	
			{	  			
				TIM2CHx_CAPTURE_STA|=0X80;	
				TIM2CHx_CAPTURE_VAL=HAL_TIM_ReadCapturedValue(&TIM2_Handler,TIM_CHANNEL_3);
				TIM_RESET_CAPTUREPOLARITY(&TIM2_Handler,TIM_CHANNEL_3); 
				if(STSTEM_TIM2_Cap_trigV == 1)
				{
					TIM_SET_CAPTUREPOLARITY(&TIM2_Handler,TIM_CHANNEL_3,TIM_ICPOLARITY_RISING);
				}else{
					TIM_SET_CAPTUREPOLARITY(&TIM2_Handler,TIM_CHANNEL_3,TIM_ICPOLARITY_FALLING);
				}
				
			}else 
			{
				TIM2CHx_CAPTURE_STA=0;
				TIM2CHx_CAPTURE_VAL=0;
				TIM2CHx_CAPTURE_STA|=0X40;
				__HAL_TIM_DISABLE(&TIM2_Handler);
				__HAL_TIM_SET_COUNTER(&TIM2_Handler,0);
				TIM_RESET_CAPTUREPOLARITY(&TIM2_Handler,TIM_CHANNEL_3); 
				
				if(STSTEM_TIM2_Cap_trigV == 1)	
				{
					TIM_SET_CAPTUREPOLARITY(&TIM2_Handler,TIM_CHANNEL_3,TIM_ICPOLARITY_FALLING);
				}else{
					TIM_SET_CAPTUREPOLARITY(&TIM2_Handler,TIM_CHANNEL_3,TIM_ICPOLARITY_RISING);
				}
				
				__HAL_TIM_ENABLE(&TIM2_Handler);
			}		    
		}
	}else if(STSTEM_TIM2_Cap_trigV == 2)				//˫�ز���
	{
		if((TIM2CHx_CAPTURE_STA&0X80)==0)				//��δ�ɹ�����
		{
			if(TIM2CHx_CAPTURE_STA&0X40)				//�Ѿ�����һ����
			{
				TIM2CHx_CAPTURE_STA|=0X80;				//��ǳɹ�����һ������
				TIM2CHx_CAPTURE_VAL=HAL_TIM_ReadCapturedValue(&TIM2_Handler,TIM_CHANNEL_3);//��ȡ��ǰ�Ĳ���ֵ
			}else										//��δ����һ����
			{
				TIM2CHx_CAPTURE_STA=0;					//���
				TIM2CHx_CAPTURE_VAL=0;
				TIM2CHx_CAPTURE_STA|=0X40;				//��ǲ�����һ����
				__HAL_TIM_DISABLE(&TIM2_Handler);      	//�رն�ʱ��2
				__HAL_TIM_SET_COUNTER(&TIM2_Handler,0);
				__HAL_TIM_ENABLE(&TIM2_Handler);		//ʹ�ܶ�ʱ��2
			}
		}
	}
}
void Process_TIM2_IC_CallBack_Channel_4(void)
{
	if((STSTEM_TIM2_Cap_trigV == 1)||(STSTEM_TIM2_Cap_trigV == 0))
	{
		if((TIM2CHx_CAPTURE_STA&0X80)==0)
		{
			if(TIM2CHx_CAPTURE_STA&0X40)	
			{	  			
				TIM2CHx_CAPTURE_STA|=0X80;	
				TIM2CHx_CAPTURE_VAL=HAL_TIM_ReadCapturedValue(&TIM2_Handler,TIM_CHANNEL_4);
				TIM_RESET_CAPTUREPOLARITY(&TIM2_Handler,TIM_CHANNEL_4); 
				if(STSTEM_TIM2_Cap_trigV == 1)
				{
					TIM_SET_CAPTUREPOLARITY(&TIM2_Handler,TIM_CHANNEL_4,TIM_ICPOLARITY_RISING);
				}else{
					TIM_SET_CAPTUREPOLARITY(&TIM2_Handler,TIM_CHANNEL_4,TIM_ICPOLARITY_FALLING);
				}
				
			}else 
			{
				TIM2CHx_CAPTURE_STA=0;
				TIM2CHx_CAPTURE_VAL=0;
				TIM2CHx_CAPTURE_STA|=0X40;
				__HAL_TIM_DISABLE(&TIM2_Handler);
				__HAL_TIM_SET_COUNTER(&TIM2_Handler,0);
				TIM_RESET_CAPTUREPOLARITY(&TIM2_Handler,TIM_CHANNEL_4); 
				
				if(STSTEM_TIM2_Cap_trigV == 1)	
				{
					TIM_SET_CAPTUREPOLARITY(&TIM2_Handler,TIM_CHANNEL_4,TIM_ICPOLARITY_FALLING);
				}else{
					TIM_SET_CAPTUREPOLARITY(&TIM2_Handler,TIM_CHANNEL_4,TIM_ICPOLARITY_RISING);
				}
				
				__HAL_TIM_ENABLE(&TIM2_Handler);
			}		    
		}
	}else if(STSTEM_TIM2_Cap_trigV == 2)				//˫�ز���
	{
		if((TIM2CHx_CAPTURE_STA&0X80)==0)				//��δ�ɹ�����
		{
			if(TIM2CHx_CAPTURE_STA&0X40)				//�Ѿ�����һ����
			{
				TIM2CHx_CAPTURE_STA|=0X80;				//��ǳɹ�����һ������
				TIM2CHx_CAPTURE_VAL=HAL_TIM_ReadCapturedValue(&TIM2_Handler,TIM_CHANNEL_4);//��ȡ��ǰ�Ĳ���ֵ
			}else										//��δ����һ����
			{
				TIM2CHx_CAPTURE_STA=0;					//���
				TIM2CHx_CAPTURE_VAL=0;
				TIM2CHx_CAPTURE_STA|=0X40;				//��ǲ�����һ����
				__HAL_TIM_DISABLE(&TIM2_Handler);      	//�رն�ʱ��2
				__HAL_TIM_SET_COUNTER(&TIM2_Handler,0);
				__HAL_TIM_ENABLE(&TIM2_Handler);		//ʹ�ܶ�ʱ��2
			}
		}
	}
}


#endif
#if (STSTEM_TIM2_asPWMorCap == 0)				//���ʹ��PWM
	//����TIM2ͨ����ռ�ձ�
	//percent:ռ�ձȰٷ���
	void TIM2_set_Channel_Pulse(u8 channel,float percent)
	{
		float compare;
		if(percent < 0) percent = 0f;
		if(percent > 100) percent = 100.0f;
		percent /= 100.0f;
		compare = ((float)tim2arr) * percent;
		switch(channel)
		{
			case TIM2PWM_Channel_1: TIM2->CCR1=(u32)compare;break;
			case TIM2PWM_Channel_2: TIM2->CCR2=(u32)compare;break;
			case TIM2PWM_Channel_3: TIM2->CCR3=(u32)compare;break;
			case TIM2PWM_Channel_4: TIM2->CCR4=(u32)compare;break;
			default:break;
		}
	}
#endif

#endif


/*________________________________________�û���ʱ��6����_________________________________________________________*/
#if STSTEM_TIM6_ENABLE

TIM_HandleTypeDef TIM6_Handler;
void sys_TIM6_ENABLE(void)
{
	TIM_MasterConfigTypeDef sMasterConfig = {0};
	
	TIM6_Handler.Instance=TIM6;                          		//������ʱ��6
    TIM6_Handler.Init.Prescaler = (84-1);                     	//��Ƶϵ��
    TIM6_Handler.Init.CounterMode=TIM_COUNTERMODE_UP;    		//���ϼ�����
    TIM6_Handler.Init.Period = tim6arr;                        	//�Զ�װ��ֵ
    TIM6_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;		//ʱ�ӷ�Ƶ����
	TIM6_Handler.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
    HAL_TIM_Base_Init(&TIM6_Handler);
	
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	HAL_TIMEx_MasterConfigSynchronization(&TIM6_Handler, &sMasterConfig);
	
    HAL_TIM_Base_Start_IT(&TIM6_Handler); //ʹ�ܶ�ʱ��6�Ͷ�ʱ��6�����жϣ�TIM_IT_UPDATE 
}


//��ʱ��6�жϷ�����
void TIM6_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&TIM6_Handler);
}

#endif

/*________________________________________�û���ʱ��7����_________________________________________________________*/
#if STSTEM_TIM7_ENABLE

TIM_HandleTypeDef TIM7_Handler;
void sys_TIM7_ENABLE(void)
{
	TIM_MasterConfigTypeDef sMasterConfig = {0};
	
	TIM7_Handler.Instance=TIM7;                          		//������ʱ��7
    TIM7_Handler.Init.Prescaler = (84-1);                     	//��Ƶϵ��
    TIM7_Handler.Init.CounterMode=TIM_COUNTERMODE_UP;    		//���ϼ�����
    TIM7_Handler.Init.Period = tim7arr;                        	//�Զ�װ��ֵ
    TIM7_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;		//ʱ�ӷ�Ƶ����
	TIM7_Handler.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
    HAL_TIM_Base_Init(&TIM7_Handler);
	
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	HAL_TIMEx_MasterConfigSynchronization(&TIM7_Handler, &sMasterConfig);
    
    HAL_TIM_Base_Start_IT(&TIM7_Handler); //ʹ�ܶ�ʱ��6�Ͷ�ʱ��7�����жϣ�TIM_IT_UPDATE 
}


//��ʱ��7�жϷ�����
void TIM7_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&TIM7_Handler);
}

#endif




/*__________________________________�͹���StandbyMode__________________________________________*/
#if SYSTEM_StdbyWKUP_ENABLE

void sys_StdbyWKUP_ENABLE(void)
{
	#if !SYSTEM_SUPPORT_OS
    GPIO_InitTypeDef GPIO_Initure;
    __HAL_RCC_GPIOA_CLK_ENABLE();			//����GPIOAʱ��
	
    GPIO_Initure.Pin=GPIO_PIN_0;            //PA0
    GPIO_Initure.Mode=GPIO_MODE_IT_RISING;  //�ж�,������
    GPIO_Initure.Pull=GPIO_PULLDOWN;        //����
    GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;//����
    HAL_GPIO_Init(GPIOA,&GPIO_Initure);
	
	/*PA0�ⲿ�жϺ����� HAL_GPIO_EXTI_Callback ��*/
    
//    //����Ƿ�����������
//    if(Check_WKUP()==0)
//    {
//        Sys_Enter_Standby();//���ǿ������������ģʽ
//    }

    HAL_NVIC_SetPriority(EXTI0_IRQn,2,0);
    HAL_NVIC_EnableIRQ(EXTI0_IRQn);
	
	#else
	
    GPIO_InitTypeDef GPIO_Initure;
    __HAL_RCC_GPIOA_CLK_ENABLE();			//����GPIOAʱ��
	
    GPIO_Initure.Pin=GPIO_PIN_0;            //PA0
    GPIO_Initure.Mode=GPIO_MODE_INPUT;  //������
    GPIO_Initure.Pull=GPIO_PULLDOWN;        //����
    GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;//����
    HAL_GPIO_Init(GPIOA,&GPIO_Initure);
	
	#endif
}


//ϵͳ�������ģʽ
void Sys_Enter_Standby(void)
{
	while(WKUP_KD == 1){;} //WKUP�����ɿ����������ʱ1s������׼���ʹ���ػ�ǰ������
	HAL_Delay(500);
	while(WKUP_KD == 1){;}
	HAL_Delay(500);
	
    __HAL_RCC_APB2_FORCE_RESET();       //��λ����IO�� 
	__HAL_RCC_PWR_CLK_ENABLE();
		
//	#if SYSTEM_RTC_ENABLE
//		__HAL_RCC_BACKUPRESET_FORCE();      //��λ��������
//		HAL_PWR_EnableBkUpAccess();         //���������ʹ��  
//		
//		//STM32F4,��������RTC����жϺ�,�����ȹر�RTC�ж�,�����жϱ�־λ,Ȼ����������
//		//RTC�ж�,�ٽ������ģʽ�ſ�����������,�����������.	
//		__HAL_PWR_CLEAR_FLAG(PWR_FLAG_SB);
//		__HAL_RTC_WRITEPROTECTION_DISABLE(&RTC_Handler);//�ر�RTCд����
//		
//		//�ر�RTC����жϣ�����RTC����
//		__HAL_RTC_WAKEUPTIMER_DISABLE_IT(&RTC_Handler,RTC_IT_WUT);
//		__HAL_RTC_TIMESTAMP_DISABLE_IT(&RTC_Handler,RTC_IT_TS);
//		__HAL_RTC_ALARM_DISABLE_IT(&RTC_Handler,RTC_IT_ALRA|RTC_IT_ALRB);
//		
//		//���RTC����жϱ�־λ
//		__HAL_RTC_ALARM_CLEAR_FLAG(&RTC_Handler,RTC_FLAG_ALRAF|RTC_FLAG_ALRBF);
//		__HAL_RTC_TIMESTAMP_CLEAR_FLAG(&RTC_Handler,RTC_FLAG_TSF); 
//		__HAL_RTC_WAKEUPTIMER_CLEAR_FLAG(&RTC_Handler,RTC_FLAG_WUTF);
//		
//		__HAL_RCC_BACKUPRESET_RELEASE();                    //��������λ����
//		__HAL_RTC_WRITEPROTECTION_ENABLE(&RTC_Handler);     //ʹ��RTCд����
//	#endif
	
    __HAL_PWR_CLEAR_FLAG(PWR_FLAG_WU);                  //���Wake_UP��־
    HAL_PWR_EnableWakeUpPin(PWR_WAKEUP_PIN1);           //����WKUP���ڻ���
    HAL_PWR_EnterSTANDBYMode();                         //�������ģʽ     
}

//���WKUP�ŵ��ź�
//����ֵ1:��������3s����
//      0:����Ĵ���	
u8 Check_WKUP(void) 
{
	u8 t=0;	//��¼���µ�ʱ��
	while(1)
	{
		if(WKUP_KD)
		{
			t++;			//�Ѿ������� 
			HAL_Delay(30);
			if(t>=100)		//���³���3����
			{
				return 1; 	//����3s������
			}
		}else 
		{ 
			return 0; //���²���3��
		}
	}
}

void sys_CheckWKUP_4RTOS(void)
{
	static u8 t=0;	//��¼���µ�ʱ��
	if(WKUP_KD)
	{
		t++;			//�Ѿ������� 
		HAL_Delay(30);
		if(t>=100)		//���³���3����
		{
			Sys_Enter_Standby();//����3s�����ˣ��������ģʽ
		}
	}else 
	{} //���²���3��
}

#endif



/*________________________________________�û�ADC1����_________________________________________________________*/
#if SYSTEM_ADC1_ENABLE


void ADC_RegularChannelConfig(ADC_HandleTypeDef *AdcHandle, uint32_t Channel, uint32_t Rank, uint32_t SamplingTime)
{
    ADC_ChannelConfTypeDef ADC1_ChanConf;      
    ADC1_ChanConf.Channel      = Channel;                      		//ͨ��
    ADC1_ChanConf.Rank         = Rank;                          	//�ڼ�������
    ADC1_ChanConf.SamplingTime = SamplingTime;                  	//����ʱ�� 
    HAL_ADC_ConfigChannel(AdcHandle,&ADC1_ChanConf);              	//ͨ������
}

ADC_HandleTypeDef ADC1_Handler;		//ADC���
void sys_ADC1_ENABLE(void)
{
	u8 i;
	i = 1;
	
	#if SYSTEM_ADC1_useScan
		/*�ȳ�ʼ��DMA���ٳ�ʼ��ADC*/
		ADC_DMA_Cfg();
		//HAL_ADC_Start_DMA(&ADC1_Handler, (uint32_t*)&adValue,12);	//��ʼDMA��ָ���������飬���һ������Ϊ���ݳ��ȣ�Ҫ�����ٴΣ�
	#endif
	
    ADC1_Handler.Instance=ADC1;
	ADC1_Handler.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2; //Ҳ��֪����ʱ���Ƕ���
    ADC1_Handler.Init.DataAlign=ADC_DATAALIGN_RIGHT;             //�Ҷ���
	ADC1_Handler.Init.Resolution = ADC_RESOLUTION_12B;
	
	if(!SYSTEM_ADC1_useScan)
	{
		ADC1_Handler.Init.ScanConvMode=DISABLE;                  //��ɨ��ģʽ
		ADC1_Handler.Init.ContinuousConvMode=DISABLE,
		ADC1_Handler.Init.DMAContinuousRequests = DISABLE;
		ADC1_Handler.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
	}else{
		ADC1_Handler.Init.ScanConvMode=ENABLE;					 //ɨ��ģʽ
		
		if(SYSTEM_ADC1_useCircular)
		{	ADC1_Handler.Init.ContinuousConvMode=ENABLE;               //����ת�� ����������ת�������ͨ����ȫ��ͨ�������Զ�������һ��ת����������������һ��ת��һ�Σ�
			ADC1_Handler.Init.DMAContinuousRequests = ENABLE;
			ADC1_Handler.Init.EOCSelection = ADC_EOC_SEQ_CONV;
		}
		else{
			ADC1_Handler.Init.ContinuousConvMode=DISABLE;
			ADC1_Handler.Init.DMAContinuousRequests = DISABLE;
			ADC1_Handler.Init.EOCSelection = ADC_EOC_SEQ_CONV;
		}
	}
	
	if(SYSTEM_ADC1_useScan)
		ADC1_Handler.Init.NbrOfConversion=SYSTEM_ADC1_useChanlNum;   	//n��ת���ڹ���������
	else ADC1_Handler.Init.NbrOfConversion=1;							//ֻת����������1
	
    ADC1_Handler.Init.DiscontinuousConvMode=DISABLE;             //��ֹ����������ģʽ
    ADC1_Handler.Init.NbrOfDiscConversion=0;                     //����������ͨ����Ϊ0
	ADC1_Handler.Init.ExternalTrigConv=ADC_SOFTWARE_START;  	 //�������
	ADC1_Handler.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
    HAL_ADC_Init(&ADC1_Handler);                                 //��ʼ�� 
	
	//HAL_ADCEx_Calibration_Start(&ADC1_Handler);					 //У׼ADC
	
	if(SYSTEM_ADC1_useScan)		//�������ɨ�裬�������ͨ�������뵽��������
	{               
		if((SYSTEM_ADC1_useChanl) & B1in16) 	ADC_RegularChannelConfig(&ADC1_Handler, ADC_CHANNEL_0, (uint32_t)(i++), ADC_SAMPLETIME_56CYCLES);
		if((SYSTEM_ADC1_useChanl) & B2in16) 	ADC_RegularChannelConfig(&ADC1_Handler, ADC_CHANNEL_1, (uint32_t)(i++), ADC_SAMPLETIME_56CYCLES);
		if((SYSTEM_ADC1_useChanl) & B3in16) 	ADC_RegularChannelConfig(&ADC1_Handler, ADC_CHANNEL_2, (uint32_t)(i++), ADC_SAMPLETIME_56CYCLES);
		if((SYSTEM_ADC1_useChanl) & B4in16) 	ADC_RegularChannelConfig(&ADC1_Handler, ADC_CHANNEL_3, (uint32_t)(i++), ADC_SAMPLETIME_56CYCLES);
		if((SYSTEM_ADC1_useChanl) & B5in16) 	ADC_RegularChannelConfig(&ADC1_Handler, ADC_CHANNEL_4, (uint32_t)(i++), ADC_SAMPLETIME_56CYCLES);
		if((SYSTEM_ADC1_useChanl) & B6in16) 	ADC_RegularChannelConfig(&ADC1_Handler, ADC_CHANNEL_5, (uint32_t)(i++), ADC_SAMPLETIME_56CYCLES);
		if((SYSTEM_ADC1_useChanl) & B7in16) 	ADC_RegularChannelConfig(&ADC1_Handler, ADC_CHANNEL_6, (uint32_t)(i++), ADC_SAMPLETIME_56CYCLES);
		if((SYSTEM_ADC1_useChanl) & B8in16) 	ADC_RegularChannelConfig(&ADC1_Handler, ADC_CHANNEL_7, (uint32_t)(i++), ADC_SAMPLETIME_56CYCLES);
		if((SYSTEM_ADC1_useChanl) & B9in16) 	ADC_RegularChannelConfig(&ADC1_Handler, ADC_CHANNEL_8, (uint32_t)(i++), ADC_SAMPLETIME_56CYCLES);
		if((SYSTEM_ADC1_useChanl) & B10in16)	ADC_RegularChannelConfig(&ADC1_Handler, ADC_CHANNEL_9, (uint32_t)(i++), ADC_SAMPLETIME_56CYCLES);
		if((SYSTEM_ADC1_useChanl) & B11in16)	ADC_RegularChannelConfig(&ADC1_Handler, ADC_CHANNEL_10, (uint32_t)(i++), ADC_SAMPLETIME_56CYCLES);
		if((SYSTEM_ADC1_useChanl) & B12in16)	ADC_RegularChannelConfig(&ADC1_Handler, ADC_CHANNEL_11, (uint32_t)(i++), ADC_SAMPLETIME_56CYCLES);
		if((SYSTEM_ADC1_useChanl) & B13in16)	ADC_RegularChannelConfig(&ADC1_Handler, ADC_CHANNEL_12, (uint32_t)(i++), ADC_SAMPLETIME_56CYCLES);
		if((SYSTEM_ADC1_useChanl) & B14in16)	ADC_RegularChannelConfig(&ADC1_Handler, ADC_CHANNEL_13, (uint32_t)(i++), ADC_SAMPLETIME_56CYCLES);
		if((SYSTEM_ADC1_useChanl) & B15in16) 	ADC_RegularChannelConfig(&ADC1_Handler, ADC_CHANNEL_14, (uint32_t)(i++), ADC_SAMPLETIME_56CYCLES);
		//if((SYSTEM_ADC1_useChanl) & 0x10) 	ADC_RegularChannelConfig(&ADC1_Handler, ADC_CHANNEL_15, (uint32_t)(i++), ADC_SAMPLETIME_56CYCLES);
		
		if((SYSTEM_ADC1_useChanl) & B16in16) 	ADC_RegularChannelConfig(&ADC1_Handler, ADC_CHANNEL_TEMPSENSOR, (uint32_t)(i++), ADC_SAMPLETIME_56CYCLES);
	}
}

//�˺����ᱻHAL_ADC_Init()����
//hadc:ADC���
void HAL_ADC_MspInit(ADC_HandleTypeDef* hadc)
{
/*	
	ͨ����	0	1	2	3	4	5	6	7	8	9	10	11	12	13	14	15	   16		     17
	IO	��	A0	A1	A2	A3	A4	A5	A6	A7	B0	B1	C0	C1	C2	C3	C4	C5	�ڲ��¶�	�ڲ��ο���ѹ
*/
	if(hadc->Instance == ADC1)
	{
		GPIO_InitTypeDef GPIO_Initure;
		__HAL_RCC_ADC1_CLK_ENABLE();            //ʹ��ADC1ʱ��
		__HAL_RCC_GPIOA_CLK_ENABLE();			//����GPIOAʱ��
		__HAL_RCC_GPIOB_CLK_ENABLE();
		
		GPIO_Initure.Mode=GPIO_MODE_ANALOG;     //ģ��
		GPIO_Initure.Pull=GPIO_NOPULL;          //����������
		               
		if((SYSTEM_ADC1_useChanl) & B1in16) {
			GPIO_Initure.Pin=GPIO_PIN_0; 
			HAL_GPIO_Init(GPIOA,&GPIO_Initure);
			}
		if((SYSTEM_ADC1_useChanl) & B2in16) {
			GPIO_Initure.Pin=GPIO_PIN_1; 
			HAL_GPIO_Init(GPIOA,&GPIO_Initure);
			}
		if((SYSTEM_ADC1_useChanl) & B3in16) {
			GPIO_Initure.Pin=GPIO_PIN_2; 
			HAL_GPIO_Init(GPIOA,&GPIO_Initure);
			}
		if((SYSTEM_ADC1_useChanl) & B4in16) {
			GPIO_Initure.Pin=GPIO_PIN_3; 
			HAL_GPIO_Init(GPIOA,&GPIO_Initure);
			}
		if((SYSTEM_ADC1_useChanl) & B5in16) {GPIO_Initure.Pin=GPIO_PIN_4; HAL_GPIO_Init(GPIOA,&GPIO_Initure);}
		if((SYSTEM_ADC1_useChanl) & B6in16) {GPIO_Initure.Pin=GPIO_PIN_5; HAL_GPIO_Init(GPIOA,&GPIO_Initure);}
		if((SYSTEM_ADC1_useChanl) & B7in16) {GPIO_Initure.Pin=GPIO_PIN_6; HAL_GPIO_Init(GPIOA,&GPIO_Initure);}
		if((SYSTEM_ADC1_useChanl) & B8in16) {GPIO_Initure.Pin=GPIO_PIN_7; HAL_GPIO_Init(GPIOA,&GPIO_Initure);}
		if((SYSTEM_ADC1_useChanl) & B9in16) {GPIO_Initure.Pin=GPIO_PIN_0; HAL_GPIO_Init(GPIOB,&GPIO_Initure);}
		if((SYSTEM_ADC1_useChanl) & B10in16) {GPIO_Initure.Pin=GPIO_PIN_1; HAL_GPIO_Init(GPIOB,&GPIO_Initure);}
		if((SYSTEM_ADC1_useChanl) & B11in16) {GPIO_Initure.Pin=GPIO_PIN_0; HAL_GPIO_Init(GPIOC,&GPIO_Initure);}
		if((SYSTEM_ADC1_useChanl) & B12in16) {GPIO_Initure.Pin=GPIO_PIN_1; HAL_GPIO_Init(GPIOC,&GPIO_Initure);}
		if((SYSTEM_ADC1_useChanl) & B13in16) {GPIO_Initure.Pin=GPIO_PIN_2; HAL_GPIO_Init(GPIOC,&GPIO_Initure);}
		if((SYSTEM_ADC1_useChanl) & B14in16) {GPIO_Initure.Pin=GPIO_PIN_3; HAL_GPIO_Init(GPIOC,&GPIO_Initure);}
		if((SYSTEM_ADC1_useChanl) & B15in16) {GPIO_Initure.Pin=GPIO_PIN_4; HAL_GPIO_Init(GPIOC,&GPIO_Initure);}
		//if((SYSTEM_ADC1_useChanl) & B166in16) {GPIO_Initure.Pin=GPIO_PIN_5; HAL_GPIO_Init(GPIOC,&GPIO_Initure);}  �����ڲ��¶�ͨ������16��ADC1ͨ��������
	}
}


u16 adValue[SYSTEM_ADC1_useChanlNum];		  /*DMA1��ADCת��������͵�Ŀ��λ��*/
u8 adValueDone = 0;			/*DMA��ADC1��ֵ���͵�adValue��ɱ�־*/

//���ADCֵ
//ch: ͨ��ֵ 0~16��ȡֵ��ΧΪ��ADC_CHANNEL_0~ADC_CHANNEL_16
//����ֵ:ת�����
u16 Get_Adc(u32 ch)   
{
	ADC_ChannelConfTypeDef ADC1_ChanConf;
	if (!SYSTEM_ADC1_useScan)
	{	
		ADC1_ChanConf.Channel=ch;                                   //ͨ��
		ADC1_ChanConf.Rank=1;                                       //��1�����У�����1
		ADC1_ChanConf.SamplingTime=ADC_SAMPLETIME_480CYCLES;      	//����ʱ��               
		HAL_ADC_ConfigChannel(&ADC1_Handler,&ADC1_ChanConf);        //ͨ������
		
		HAL_ADC_Start(&ADC1_Handler);                               //����ADC
		HAL_ADC_PollForConversion(&ADC1_Handler,2);                 //����
		return (u16)HAL_ADC_GetValue(&ADC1_Handler);	        	//�������һ��ADC1�������ת�����
	}else
	{
		return 2333;
	}
}

u32 Get_Adc_Average(u32 ch,u8 times)
{
	u32 temp_val = 0;
	u8 t;
	
	for(t=0;t < times;t++)
	{
		temp_val += Get_Adc(ch);
		HAL_Delay(1);
	}
	return (temp_val/times);
}

/*��AD�ɼ��¶�ͨ����ԭʼֵ��ת��Ϊ�¶�ֵ*/
float Get_Temprate(u32 adcx)
{
 	float temperate;
	temperate = ((float)adcx)*(3.3f/4096.0f);				//��ѹֵ
	temperate=(temperate-0.76f)/0.0025f + 25.0f;			//ת��Ϊ�¶�ֵ 	 
	return temperate;
}

#if SYSTEM_ADC1_useScan
DMA_HandleTypeDef  ADC1rxDMA_Handler; //DMA���

//DMA1�ĸ�ͨ������
//����Ĵ�����ʽ�ǹ̶���,���Ҫ���ݲ�ͬ��������޸�
//�Ӵ洢��->����ģʽ/8λ���ݿ��/�洢������ģʽ
void ADC_DMA_Cfg(void)
{
	__HAL_RCC_DMA2_CLK_ENABLE();

    ADC1rxDMA_Handler.Instance = DMA2_Stream0;                                 //DMA Stream0
	ADC1rxDMA_Handler.Init.Channel = DMA_CHANNEL_0;
    ADC1rxDMA_Handler.Init.Direction=DMA_PERIPH_TO_MEMORY;                     //���赽�洢��
    ADC1rxDMA_Handler.Init.PeriphInc=DMA_PINC_DISABLE;                        //���������ģʽ
    ADC1rxDMA_Handler.Init.MemInc=DMA_MINC_ENABLE;                             //�洢������ģʽ
    ADC1rxDMA_Handler.Init.PeriphDataAlignment=DMA_PDATAALIGN_HALFWORD;        //�������ݳ���:16λ
    ADC1rxDMA_Handler.Init.MemDataAlignment=DMA_MDATAALIGN_HALFWORD;          //�洢�����ݳ���:16λ
	
	if(SYSTEM_ADC1_useCircular)
		ADC1rxDMA_Handler.Init.Mode=DMA_CIRCULAR;                                 	//���ADCѡ������ģʽ��������ѭ�����������������ģʽ������������ģʽ
	else ADC1rxDMA_Handler.Init.Mode=DMA_NORMAL;
   
	ADC1rxDMA_Handler.Init.Priority=DMA_PRIORITY_MEDIUM;                       //���ȼ�

    //ADC1rxDMA_Handler.XferCpltCallback = HAL_DMA_IRQHandler;
	ADC1rxDMA_Handler.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    
	HAL_DMA_DeInit(&ADC1rxDMA_Handler);                                      //DMA��λ
    HAL_DMA_Init(&ADC1rxDMA_Handler);                                        //DMA��ʼ�� 
        
		/*			����Դ   ����Դ����е�DMA����	  ʹ�õ�DMA���*/
	__HAL_LINKDMA(&ADC1_Handler,DMA_Handle,ADC1rxDMA_Handler);               //��DMA��ADC��ϵ����(����DMA)
	/*��DMA���ADC1rxDMA_Handler����ADC1_Handler��DMA_Handle*/
        
    HAL_NVIC_SetPriority(DMA2_Stream0_IRQn, 2, 0);                          //DMA�ж����ȼ� ���뿪���𶯣�
    HAL_NVIC_EnableIRQ(DMA2_Stream0_IRQn);                                  //ʹ��DMA�ж�
}

//DMA2 Stream0�жϷ���������ɴ���һ��ʱ���жϣ����ã���ΪҪ��ADȫ������ͨ��ת������ٲ���һ���ж�
void DMA2_Stream0_IRQHandler(void)
{
	HAL_DMA_IRQHandler(&ADC1rxDMA_Handler); /*����жϱ�־�����ж��Ƿ����ȫ��ת�����𶯣�*/
}

//HAL_DMA_IRQHandler�Ļص�������ADCת��������й�����ͨ������жϺ���
/*HAL_ADC_Start_DMA���������HAL_ADC_ConvCpltCallback��ΪADC1rxDMA_Handler���DMA����Ļص������ˣ�
�Զ��ģ�����ֻ�迪DMA���жϣ�����Ҫ��ADC�жϣ�������ͨ����ת���ú�DMA�жϾͻ�ص��������*/
/*TODO������һ�£���ADC1rxDMA_Handler.XferCpltCallback = HAL_DMA_IRQHandler;��仰ע�͵���Ӧ�ò�Ӱ��Ч����
��ΪHAL_ADC_Start_DMA�����������Ҫ�����ã�����DMA�Ļص������������ˣ�*/
/*��֮����ADC1rxDMA_Handler.XferCpltCallback = HAL_DMA_IRQHandler;ע�͵���ʣ�µĲ��־������׼��д�������*/
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
	adValueDone = 1; /*��־���ι�����ͨ��ȫ��ת����ɣ��𶯣�*/
}

#endif

#endif


/*_________________________________________________DAC_________________________________________________________*/
#if ((SYSTEM_DAC_OUT1_ENABLE) || (SYSTEM_DAC_OUT2_ENABLE))

DAC_HandleTypeDef DAC1_Handler;//DAC���

void sys_DAC_ENABLE(void)
{
	DAC_ChannelConfTypeDef DACCH1_Config;
	DAC_ChannelConfTypeDef DACCH2_Config;
	
	DAC1_Handler.Instance=DAC;
	HAL_DAC_Init(&DAC1_Handler);                 			//��ʼ��DAC
    
		/*ͨ��1����*/
		DACCH1_Config.DAC_Trigger=DAC_TRIGGER_SOFTWARE;             		//��������
							/*��ѡ��
								DAC_TRIGGER_T6_TRGO
								DAC_TRIGGER_T7_TRGO
								DAC_TRIGGER_T8_TRGO
								DAC_TRIGGER_T2_TRGO
								DAC_TRIGGER_T4_TRGO
								DAC_TRIGGER_EXT_IT9
								DAC_TRIGGER_SOFTWARE*/
		DACCH1_Config.DAC_OutputBuffer=DAC_OUTPUTBUFFER_ENABLE;		//DAC1�������
		/*ͨ��2����*/
		DACCH2_Config.DAC_Trigger=DAC_TRIGGER_SOFTWARE;             	//��������
		DACCH2_Config.DAC_OutputBuffer=DAC_OUTPUTBUFFER_ENABLE;		//DAC1�������
		
		if(SYSTEM_DAC_OUT1_ENABLE)
		{	HAL_DAC_ConfigChannel(&DAC1_Handler,&DACCH1_Config,DAC_CHANNEL_1);//DACͨ��1����
			HAL_DAC_Start(&DAC1_Handler,DAC_CHANNEL_1);  			//����DACͨ��1
		}
		
		if(SYSTEM_DAC_OUT2_ENABLE)
		{	HAL_DAC_ConfigChannel(&DAC1_Handler,&DACCH2_Config,DAC_CHANNEL_2);//DACͨ��2����
			HAL_DAC_Start(&DAC1_Handler,DAC_CHANNEL_2);  			//����DACͨ��2
		}
    
	#if SYSTEM_DAC_OUT1_TriangleWave_ENABLE
		HAL_DACEx_TriangleWaveGenerate(&DAC1_Handler, DAC_CHANNEL_1, DAC_TRIANGLEAMPLITUDE_1);
			//��ѡDAC_TRIANGLEAMPLITUDE_1 ~ DAC_TRIANGLEAMPLITUDE_4095 TODO:��֪�����������ʲô�ģ��д�ʵ��
	#elif SYSTEM_DAC_OUT1_NoiseWave_ENABLE
		HAL_DACEx_NoiseWaveGenerate(&DAC1_Handler, DAC_CHANNEL_1,DAC_LFSRUNMASK_BITS1_0);
			//��ѡDAC_LFSRUNMASK_BITS1_0 ~ DAC_LFSRUNMASK_BITS11_0 TODO:��֪�����������ʲô�ģ��д�ʵ��
	#endif
	
	#if SYSTEM_DAC_OUT2_TriangleWave_ENABLE
		HAL_DACEx_TriangleWaveGenerate(&DAC1_Handler, DAC_CHANNEL_2, DAC_TRIANGLEAMPLITUDE_1);
			//��ѡDAC_TRIANGLEAMPLITUDE_1 ~ DAC_TRIANGLEAMPLITUDE_4095 
	#elif SYSTEM_DAC_OUT2_NoiseWave_ENABLE
		HAL_DACEx_NoiseWaveGenerate(&DAC1_Handler, DAC_CHANNEL_2,DAC_LFSRUNMASK_BITS1_0);
			//��ѡDAC_LFSRUNMASK_BITS1_0 ~ DAC_LFSRUNMASK_BITS11_0 
	#endif
}

//DAC�ײ�������ʱ�����ã����� ����
//�˺����ᱻHAL_DAC_Init()����
//hdac:DAC���
void HAL_DAC_MspInit(DAC_HandleTypeDef* hdac)
{      
	if(SYSTEM_DAC_OUT1_ENABLE)
	{
		GPIO_InitTypeDef GPIO_Initure;
		__HAL_RCC_DAC_CLK_ENABLE();             //ʹ��DACʱ��
		__HAL_RCC_GPIOA_CLK_ENABLE();			//����GPIOAʱ��
		
		GPIO_Initure.Pin=GPIO_PIN_4;            //PA4
		GPIO_Initure.Mode=GPIO_MODE_ANALOG;     //ģ��
		GPIO_Initure.Pull=GPIO_NOPULL;          //����������
		HAL_GPIO_Init(GPIOA,&GPIO_Initure);
	}
	
	if(SYSTEM_DAC_OUT2_ENABLE)
	{
		GPIO_InitTypeDef GPIO_Initure;
		__HAL_RCC_DAC_CLK_ENABLE();             //ʹ��DACʱ��
		__HAL_RCC_GPIOA_CLK_ENABLE();			//����GPIOAʱ��
		
		GPIO_Initure.Pin=GPIO_PIN_5;            //PA5
		GPIO_Initure.Mode=GPIO_MODE_ANALOG;     //ģ��
		GPIO_Initure.Pull=GPIO_NOPULL;          //����������
		HAL_GPIO_Init(GPIOA,&GPIO_Initure);
	}
}

//����ͨ��1�����ѹ
//vol:0~3.30V
void DAC_Set_Ch1_Vol(float vol)
{
	float temp = vol;
	temp = (temp/3.30f)*4096.0f;
    HAL_DAC_SetValue(&DAC1_Handler,DAC_CHANNEL_1,DAC_ALIGN_12B_R,(uint32_t)temp);//12λ�Ҷ������ݸ�ʽ����DACֵ
}

//����ͨ��2�����ѹ
//vol:0~3.30V
void DAC_Set_Ch2_Vol(float vol)
{
	float temp = vol;
	temp = (temp/3.30f)*4096.0f;
    HAL_DAC_SetValue(&DAC1_Handler,DAC_CHANNEL_2,DAC_ALIGN_12B_R,(uint32_t)temp);//12λ�Ҷ������ݸ�ʽ����DACֵ
}


#endif


/*________________________________________________FSMC_________________________________________________________*/
#if ((SYSTEM_FSMC_ENABLE) && (SYSTEM_FSMC_use4SRAM))

SRAM_HandleTypeDef SRAM_Handler;    //SRAM���

//SRAM��ʼ��
void sys_FSMC_SRAM_ENABLE(void)
{	
	FSMC_NORSRAM_TimingTypeDef FSMC_ReadWriteTim;
	GPIO_InitTypeDef GPIO_Initure;
	
//	XmRamInit();
//	HAL_Delay(1);
		
		__HAL_RCC_FSMC_CLK_ENABLE();                //ʹ��FSMCʱ��
		__HAL_RCC_GPIOD_CLK_ENABLE();               //ʹ��GPIODʱ��
		__HAL_RCC_GPIOE_CLK_ENABLE();               //ʹ��GPIOEʱ��
		__HAL_RCC_GPIOF_CLK_ENABLE();               //ʹ��GPIOFʱ��
		__HAL_RCC_GPIOG_CLK_ENABLE();               //ʹ��GPIOGʱ��
		
		//PD0,1,4,5,8~15
		GPIO_Initure.Pin=GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_8|\
						 GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|\
						 GPIO_PIN_14|GPIO_PIN_15;  
		GPIO_Initure.Mode=GPIO_MODE_AF_PP;          //���츴��
		GPIO_Initure.Pull=GPIO_PULLUP;              //
		GPIO_Initure.Speed=GPIO_SPEED_HIGH;    //���� 
		GPIO_Initure.Alternate = GPIO_AF12_FSMC;
		HAL_GPIO_Init(GPIOD,&GPIO_Initure);     	
		
		//PE0,1,7~15
		GPIO_Initure.Pin=GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9|\
						 GPIO_PIN_10| GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|\
						 GPIO_PIN_15;    
		HAL_GPIO_Init(GPIOE,&GPIO_Initure);    
		
		//PF0~5,12~15
		GPIO_Initure.Pin=GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|\
						 GPIO_PIN_5|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;              
		HAL_GPIO_Init(GPIOF,&GPIO_Initure);     
		
		//PG0~5,10
		GPIO_Initure.Pin=GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_10;              
		HAL_GPIO_Init(GPIOG,&GPIO_Initure);  
		
		
	SRAM_Handler.Instance=FSMC_NORSRAM_DEVICE;                
	SRAM_Handler.Extended=FSMC_NORSRAM_EXTENDED_DEVICE;    
	
	SRAM_Handler.Init.NSBank=FSMC_NORSRAM_BANK3;     					//ʹ��NE3
	SRAM_Handler.Init.DataAddressMux=FSMC_DATA_ADDRESS_MUX_DISABLE; 	//��ַ/�����߲�����
	SRAM_Handler.Init.MemoryType=FSMC_MEMORY_TYPE_SRAM;   				//SRAM
	SRAM_Handler.Init.MemoryDataWidth=FSMC_NORSRAM_MEM_BUS_WIDTH_16; 	//16λ���ݿ��
	SRAM_Handler.Init.BurstAccessMode=FSMC_BURST_ACCESS_MODE_DISABLE; 	//�Ƿ�ʹ��ͻ������,����ͬ��ͻ���洢����Ч,�˴�δ�õ�
	SRAM_Handler.Init.WaitSignalPolarity=FSMC_WAIT_SIGNAL_POLARITY_LOW;	//�ȴ��źŵļ���,����ͻ��ģʽ����������
	//SRAM_Handler.Init.WrapMode = FSMC_WRAP_MODE_DISABLE; 
	SRAM_Handler.Init.WaitSignalActive=FSMC_WAIT_TIMING_BEFORE_WS;   	//�洢�����ڵȴ�����֮ǰ��һ��ʱ�����ڻ��ǵȴ������ڼ�ʹ��NWAIT
	SRAM_Handler.Init.WriteOperation=FSMC_WRITE_OPERATION_ENABLE;    	//�洢��дʹ��
	SRAM_Handler.Init.WaitSignal=FSMC_WAIT_SIGNAL_DISABLE;           	//�ȴ�ʹ��λ,�˴�δ�õ�
	SRAM_Handler.Init.ExtendedMode=FSMC_EXTENDED_MODE_DISABLE;        	//��дʹ����ͬ��ʱ��
	SRAM_Handler.Init.AsynchronousWait=FSMC_ASYNCHRONOUS_WAIT_DISABLE;	//�Ƿ�ʹ��ͬ������ģʽ�µĵȴ��ź�,�˴�δ�õ�
	SRAM_Handler.Init.WriteBurst=FSMC_WRITE_BURST_DISABLE;           	//��ֹͻ��д
	SRAM_Handler.Init.ContinuousClock=FSMC_CONTINUOUS_CLOCK_SYNC_ASYNC;
  
	//FMC��ʱ����ƼĴ���
	FSMC_ReadWriteTim.AddressSetupTime=0x0f;       	//��ַ����ʱ�䣨ADDSET�� ���ٸ�HCLK�����Ըĳ�0x00���ԣ�Ϊ1��HCLK 1/168M=6ns*16=96ns
	FSMC_ReadWriteTim.AddressHoldTime=0x0f;			//��ַ����ʱ�䣨ADDHLD��ģʽAδ�õ�
	FSMC_ReadWriteTim.DataSetupTime=0x18;			//���ݱ���ʱ��Ϊ18��HCLK
	FSMC_ReadWriteTim.BusTurnAroundDuration=0X00;
	FSMC_ReadWriteTim.AccessMode=FSMC_ACCESS_MODE_A;//ģʽA
	HAL_SRAM_Init(&SRAM_Handler,&FSMC_ReadWriteTim,&FSMC_ReadWriteTim);	
	
}

//��ָ����ַ(WriteAddr+Bank1_SRAM3_ADDR)��ʼ,����д��n���ֽ�.
//pBuffer:�ֽ�ָ��
//WriteAddr:Ҫд��ĵ�ַ
//n:Ҫд����ֽ���
void FSMC_SRAM_WriteBuffer(u8 *pBuffer,u32 WriteAddr,u32 n)
{
	for(;n!=0;n--)
	{
		*(vu8*)(SRAM1_BANK3_ADDR + WriteAddr) = *pBuffer;
		WriteAddr++;
		pBuffer++;
	}
}

//��ָ����ַ((WriteAddr+Bank1_SRAM3_ADDR))��ʼ,��������n���ֽ�.
//pBuffer:�ֽ�ָ��
//ReadAddr:Ҫ��������ʼ��ַ
//n:Ҫд����ֽ���
void FSMC_SRAM_ReadBuffer(u8 *pBuffer,u32 ReadAddr,u32 n)
{
	for(;n!=0;n--)
	{
		*pBuffer++ = *(vu8*)(SRAM1_BANK3_ADDR + ReadAddr);
		ReadAddr++;
	}
}

#endif

#if ((SYSTEM_FSMC_ENABLE) && (SYSTEM_FSMC_use4LCD))

SRAM_HandleTypeDef TFTSRAM_Handler;    //SRAM���(���ڿ���LCD)

void LCD_with_FSMC_init_FSMC(void)
{
	FSMC_NORSRAM_TimingTypeDef FSMC_ReadWriteTim;
	FSMC_NORSRAM_TimingTypeDef FSMC_WriteTim;
	
		GPIO_InitTypeDef GPIO_Initure;
		
		__HAL_RCC_FSMC_CLK_ENABLE();			//ʹ��FSMCʱ��
		__HAL_RCC_GPIOD_CLK_ENABLE();			//ʹ��GPIODʱ��
		__HAL_RCC_GPIOE_CLK_ENABLE();			//ʹ��GPIOEʱ��
		__HAL_RCC_GPIOG_CLK_ENABLE();			//ʹ��GPIOGʱ��
		
		//��ʼ��PD0,1,4,5,8,9,10,14,15
		GPIO_Initure.Pin=GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_8|\
						 GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_14|GPIO_PIN_15;
		GPIO_Initure.Mode=GPIO_MODE_AF_PP; 		//���츴��
		GPIO_Initure.Pull=GPIO_NOPULL;			//
		GPIO_Initure.Speed=GPIO_SPEED_FREQ_VERY_HIGH;//����
		GPIO_Initure.Alternate = GPIO_AF12_FSMC;
		HAL_GPIO_Init(GPIOD,&GPIO_Initure);     //��ʼ��
		
		//��ʼ��PE7,8,9,10,11,12,13,14,15
		GPIO_Initure.Pin=GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11|\
						 GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
		HAL_GPIO_Init(GPIOE,&GPIO_Initure);
		
		//��ʼ��PG0,12
		GPIO_Initure.Pin=GPIO_PIN_0|GPIO_PIN_12;
		HAL_GPIO_Init(GPIOG,&GPIO_Initure);
		
	TFTSRAM_Handler.Instance=FSMC_NORSRAM_DEVICE;                
	TFTSRAM_Handler.Extended=FSMC_NORSRAM_EXTENDED_DEVICE;    
    
	TFTSRAM_Handler.Init.NSBank=FSMC_NORSRAM_BANK4;     				//ʹ��NE4
	TFTSRAM_Handler.Init.DataAddressMux=FSMC_DATA_ADDRESS_MUX_DISABLE; 	//��ַ/�����߲�����
	TFTSRAM_Handler.Init.MemoryType=FSMC_MEMORY_TYPE_SRAM;   			//SRAM
	TFTSRAM_Handler.Init.MemoryDataWidth=FSMC_NORSRAM_MEM_BUS_WIDTH_16; //16λ���ݿ��
	TFTSRAM_Handler.Init.BurstAccessMode=FSMC_BURST_ACCESS_MODE_DISABLE; //�Ƿ�ʹ��ͻ������,����ͬ��ͻ���洢����Ч,�˴�δ�õ�
	TFTSRAM_Handler.Init.WaitSignalPolarity=FSMC_WAIT_SIGNAL_POLARITY_LOW;//�ȴ��źŵļ���,����ͻ��ģʽ����������
	TFTSRAM_Handler.Init.WrapMode = FSMC_WRAP_MODE_DISABLE;
	TFTSRAM_Handler.Init.WaitSignalActive=FSMC_WAIT_TIMING_BEFORE_WS;   //�洢�����ڵȴ�����֮ǰ��һ��ʱ�����ڻ��ǵȴ������ڼ�ʹ��NWAIT
	TFTSRAM_Handler.Init.WriteOperation=FSMC_WRITE_OPERATION_ENABLE;    //�洢��дʹ��
	TFTSRAM_Handler.Init.WaitSignal=FSMC_WAIT_SIGNAL_DISABLE;           //�ȴ�ʹ��λ,�˴�δ�õ�
	TFTSRAM_Handler.Init.ExtendedMode=FSMC_EXTENDED_MODE_ENABLE;        //��дʹ�ò�ͬ��ʱ��
	TFTSRAM_Handler.Init.AsynchronousWait=FSMC_ASYNCHRONOUS_WAIT_DISABLE;//�Ƿ�ʹ��ͬ������ģʽ�µĵȴ��ź�,�˴�δ�õ�
	TFTSRAM_Handler.Init.WriteBurst=FSMC_WRITE_BURST_DISABLE;           //��ֹͻ��д
    
	//FMC��ʱ����ƼĴ���
	FSMC_ReadWriteTim.AddressSetupTime=0x0F;       	//��ַ����ʱ�䣨ADDSET��Ϊ����HCLK
	FSMC_ReadWriteTim.AddressHoldTime=0;
	FSMC_ReadWriteTim.DataSetupTime=60;				//���ݱ���ʱ��
	FSMC_ReadWriteTim.AccessMode=FSMC_ACCESS_MODE_A;//ģʽA
	//FMCдʱ����ƼĴ���
	FSMC_WriteTim.BusTurnAroundDuration=0;			//������ת�׶γ���ʱ��Ϊ0���˱�������ֵ�Ļ���Ī��������Զ��޸�Ϊ4�����³�����������
	FSMC_WriteTim.AddressSetupTime=9;          		//��ַ����ʱ�䣨ADDSET��Ϊ����HCLK
	FSMC_WriteTim.AddressHoldTime=0;
	FSMC_WriteTim.DataSetupTime=8;              	//���ݱ���ʱ��
	FSMC_WriteTim.AccessMode=FSMC_ACCESS_MODE_A;    //ģʽA
	HAL_SRAM_Init(&TFTSRAM_Handler,&FSMC_ReadWriteTim,&FSMC_WriteTim);	
	
	HAL_Delay(50); // delay 50 ms 
}

#endif

/*________________________________________�û�FLASH���_________________________________________________________*/
#if SYSTEM_FLASH_IAP_ENABLE

//��ȡָ����ַ����(32λ����) 
//faddr:����ַ 
//����ֵ:��Ӧ����.
u32 STMFLASH_ReadWord(u32 faddr)
{
	return *(vu32*)faddr; 
}

//��ָ����ַ��ʼ����ָ�����ȵ�����
//ReadAddr:��ʼ��ַ
//pBuffer:����ָ��
//NumToRead:��(32λ)��
void STMFLASH_Read(u32 ReadAddr,u32 *pBuffer,u32 NumToRead)   	
{
	u32 i;
	for(i=0;i<NumToRead;i++)
	{
		pBuffer[i]=STMFLASH_ReadWord(ReadAddr);//��ȡ4���ֽ�.
		ReadAddr+=4;//ƫ��4���ֽ�.	
	}
}


#if STM32_FLASH_WREN	//���ʹ����д   

//��ȡĳ����ַ���ڵ�flash����
//addr:flash��ַ
//����ֵ:0~11,��addr���ڵ�����
u8 STMFLASH_GetFlashSector(u32 addr)
{
	if(addr<ADDR_FLASH_SECTOR_1)return FLASH_SECTOR_0;
	else if(addr<ADDR_FLASH_SECTOR_2)return FLASH_SECTOR_1;
	else if(addr<ADDR_FLASH_SECTOR_3)return FLASH_SECTOR_2;
	else if(addr<ADDR_FLASH_SECTOR_4)return FLASH_SECTOR_3;
	else if(addr<ADDR_FLASH_SECTOR_5)return FLASH_SECTOR_4;
	else if(addr<ADDR_FLASH_SECTOR_6)return FLASH_SECTOR_5;
	else if(addr<ADDR_FLASH_SECTOR_7)return FLASH_SECTOR_6;
	else if(addr<ADDR_FLASH_SECTOR_8)return FLASH_SECTOR_7;
	else if(addr<ADDR_FLASH_SECTOR_9)return FLASH_SECTOR_8;
	else if(addr<ADDR_FLASH_SECTOR_10)return FLASH_SECTOR_9;
	else if(addr<ADDR_FLASH_SECTOR_11)return FLASH_SECTOR_10;   
	return FLASH_SECTOR_11;	
}

//��ָ����ַ��ʼд��ָ�����ȵ�����
//�ر�ע��:��ΪSTM32F4������ʵ��̫��,û�취���ر�����������,���Ա�����
//         д��ַ�����0XFF,��ô���Ȳ������������Ҳ�������������.����
//         д��0XFF�ĵ�ַ,�����������������ݶ�ʧ.����д֮ǰȷ��������
//         û����Ҫ����,��������������Ȳ�����,Ȼ����������д. 
//�ú�����OTP����Ҳ��Ч!��������дOTP��!
//OTP�����ַ��Χ:0X1FFF7800~0X1FFF7A0F(ע�⣺���16�ֽڣ�����OTP���ݿ�����������д����)
//WriteAddr:��ʼ��ַ(�˵�ַ����Ϊ4�ı���!!)
//pBuffer:����ָ��
//NumToWrite:��(32λ)��(����Ҫд���32λ���ݵĸ���.) 
void STMFLASH_Write(u32 WriteAddr,u32 *pBuffer,u32 NumToWrite)	
{ 
	FLASH_EraseInitTypeDef FlashEraseInit;
	HAL_StatusTypeDef FlashStatus=HAL_OK;
	u32 SectorError=0;
	u32 addrx=0;
	u32 endaddr=0;	
	if(WriteAddr<STM32_FLASH_BASE||WriteAddr%4)return;	//�Ƿ���ַ
    
	HAL_FLASH_Unlock();             //����	
	addrx=WriteAddr;				//д�����ʼ��ַ
	endaddr=WriteAddr+NumToWrite*4;	//д��Ľ�����ַ
    
	if(addrx<0X1FFF0000)
	{
		while(addrx<endaddr)		//ɨ��һ���ϰ�.(�Է�FFFFFFFF�ĵط�,�Ȳ���)
		{
			 if(STMFLASH_ReadWord(addrx)!=0XFFFFFFFF)//�з�0XFFFFFFFF�ĵط�,Ҫ�����������
			{   
				FlashEraseInit.TypeErase=FLASH_TYPEERASE_SECTORS;       //�������ͣ��������� 
				FlashEraseInit.Sector=STMFLASH_GetFlashSector(addrx);   //Ҫ����������
				FlashEraseInit.NbSectors=1;                             //һ��ֻ����һ������
				FlashEraseInit.VoltageRange=FLASH_VOLTAGE_RANGE_3;      //��ѹ��Χ��VCC=2.7~3.6V֮��!!
				if(HAL_FLASHEx_Erase(&FlashEraseInit,&SectorError)!=HAL_OK) 
				{
					break;//����������	
				}
				}else addrx+=4;
				FLASH_WaitForLastOperation(FLASH_WAITETIME);                //�ȴ��ϴβ������
		}
	}
	FlashStatus=FLASH_WaitForLastOperation(FLASH_WAITETIME);            //�ȴ��ϴβ������
	if(FlashStatus==HAL_OK)
	{
		 while(WriteAddr<endaddr)//д����
		 {
			if(HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD,WriteAddr,*pBuffer)!=HAL_OK)//д������
			{ 
				break;	//д���쳣
			}
			WriteAddr+=4;
			pBuffer++;
		}  
	}
	HAL_FLASH_Lock();           //����
} 

#endif

#endif


/*____________________SDIO SD_____________________________________________*/
#if SYSTEM_SDIO_SD_ENABLE

SD_HandleTypeDef        SDCARD_Handler;     //SD�����
HAL_SD_CardInfoTypeDef  SDCardInfo;         //SD����Ϣ�ṹ��
DMA_HandleTypeDef SDTxDMAHandler,SDRxDMAHandler;    //SD��DMA���ͺͽ��վ��

//SD_ReadDisk/SD_WriteDisk����ר��buf,�����������������ݻ�������ַ����4�ֽڶ����ʱ��,
//��Ҫ�õ�������,ȷ�����ݻ�������ַ��4�ֽڶ����.
__align(4) u8 SDIO_DATA_BUFFER[512];

//SD����ʼ��
//����ֵ:0 ��ʼ����ȷ������ֵ����ʼ������
u8 SD_Init(void)
{
    u8 SD_Error;
    
    //��ʼ��ʱ��ʱ�Ӳ��ܴ���400KHZ 
    SDCARD_Handler.Instance=SDIO;
    SDCARD_Handler.Init.ClockEdge=SDIO_CLOCK_EDGE_RISING;          			//������     
    SDCARD_Handler.Init.ClockBypass=SDIO_CLOCK_BYPASS_DISABLE;     			//��ʹ��bypassģʽ��ֱ����HCLK���з�Ƶ�õ�SDIO_CK
    SDCARD_Handler.Init.ClockPowerSave=SDIO_CLOCK_POWER_SAVE_DISABLE;    	//����ʱ���ر�ʱ�ӵ�Դ
    SDCARD_Handler.Init.BusWide=SDIO_BUS_WIDE_1B;                        	//1λ������
    SDCARD_Handler.Init.HardwareFlowControl=SDIO_HARDWARE_FLOW_CONTROL_DISABLE;//�ر�Ӳ������
    SDCARD_Handler.Init.ClockDiv=SDIO_TRANSFER_CLK_DIV;            			//SD����ʱ��Ƶ�����25MHZ
    
    SD_Error=HAL_SD_Init(&SDCARD_Handler);
    if(SD_Error!=HAL_OK) return 1;
	
	//��ȡSD����Ϣ
	HAL_SD_GetCardInfo(&SDCARD_Handler,&SDCardInfo);
    
    SD_Error=HAL_SD_ConfigWideBusOperation(&SDCARD_Handler,SDIO_BUS_WIDE_4B);//ʹ�ܿ�����ģʽ
    if(SD_Error!=HAL_OK) return 2;
    return 0;
}

//SDMMC�ײ�������ʱ��ʹ�ܣ��������ã�DMA����
//�˺����ᱻHAL_SD_Init()����
//hsd:SD�����
void HAL_SD_MspInit(SD_HandleTypeDef *hsd)
{
    DMA_HandleTypeDef TxDMAHandler,RxDMAHandler;
    GPIO_InitTypeDef GPIO_Initure;
    
    __HAL_RCC_SDIO_CLK_ENABLE();    //ʹ��SDIOʱ��
    __HAL_RCC_DMA2_CLK_ENABLE();    //ʹ��DMA2ʱ�� 
    __HAL_RCC_GPIOC_CLK_ENABLE();   //ʹ��GPIOCʱ��
    __HAL_RCC_GPIOD_CLK_ENABLE();   //ʹ��GPIODʱ��
    
    //PC8,9,10,11,12
    GPIO_Initure.Pin=GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12;
    GPIO_Initure.Mode=GPIO_MODE_AF_PP;      //���츴��
    GPIO_Initure.Pull=GPIO_PULLUP;          //����
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //����
    GPIO_Initure.Alternate=GPIO_AF12_SDIO;  //����ΪSDIO
    HAL_GPIO_Init(GPIOC,&GPIO_Initure);     //��ʼ��
    
    //PD2
    GPIO_Initure.Pin=GPIO_PIN_2;            
    HAL_GPIO_Init(GPIOD,&GPIO_Initure);     //��ʼ��

#if (SD_DMA_MODE==1)                        //ʹ��DMAģʽ
    HAL_NVIC_SetPriority(SDMMC1_IRQn,2,0);  //����SDMMC1�жϣ���ռ���ȼ�2�������ȼ�0
    HAL_NVIC_EnableIRQ(SDMMC1_IRQn);        //ʹ��SDMMC1�ж�
    
    //���÷���DMA
    SDRxDMAHandler.Instance=DMA2_Stream3;
    SDRxDMAHandler.Init.Channel=DMA_CHANNEL_4;
    SDRxDMAHandler.Init.Direction=DMA_PERIPH_TO_MEMORY;
    SDRxDMAHandler.Init.PeriphInc=DMA_PINC_DISABLE;
    SDRxDMAHandler.Init.MemInc=DMA_MINC_ENABLE;
    SDRxDMAHandler.Init.PeriphDataAlignment=DMA_PDATAALIGN_WORD;
    SDRxDMAHandler.Init.MemDataAlignment=DMA_MDATAALIGN_WORD;
    SDRxDMAHandler.Init.Mode=DMA_PFCTRL;
    SDRxDMAHandler.Init.Priority=DMA_PRIORITY_VERY_HIGH;
    SDRxDMAHandler.Init.FIFOMode=DMA_FIFOMODE_ENABLE;
    SDRxDMAHandler.Init.FIFOThreshold=DMA_FIFO_THRESHOLD_FULL;
    SDRxDMAHandler.Init.MemBurst=DMA_MBURST_INC4;
    SDRxDMAHandler.Init.PeriphBurst=DMA_PBURST_INC4;

    __HAL_LINKDMA(hsd, hdmarx, SDRxDMAHandler); //������DMA��SD���ķ���DMA��������
    HAL_DMA_DeInit(&SDRxDMAHandler);
    HAL_DMA_Init(&SDRxDMAHandler);              //��ʼ������DMA
    
    //���ý���DMA 
    SDTxDMAHandler.Instance=DMA2_Stream6;
    SDTxDMAHandler.Init.Channel=DMA_CHANNEL_4;
    SDTxDMAHandler.Init.Direction=DMA_MEMORY_TO_PERIPH;
    SDTxDMAHandler.Init.PeriphInc=DMA_PINC_DISABLE;
    SDTxDMAHandler.Init.MemInc=DMA_MINC_ENABLE;
    SDTxDMAHandler.Init.PeriphDataAlignment=DMA_PDATAALIGN_WORD;
    SDTxDMAHandler.Init.MemDataAlignment=DMA_MDATAALIGN_WORD;
    SDTxDMAHandler.Init.Mode=DMA_PFCTRL;
    SDTxDMAHandler.Init.Priority=DMA_PRIORITY_VERY_HIGH;
    SDTxDMAHandler.Init.FIFOMode=DMA_FIFOMODE_ENABLE;
    SDTxDMAHandler.Init.FIFOThreshold=DMA_FIFO_THRESHOLD_FULL;
    SDTxDMAHandler.Init.MemBurst=DMA_MBURST_INC4;
    SDTxDMAHandler.Init.PeriphBurst=DMA_PBURST_INC4;
    
    __HAL_LINKDMA(hsd, hdmatx, SDTxDMAHandler);//������DMA��SD���ķ���DMA��������
    HAL_DMA_DeInit(&SDTxDMAHandler);
    HAL_DMA_Init(&SDTxDMAHandler);              //��ʼ������DMA 
  

    HAL_NVIC_SetPriority(DMA2_Stream3_IRQn, 3, 0);  //����DMA�ж����ȼ�
    HAL_NVIC_EnableIRQ(DMA2_Stream3_IRQn);
    HAL_NVIC_SetPriority(DMA2_Stream6_IRQn, 3, 0);  //����DMA�ж����ȼ�
    HAL_NVIC_EnableIRQ(DMA2_Stream6_IRQn);
#endif
}

//�õ�����Ϣ
//cardinfo:����Ϣ�洢��
//����ֵ:����״̬
u8 SD_GetCardInfo(HAL_SD_CardInfoTypeDef *cardinfo)
{
    u8 sta;
    sta=HAL_SD_GetCardInfo(&SDCARD_Handler,cardinfo);
    return sta;
}

//�ж�SD���Ƿ���Դ���(��д)����
//����ֵ:SD_TRANSFER_OK ������ɣ����Լ�����һ�δ���
//		 SD_TRANSFER_BUSY SD����æ�������Խ�����һ�δ���
u8 SD_GetCardState(void)
{
  return((HAL_SD_GetCardState(&SDCARD_Handler)==HAL_SD_CARD_TRANSFER )?SD_TRANSFER_OK:SD_TRANSFER_BUSY);
}

 #if (SD_DMA_MODE==1)        //DMAģʽ

//ͨ��DMA��ȡSD��һ������
//buf:�����ݻ�����
//sector:������ַ
//blocksize:������С(һ�㶼��512�ֽ�)
//cnt:��������	
//����ֵ:����״̬;0,����;����,�������;
u8 SD_ReadBlocks_DMA(uint32_t *buf,uint64_t sector,uint32_t blocksize,uint32_t cnt)
{
    u8 err=0;
	u32 timeout=SD_TIMEOUT;
	err=HAL_SD_ReadBlocks_DMA(&SDCARD_Handler,(uint8_t*)buf,sector,cnt);//ͨ��DMA��ȡSD��n������

	if(err==0)
	{
		//�ȴ�SD������
		while(SD_GetCardState()!=SD_TRANSFER_OK)
		{
			if(timeout-- == 0)
			{	
				err=SD_TRANSFER_BUSY;
			}
		} 
	}
    return err;
}

//дSD��
//buf:д���ݻ�����
//sector:������ַ
//blocksize:������С(һ�㶼��512�ֽ�)
//cnt:��������	
//����ֵ:����״̬;0,����;����,�������;	
u8 SD_WriteBlocks_DMA(uint32_t *buf,uint64_t sector,uint32_t blocksize,uint32_t cnt)
{
    u8 err=0; 
	u32 timeout=SD_TIMEOUT;
	err=HAL_SD_WriteBlocks_DMA(&SDCARD_Handler,(uint8_t*)buf,sector,cnt);//ͨ��DMAдSD��n������

	if(err==0)
	{
		//�ȴ�SD��д��
		while(SD_GetCardState()!=SD_TRANSFER_OK)
		{
			if(timeout-- == 0)
			{	
				err=SD_TRANSFER_BUSY;
			}
		} 
	}
    return err;
}

//��SD��
//buf:�����ݻ�����
//sector:������ַ
//cnt:��������	
//����ֵ:����״̬;0,����;����,�������;
u8 SD_ReadDisk(u8* buf,u32 sector,u32 cnt)
{
    u8 sta=HAL_OK;
    long long lsector=sector;
	u32 timeout=SD_TIMEOUT;
    u8 n;
	
	sta=SD_ReadBlocks_DMA((uint32_t*)buf,lsector, 512,cnt);
   
    return sta;
}  

//дSD��
//buf:д���ݻ�����
//sector:������ַ
//cnt:��������	
//����ֵ:����״̬;0,����;����,�������;	
u8 SD_WriteDisk(u8 *buf,u32 sector,u32 cnt)
{   
    u8 sta=HAL_OK;
    long long lsector=sector;
	u32 timeout=SD_TIMEOUT;
    u8 n;

	sta=SD_WriteBlocks_DMA((uint32_t*)buf,lsector,512,cnt);//���sector��д����

    return sta;
} 

//SDMMC1�жϷ�����
void SDMMC1_IRQHandler(void)
{
    HAL_SD_IRQHandler(&SDCARD_Handler);
}

//DMA2������6�жϷ�����
void DMA2_Stream6_IRQHandler(void)
{
    HAL_DMA_IRQHandler(SDCARD_Handler.hdmatx);
}

//DMA2������3�жϷ�����
void DMA2_Stream3_IRQHandler(void)
{
    HAL_DMA_IRQHandler(SDCARD_Handler.hdmarx);
}
#else                                   //��ѵģʽ
 
//��SD��
//buf:�����ݻ�����
//sector:������ַ
//cnt:��������	
//����ֵ:����״̬;0,����;����,�������;
u8 SD_ReadDisk(u8* buf,u32 sector,u32 cnt)
{
    u8 sta=HAL_OK;
	u32 timeout=SD_TIMEOUT;
    long long lsector=sector;
    INTX_DISABLE();//�ر����ж�(POLLINGģʽ,�Ͻ��жϴ��SDIO��д����!!!)
	sta=HAL_SD_ReadBlocks(&SDCARD_Handler, (uint8_t*)buf,lsector,cnt,SD_TIMEOUT);//���sector�Ķ�����
	
	//�ȴ�SD������
	while(SD_GetCardState()!=SD_TRANSFER_OK)
    {
		if(timeout-- == 0)
		{	
			sta=SD_TRANSFER_BUSY;
		}
    }
    INTX_ENABLE();//�������ж�
    return sta;
}  


//дSD��
//buf:д���ݻ�����
//sector:������ַ
//cnt:��������	
//����ֵ:����״̬;0,����;����,�������;	
u8 SD_WriteDisk(u8 *buf,u32 sector,u32 cnt)
{   
    u8 sta=HAL_OK;
	u32 timeout=SD_TIMEOUT;
    long long lsector=sector;
    INTX_DISABLE();//�ر����ж�(POLLINGģʽ,�Ͻ��жϴ��SDIO��д����!!!)
	sta=HAL_SD_WriteBlocks(&SDCARD_Handler,(uint8_t*)buf,lsector,cnt,SD_TIMEOUT);//���sector��д����
		
	//�ȴ�SD��д��
	while(SD_GetCardState()!=SD_TRANSFER_OK)
    {
		if(timeout-- == 0)
		{	
			sta=SD_TRANSFER_BUSY;
		}
    }    
	INTX_ENABLE();//�������ж�
    return sta;
}
#endif

#endif







