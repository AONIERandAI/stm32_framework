#ifndef __UDP_DEMO_H
#define __UDP_DEMO_H

#include "lwip_comm.h"
#include "PeriphConfigCore.h"
#include "PeriphConfig.h"

#include "lwip/pbuf.h"
#include "lwip/udp.h"
#include "lwip/tcp.h"

#if ((NO_SYS == 1) && (LWIP_UDP == 1))

#define UDP_RX_BUFSIZE			200		//����udp���������ݳ��ȣ�ʹ��mallocΪ����������ռ䣬�û����޸� 
#define UDP_TX_BUFSIZE			200		//����udp��������ݳ��ȣ�ʹ��mallocΪ����������ռ䣬�û����޸� 
#define UDP_PORT_test			8089	//����udp���ӵĶ˿ڣ��û���

//UDP�������ݻ�����
extern char* udp_demo_recvbuf;			//�û���
//UDP�������ݻ�����
extern char* tcp_demo_sendbuf;			//��Ҫ�� '\0'Ϊ��β�����û���

	extern struct udp_pcb *UDP_PCB_test;
	extern u8 udp_demo_recv_flag;	//�ɹ����յ�һ�����ݵı�־λ�������жϣ���Ϊ1��ɴ� udp_demo_recvbuf ȡ���ݣ��û���
	u8 UDP_init_test(struct udp_pcb *pcb, u8 remoteip_3, u16 udp_port);	//UDP��ʼ�������������udp_pcb��ѡ�� remoteip[3] �� �˿ںţ��û���

//	void UDP_recv_test(void *arg, struct udp_pcb *pcb, struct pbuf *p, const ip_addr_t *addr, u16_t port);
	void UDP_senddata_test(struct udp_pcb *upcb); 		//UDP�������������ݣ����� tcp_demo_sendbuf �ַ�������������ݣ��û���
	void UDP_connection_close(struct udp_pcb *upcb); 	//�ر�tcp���ӣ��û���


#endif


#endif

