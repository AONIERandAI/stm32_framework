#ifndef _LWIP_COMM_H
#define _LWIP_COMM_H 
#include "NetCard.h" 

#define LWIP_MAX_DHCP_TRIES		4   //DHCP������������Դ���

//lwip��Ϣ�ṹ��
typedef struct  
{
	u8 mac[6];      //MAC��ַ
	u8 remoteip[4];	//Զ������IP��ַ 
	u8 ip[4];       //����IP��ַ
	u8 netmask[4]; 	//��������
	u8 gateway[4]; 	//Ĭ�����ص�IP��ַ
	
	vu8 dhcpstatus;	//dhcp״̬ 
					//0,δ��ȡDHCP��ַ;
					//1,����DHCP��ȡ״̬
					//2,�ɹ���ȡDHCP��ַ
					//0XFF,��ȡʧ��.
}__lwip_dev;
extern __lwip_dev lwip_inf;	//lwip��Ϣ�ṹ��

/*�����LWIP��Ҫѭ��ִ�е���������*/
void lwip_pkt_handle(void);
void lwip_periodic_handle(void);

u8 lwip_comm_init(void);

#endif













