#include "NetCard.h"
#include "lwip_comm.h"

struct NetCard_config NetCardcfg;				//�������ýṹ��

/*
�����������ʼ��
	����ʼ��IO������MAC��ַ���鲥��ַ�����üĴ��������ù���ģʽ������ID��

�ٸ��� struct pbuf ��������� ��������շ�����
*/

u8 NetCard_Init(void)
{
	u32 temp;
	
	/*_________________________________IO����������ʼ��_____________________________________*/

	
	/*_________________________________��������_____________________________________*/
	
	temp=*(vu32*)(0x1FFFF7E8);				//��ȡSTM32��ΨһID��ǰ24λ��ΪMAC��ַ�����ֽ�
	NetCardcfg.mode=NetCard_AUTO;	
 	NetCardcfg.queue_packet_len=0;
	
	//��ʼ��MAC��ַ
	NetCardcfg.mac_addr[0]=2;
	NetCardcfg.mac_addr[1]=0;
	NetCardcfg.mac_addr[2]=0;
	NetCardcfg.mac_addr[3]=(temp>>16)&0XFF;	//�����ֽ���STM32��ΨһID
	NetCardcfg.mac_addr[4]=(temp>>8)&0XFFF;
	NetCardcfg.mac_addr[5]=temp&0XFF;
	
	//��ʼ���鲥��ַ
	NetCardcfg.multicase_addr[0]=0Xff;
	NetCardcfg.multicase_addr[1]=0Xff;
	NetCardcfg.multicase_addr[2]=0Xff;
	NetCardcfg.multicase_addr[3]=0Xff;
	NetCardcfg.multicase_addr[4]=0Xff;
	NetCardcfg.multicase_addr[5]=0Xff;
	NetCardcfg.multicase_addr[6]=0Xff;
	NetCardcfg.multicase_addr[7]=0Xff; 
	
	NetCard_Reset();							//��λNetCard
	delay_ms(100);
	
	
	/*_________________________________�����Ĵ�����ʼ��_____________________________________*/
	
	temp=NetCard_Get_DeiviceID();			//��ȡNetCardID
	if(temp!=NetCard_ID) return 1; 			//��ȡID����
	
	NetCard_Set_PHYMode(NetCardcfg.mode);		//����PHY����ģʽ
	
	//һ��...
	//NetCard_WriteReg(,); 	
	
	
	//����MAC��ַ���鲥��ַ
	NetCard_Set_MACAddress(NetCardcfg.mac_addr);		//����MAC��ַ
	NetCard_Set_Multicast(NetCardcfg.multicase_addr);	//�����鲥��ַ
	//temp=NetCard_Get_SpeedAndDuplex();		//��ȡNetCard�������ٶȺ�˫��״̬
	//NetCard_WriteReg(NetCard_IMR,NetCardcfg.imr_all);	//�����ж�
	return 0;		
}

//��ȡNetCardָ���Ĵ�����ֵ
//reg:�Ĵ�����ַ
//����ֵ��NetCardָ���Ĵ�����ֵ
u16 NetCard_ReadReg(u16 reg)
{
	u16 value;
	
	return value;
}

//��NetCardָ���Ĵ�����д��ָ��ֵ
//reg:Ҫд��ļĴ���
//data:Ҫд���ֵ
void NetCard_WriteReg(u16 reg,u16 data)
{
	
}

//��ȡNetCard��PHY��ָ���Ĵ���
//reg:Ҫ����PHY�Ĵ���
//����ֵ:��ȡ����PHY�Ĵ���ֵ
u16 NetCard_PHY_ReadReg(u16 reg)
{
	u16 value;
	
	return value;
}

//��NetCard��PHY�Ĵ���д��ָ��ֵ
//reg:PHY�Ĵ���
//data:Ҫд���ֵ
void NetCard_PHY_WriteReg(u16 reg,u16 data)
{
	
}

//��ȡNetCard��оƬID
//����ֵ��NetCard��оƬIDֵ
u32 NetCard_Get_DeiviceID(void)
{
	u32 value;
	
	return value;
}

//��ȡNetCard�������ٶȺ�˫��ģʽ
//����ֵ��	0,100M��˫��
//			1,100Mȫ˫��
//			2,10M��˫��
//			3,10Mȫ˫��
//			0XFF,����ʧ�ܣ�
u8 NetCard_Get_SpeedAndDuplex(void)
{
	u8 temp;
	
	return temp;
}

