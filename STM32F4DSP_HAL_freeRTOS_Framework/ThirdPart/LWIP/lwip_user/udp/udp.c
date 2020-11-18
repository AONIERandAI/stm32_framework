#include "udp.h"

/*��ʷ�������⣬�ַ�������������string.c��׼���API*/

/*ʹ�ý��ܣ�

�������ӣ�
	//UDP��ʼ�������������udp_pcb��ѡ�� remoteip[3] �� �˿ں�
	//��ʼ������ �� UDP_init_test(UDP_PCB_test,100,UDP_PORT_test);
	//����0��ɹ���������ʧ��
	u8 UDP_init_test(struct udp_pcb *pcb, u8 remoteip_3, u16 udp_port)
		���ӣ�UDP_init_test(UDP_PCB_test,100,UDP_PORT_test);
��ѯ���ӣ�
	��ѯ��־λ UDP_IS_CONN_Flag �Ƿ�Ϊ�棬lwipû���ṩר�ŵ�API��
	������ֻ����û�н��յ�udp����ʱ�Ż��� UDP_IS_CONN_Flag Ϊ0
ע�⣺
	��������һ�����ϵ��ó�ʼ��API���ڵ��� �ر�����API ֮ǰֻ�ܵ���һ�Σ�
	��ʼ�����������Ϻ����ڼ�� UDP_IS_CONN_Flag�����ʧ����
	�ȵ���	UDP_connection_close(UDP_PCB_test);
	�ٵ���	UDP_init_test(UDP_PCB_test,100,UDP_PORT_test);

�ر����ӣ�
	//�ر�tcp����
	//���ӣ�UDP_connection_close(UDP_PCB_test);
	void UDP_connection_close(struct udp_pcb *upcb)
�������ݣ�
	��� udp_demo_recv_flag��Ϊ1���ʾ�յ����ݣ�
	�ӽ��ջ����� udp_demo_recvbuf ȡ�����ݣ�
	Ȼ�� udp_demo_recv_flag ����
�������ݣ�
	�ȸ� tcp_demo_sendbuf ����Ҫ�������ݣ���Ҫ�� '\0'Ϊ��β��
		���磺sprintf_(tcp_demo_sendbuf,"stm32_framework - STM32F407 UDP demo send data\r\n");
	//UDP�������������ݣ����� tcp_demo_sendbuf �ַ��������������
	void UDP_senddata_test(struct udp_pcb *upcb)

���ջ����� udp_demo_recvbuf �� ���ͻ����� tcp_demo_sendbuf �Ŀռ��Ϊ UDP_RX_BUFSIZE �� UDP_TX_BUFSIZE

*/

#if ((NO_SYS == 1) && (LWIP_UDP == 1))		//�����ʹ�ò���ϵͳ����ʹ��UDPʱ

//UDP�������ݻ�����
char* udp_demo_recvbuf;
//UDP�������ݻ�����
char* tcp_demo_sendbuf;			//��Ҫ�� '\0'Ϊ��β��

struct udp_pcb *UDP_PCB_test;  	//����һ��UDP������

u8 udp_demo_recv_flag = 0;		//�ɹ����յ�һ�����ݵı�־λ�������жϣ���Ϊ1��ɴ� udp_demo_recvbuf ȡ���ݣ�Ȼ������
u8 UDP_IS_CONN_Flag = 0;		//�Ƿ������ϱ�־λ��ֻ�ɲ�ѯ�����޸�

u8 UDP_inited = 0; 				//udp�ĳ�ʼ����־λ�����ڷ�ֹ����һ�����ϵ��ó�ʼ��������ϵͳ���ã��û�����


