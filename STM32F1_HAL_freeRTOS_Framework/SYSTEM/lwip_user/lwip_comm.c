#include "lwip_comm.h" 
#include "netif/etharp.h"
#include "lwip/dhcp.h"
#include "lwip/init.h"

#include "lwip/timeouts.h"
#include "lwip/mem.h"

//#include "lwip/timers.h"		//�⼸����LWIP 1.4�汾���õġ���
//#include "lwip/tcp_impl.h"
//#include "lwip/ip_frag.h"
//#include "lwip/tcpip.h" 
//#include "lwip/timers.h"
#include "lwip/priv/tcp_priv.h"

#include "NetCard.h"


//�û��Զ�������������
#define IFNAME0 'e'
#define IFNAME1 'n'

//lwip��Ϣ�ṹ�� 
__lwip_dev lwip_inf = 
{
	/*�û��Զ���
		Զ��IP��ַ��IP��ַ���������룬���� ��MAC��ַ��NetCard.c�ļ����涨�壩
	*/
	
	//Ĭ��Զ��IPΪ:192.168.1.100
	.remoteip[0] = 192,
	.remoteip[1] = 168,
	.remoteip[2] = 1,
	.remoteip[3] = 100,
	
	//Ĭ�ϱ���IPΪ:192.168.1.30
	.ip[0] = 192,
	.ip[1] = 168,
	.ip[2] = 1,
	.ip[3] = 30,
	
	//Ĭ����������:255.255.255.0
	.netmask[0] = 255,
	.netmask[1] = 255,
	.netmask[2] = 255,
	.netmask[3] = 0,
	
	//Ĭ������:192.168.1.1
	.gateway[0] = 192,
	.gateway[1] = 168,
	.gateway[2] = 1,
	.gateway[3] = 1,
	
	//DHCP״̬
	.dhcpstatus = 0  //DHCP��δ��ʼ��
};


/*_____�û��޸ĵײ��շ�����________*/

//���ڷ������ݰ�����ײ㺯��(lwipͨ��netif->linkoutputָ��ú���)
static err_t low_level_output(struct netif *netif, struct pbuf *p)
{
	//Ĭ��ֻ��һ������ӿ�ʵ�壬�������ѡ�����ĸ���������
	NetCard_SendPacket(p);
	return ERR_OK;
}  
///���ڽ������ݰ�����ײ㺯��
static struct pbuf * low_level_input(struct netif *netif)
{
	//Ĭ��ֻ��һ������ӿ�ʵ�壬�������ѡ�����ĸ���������
	struct pbuf *p;
	p = NetCard_Receive_Packet();
	return p;
}

/*____________________________________���������˵������Ķ����ö��ˣ�____________________________________*/


//�����������ݣ����ѭ�����ã������յ����ݰ���ͷ��͵�ethernet_input���䴦����ٷ���etharp_input��arp�㣩
//netif:�����ṹ��ָ��
//����ֵ:ERR_OK,��������
//       ERR_MEM,����ʧ��
err_t ethernetif_input(struct netif *netif)
{
	err_t err;
	struct pbuf *p;
	p=low_level_input(netif);   //����low_level_input������������
	if(p==NULL) return ERR_MEM;
	err=netif->input(p, netif); //����netif�ṹ���е�input�ֶ�(һ������)���������ݰ�
	if(err!=ERR_OK)
	{
		LWIP_DEBUGF(NETIF_DEBUG,("ethernetif_input: IP input error\n"));
		pbuf_free(p);
		p = NULL;
	} 
	return err;
}

err_t ethernetif_init(struct netif *netif)
{
	LWIP_ASSERT("netif!=NULL",(netif!=NULL));
#if LWIP_NETIF_HOSTNAME			//LWIP_NETIF_HOSTNAME 
	netif->hostname="lwip";  	//��ʼ������
#endif 
	netif->name[0] = IFNAME0; 	//��ʼ������netif��name�ֶ�
	netif->name[1] = IFNAME1;
	
	//MAC��ַ���ã������ֽڹ̶�Ϊ:2.0.0,�����ֽ���STM32ΨһID
	lwip_inf.mac[0] = NetCardcfg.mac_addr[0];
	lwip_inf.mac[1] = NetCardcfg.mac_addr[0];
	lwip_inf.mac[2] = NetCardcfg.mac_addr[0];
	lwip_inf.mac[3] = NetCardcfg.mac_addr[0];
	lwip_inf.mac[4] = NetCardcfg.mac_addr[0];
	lwip_inf.mac[5] = NetCardcfg.mac_addr[0];
	
	netif->output = etharp_output;//IP�㷢�����ݰ�����
	
	netif->linkoutput = low_level_output;//ARPģ�鷢�����ݰ�����
	
	netif->hwaddr_len = ETHARP_HWADDR_LEN; //����MAC��ַ����,Ϊ6���ֽ�
	
	//��ʼ��MAC��ַ,����ʲô��ַ���û��Լ�����,���ǲ����������������豸MAC��ַ�ظ�
	netif->hwaddr[0]=lwip_inf.mac[0]; netif->hwaddr[1]=lwip_inf.mac[1]; netif->hwaddr[2]=lwip_inf.mac[2];
	netif->hwaddr[3]=lwip_inf.mac[3]; netif->hwaddr[4]=lwip_inf.mac[4]; netif->hwaddr[5]=lwip_inf.mac[5];
	
	netif->mtu=1500; //��������䵥Ԫ,����������㲥��ARP����
	
	netif->flags = NETIF_FLAG_BROADCAST|NETIF_FLAG_ETHARP|NETIF_FLAG_LINK_UP;
	
	return ERR_OK;
}

