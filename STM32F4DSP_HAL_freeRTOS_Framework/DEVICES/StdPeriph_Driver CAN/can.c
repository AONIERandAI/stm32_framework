#include "can.h"
#include "usart.h"



//CAN��ʼ��
//tsjw:����ͬ����Ծʱ�䵥Ԫ.��Χ:CAN_SJW_1tq~ CAN_SJW_4tq
//tbs2:ʱ���2��ʱ�䵥Ԫ.   ��Χ:CAN_BS2_1tq~CAN_BS2_8tq;
//tbs1:ʱ���1��ʱ�䵥Ԫ.   ��Χ:CAN_BS1_1tq ~CAN_BS1_16tq
//brp :�����ʷ�Ƶ��.��Χ:1~1024; tq=(brp)*tpclk1
//������=Fpclk1/((tbs1+1+tbs2+1+1)*brp);
//mode:CAN_Mode_Normal,��ͨģʽ;CAN_Mode_LoopBack,�ػ�ģʽ;
//Fpclk1��ʱ���ڳ�ʼ����ʱ������Ϊ42M,�������CAN1_Mode_Init(CAN_SJW_1tq,CAN_BS2_6tq,CAN_BS1_7tq,6,CAN_Mode_LoopBack);
//������Ϊ:42M/((6+7+1)*6)=500Kbps
void CAN1_Mode_Init(u8 tsjw,u8 tbs2,u8 tbs1,u16 brp,u8 mode)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	CAN_InitTypeDef        CAN_InitStructure;
	CAN_FilterInitTypeDef  CAN_FilterInitStructure;
	
	#if CAN1_RX0_INT_ENABLE 
		NVIC_InitTypeDef  NVIC_InitStructure;
	#endif
	
	
	//ʹ�����ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//ʹ��PORTAʱ��	                   											 
  	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);//ʹ��CAN1ʱ��	
	
	//���Ÿ���ӳ������
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource11,GPIO_AF_CAN1); //GPIOA11����ΪCAN1
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource12,GPIO_AF_CAN1); //GPIOA12����ΪCAN1
		
	//��ʼ��GPIO
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11| GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
    GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��PA11,PA12
	
	//CAN��Ԫ����
   	CAN_InitStructure.CAN_TTCM=DISABLE;		//��ʱ�䴥��ͨ��ģʽ   	0=ʱ�䴥��ͨѶ��ʹ�ã�����Ĭ��
  	CAN_InitStructure.CAN_ABOM=DISABLE;		//����Զ����߹���	  	0=���߶Ͽ�״̬����������󣬱���Ĭ��
  	CAN_InitStructure.CAN_AWUM=DISABLE;		//˯��ģʽͨ���������(���CAN->MCR��SLEEPλ)������Ĭ��
  	
	CAN_InitStructure.CAN_NART=DISABLE;		//ʹ�ñ����Զ����� 		
		//0=The CAN hardware will automatically retransmit the message until it has been successfully transmitted according to the CAN standard.
		//1=A message will be transmitted only once, independently of the transmission result (successful, error or arbitration lost).
  	
	CAN_InitStructure.CAN_RFLM=DISABLE;		//���Ĳ�����,�µĸ��Ǿɵģ�����Ĭ��
  	CAN_InitStructure.CAN_TXFP=DISABLE;		//���ȼ��ɱ��ı�ʶ��ID����������Ĭ��
  	
	CAN_InitStructure.CAN_Mode= mode;	 	//ģʽ���� 
  	CAN_InitStructure.CAN_SJW=tsjw;			//����ͬ����Ծ���(Tsjw)Ϊtsjw+1��ʱ�䵥λ CAN_SJW_1tq~CAN_SJW_4tq
  	CAN_InitStructure.CAN_BS1=tbs1; 		//Tbs1��ΧCAN_BS1_1tq ~CAN_BS1_16tq
  	CAN_InitStructure.CAN_BS2=tbs2;			//Tbs2��ΧCAN_BS2_1tq ~	CAN_BS2_8tq
  	CAN_InitStructure.CAN_Prescaler=brp;  	//��Ƶϵ��(Fdiv)Ϊbrp+1	
  	CAN_Init(CAN1, &CAN_InitStructure);   	// ��ʼ��CAN1
	
	//���ù�����
 	CAN_FilterInitStructure.CAN_FilterNumber=0;	  //������0
  	CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdMask; //����λģʽ
  	CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_32bit;
  	CAN_FilterInitStructure.CAN_FilterIdHigh=0x0000;
  	CAN_FilterInitStructure.CAN_FilterIdLow=0x0000;
  	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0x0000;//32λMASK	������0��ʾ�������ض��Ľ���ID�����߶��ջ����ɽ��պ������趨��
  	CAN_FilterInitStructure.CAN_FilterMaskIdLow=0x0000;
   	CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_Filter_FIFO0;//������0������FIFO0
  	CAN_FilterInitStructure.CAN_FilterActivation=ENABLE; //���������0
  	CAN_FilterInit(&CAN_FilterInitStructure);//�˲�����ʼ��
	
	#if CAN1_RX0_INT_ENABLE
		CAN_ITConfig(CAN1,CAN_IT_FMP0,ENABLE);						//FIFO0��Ϣ�Һ��ж�����FIFO 0 message pending Interrupt
		
		NVIC_InitStructure.NVIC_IRQChannel = CAN1_RX0_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	// �����ȼ�Ϊ1
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;			// �����ȼ�Ϊ0
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);
	#endif
}

