#ifndef _can_H
#define _can_H

#include "system.h"

//CAN1����RX0�ж�ʹ��
#define CAN1_RX0_INT_ENABLE	1		//0,��ʹ��;1,ʹ��
/*
ʹ�ý����жϷ�ʽ�󣺲�ѯCAN1_IT_RxMessage_flag�Ƿ��Ϊ1���������� CAN1_IT_RxMessage ʰȡ���ݺ�֡���͡�ID����Ϣ������CAN1_IT_RxMessage_flag����
��ʹ�ý����жϣ���ѭ������ CAN1_Receive_Msg(rbuf,&ReceiveFrameType,&receiveID);
*/


#if CAN1_RX0_INT_ENABLE
	extern u8 CAN1_IT_RxMessage_flag;	//CAN1���жϽ��յ����ݵı�־
	extern CanRxMsg CAN1_IT_RxMessage;	//CAN1���жϽ��յ����ݵĽṹ��
#endif

void CAN1_Mode_Init(u8 tsjw,u8 tbs2,u8 tbs1,u16 brp,u8 mode);//CAN��ʼ��
/*
	//��CAN����Ƶ��Ϊ42Mhzʱ���Ƽ���Ƶϵ��(brp+1)Ϊ6�����ηֱ�Ϊ��1tq\7tq\6tq
	CAN1_Mode_Init(CAN_SJW_1tq,CAN_BS2_6tq,CAN_BS1_7tq,6,CAN_Mode_Normal);
*/
 
 
//can����һ������			     
//msg:����ָ��,���Ϊ8���ֽ�
//len:���ݳ���(���Ϊ8)
//frameType:֡���ͣ�0Ϊ��׼֡��IDΪ11λ����1Ϊ��չ֡��IDΪ29λ��
//id:ID��ʶ������frameTypeΪ0����Ϊ��׼��ʶ������frameTypeΪ������Ϊ��չ��ʶ��
//Ĭ����Ϣ����Ϊ����֡
//����ֵ:0,�ɹ�;
//		 ����,ʧ��;
u8 CAN1_Send_Msg(u8* msg,u8 len,u8 frameType,u32 id);	//��������


//can�ڽ������ݲ�ѯ����ʹ���жϷ�ʽʱ��ʹ��
//buf:���ݻ�����;
//frameType:֡���ͣ�0Ϊ��׼֡��IDΪ11λ����1Ϊ��չ֡��IDΪ29λ��
//id:ID��ʶ������frameTypeΪ0����Ϊ��׼��ʶ������frameTypeΪ������Ϊ��չ��ʶ��
//����ֵ:0,�����ݱ��յ�;
//		 ����,���յ����ݳ���;
u8 CAN1_Receive_Msg(u8* buf,u8* frameType,u32* id);							//��������


//�������������ض�������֡��ID����Ϣ
//care��0��ʾ�κ�ID�����գ�1��ʾֻ������FilterIdһ�µ�ID����Ϣ
//frameType����������֡�����ͣ�0Ϊ��׼֡��IDΪ11λ����1Ϊ��չ֡��IDΪ29λ��
//FilterId���������յ�ID
//Ĭ����Ϣ����Ϊ����֡
void CAN1_setExceptId(u8 care,u8 frameType,u32 FilterId);


#endif
