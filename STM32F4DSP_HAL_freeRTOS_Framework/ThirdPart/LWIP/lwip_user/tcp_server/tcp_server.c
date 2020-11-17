#include "tcp_server.h"  

/*��ʷ�������⣬�ַ�������������string.c��׼���API*/


/*ʹ�ý��ܣ�

�������ӣ�
	//TCP Server ��ʼ�������������tcp_pcb��ѡ�� remoteip[3] �� �˿ں�
	//��ʼ�����ӣ� tcp_server_init_test(TCP_Server_PCB_test,TCP_Server_PCBCONN_test,TCP_SERVER_PORT_test);
	//�����ɹ��󣬱���IP��TCP Server��IP��lwip_inf.remoteip ��д��Զ�������ϵ�IP
	//����0�ɹ�������ʧ��
	u8 tcp_server_init_test(struct tcp_pcb* tcppcbnew,struct tcp_pcb* tcppcbconn,u16_t tcp_server_port)
��ѯ�Ƿ��пͻ��������ϣ�
	һֱѭ����� TCP_Server_IS_CONN_Flag ���Ƿ�Ϊ�棬���ӻ�ʧ��������ϵͳ�����0
ע�⣺
	��������һ�����ϵ��ó�ʼ��API���ڵ��� �ر�����API ֮ǰֻ�ܵ���һ�Σ�
	��ʼ�����������Ϻ����ڼ�� TCP_Server_IS_CONN_Flag �꣬���ʧ����
	�ȵ���	tcp_server_close(TCP_Server_PCB_test,TCP_Server_PCBCONN_test);
	�ٵ���	tcp_server_init_test(TCP_Server_PCB_test,TCP_Server_PCBCONN_test,TCP_SERVER_PORT_test);

�ر����ӣ�
	//�ر�tcp server����
	//���ӣ�tcp_server_close(TCP_Server_PCB_test,TCP_Server_PCBCONN_test);
	void tcp_server_close(struct tcp_pcb* tspcb,struct tcp_pcb* tspcbconn)
�������ݣ�
	��� TCP_Server_IS_RECV_Flag ���Ƿ�Ϊ�棬Ϊ�����ʾ�յ����ݣ�
	�ӽ��ջ����� tcp_server_recvbuf ȡ�����ݣ�
	Ȼ����� TCP_Server_Clear_RECV_Flag; �� ������ձ�־λ
�������ݣ�
	�ȸ� tcp_server_sendbuf ����Ҫ�������ݣ���Ҫ�� '\0'Ϊ��β��
		���磺sprintf_(tcp_server_sendbuf,"stm32_framework - STM32F407 TCP Server demo send data\r\n");
	Ȼ����� TCP_Server_SET_SEND_Flag; �� ���÷��ͱ�־λ��ϵͳ���Զ����� tcp_server_sendbuf ������

���ջ����� tcp_server_recvbuf �� ���ͻ����� tcp_server_sendbuf �Ŀռ��Ϊ TCP_SERVER_RX_BUFSIZE �� TCP_SERVER_TX_BUFSIZE 

*/

#if LWIP_TCP && (NO_SYS == 1)

//TCP Server�������ݻ�����
char* tcp_server_recvbuf;	
//TCPP Server�������ݻ�����
char* tcp_server_sendbuf;		//��Ҫ�� '\0'Ϊ��β��

//TCP Server ����ȫ��״̬��Ǳ���
//bit7:0,û������Ҫ����;1,������Ҫ����
//bit6:0,û���յ�����;1,�յ�������
//bit5:0,û�пͻ���������;1,�пͻ�����������
//bit4:0,û�г�ʼ�����߾����˷���ʼ��;1,��ʼ����
//bit3~0:����
u8 tcp_server_flag;


//tcp_server�ĳ�ʼ����־λ�����ڷ�ֹ����һ�����ϵ��ó�ʼ��������ϵͳ���ã��û�����
#define TCP_Server_SET_INITED_Flag		(tcp_server_flag|=0x10)
#define TCP_Server_Clear_INITED_Flag	(tcp_server_flag&=(~0x10))
#define TCP_Server_IS_INITED_Flag		(tcp_server_flag&0x10)

struct tcp_pcb *TCP_Server_PCB_test;  		//����һ��TCP���������ƿ�
struct tcp_pcb *TCP_Server_PCBCONN_test;  	//����һ��TCP���������ƿ�


