#ifndef __TCP_CLIENT_DEMO_H
#define __TCP_CLIENT_DEMO_H
#include "lwip_comm.h"
#include "PeriphConfigCore.h"
#include "PeriphConfig.h"


#include "lwip/debug.h"
#include "lwip/stats.h"
#include "lwip/tcp.h"
#include "lwip/memp.h"
#include "lwip/mem.h"

#if LWIP_TCP && (NO_SYS == 1)

#define TCP_CLIENT_RX_BUFSIZE	200		//����tcp client���������ݳ���
#define TCP_CLIENT_TX_BUFSIZE	200		//����tcp client���������ݳ���
#define	TCP_CLIENT_PORT			8087	//����tcp clientҪ���ӵ�Զ�˶˿�

//TCP Client�������ݻ�����
extern char* tcp_client_recvbuf;	
//TCP Client�������ݻ�����
extern char* tcp_client_sendbuf;			//��Ҫ�� '\0'Ϊ��β��

//TCP Client ����ȫ��״̬��Ǳ���
//bit7:0,û������Ҫ����;1,������Ҫ����
//bit6:0,û���յ�����;1,�յ�������
//bit5:0,û�������Ϸ�����;1,�����Ϸ�������
//bit4:0,û�г�ʼ�����߾����˷���ʼ��;1,��ʼ����
//bit3~0:����
extern u8 tcp_client_flag;


//���÷��ͱ�־��ϵͳ���Զ����� tcp_client_sendbuf ������
#define TCP_Client_SET_SEND_Flag	(tcp_client_flag|=0x80)	

//��ѯ�Ƿ������ݱ����յ���Ϊ������Դ� tcp_client_recvbuf ȡ����
#define TCP_Client_IS_RECV_Flag		(tcp_client_flag&0x40)
//Ҫ���ֲ�ѯ���������־λ�ĺ�ϰ����~
#define TCP_Client_Clear_RECV_Flag	(tcp_client_flag&=(~0x40))

//��ѯ��ǰ�����Ƿ���Ч�������ӶϿ�(������������)������ϵͳ�����0��Ӧ��һֱ��ѯ
#define TCP_Client_IS_CONN_Flag		(tcp_client_flag&0x20)	



extern struct tcp_pcb* TCP_Client_PCB_test;

//tcp����������״̬
enum tcp_client_states
{
	ES_TCPCLIENT_NONE = 0,		//û������
	ES_TCPCLIENT_CONNECTED,		//���ӵ��������� 
	ES_TCPCLIENT_CLOSING,		//�ر�����
}; 
//LWIP�ص�����ʹ�õĽṹ��
struct tcp_client_struct
{
	u8 state;               //��ǰ����״
	struct tcp_pcb *pcb;    //ָ��ǰ��pcb
	struct pbuf *p;         //ָ�����/�����pbuf
};  

u8 tcp_client_init_test(struct tcp_pcb *tcppcb, u8 remoteip_3, u16 tcp_client_port);
//err_t tcp_client_connected(void *arg, struct tcp_pcb *tpcb, err_t err);
//err_t tcp_client_recv(void *arg,struct tcp_pcb *tpcb,struct pbuf *p,err_t err);
//void tcp_client_error(void *arg,err_t err);
//err_t tcp_client_poll(void *arg, struct tcp_pcb *tpcb);
//err_t tcp_client_sent(void *arg, struct tcp_pcb *tpcb, u16_t len);
//void tcp_client_senddata(struct tcp_pcb *tpcb, struct tcp_client_struct * es);
void tcp_client_close(struct tcp_pcb *tpcb, struct tcp_client_struct * es );


#endif


#endif


