#include "tcp_client.h" 



/*ʹ�ý��ܣ�

�������ӣ�
	//TCP Client ��ʼ��
	//lwip_inf.remoteip ΪԶ������Server��IP��lwip_inf.ipΪ���ؿͻ��˵�IP
	//��ʼ������ �� tcp_client_test(TCP_Client_PCB_test,100,TCP_CLIENT_PORT);
	//����0�ɹ�������ʧ��
	u8 tcp_client_test(struct tcp_pcb *tcppcb, u8 remoteip_3, u16 tcp_client_port)
��ѯ�Ƿ��пͻ��������ϣ�
	һֱѭ����� TCP_Client_IS_CONN_Flag ���Ƿ�Ϊ�棬������ʧ��������ϵͳ�����0
ע�⣺
	��������һ�����ϵ��ó�ʼ��API���ڵ��� �ر�����API ֮ǰֻ�ܵ���һ�Σ�
	��ʼ�����������Ϻ����ڼ�� TCP_Client_IS_CONN_Flag �꣬���ʧ����
	�ȵ���	tcp_client_close(TCP_Client_PCB_test,0);
	�ٵ���	tcp_client_init_test(TCP_Client_PCB_test,100,TCP_CLIENT_PORT);
�ر����ӣ�
	//�ر�tcp server����
	//���ӣ�tcp_client_close(TCP_Client_PCB_test,0);
	void tcp_client_close(struct tcp_pcb* tspcb,struct tcp_pcb* tspcbconn);
�������ݣ�
	��� TCP_Client_IS_RECV_Flag ���Ƿ�Ϊ�棬Ϊ�����ʾ�յ����ݣ�
	�ӽ��ջ����� tcp_client_recvbuf ȡ�����ݣ�
	Ȼ����� TCP_Client_Clear_RECV_Flag; �� ������ձ�־λ
�������ݣ�
	�ȸ� tcp_client_sendbuf ����Ҫ�������ݣ���Ҫ�� '\0'Ϊ��β��
		���磺sprintf_(tcp_client_sendbuf,"stm32_framework - STM32F407 TCP Client demo send data\r\n");
	Ȼ����� TCP_Client_SET_SEND_Flag; �� ���÷��ͱ�־λ��ϵͳ���Զ����� tcp_client_sendbuf ������

���ջ����� tcp_client_recvbuf �� ���ͻ����� tcp_client_sendbuf �Ŀռ��Ϊ TCP_CLIENT_RX_BUFSIZE �� TCP_CLIENT_TX_BUFSIZE 

*/


#if LWIP_TCP && (NO_SYS == 1)

//TCP Client�������ݻ�����
char* tcp_client_recvbuf;	
//TCP Client�������ݻ�����
char* tcp_client_sendbuf;			//��Ҫ�� '\0'Ϊ��β��

//TCP Client ����ȫ��״̬��Ǳ���
//bit7:0,û������Ҫ����;1,������Ҫ����
//bit6:0,û���յ�����;1,�յ�������
//bit5:0,û�������Ϸ�����;1,�����Ϸ�������
//bit4:0,û�г�ʼ�����߾����˷���ʼ��;1,��ʼ����
//bit3~0:����
u8 tcp_client_flag;


//tcp_client�ĳ�ʼ����־λ�����ڷ�ֹ����һ�����ϵ��ó�ʼ��������ϵͳ���ã��û�����
#define TCP_Client_SET_INITED_Flag		(tcp_client_flag|=0x10)
#define TCP_Client_Clear_INITED_Flag	(tcp_client_flag&=(~0x10))
#define TCP_Client_IS_INITED_Flag		(tcp_client_flag&0x10)	


struct tcp_pcb* TCP_Client_PCB_test;