//lwIP tcp_recv()�����Ļص����������յ����ݵĻص����� Called when data has been received.ϵͳ���Ĳ����û�����
err_t tcp_server_recv(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err)
{
	err_t ret_err;
	u32 data_len = 0;
	struct pbuf *q;
  	struct tcp_server_struct *es;
	LWIP_ASSERT("arg != NULL",arg != NULL);
	es=(struct tcp_server_struct *)arg;
	if(p==NULL) //�ӿͻ��˽��յ�������
	{
		es->state=ES_TCPSERVER_CLOSING;//��Ҫ�ر�TCP ������
		es->p=p; 
		ret_err=ERR_OK;
	}else if(err!=ERR_OK)	//�ӿͻ��˽��յ�һ���ǿ�����,��������ĳ��ԭ��err!=ERR_OK
	{
		if(p)pbuf_free(p);	//�ͷŽ���pbuf
		ret_err=err;
	}else if(es->state==ES_TCPSERVER_ACCEPTED) 	//��������״̬
	{
		if(p!=NULL)  //����������״̬���ҽ��յ������ݲ�Ϊ��ʱ�����ӡ����
		{
			memset(tcp_server_recvbuf,0,TCP_SERVER_RX_BUFSIZE);  //���ݽ��ջ���������
			for(q=p;q!=NULL;q=q->next)  //����������pbuf����
			{
				//�ж�Ҫ������TCP_SERVER_RX_BUFSIZE�е������Ƿ����TCP_SERVER_RX_BUFSIZE��ʣ��ռ䣬�������
				//�Ļ���ֻ����TCP_SERVER_RX_BUFSIZE��ʣ�೤�ȵ����ݣ�����Ļ��Ϳ������е�����
				if(q->len > (TCP_SERVER_RX_BUFSIZE-data_len)) memcpy(tcp_server_recvbuf+data_len,q->payload,(TCP_SERVER_RX_BUFSIZE-data_len));//��������
				else memcpy(tcp_server_recvbuf+data_len,q->payload,q->len);
				data_len += q->len;  	
				if(data_len > TCP_SERVER_RX_BUFSIZE) break; //����TCP�ͻ��˽�������,����	
			}
			
			tcp_server_flag|=1<<6;			//��ǽ��յ������ˣ�
			
			lwip_inf.remoteip[0]=tpcb->remote_ip.addr&0xff; 		//IADDR4
			lwip_inf.remoteip[1]=(tpcb->remote_ip.addr>>8)&0xff; 	//IADDR3
			lwip_inf.remoteip[2]=(tpcb->remote_ip.addr>>16)&0xff;	//IADDR2
			lwip_inf.remoteip[3]=(tpcb->remote_ip.addr>>24)&0xff;	//IADDR1
 			tcp_recved(tpcb,p->tot_len);	//���ڻ�ȡ��������,֪ͨLWIP���Ի�ȡ��������
			pbuf_free(p);  					//�ͷ��ڴ�
			ret_err=ERR_OK;
		}
	}else//�������ر���
	{
		tcp_recved(tpcb,p->tot_len);//���ڻ�ȡ��������,֪ͨLWIP���Ի�ȡ��������
		es->p=NULL;
		pbuf_free(p); //�ͷ��ڴ�
		ret_err=ERR_OK;
	}
	return ret_err;
}
//lwIP tcp_err�����Ļص�����
//Called when the pcb receives a RST or is unexpectedly closed for any other reason.
void tcp_server_error(void *arg,err_t err)
{  
	char* buf = mymalloc(InrRAM,50);
	LWIP_UNUSED_ARG(err);
	
	sprintf_(buf,"tcp error:%x\r\n",(u32)arg);
	FaultASSERT(buf,7,flag_Warning);
	myfree(InrRAM,buf);
	
	if(arg!=NULL)mem_free(arg);//�ͷ��ڴ�
}

//�ر�tcp����
void tcp_server_connection_close(struct tcp_pcb *tpcb, struct tcp_server_struct *es)
{
	tcp_close(tpcb);
	tcp_arg(tpcb,NULL);
	tcp_sent(tpcb,NULL);
	tcp_recv(tpcb,NULL);
	tcp_err(tpcb,NULL);
	tcp_poll(tpcb,NULL,0);
	if(es)mem_free(es); 
	tcp_server_flag&=~(1<<5);//������ӶϿ���
}

//�˺��������������ݣ�ϵͳ���Զ��ģ��� tcp_server_poll �������ã��û����õ���
void tcp_server_senddata(struct tcp_pcb *tpcb, struct tcp_server_struct *es)
{
	struct pbuf *ptr;
	u16 plen;
	err_t wr_err=ERR_OK;
	 while((wr_err==ERR_OK)&&es->p&&(es->p->len<=tcp_sndbuf(tpcb)))
	 {
		ptr=es->p;
		wr_err=tcp_write(tpcb,ptr->payload,ptr->len,1); //��Ҫ���͵����ݼ��뷢�ͻ��������
		if(wr_err==ERR_OK)
		{ 
			plen=ptr->len;
			es->p=ptr->next;			//ָ����һ��pbuf
			if(es->p)pbuf_ref(es->p);	//pbuf��ref��һ
			pbuf_free(ptr);
			tcp_recved(tpcb,plen); 		//����tcp���ڴ�С
		}else if(wr_err==ERR_MEM)es->p=ptr;
		tcp_output(tpcb);   //�����ͻ�������е����ݷ��ͳ�ȥ
	 }
}

