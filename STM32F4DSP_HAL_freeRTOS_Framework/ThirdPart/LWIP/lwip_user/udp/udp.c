#include "udp.h"


//UDP�������ݻ�����
u8 udp_demo_recvbuf[UDP_RX_BUFSIZE];	//UDP�������ݻ�����
//UDP�������ݻ�����
const u8 tcp_demo_sendbuf[] = "stm32_framework - STM32F407 UDP demo send data\r\n";

struct udp_pcb *UDP_PCB_test;  	//����һ��UDP���������ƿ�


#if (LWIP_UDP == 1)			//���ʹ��UDPʱ

u8 udp_demo_flag = 0;		//�ɹ����յ�һ�����ݵı�־λ�������ж�


//UDP��ʼ�������������udp_pcb��ѡ�� remoteip[3] �� �˿ں�
u8 UDP_init_test(struct udp_pcb *pcb, u8 remoteip_3, u16 udp_port)
{
 	err_t err;
	struct ip4_addr rmtipaddr;  	//Զ��ip��ַ
 	
	//����Զ��IP��ַ
	//ǰ����IP���ֺ�DHCP�õ���IPһ��
	lwip_inf.remoteip[0]=lwip_inf.ip[0];
	lwip_inf.remoteip[1]=lwip_inf.ip[1];
	lwip_inf.remoteip[2]=lwip_inf.ip[2];
	lwip_inf.remoteip[3] = remoteip_3;
	
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
				return 0;
			}else return 3;
		}else return 2;		
	}else return 1;
}

#endif

#if ((NO_SYS == 1) && (LWIP_UDP == 1))		//�����ʹ�ò���ϵͳ����ʹ��UDPʱ
//UDP�������ص��������Զ��ѽ��յ��ַ���д�� tcp_demo_sendbuf �ַ���������
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
		
		udp_demo_flag = 1;	//��ǽ��յ�������
		
		pbuf_free(p);//�ͷ��ڴ�
	}else
	{
		udp_disconnect(pcb); 
	} 
} 
//UDP�������������ݣ����� tcp_demo_sendbuf �ַ��������������
void UDP_senddata_test(struct udp_pcb *upcb)
{
	struct pbuf *ptr;
	ptr=pbuf_alloc(PBUF_TRANSPORT,strlen((char*)tcp_demo_sendbuf),PBUF_POOL); //�����ڴ�
	if(ptr)
	{
		ptr->payload=(void*)tcp_demo_sendbuf; 
		udp_send(upcb,ptr);	//udp�������� 
		pbuf_free(ptr);//�ͷ��ڴ�
	} 
} 

#endif


//�ر�tcp����
void UDP_connection_close(struct udp_pcb *upcb)
{
	udp_disconnect(upcb); 
	udp_remove(upcb);		//�Ͽ�UDP���� 
}
