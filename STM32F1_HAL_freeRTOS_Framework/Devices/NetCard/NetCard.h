#ifndef _NETCARD_H
#define _NETCARD_H
#include "lwip/sys.h"
#include "lwip/pbuf.h"

#include "sys_config.h"


#define NetCard_ID 0x3971038

//�����Ĵ���

//�����ڲ�PHY�Ĵ���

//��������ģʽ����
enum NetCard_PHY_mode
{
	NetCard_10MHD 	= 	0, 					//10M��˫��
	NetCard_100MHD 	= 	1,					//100M��˫��	
	NetCard_10MFD 	= 	4, 					//10Mȫ˫��
	NetCard_100MFD 	= 	5,					//100Mȫ˫��
	NetCard_AUTO  	= 	8, 					//�Զ�Э��
};

//�������ýṹ�壬ֻ���ڳ�ʼ������
struct NetCard_config
{
	enum NetCard_PHY_mode mode;				//����ģʽ
	u8  imr_all;							//�ж����� 
	u16 queue_packet_len;					//ÿ�����ݰ���С
	u8  mac_addr[6];						//MAC��ַ
	u8  multicase_addr[8];					//�鲥��ַ
};
extern struct NetCard_config NetCardcfg;	//�������ýṹ��

u8   NetCard_Init(void);
u16  NetCard_ReadReg(u16 reg);
void NetCard_WriteReg(u16 reg,u16 data);
u16  NetCard_PHY_ReadReg(u16 reg);
void NetCard_PHY_WriteReg(u16 reg,u16 data);
u32  NetCard_Get_DeiviceID(void);
u8   NetCard_Get_SpeedAndDuplex(void);	
void NetCard_Set_PHYMode(u8 mode);
void NetCard_Set_MACAddress(u8 *macaddr);
void NetCard_Set_Multicast(u8 *multicastaddr);
void NetCard_Reset(void);


void NetCard_SendPacket(struct pbuf *p);
struct pbuf *NetCard_Receive_Packet(void);
void NetCard_ISRHandler(void);
#endif