//lwIP tcp_recv()�����Ļص����������յ����ݵĻص����� Called when data has been received.ϵͳ���Ĳ����û�����
err_t tcp_client_recv(void *arg,struct tcp_pcb *tpcb,struct pbuf *p,err_t err)
{ 
	u32 data_len=0;
	struct pbuf *q;
	struct tcp_client_struct *es;
	err_t ret_err; 
	LWIP_ASSERT("arg != NULL",arg != NULL);
	es=(struct tcp_client_struct *)arg; 
	if(p==NULL)//����ӷ��������յ��յ�����֡�͹ر�����
	{
		es->state=ES_TCPCLIENT_CLOSING;//��Ҫ�ر�TCP ������ 
 		es->p=p; 
		ret_err=ERR_OK;
	}else if(err!= ERR_OK)//�����յ�һ���ǿյ�����֡,����err!=ERR_OK
	{ 
		if(p)pbuf_free(p);//�ͷŽ���pbuf
		ret_err=err;
	}else if(es->state==ES_TCPCLIENT_CONNECTED)	//����������״̬ʱ
	{
		if(p!=NULL)//����������״̬���ҽ��յ������ݲ�Ϊ��ʱ
		{
			memset(tcp_client_recvbuf,0,TCP_CLIENT_RX_BUFSIZE);  //���ݽ��ջ���������
			for(q=p;q!=NULL;q=q->next)  //����������pbuf����
			{
				//�ж�Ҫ������TCP_CLIENT_RX_BUFSIZE�е������Ƿ����TCP_CLIENT_RX_BUFSIZE��ʣ��ռ䣬�������
				//�Ļ���ֻ����TCP_CLIENT_RX_BUFSIZE��ʣ�೤�ȵ����ݣ�����Ļ��Ϳ������е�����
				if(q->len > (TCP_CLIENT_RX_BUFSIZE-data_len)) memcpy(tcp_client_recvbuf+data_len,q->payload,(TCP_CLIENT_RX_BUFSIZE-data_len));//��������
				else memcpy(tcp_client_recvbuf+data_len,q->payload,q->len);
				data_len += q->len;  	
				if(data_len > TCP_CLIENT_RX_BUFSIZE) break; //����TCP�ͻ��˽�������,����	
			}
			
			tcp_client_flag|=1<<6;		//��ǽ��յ������ˣ�
 			
			tcp_recved(tpcb,p->tot_len);//���ڻ�ȡ��������,֪ͨLWIP���Ի�ȡ��������
			pbuf_free(p);  	//�ͷ��ڴ�
			ret_err=ERR_OK;
		}
	}else  //���յ����ݵ��������Ѿ��ر�,
	{ 
		tcp_recved(tpcb,p->tot_len);//���ڻ�ȡ��������,֪ͨLWIP���Ի�ȡ��������
		es->p=NULL;
		pbuf_free(p); //�ͷ��ڴ�
		ret_err=ERR_OK;
	}
	return ret_err;
} 
//lwIP tcp_err�����Ļص�������ϵͳ���Ĳ����û�����
void tcp_client_error(void *arg,err_t err)
{  
	//�������ǲ����κδ���
}

//�˺��������������ݣ�ϵͳ���Զ��ģ��� tcp_server_poll �������ã��û����õ���
void tcp_client_senddata(struct tcp_pcb *tpcb, struct tcp_client_struct * es)
{
	struct pbuf *ptr;
 	err_t wr_err=ERR_OK;
	while((wr_err==ERR_OK)&&es->p&&(es->p->len<=tcp_sndbuf(tpcb))) //��Ҫ���͵����ݼ��뵽���ͻ��������
	{
		ptr=es->p;
		wr_err=tcp_write(tpcb,ptr->payload,ptr->len,1);
		if(wr_err==ERR_OK)
		{  
			es->p=ptr->next;			//ָ����һ��pbuf
			if(es->p)pbuf_ref(es->p);	//pbuf��ref��һ
			pbuf_free(ptr);				//�ͷ�ptr 
		}else if(wr_err==ERR_MEM)es->p=ptr;
		tcp_output(tpcb);		//�����ͻ�������е������������ͳ�ȥ
	} 
}