struct netif lwip_handle;					//����һ��ȫ�ֵ�����ӿھ��

//LWIP��ʼ��(LWIP������ʱ��ʹ��)
//����ֵ:0,�ɹ�
//      1,�ڴ����
//      2,DM9000��ʼ��ʧ��
//      3,�������ʧ��.
u8 lwip_comm_init(void)
{
	//Ϊlwip��memp��mem�����ڴ棬Ĭ����lwip�Լ�����������������
	
	if(NetCard_Init())return 2;			//��ʼ������
	
	lwip_init();						//��ʼ��LWIP�ں�

	#if LWIP_DHCP		//ʹ�ö�̬IP
		ip4_addr_t ipaddr;  			//ip��ַ
		ip4_addr_t netmask; 			//��������
		ip4_addr_t gw;      			//Ĭ������ 
		
		ipaddr.addr = 0;
		netmask.addr = 0;
		gw.addr = 0;
	#else				//ʹ�þ�̬IP
		IP4_ADDR(&ipaddr,lwip_inf.ip[0],lwip_inf.ip[1],lwip_inf.ip[2],lwip_inf.ip[3]);
		IP4_ADDR(&netmask,lwip_inf.netmask[0],lwip_inf.netmask[1] ,lwip_inf.netmask[2],lwip_inf.netmask[3]);
		IP4_ADDR(&gw,lwip_inf.gateway[0],lwip_inf.gateway[1],lwip_inf.gateway[2],lwip_inf.gateway[3]);
	#endif
	
	struct netif *Netif_Init_Flag;		//����netif_add()����ʱ�ķ���ֵ,�����ж������ʼ���Ƿ�ɹ�
	Netif_Init_Flag=netif_add(&lwip_handle,&ipaddr,&netmask,&gw,NULL,ethernetif_init,&ethernet_input);//�������б������һ������
	
	
	
	#if LWIP_DHCP			//���ʹ��DHCP�Ļ��������Զ���ȡ����IP���������������
		dhcp_start(&lwip_handle);	//����DHCP����
		lwip_inf.dhcpstatus = 0;	//��
	#endif
	
	if(Netif_Init_Flag==NULL)return 3;//�������ʧ�� 
	else//������ӳɹ���,����netifΪĬ��ֵ,���Ҵ�netif����
	{
		netif_set_default(&lwip_handle); //����netifΪĬ������
		netif_set_up(&lwip_handle);		//��netif����
	}
	return 0;
}