#if CAN1_RX0_INT_ENABLE
CanRxMsg CAN1_IT_RxMessage;
u8 CAN1_IT_RxMessage_flag;
	//FIFO0��Ϣ�Һ��жϣ�RX0�жϷ�����			    
	void CAN1_RX0_IRQHandler(void)
	{
//		if(CAN_GetITStatus(CAN1,CAN_IT_FMP0) == SET) //FIFO 0 message pending Interrupt 
		//����������û�м���жϱ�־λ������жϱ�־λ�Ĵ���
		{
			CAN1_IT_RxMessage_flag = 1;
			CAN_Receive(CAN1, CAN_FIFO0, &CAN1_IT_RxMessage);
			
//			CAN_ClearFlag(CAN1,CAN_FLAG_RQCP0);
		}

	}
#endif

	
	
//�������������ض�������֡��ID����Ϣ
//care��0��ʾ�κ�ID�����գ�1��ʾֻ������FilterIdһ�µ�ID����Ϣ
//frameType����������֡�����ͣ�0Ϊ��׼֡��IDΪ11λ����1Ϊ��չ֡��IDΪ29λ��
//FilterId���������յ�ID
//Ĭ����Ϣ����Ϊ����֡
void CAN1_setExceptId(u8 care,u8 frameType,u32 FilterId)
{
	CAN_FilterInitTypeDef  CAN_FilterInitStructure;		//���ù�����
	if(care == 0)
	{
		CAN_FilterInitStructure.CAN_FilterNumber=0;	  //������0
		CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdMask; //����λģʽ
		CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_32bit;
		CAN_FilterInitStructure.CAN_FilterIdHigh=0x0000;
		CAN_FilterInitStructure.CAN_FilterIdLow=0x0000;
		CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0x0000;//32λMASK	������0��ʾ�������ض��Ľ���ID�����߶��ջ����ɽ��պ������趨��
		CAN_FilterInitStructure.CAN_FilterMaskIdLow=0x0000;
		CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_Filter_FIFO0;//������0������FIFO0
		CAN_FilterInitStructure.CAN_FilterActivation=ENABLE; //���������0
		CAN_FilterInit(&CAN_FilterInitStructure);//�˲�����ʼ��
	}else
	{
		if(frameType == CAN_Id_Standard)	//ֻ���ܱ�׼����֡
		{
			CAN_FilterInitStructure.CAN_FilterNumber=0;
			CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdMask; //����λģʽ
			CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_32bit;
			CAN_FilterInitStructure.CAN_FilterIdHigh = ((FilterId << 21) & 0xffff0000) >> 16;
			CAN_FilterInitStructure.CAN_FilterIdLow = ((FilterId << 21) | CAN_ID_STD | CAN_RTR_DATA) & 0xffff;
			CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0xFFFF;	
			CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0xFFFF;
			CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_Filter_FIFO0;
			CAN_FilterInitStructure.CAN_FilterActivation=ENABLE;
			CAN_FilterInit(&CAN_FilterInitStructure);
		}else								//ֻ������չ����֡
		{
			CAN_FilterInitStructure.CAN_FilterNumber=0;
			CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdMask; //����λģʽ
			CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_32bit;
			CAN_FilterInitStructure.CAN_FilterIdHigh = ((FilterId << 3) & 0xffff0000) >> 16;
			CAN_FilterInitStructure.CAN_FilterIdLow = ((FilterId << 3) | CAN_ID_EXT | CAN_RTR_DATA) & 0xffff;
			CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0xFFFF;	
			CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0xFFFF;
			CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_Filter_FIFO0;
			CAN_FilterInitStructure.CAN_FilterActivation=ENABLE;
			CAN_FilterInit(&CAN_FilterInitStructure);
		}

	}
}


