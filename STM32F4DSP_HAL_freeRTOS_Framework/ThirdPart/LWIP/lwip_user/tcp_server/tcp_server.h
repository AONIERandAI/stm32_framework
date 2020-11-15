#ifndef __TCP_SERVER_DEMO_H
#define __TCP_SERVER_DEMO_H

#include "lwip_comm.h"
#include "PeriphConfigCore.h"
#include "PeriphConfig.h"

#include "lwip/debug.h"
#include "lwip/stats.h"
#include "lwip/tcp.h"
#include "lwip/memp.h"
#include "lwip/mem.h"

#if LWIP_TCP && (NO_SYS == 1)


#define TCP_SERVER_RX_BUFSIZE	200		//����tcp server���������ݳ���
#define TCP_SERVER_TX_BUFSIZE	200		//����tcp server��������ݳ���
#define TCP_SERVER_PORT_test	8088	//����tcp server�Ķ˿�

//TCP Server�������ݻ�����
extern char* tcp_server_recvbuf;	
//TCPP Server�������ݻ�����
extern char* tcp_server_sendbuf;		//��Ҫ�� '\0'Ϊ��β��

//TCP Server ����ȫ��״̬��Ǳ���
//bit7:0,û������Ҫ����;1,������Ҫ����
//bit6:0,û���յ�����;1,�յ�������.
//bit5:0,û�пͻ���������;1,�пͻ�����������.
//bit4~0:����
extern u8 tcp_server_flag;

//���÷��ͱ�־��ϵͳ���Զ����� tcp_server_sendbuf ������
#define TCP_Server_SET_SEND_Flag	tcp_server_flag|=0x80	

//��ѯ�Ƿ������ݱ����յ���Ϊ������Դ� tcp_server_recvbuf ȡ����
#define TCP_Server_IS_RECV_Flag		tcp_server_flag&0x40
//Ҫ���ֲ�ѯ���������־λ�ĺ�ϰ����~
#define TCP_Server_Clear_RECV_Flag	tcp_server_flag&=(~0x40)

//��ѯ��ǰ�����Ƿ���Ч�����ӻ�ʧ��������ϵͳ�����0��Ӧ��һֱ��ѯ
#define TCP_Server_IS_CONN_Flag		tcp_server_flag&0x20	


extern struct tcp_pcb *TCP_Server_PCB_test;  		//����һ��TCP���������ƿ�
extern struct tcp_pcb *TCP_Server_PCBCONN_test;  	//����һ��TCP���������ƿ�


//tcp����������״̬
enum tcp_server_states
{
	ES_TCPSERVER_NONE = 0,		//û������
	ES_TCPSERVER_ACCEPTED,		//�пͻ����������� 
	ES_TCPSERVER_CLOSING,		//�����ر�����
}; 
//LWIP�ص�����ʹ�õĽṹ��
struct tcp_server_struct
{
	u8 state;               //��ǰ����״
	struct tcp_pcb *pcb;    //ָ��ǰ��pcb
	struct pbuf *p;         //ָ�����/�����pbuf
}; 

//TCP Server ��ʼ�������������tcp_pcb��ѡ�� remoteip[3] �� �˿ں�
//��ʼ�����ӣ� tcp_server_init_test(TCP_Server_PCB_test,TCP_Server_PCBCONN_test,TCP_SERVER_PORT_test);
//�����ɹ��󣬱���IP��TCP Server��IP��lwip_inf.remoteip ��д��Զ�������ϵ�IP
//����0�ɹ�������ʧ��
u8 tcp_server_init_test(struct tcp_pcb* tcppcbnew,struct tcp_pcb* tcppcbconn,u16_t tcp_server_port);
//�ر�tcp server���ӣ��û�����
void TCP_Server_connection_close(struct tcp_pcb* tspcb,struct tcp_pcb* tspcbconn);
//err_t tcp_server_accept(void *arg,struct tcp_pcb *newpcb,err_t err);
//err_t tcp_server_recv(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err);
//void tcp_server_error(void *arg,err_t err);
//err_t tcp_server_poll(void *arg, struct tcp_pcb *tpcb);
//err_t tcp_server_sent(void *arg, struct tcp_pcb *tpcb, u16_t len);
//void tcp_server_senddata(struct tcp_pcb *tpcb, struct tcp_server_struct *es);
//void tcp_server_connection_close(struct tcp_pcb *tpcb, struct tcp_server_struct *es);
//void tcp_server_remove_timewait(void);

#endif



#endif 