//lwIP tcp_poll�Ļص�������Called periodically as specified by��ϵͳ���Ĳ����û�����
//���� tcp_server_flag ��־λ���Ϸ��ͱ�־�󣬻��ڴ˺������÷��ͺ������� tcp_server_sendbuf ������
//���жϵ�ǰ�����Ƿ�رգ�����ر������ tcp_server_connection_close ������������ʧ����־λ
err_t tcp_server_poll(void *arg, struct tcp_pcb *tpcb)
{
	err_t ret_err;
	struct tcp_server_struct *es; 
	es=(struct tcp_server_struct *)arg; 
	if(es!=NULL)
	{
		if(tcp_server_flag&(1<<7))	//�ж��Ƿ�������Ҫ����
		{
			es->p=pbuf_alloc(PBUF_TRANSPORT,strlen((char*)tcp_server_sendbuf),PBUF_POOL);//�����ڴ�
			pbuf_take(es->p,(char*)tcp_server_sendbuf,strlen((char*)tcp_server_sendbuf));
			tcp_server_senddata(tpcb,es); 		//��ѯ��ʱ����Ҫ���͵�����
			tcp_server_flag&=~(1<<7);  			//������ݷ��ͱ�־λ
			if(es->p!=NULL)pbuf_free(es->p); 	//�ͷ��ڴ�	
		}else if(es->state==ES_TCPSERVER_CLOSING)//��Ҫ�ر�����?ִ�йرղ���
		{
			tcp_server_connection_close(tpcb,es);//�ر�����
		}
		ret_err=ERR_OK;
	}else
	{
		tcp_abort(tpcb);//��ֹ����,ɾ��pcb���ƿ�
		ret_err=ERR_ABRT; 
	}
	return ret_err;
} 
//lwIP tcp_sent�Ļص�����(����Զ���������յ�ACK�źź�������)��ϵͳ���Ĳ����û�����
err_t tcp_server_sent(void *arg, struct tcp_pcb *tpcb, u16_t len)
{
	struct tcp_server_struct *es;
	LWIP_UNUSED_ARG(len); 
	es = (struct tcp_server_struct *) arg;
	if(es->p)tcp_server_senddata(tpcb,es);//��������
	return ERR_OK;
}

//lwIP tcp_accept()�Ļص�������ע����ֻص�������
//�ͻ��������ϱ���Server IPʱ�Ļص�������ϵͳ���Ĳ����û�����
//Called when a new connection can be accepted on a listening pcb.
err_t tcp_server_accept(void *arg,struct tcp_pcb *newpcb,err_t err)
{
	err_t ret_err;
	struct tcp_server_struct *es; 
 	LWIP_UNUSED_ARG(arg);
	LWIP_UNUSED_ARG(err);
	tcp_setprio(newpcb,TCP_PRIO_NORMAL);//�����´�����pcb���ȼ�
	es=(struct tcp_server_struct*)mem_malloc(sizeof(struct tcp_server_struct)); //�����ڴ�
 	if(es != NULL) //�ڴ����ɹ�
	{
		es->state=ES_TCPSERVER_ACCEPTED;  	//��������
		es->pcb=newpcb;
		es->p=NULL;
		
		tcp_arg(newpcb,es);
		tcp_recv(newpcb,tcp_server_recv);	//��ʼ��tcp_recv()�Ļص�����
		tcp_err(newpcb,tcp_server_error); 	//��ʼ��tcp_err()�ص�����
		tcp_poll(newpcb,tcp_server_poll,1);	//��ʼ��tcp_poll�ص�����
		tcp_sent(newpcb,tcp_server_sent);  	//��ʼ�����ͻص�����
		  
		tcp_server_flag|=1<<5;				//����пͻ��������ˣ�
		
		//���Զ�������ϵ�IP
		lwip_inf.remoteip[0] = newpcb->remote_ip.addr&0xff; 		//IADDR4
		lwip_inf.remoteip[1] = (newpcb->remote_ip.addr>>8)&0xff;  	//IADDR3
		lwip_inf.remoteip[2] = (newpcb->remote_ip.addr>>16)&0xff; 	//IADDR2
		lwip_inf.remoteip[3] = (newpcb->remote_ip.addr>>24)&0xff; 	//IADDR1 
		ret_err=ERR_OK;
	}else ret_err=ERR_MEM;
	return ret_err;
}