//lwIP tcp_poll�Ļص�������ϵͳ���Ĳ����û�����
//���� tcp_client_flag ��־λ���Ϸ��ͱ�־�󣬻��ڴ˺������÷��ͺ������� tcp_client_sendbuf ������
//���жϵ�ǰ�����Ƿ�رգ�����ر������ tcp_client_connection_close ������������ʧ����־λ
err_t tcp_client_poll(void *arg, struct tcp_pcb *tpcb)
{
	err_t ret_err;
	struct tcp_client_struct *es; 
	es=(struct tcp_client_struct*)arg;
	if(es!=NULL)  //���Ӵ��ڿ��п��Է�������
	{
		if(tcp_client_flag&(1<<7))	//�ж��Ƿ�������Ҫ���� 
		{
			es->p=pbuf_alloc(PBUF_TRANSPORT, strlen((char*)tcp_client_sendbuf),PBUF_POOL);	//�����ڴ� 
			pbuf_take(es->p,(char*)tcp_client_sendbuf,strlen((char*)tcp_client_sendbuf));	//��tcp_client_sentbuf[]�е����ݿ�����es->p_tx��
			tcp_client_senddata(tpcb,es);//��tcp_client_sentbuf[]���渴�Ƹ�pbuf�����ݷ��ͳ�ȥ
			tcp_client_flag&=~(1<<7);	//������ݷ��ͱ�־��
			if(es->p)pbuf_free(es->p);	//�ͷ��ڴ�
		}else if(es->state==ES_TCPCLIENT_CLOSING)
		{ 
 			tcp_client_close(tpcb,es);//�ر�TCP����
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
err_t tcp_client_sent(void *arg, struct tcp_pcb *tpcb, u16_t len)
{
	struct tcp_client_struct *es;
	LWIP_UNUSED_ARG(len);
	es=(struct tcp_client_struct*)arg;
	if(es->p)tcp_client_senddata(tpcb,es);//��������
	return ERR_OK;
}


//lwIP TCP���ӽ�������ûص�������ע����ֻص�������ϵͳ���Ĳ����û�����
err_t tcp_client_connected(void *arg, struct tcp_pcb *tpcb, err_t err)
{
	struct tcp_client_struct *es=NULL;  
	if(err==ERR_OK)   
	{
		es=(struct tcp_client_struct*)mem_malloc(sizeof(struct tcp_client_struct));  //�����ڴ�
		if(es) //�ڴ�����ɹ�
		{
 			es->state=ES_TCPCLIENT_CONNECTED;//״̬Ϊ���ӳɹ�
			es->pcb=tpcb;  
			es->p=NULL; 
			tcp_arg(tpcb,es);        			//ʹ��es����tpcb��callback_arg
			tcp_recv(tpcb,tcp_client_recv);  	//��ʼ��LwIP��tcp_recv�ص�����
			tcp_err(tpcb,tcp_client_error); 	//��ʼ��tcp_err()�ص�����
			tcp_sent(tpcb,tcp_client_sent);		//��ʼ��LwIP��tcp_sent�ص�����
			tcp_poll(tpcb,tcp_client_poll,1); 	//��ʼ��LwIP��tcp_poll�ص�����
 			
			tcp_client_flag|=1<<5; 				//������ӵ��������ˣ�
			
			err=ERR_OK;
		}else
		{ 
			tcp_client_close(tpcb,es);//�ر�����
			err=ERR_MEM;	//�����ڴ�������
		}
	}else
	{
		tcp_client_close(tpcb,0);//�ر�����
	}
	return err;
}

//TCP Client ��ʼ��
//lwip_inf.remoteip ΪԶ������Server��IP��lwip_inf.ipΪ���ؿͻ��˵�IP
//��ʼ������ �� tcp_client_test(TCP_Client_PCB_test,100,TCP_CLIENT_PORT);
/*��������һ�����ϵ��ã��ڵ��� �ر����� ֮ǰֻ�ܵ���һ��
��ʼ�����������Ϻ����ڼ�� TCP_Client_IS_CONN_Flag �꣬���ʧ����
�ȵ���	tcp_client_close(TCP_Client_PCB_test,0);
�ٵ���	tcp_client_init_test(TCP_Client_PCB_test,100,TCP_CLIENT_PORT);*/
//����0�ɹ�������ʧ��
u8 tcp_client_init_test(struct tcp_pcb *tcppcb, u8 remoteip_3, u16 tcp_client_port)
{
	struct ip4_addr rmtipaddr;  	//Զ��ip��ַ
	
	if(TCP_Client_IS_INITED_Flag == 0)	//��ѯ�Ƿ��ʼ���������ڷ�ֹ����һ�����ϵ��ó�ʼ������
	{
		tcp_client_recvbuf = (char*)mymalloc(InrRAM,TCP_CLIENT_RX_BUFSIZE);
		tcp_client_sendbuf = (char*)mymalloc(InrRAM,TCP_CLIENT_TX_BUFSIZE);
		if((tcp_client_recvbuf == NULL)||(tcp_client_sendbuf == NULL))return 4;
		
		sprintf_(tcp_client_sendbuf,"stm32_framework - STM32F407 TCP Client demo send data\r\n");
		
		//ǰ����IP���ֺ�DHCP�õ���IPһ��
		lwip_inf.remoteip[0] = lwip_inf.ip[0];
		lwip_inf.remoteip[1] = lwip_inf.ip[1];
		lwip_inf.remoteip[2] = lwip_inf.ip[2];
		lwip_inf.remoteip[3] = remoteip_3;
		
		tcppcb = tcp_new();	//����һ���µ�pcb
		if(tcppcb)			//�����ɹ�
		{
			IP4_ADDR(&rmtipaddr,lwip_inf.remoteip[0],lwip_inf.remoteip[1],lwip_inf.remoteip[2],lwip_inf.remoteip[3]); 
			tcp_connect(tcppcb,&rmtipaddr,tcp_client_port,tcp_client_connected);  //���ӵ�Ŀ�ĵ�ַ��ָ���˿���,�����ӳɹ���ص�tcp_client_connected()����
			TCP_Client_SET_INITED_Flag;	//��ǳ�ʼ����
			return 0;
		}else return 2;
	
	}else return 1;
}

//�ر��������������
//���ӣ�tcp_client_close(TCP_Client_PCB_test,0);
void tcp_client_close(struct tcp_pcb *tpcb, struct tcp_client_struct * es)
{
	//�Ƴ��ص�
	tcp_abort(tpcb);//��ֹ����,ɾ��pcb���ƿ�
	tcp_arg(tpcb,NULL);  
	tcp_recv(tpcb,NULL);
	tcp_sent(tpcb,NULL);
	tcp_err(tpcb,NULL);
	tcp_poll(tpcb,NULL,0);  
	if(es)mem_free(es); 
	
	myfree(InrRAM,tcp_client_recvbuf);	
	myfree(InrRAM,tcp_client_sendbuf);
	
	tcp_client_flag&=~(1<<5);		//������ӶϿ���
	TCP_Client_Clear_INITED_Flag;	//��Ƿ���ʼ����
}

#endif


