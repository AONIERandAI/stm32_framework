#ifndef _LWIP_COMM_H
#define _LWIP_COMM_H 
#include "NetCard.h" 
#include "netif/etharp.h"

/*����Ӧ�ò��ͷ�ļ�*/
#include "udp.h"
#include "tcp_server.h"
#include "tcp_client.h" 

#include "httpd.h"

//extern ETH_HandleTypeDef ETH_Handler;             //��̫�����
//extern ETH_DMADescTypeDef *DMARxDscrTab;			//��̫��DMA�������������ݽṹ��ָ��
//extern ETH_DMADescTypeDef *DMATxDscrTab;			//��̫��DMA�������������ݽṹ��ָ�� 
//extern uint8_t *Rx_Buff; 							//��̫���ײ���������buffersָ�� 
//extern uint8_t *Tx_Buff; 							//��̫���ײ���������buffersָ��
//extern ETH_DMADescTypeDef  *DMATxDescToSet;		//DMA����������׷��ָ��
//extern ETH_DMADescTypeDef  *DMARxDescToGet; 		//DMA����������׷��ָ�� 

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

extern struct netif lwip_handle;	//����һ��ȫ�ֵ�����ӿھ��

/*�����LWIP��Ҫѭ��ִ�е���������*/
//void lwip_pkt_handle(void);		//��ETH�����ж������Ҫ�ⲿ����
void lwip_periodic_handle(void);	//�ϸ�10ms���ڵ���
u8 lwip_comm_init(struct netif *netif);
void lwip_comm_destroy(struct netif *netif);


#endif