//TCP Server ��ʼ�������������tcp_pcb��ѡ�� remoteip[3] �� �˿ں�
//��ʼ�����ӣ� tcp_server_init_test(TCP_Server_PCB_test,TCP_Server_PCBCONN_test,TCP_SERVER_PORT_test);
//�����ɹ��󣬱���IP��TCP Server��IP��lwip_inf.remoteip ��д��Զ�������ϵ�IP
/*��������һ�����ϵ��ã��ڵ��� �ر����� ֮ǰֻ�ܵ���һ��
��ʼ�����������Ϻ����ڼ�� TCP_Server_IS_CONN_Flag �꣬���ʧ����
�ȵ���	tcp_server_connection_close(TCP_Server_PCB_test,TCP_Server_PCBCONN_test);
�ٵ���	tcp_server_init_test(TCP_Server_PCB_test,TCP_Server_PCBCONN_test,TCP_SERVER_PORT_test);*/
//����0�ɹ�������ʧ��
u8 tcp_server_init_test(struct tcp_pcb* tcppcbnew,struct tcp_pcb* tcppcbconn,u16_t tcp_server_port)
{
	err_t err;
	
	if(TCP_Server_IS_INITED_Flag == 0)	//��ѯ�Ƿ��ʼ���������ڷ�ֹ����һ�����ϵ��ó�ʼ������
	{
			tcp_server_recvbuf = (char*)mymalloc(InrRAM,TCP_SERVER_RX_BUFSIZE);
		tcp_server_sendbuf = (char*)mymalloc(InrRAM,TCP_SERVER_TX_BUFSIZE);
		if((tcp_server_recvbuf == NULL)||(tcp_server_sendbuf == NULL))return 4;
		
		sprintf_(tcp_server_sendbuf,"stm32_framework - STM32F407 TCP Server demo send data\r\n");
		
		tcppcbnew = tcp_new();		//����һ���µ�pcb
		if(tcppcbnew)				//�����ɹ�
		{ 
			err = tcp_bind(tcppcbnew,IP_ADDR_ANY,tcp_server_port);	//������IP��ָ���Ķ˿ںŰ���һ��,IP_ADDR_ANYΪ�󶨱������е�IP��ַ
			if(err == ERR_OK)		//�����
			{
				tcppcbconn = tcp_listen(tcppcbnew); 			//����tcppcb�������״̬
				tcp_accept(tcppcbconn,tcp_server_accept); 		//��ʼ��LWIP��tcp_accept�Ļص�����
				TCP_Server_SET_INITED_Flag;	//��ǳ�ʼ����
				return 0;
			}else return 2;
		}else return 1;
	}return 3;
}
 
 
extern void tcp_pcb_purge(struct tcp_pcb *pcb);	//�� tcp.c���� 
extern struct tcp_pcb *tcp_active_pcbs;			//�� tcp.c���� 
extern struct tcp_pcb *tcp_tw_pcbs;				//�� tcp.c����  
//ǿ��ɾ��TCP Server�����Ͽ�ʱ��time wait
void tcp_server_remove_timewait(void)
{
	struct tcp_pcb *pcb,*pcb2; 
	while(tcp_active_pcbs!=NULL)
	{
		lwip_periodic_handle();//������ѯ
		HAL_Delay(10);//�ȴ�tcp_active_pcbsΪ��
	}
	pcb=tcp_tw_pcbs;
	while(pcb!=NULL)//����еȴ�״̬��pcbs
	{
		tcp_pcb_purge(pcb); 
		tcp_tw_pcbs=pcb->next;
		pcb2=pcb;
		pcb=pcb->next;
		memp_free(MEMP_TCP_PCB,pcb2);	
	}
}


//�ر�tcp server���ӣ��û�����
//���ӣ�tcp_server_close(TCP_Server_PCB_test,TCP_Server_PCBCONN_test);
void tcp_server_close(struct tcp_pcb* tspcb,struct tcp_pcb* tspcbconn)
{
	tcp_server_connection_close(tspcb,0);
	tcp_server_connection_close(tspcbconn,0);
	tcp_server_remove_timewait(); 
	memset(tspcb,0,sizeof(struct tcp_pcb));
	memset(tspcbconn,0,sizeof(struct tcp_pcb)); 
	
	myfree(InrRAM,tcp_server_recvbuf);
	myfree(InrRAM,tcp_server_sendbuf);
	
	TCP_Server_Clear_INITED_Flag;	//��Ƿ���ʼ����
}

#endif