//UDP�������ص��������Զ��ѽ��յ��ַ���д�� udp_demo_recvbuf �ַ���������
void UDP_recv_test(void *arg, struct udp_pcb *pcb, struct pbuf *p, const ip_addr_t *addr, u16_t port)
{
	u32 data_len = 0;
	struct pbuf *q;
	if(p!=NULL)	//���յ���Ϊ�յ�����ʱ
	{
		memset(udp_demo_recvbuf,0,UDP_RX_BUFSIZE);  //���ݽ��ջ���������
		for(q=p;q!=NULL;q=q->next)  //����������pbuf����
		{
			//�ж�Ҫ������UDP_DEMO_RX_BUFSIZE�е������Ƿ����UDP_DEMO_RX_BUFSIZE��ʣ��ռ䣬�������
			//�Ļ���ֻ����UDP_DEMO_RX_BUFSIZE��ʣ�೤�ȵ����ݣ�����Ļ��Ϳ������е�����
			if(q->len > (UDP_RX_BUFSIZE-data_len)) memcpy(udp_demo_recvbuf+data_len,q->payload,(UDP_RX_BUFSIZE-data_len));//��������
			else memcpy(udp_demo_recvbuf+data_len,q->payload,q->len);
			data_len += q->len;  	
			if(data_len > UDP_RX_BUFSIZE) break; //����TCP�ͻ��˽�������,����	
		}
		pcb->remote_ip=*addr; 				//��¼Զ��������IP��ַ
		pcb->remote_port=port;  			//��¼Զ�������Ķ˿ں�
		lwip_inf.remoteip[0]= pcb->remote_ip.addr&0xff; 	//IADDR4
		lwip_inf.remoteip[1]=(pcb->remote_ip.addr>>8)&0xff; //IADDR3
		lwip_inf.remoteip[2]=(pcb->remote_ip.addr>>16)&0xff;//IADDR2
		lwip_inf.remoteip[3]=(pcb->remote_ip.addr>>24)&0xff;//IADDR1 
		
		udp_demo_recv_flag = 1;	//��ǽ��յ�������
		
		pbuf_free(p);//�ͷ��ڴ�
	}else
	{
		udp_disconnect(pcb); 
		UDP_IS_CONN_Flag = 0;
	} 
}
//UDP�������������ݣ����� tcp_demo_sendbuf �ַ��������������
void UDP_senddata_test(struct udp_pcb *upcb)
{
	struct pbuf *ptr;
	ptr=pbuf_alloc(PBUF_TRANSPORT,strlen(tcp_demo_sendbuf),PBUF_POOL); //�����ڴ�
	if(ptr)
	{
		ptr->payload=(void*)tcp_demo_sendbuf; 
		udp_send(upcb,ptr);	//udp��������
		pbuf_free(ptr);//�ͷ��ڴ�
	}
} 


//�ر�tcp����
//���ӣ�UDP_connection_close(UDP_PCB_test);
void UDP_connection_close(struct udp_pcb *upcb)
{
	myfree(InrRAM,udp_demo_recvbuf);
	myfree(InrRAM,tcp_demo_sendbuf);
	udp_disconnect(upcb); 
	udp_remove(upcb);		//�Ͽ�UDP���� 
	UDP_inited = 0;			//��Ƿ���ʼ����
	UDP_IS_CONN_Flag = 0;
}

//UDP��ʼ�������������udp_pcb��ѡ�� remoteip[3] �� �˿ں�
//��ʼ������ �� UDP_init_test(UDP_PCB_test,100,UDP_PORT_test);
/*��������һ�����ϵ��ã��ڵ��� �ر����� ֮ǰֻ�ܵ���һ��
��ʼ�����������Ϻ����ڼ�� UDP_IS_CONN_Flag�����ʧ����
�ȵ���	UDP_connection_close(UDP_PCB_test);
�ٵ���	UDP_init_test(UDP_PCB_test,100,UDP_PORT_test);*/
//����0�ɹ�������ʧ��
u8 UDP_init_test(struct udp_pcb *pcb, u8 remoteip_3, u16 udp_port)
{
 	err_t err;
	struct ip4_addr rmtipaddr;  	//Զ��ip��ַ
 	
	if(UDP_inited == 0)	//��ѯ�Ƿ��ʼ���������ڷ�ֹ����һ�����ϵ��ó�ʼ������
	{
		//����Զ��IP��ַ
		//ǰ����IP���ֺ�DHCP�õ���IPһ��
		lwip_inf.remoteip[0]=lwip_inf.ip[0];
		lwip_inf.remoteip[1]=lwip_inf.ip[1];
		lwip_inf.remoteip[2]=lwip_inf.ip[2];
		lwip_inf.remoteip[3] = remoteip_3;
		
		udp_demo_recvbuf = (char*)mymalloc(InrRAM,UDP_RX_BUFSIZE);
		tcp_demo_sendbuf = (char*)mymalloc(InrRAM,UDP_TX_BUFSIZE);
		if((udp_demo_recvbuf == NULL)||(tcp_demo_sendbuf == NULL))return 4;
		
		sprintf_(tcp_demo_sendbuf,"stm32_framework - STM32F407 UDP demo send data\r\n");
		
		pcb=udp_new();
		if(pcb)//�����ɹ�
		{ 
			IP4_ADDR(&rmtipaddr,lwip_inf.remoteip[0],lwip_inf.remoteip[1],lwip_inf.remoteip[2],lwip_inf.remoteip[3]);
			err=udp_connect(pcb,&rmtipaddr,udp_port);	//UDP�ͻ������ӵ�ָ��IP��ַ�Ͷ˿ںŵķ�����
			if(err==ERR_OK)
			{
				err=udp_bind(pcb,IP_ADDR_ANY,udp_port);	//�󶨱���IP��ַ��˿ں�
				if(err==ERR_OK)	//�����
				{
					udp_recv(pcb,UDP_recv_test,NULL);	//ע����ջص�����
					UDP_IS_CONN_Flag = 1;
					UDP_inited = 1; //��ǳ�ʼ����
					return 0;
				}else return 3;
			}else return 2;		
		}else return 1;
	
	}return 4;
}

#endif