//����DM900��PHY����ģʽ
//mode:PHYģʽ
void NetCard_Set_PHYMode(u8 mode)
{
//	u16 BMCR_Value,ANAR_Value;	
//	switch(mode)
//	{
//		case NetCard_10MHD:		//10M��˫��
//			BMCR_Value=0X0000;
//			ANAR_Value=0X21;
//			break;
//		case NetCard_10MFD:		//10Mȫ˫��
//			BMCR_Value=0X0100;
//			ANAR_Value=0X41;
//			break;
//		case NetCard_100MHD:		//100M��˫��
//			BMCR_Value=0X2000;
//			ANAR_Value=0X81;
//			break;
//		case NetCard_100MFD:		//100Mȫ˫��
//			BMCR_Value=0X2100;
//			ANAR_Value=0X101;
//			break;
//		case NetCard_AUTO:		//�Զ�Э��ģʽ
//			BMCR_Value=0X1000;
//			ANAR_Value=0X01E1;
//			break;		
//	}
//	NetCard_PHY_WriteReg(NetCard_PHY_BMCR,BMCR_Value);
//	NetCard_PHY_WriteReg(NetCard_PHY_ANAR,ANAR_Value);
// 	NetCard_WriteReg(NetCard_GPR,0X00);	//ʹ��PHY
}

//����NetCard��MAC��ַ
//macaddr:ָ��MAC��ַ
void NetCard_Set_MACAddress(u8 *macaddr)
{
	u8 i;
	for(i=0;i<6;i++)
	{
		//NetCard_WriteReg(NetCard_PAR+i,macaddr[i]);
	}
}
//����NetCard���鲥��ַ
//multicastaddr:ָ��ಥ��ַ
void NetCard_Set_Multicast(u8 *multicastaddr)
{
	u8 i;
	for(i=0;i<8;i++)
	{
		//NetCard_WriteReg(NetCard_MAR+i,multicastaddr[i]);
	}
}
//��λNetCard
void NetCard_Reset(void)
{
	//��λNetCard,��λ����ο� NetCard Application �ֲ�
	
} 

//ͨ��NetCard�������ݰ�
//p:pbuf�ṹ��ָ��
void NetCard_SendPacket(struct pbuf *p)
{
//	struct pbuf *q;
	
//	q->next;
//	q->len;
//	q->payload;					
}

//NetCard�������ݰ�
//���յ������ݰ������NetCard��RX FIFO�У���ַΪ0X0C00~0X3FFF
//���յ������ݰ���ǰ�ĸ��ֽڲ�������ʵ�����ݣ��������ض������
//byte1:�����Ƿ���յ����ݣ�Ϊ0x00����0X01��������������ǵĻ�һ��Ҫ�����λNetCard
//		0x01�����յ�����
//		0x00��δ���յ�����
//byte2:�ڶ����ֽڱ�ʾһЩ״̬��Ϣ����NetCard��RSR(0X06)�Ĵ���һ�µ�
//byte3:��֡���ݳ��ȵĵ��ֽ�
//byte4:��֡���ݳ��ȵĸ��ֽ�
//����ֵ��pbuf��ʽ�Ľ��յ������ݰ�
struct pbuf *NetCard_Receive_Packet(void)
{
	struct pbuf* p;
	//p=pbuf_alloc(PBUF_RAW,rx_length,PBUF_POOL);	//pbufs�ڴ�ط���pbuf

	return (struct pbuf*)p; 
}


//�жϴ�����
//���ⲿ�жϻص������е��ô˺���
void NetCard_ISRHandler(void)
{
//	u16 int_status;
//	u16 last_io; 
//	last_io = NetCard->REG;
//	int_status=NetCard_ReadReg(NetCard_ISR); 
//	NetCard_WriteReg(NetCard_ISR,int_status);				//����жϱ�־λ��NetCard��ISR�Ĵ�����bit0~bit5д1����
//	if(int_status & ISR_ROS)printf("overflow \r\n");
//    if(int_status & ISR_ROOS)printf("overflow counter overflow \r\n");	
//	if(int_status & ISR_PRS)		//�����ж�
//	{  
// 		//��������жϣ��û���������������
//	} 
//	if(int_status&ISR_PTS)			//�����ж�
//	{ 
//		//��������жϣ��û���������������
//	}
//	NetCard->REG=last_io;	
}