//can����һ������			     
//msg:����ָ��,���Ϊ8���ֽ�
//len:���ݳ���(���Ϊ8)
//frameType:֡���ͣ�0Ϊ��׼֡��IDΪ11λ����1Ϊ��չ֡��IDΪ29λ��
//id:ID��ʶ������frameTypeΪ0����Ϊ��׼��ʶ������frameTypeΪ������Ϊ��չ��ʶ��
//Ĭ����Ϣ����Ϊ����֡
//����ֵ:0,�ɹ�;
//		 ����,ʧ��;
u8 CAN1_Send_Msg(u8* msg,u8 len,u8 frameType,u32 id)
{	
	u8 mbox;
	u16 i=0;
	CanTxMsg TxMessage;
	if(frameType == CAN_Id_Standard)
	{
		TxMessage.IDE=CAN_Id_Standard;		// ʹ�ñ�׼��ʶ��
		TxMessage.StdId = id;	 			// ���ñ�׼��ʶ��	��11λ��
	}else{
		TxMessage.IDE=CAN_Id_Extended;		// ʹ����չ��ʶ��
		TxMessage.ExtId = id;	 			// ������չ��ʾ��	��29λ��
	}
	TxMessage.RTR=CAN_RTR_Data;		  		// ��Ϣ����Ϊ����֡	������֡����ң��֡��CAN_RTR_Data ���� CAN_RTR_Remote��
	
	if(len > 8)return 1;
	TxMessage.DLC=len;						// ���ͼ��ֽ���Ϣ	��С�ڵ���8��
	for(i=0;i<len;i++)
		TxMessage.Data[i]=msg[i];   
	mbox= CAN_Transmit(CAN1, &TxMessage);   
	i=0;
	while((CAN_TransmitStatus(CAN1, mbox)==CAN_TxStatus_Failed)&&(i<0XFFF))i++;	//�ȴ����ͽ���
	if(i>=0XFFF)return 2;
	return 0;
}

//can�ڽ������ݲ�ѯ����ʹ���жϷ�ʽʱ��ʹ��
//buf:���ݻ�����;
//frameType:֡���ͣ�0Ϊ��׼֡��IDΪ11λ����1Ϊ��չ֡��IDΪ29λ��
//id:ID��ʶ������frameTypeΪ0����Ϊ��׼��ʶ������frameTypeΪ������Ϊ��չ��ʶ��
//����ֵ:0,�����ݱ��յ�;
//		 ����,���յ����ݳ���;
u8 CAN1_Receive_Msg(u8* buf,u8* frameType,u32* id)
{		   		   
 	u32 i;
	CanRxMsg RxMessage;
    if( CAN_MessagePending(CAN1,CAN_FIFO0)==0)return 0;		//û�н��յ�����,ֱ���˳� 
    CAN_Receive(CAN1, CAN_FIFO0, &RxMessage);				//��FIFO0��ȡ����
    for(i=0;i<RxMessage.DLC;i++)
		buf[i] = RxMessage.Data[i];
	
	if(RxMessage.IDE == CAN_Id_Standard)
	{
		*frameType = CAN_Id_Standard;
		*id = RxMessage.StdId;
	}else{
		*frameType = 1;
		*id = RxMessage.ExtId;
	}
	
	return RxMessage.DLC;	
}