//���ʹ����DHCP
#if LWIP_DHCP
//DHCP��������
void lwip_dhcp_process_handle(void)
{
	u32 ip=0,netmask=0,gw=0;
	switch(lwip_inf.dhcpstatus)
	{
		case 0: 	//����DHCP
			dhcp_start(&lwip_handle);
			lwip_inf.dhcpstatus = 1;		//�ȴ�ͨ��DHCP��ȡ���ĵ�ַ
			//printf("���ڲ���DHCP������,���Ե�...........\r\n");  
			break;
		case 1:		//�ȴ���ȡ��IP��ַ
		{
			static u8 try_times = 0;
			//DHCP��ȡ��IP��ַ���ȸ�lwip_handle��������Ȼ������ٸ�lwip_inf
			ip=lwip_handle.ip_addr.addr;		//��ȡ��IP��ַ
			netmask=lwip_handle.netmask.addr;	//��ȡ��������
			gw=lwip_handle.gw.addr;				//��ȡĬ������
			
			if(ip!=0)			//��ȷ��ȡ��IP��ַ��ʱ��
			{
				lwip_inf.dhcpstatus = 2;		//DHCP�ɹ�
				//printf("����en��MAC��ַΪ:................%d.%d.%d.%d.%d.%d\r\n",lwip_inf.mac[0],lwip_inf.mac[1],lwip_inf.mac[2],lwip_inf.mac[3],lwip_inf.mac[4],lwip_inf.mac[5]);
				
				//������ͨ��DHCP��ȡ����IP��ַ
				lwip_inf.ip[3]=(uint8_t)(ip>>24); 
				lwip_inf.ip[2]=(uint8_t)(ip>>16);
				lwip_inf.ip[1]=(uint8_t)(ip>>8);
				lwip_inf.ip[0]=(uint8_t)(ip);
				//printf("ͨ��DHCP��ȡ��IP��ַ..............%d.%d.%d.%d\r\n",lwip_inf.ip[0],lwip_inf.ip[1],lwip_inf.ip[2],lwip_inf.ip[3]);
				
				//����ͨ��DHCP��ȡ�������������ַ
				lwip_inf.netmask[3]=(uint8_t)(netmask>>24);
				lwip_inf.netmask[2]=(uint8_t)(netmask>>16);
				lwip_inf.netmask[1]=(uint8_t)(netmask>>8);
				lwip_inf.netmask[0]=(uint8_t)(netmask);
				//printf("ͨ��DHCP��ȡ����������............%d.%d.%d.%d\r\n",lwip_inf.netmask[0],lwip_inf.netmask[1],lwip_inf.netmask[2],lwip_inf.netmask[3]);
				
				//������ͨ��DHCP��ȡ����Ĭ������
				lwip_inf.gateway[3]=(uint8_t)(gw>>24);
				lwip_inf.gateway[2]=(uint8_t)(gw>>16);
				lwip_inf.gateway[1]=(uint8_t)(gw>>8);
				lwip_inf.gateway[0]=(uint8_t)(gw);
				//printf("ͨ��DHCP��ȡ����Ĭ������..........%d.%d.%d.%d\r\n",lwip_inf.gateway[0],lwip_inf.gateway[1],lwip_inf.gateway[2],lwip_inf.gateway[3]);
				
				try_times = 0;
			}
			try_times++;
			if(try_times > LWIP_MAX_DHCP_TRIES) //ͨ��DHCP�����ȡIP��ַʧ��,�ҳ�������Դ���
			{
				try_times = 0;
				lwip_inf.dhcpstatus=0XFF;//DHCP��ʱʧ��.
				//ʹ�þ�̬IP��ַ
				IP4_ADDR(&(lwip_handle.ip_addr),lwip_inf.ip[0],lwip_inf.ip[1],lwip_inf.ip[2],lwip_inf.ip[3]);
				IP4_ADDR(&(lwip_handle.netmask),lwip_inf.netmask[0],lwip_inf.netmask[1],lwip_inf.netmask[2],lwip_inf.netmask[3]);
				IP4_ADDR(&(lwip_handle.gw),lwip_inf.gateway[0],lwip_inf.gateway[1],lwip_inf.gateway[2],lwip_inf.gateway[3]);
//				printf("DHCP����ʱ,ʹ�þ�̬IP��ַ!\r\n");
//				printf("����en��MAC��ַΪ:................%d.%d.%d.%d.%d.%d\r\n",lwip_inf.mac[0],lwip_inf.mac[1],lwip_inf.mac[2],lwip_inf.mac[3],lwip_inf.mac[4],lwip_inf.mac[5]);
//				printf("��̬IP��ַ........................%d.%d.%d.%d\r\n",lwip_inf.ip[0],lwip_inf.ip[1],lwip_inf.ip[2],lwip_inf.ip[3]);
//				printf("��������..........................%d.%d.%d.%d\r\n",lwip_inf.netmask[0],lwip_inf.netmask[1],lwip_inf.netmask[2],lwip_inf.netmask[3]);
//				printf("Ĭ������..........................%d.%d.%d.%d\r\n",lwip_inf.gateway[0],lwip_inf.gateway[1],lwip_inf.gateway[2],lwip_inf.gateway[3]);
			}
		}
		break;
		default : break;
	}
}
#endif 



u32 lwip_1ms_Tick;							//lwip����ʱ�����������λ:ms
//lwip�����ճ����񣬱���ŵ�10msѭ����
void lwip_periodic_handle(void)
{
	lwip_1ms_Tick +=10;
	
	sys_check_timeouts(); /*check timeouts,handle all timers for all protocols in the stack*/
	
	#if SYS_Test_LWIP	//�����ʹ��TCP/UDPͨѶ�Ļ�
		if(lwip_1ms_Tick % 250 == 0)
		{
			#if LWIP_TCP
				//ÿ250ms����һ��tcp_tmr()����
				tcp_tmr();
			#endif
		}
		
		if(lwip_1ms_Tick % 5000 == 0)
		{
			//ARPÿ5s�����Ե���һ��
			etharp_tmr();
		}
	#endif
	
	#if LWIP_DHCP //���ʹ��DHCP�Ļ�
		if(lwip_1ms_Tick % 500 == 0)
		{
			//ÿ500ms����һ��dhcp_fine_tmr()
			dhcp_fine_tmr();
			if ((lwip_inf.dhcpstatus != 2)&&(lwip_inf.dhcpstatus != 0XFF))
			{ 
				lwip_dhcp_process_handle();  //DHCP����
			}
		}
	
		if(lwip_1ms_Tick % (60*1000) == 0)
		{
			//ÿ60sִ��һ��DHCP�ֲڴ���
			dhcp_coarse_tmr();
		}
	#endif
}

//ѭ��ɨ�������Ƿ������ݷ���������ŵ����ӳٴ�ѭ����
void lwip_pkt_handle(void)
{
	//�����绺�����ж�ȡ���յ������ݰ������䷢�͸�LWIP���� 
	ethernetif_input(&lwip_handle);
}



























