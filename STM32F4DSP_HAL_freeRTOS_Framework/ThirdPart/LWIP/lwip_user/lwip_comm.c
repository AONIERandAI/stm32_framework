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
#include "malloc.h"

ETH_HandleTypeDef ETH_Handler;      //��̫�����
__align(4) ETH_DMADescTypeDef *DMARxDscrTab;	//��̫��DMA�������������ݽṹ��ָ��
__align(4) ETH_DMADescTypeDef *DMATxDscrTab;	//��̫��DMA�������������ݽṹ��ָ�� 
__align(4) uint8_t *Rx_Buff; 					//��̫���ײ���������buffersָ�� 
__align(4) uint8_t *Tx_Buff; 					//��̫���ײ���������buffersָ��



extern u8_t *ram_heap;					//LWIP�����ڴ��ram_heap����mem.c���涨�壬�ڴ��mem_pool��opt.h���汻����Ϊ���ڴ��ram_heap��ȡ
/*LWIPԴ�ļ��޸ļ�¼��
	������mem.c�����
		349�е�
			struct mem�ᵽ��mem.h����
		371�е�
			��������ᵽ��mem.h����
	����lwip��mem���ʽ�����https://blog.csdn.net/ZCShouCSDN/article/details/80282907
*/

#define LWIP_MAX_DHCP_TRIES		4   //DHCP������������Դ���

//�û��Զ�������������
#define IFNAME0 'e'
#define IFNAME1 '0'

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

//���ڷ������ݰ�����ײ㺯��(lwipͨ��netif->linkoutputָ��ú���)
//netif:�����ṹ��ָ��
//p:pbuf���ݽṹ��ָ��
//����ֵ:ERR_OK,��������
//       ERR_MEM,����ʧ��
static err_t low_level_output(struct netif *netif, struct pbuf *p)
{
    err_t errval;
    struct pbuf *q;
    uint8_t *buffer=(uint8_t *)(ETH_Handler.TxDesc->Buffer1Addr);
    __IO ETH_DMADescTypeDef *DmaTxDesc;
    uint32_t framelength = 0;
    uint32_t bufferoffset = 0;
    uint32_t byteslefttocopy = 0;
    uint32_t payloadoffset = 0;

    DmaTxDesc = ETH_Handler.TxDesc;
    bufferoffset = 0;

    //��pbuf�п���Ҫ���͵�����
    for(q=p;q!=NULL;q=q->next)
    {
        //�жϴ˷����������Ƿ���Ч�����жϴ˷����������Ƿ����̫��DMA����
        if((DmaTxDesc->Status&ETH_DMATXDESC_OWN)!=(uint32_t)RESET)
        {
            errval=ERR_USE;
            goto error;             //������������Ч��������
        }
        byteslefttocopy=q->len;     //Ҫ���͵����ݳ���
        payloadoffset=0;
   
        //��pbuf��Ҫ���͵�����д�뵽��̫�������������У���ʱ������Ҫ���͵����ݿ��ܴ���һ����̫��
        //��������Tx Buffer�����������Ҫ�ֶ�ν����ݿ��������������������
        while((byteslefttocopy+bufferoffset)>ETH_TX_BUF_SIZE )
        {
            //�����ݿ�������̫��������������Tx Buffer��
            mymemcpy((uint8_t*)((uint8_t*)buffer+bufferoffset),(uint8_t*)((uint8_t*)q->payload+payloadoffset),(ETH_TX_BUF_SIZE-bufferoffset));
            //DmaTxDscָ����һ������������
            DmaTxDesc=(ETH_DMADescTypeDef *)(DmaTxDesc->Buffer2NextDescAddr);
            //����µķ����������Ƿ���Ч
            if((DmaTxDesc->Status&ETH_DMATXDESC_OWN)!=(uint32_t)RESET)
            {
                errval = ERR_USE;
                goto error;     //������������Ч��������
            }
            buffer=(uint8_t *)(DmaTxDesc->Buffer1Addr);   //����buffer��ַ��ָ���µķ�����������Tx Buffer
            byteslefttocopy=byteslefttocopy-(ETH_TX_BUF_SIZE-bufferoffset);
            payloadoffset=payloadoffset+(ETH_TX_BUF_SIZE-bufferoffset);
            framelength=framelength+(ETH_TX_BUF_SIZE-bufferoffset);
            bufferoffset=0;
        }
        //����ʣ�������
        mymemcpy( (uint8_t*)((uint8_t*)buffer+bufferoffset),(uint8_t*)((uint8_t*)q->payload+payloadoffset),byteslefttocopy );
        bufferoffset=bufferoffset+byteslefttocopy;
        framelength=framelength+byteslefttocopy;
    }
    //������Ҫ���͵����ݶ��Ž�������������Tx Buffer�Ժ�Ϳɷ��ʹ�֡��
    HAL_ETH_TransmitFrame(&ETH_Handler,framelength);
    errval = ERR_OK;
error:    
    //���ͻ������������磬һ�����ͻ�������������TxDMA��������״̬
    if((ETH_Handler.Instance->DMASR&ETH_DMASR_TUS)!=(uint32_t)RESET)
    {
        //��������־
        ETH_Handler.Instance->DMASR = ETH_DMASR_TUS;
        //������֡�г�����������ʱ��TxDMA�������ʱ����Ҫ��DMATPDR�Ĵ���
        //���д��һ��ֵ�����份�ѣ��˴�����д0
        ETH_Handler.Instance->DMATPDR=0;
    }
    return errval;
}  
///���ڽ������ݰ�����ײ㺯��
//neitif:�����ṹ��ָ��
//����ֵ:pbuf���ݽṹ��ָ��
static struct pbuf * low_level_input(struct netif *netif)
{  
	struct pbuf *p = NULL;
    struct pbuf *q;
    uint16_t len;
    uint8_t *buffer;
    __IO ETH_DMADescTypeDef *dmarxdesc;
    uint32_t bufferoffset=0;
    uint32_t payloadoffset=0;
    uint32_t byteslefttocopy=0;
    uint32_t i=0;
  
    if(HAL_ETH_GetReceivedFrame(&ETH_Handler)!=HAL_OK)  //�ж��Ƿ���յ�����
    return NULL;
    
    len=ETH_Handler.RxFrameInfos.length;                //��ȡ���յ�����̫��֡����
    buffer=(uint8_t *)ETH_Handler.RxFrameInfos.buffer;  //��ȡ���յ�����̫��֡������buffer
  
    if(len>0) p=pbuf_alloc(PBUF_RAW,len,PBUF_POOL);     //����pbuf
    if(p!=NULL)                                        //pbuf����ɹ�
    {
        dmarxdesc=ETH_Handler.RxFrameInfos.FSRxDesc;    //��ȡ���������������еĵ�һ��������
        bufferoffset = 0;
        for(q=p;q!=NULL;q=q->next)                      
        {
            byteslefttocopy=q->len;                  
            payloadoffset=0;
            //��������������Rx Buffer�����ݿ�����pbuf��
            while((byteslefttocopy+bufferoffset)>ETH_RX_BUF_SIZE )
            {
                //�����ݿ�����pbuf��
                mymemcpy((uint8_t*)((uint8_t*)q->payload+payloadoffset),(uint8_t*)((uint8_t*)buffer+bufferoffset),(ETH_RX_BUF_SIZE-bufferoffset));
                 //dmarxdesc����һ������������
                dmarxdesc=(ETH_DMADescTypeDef *)(dmarxdesc->Buffer2NextDescAddr);
                //����buffer��ַ��ָ���µĽ�����������Rx Buffer
                buffer=(uint8_t *)(dmarxdesc->Buffer1Addr);
 
                byteslefttocopy=byteslefttocopy-(ETH_RX_BUF_SIZE-bufferoffset);
                payloadoffset=payloadoffset+(ETH_RX_BUF_SIZE-bufferoffset);
                bufferoffset=0;
            }
            //����ʣ�������
            mymemcpy((uint8_t*)((uint8_t*)q->payload+payloadoffset),(uint8_t*)((uint8_t*)buffer+bufferoffset),byteslefttocopy);
            bufferoffset=bufferoffset+byteslefttocopy;
        }
    }    
    //�ͷ�DMA������
    dmarxdesc=ETH_Handler.RxFrameInfos.FSRxDesc;
    for(i=0;i<ETH_Handler.RxFrameInfos.SegCount; i++)
    {  
        dmarxdesc->Status|=ETH_DMARXDESC_OWN;       //�����������DMA����
        dmarxdesc=(ETH_DMADescTypeDef *)(dmarxdesc->Buffer2NextDescAddr);
    }
    ETH_Handler.RxFrameInfos.SegCount =0;           //����μ�����
    if((ETH_Handler.Instance->DMASR&ETH_DMASR_RBUS)!=(uint32_t)RESET)  //���ջ�����������
    {
        //������ջ����������ñ�־
        ETH_Handler.Instance->DMASR = ETH_DMASR_RBUS;
        //�����ջ����������õ�ʱ��RxDMA���ȥ����״̬��ͨ����DMARPDRд������һ��ֵ������Rx DMA
        ETH_Handler.Instance->DMARPDR=0;
    }
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
	
	#if LWIP_NETIF_HOSTNAME					//LWIP_NETIF_HOSTNAME 
		netif->hostname="lwip";  			//��ʼ������
	#endif 
	
	netif->name[0] = IFNAME0; 				//��ʼ������netif��name�ֶ�
	netif->name[1] = IFNAME1;
	
	netif->hwaddr_len = ETHARP_HWADDR_LEN; //����MAC��ַ����,Ϊ6���ֽ�
	
	netif->flags = NETIF_FLAG_BROADCAST|NETIF_FLAG_ETHARP|NETIF_FLAG_LINK_UP;
	
											//��lwip_handle��ʼ��MAC��ַ
	netif->hwaddr[0]=lwip_inf.mac[0]; netif->hwaddr[1]=lwip_inf.mac[1]; netif->hwaddr[2]=lwip_inf.mac[2];
	netif->hwaddr[3]=lwip_inf.mac[3]; netif->hwaddr[4]=lwip_inf.mac[4]; netif->hwaddr[5]=lwip_inf.mac[5];
	
	netif->mtu=1500; 						//��������䵥Ԫ,����������㲥��ARP����
	
	netif->output = etharp_output;			//IP�㷢�����ݰ�����
	
	netif->linkoutput = low_level_output;	//ARPģ�鷢�����ݰ�����
	
	HAL_ETH_DMATxDescListInit(&ETH_Handler,DMATxDscrTab,Tx_Buff,ETH_TXBUFNB);//��ʼ������������
	HAL_ETH_DMARxDescListInit(&ETH_Handler,DMARxDscrTab,Rx_Buff,ETH_RXBUFNB);//��ʼ������������
	HAL_ETH_Start(&ETH_Handler); 			//����MAC��DMA
	
	return ERR_OK;
}



//lwip���ڴ��ram_heap�ڴ��ͷ�
void lwip_comm_mem_free(void)
{ 	
	myfree(InrRAM,ram_heap);
}

//lwip���ڴ��ram_heap�ڴ�����
//����ֵ:0,�ɹ�;
//    ����,ʧ��
u8 lwip_comm_mem_malloc(void)
{
	u32 ram_heap_size; 
	
	ram_heap_size = MEM_SIZE_ALIGNED + (2 * SIZEOF_STRUCT_MEM);
	ram_heap = mymalloc(InrRAM,ram_heap_size);	//Ϊram_heap�����ڴ� 
	
	if(!(u32)&ram_heap)//������ʧ�ܵ�
	{
		lwip_comm_mem_free();
		return 1;
	}
	return 0;	
}

//�ͷ�ETH �ײ�����������ڴ�
void ETH_Mem_Free(void)
{ 
	myfree(InrRAM,DMARxDscrTab);//�ͷ��ڴ�
	myfree(InrRAM,DMATxDscrTab);//�ͷ��ڴ�
	myfree(InrRAM,Rx_Buff);		//�ͷ��ڴ�
	myfree(InrRAM,Tx_Buff);		//�ͷ��ڴ�  
}

//ΪETH�ײ����������ڴ�
//����ֵ:0,����
//    ����,ʧ��
u8 ETH_Mem_Malloc(void)
{ 
	DMARxDscrTab=mymalloc(InrRAM,ETH_RXBUFNB*sizeof(ETH_DMADescTypeDef));//�����ڴ�
	DMATxDscrTab=mymalloc(InrRAM,ETH_TXBUFNB*sizeof(ETH_DMADescTypeDef));//�����ڴ�  
	Rx_Buff=mymalloc(InrRAM,ETH_RX_BUF_SIZE*ETH_RXBUFNB);	//�����ڴ�
	Tx_Buff=mymalloc(InrRAM,ETH_TX_BUF_SIZE*ETH_TXBUFNB);	//�����ڴ�
	if(!(u32)&DMARxDscrTab||!(u32)&DMATxDscrTab||!(u32)&Rx_Buff||!(u32)&Tx_Buff)
	{
		ETH_Mem_Free();
		return 1;	//����ʧ��
	}	
	return 0;		//����ɹ�
}


struct netif lwip_handle;					//����һ��ȫ�ֵ�����ӿھ��
//LWIP��ʼ��(LWIP������ʱ��ʹ��)
//����ֵ:0,�ɹ�
//      1,�ڴ����
//      2,������ʼ��ʧ��
//      3,�������ʧ��
//�������� lwip_comm_init(&lwip_handle);
u8 lwip_comm_init(struct netif *netif)
{
	//Ϊlwip��memp��mem�����ڴ棬Ĭ����lwip�Լ�����������������
	
	//TODO��ETH���ڴ��������ͷ������ܲ��ܻ���CCM�������ڲ�SRAM��ʡ��
	if(ETH_Mem_Malloc())return 1;		//�ڴ�����ʧ��
	if(lwip_comm_mem_malloc())return 1;	//�ڴ�����ʧ��
	
	
	//��һ��MAC��Ϣ��lwip_inf������lwip_inf����Ϣȫ��
	//MAC��ַ��Ϣ���ã������ֽڹ̶�Ϊ:2.0.0,�����ֽ���STM32ΨһID
	u32 sn0 = *(vu32*)(0x1FFF7A10);		//��ȡSTM32��ΨһID��ǰ24λ��ΪMAC��ַ�����ֽ�
	lwip_inf.mac[0]=2;//�����ֽ�(IEEE��֮Ϊ��֯ΨһID,OUI)��ַ�̶�Ϊ:2.0.0
	lwip_inf.mac[1]=0;
	lwip_inf.mac[2]=0;
	lwip_inf.mac[3]=(sn0>>16)&0XFF;//�����ֽ���STM32��ΨһID
	lwip_inf.mac[4]=(sn0>>8)&0XFFF;
	lwip_inf.mac[5]=sn0&0XFF; 
	
	
	u8 retry = 0;
    while(1)		        //��ʼ��NetCard_PHY,���ʧ�ܵĻ�������5��
    {
		NetCard_PHY_RST=0;					//Ӳ����λNetCard_PHY
		HAL_Delay(50);	
		NetCard_PHY_RST=1;				 	//��λ���� 
		
		u8 macaddress[6];
		macaddress[0]=lwip_inf.mac[0];macaddress[1]=lwip_inf.mac[1];macaddress[2]=lwip_inf.mac[2];
		macaddress[3]=lwip_inf.mac[3];macaddress[4]=lwip_inf.mac[4];macaddress[5]=lwip_inf.mac[5];
		
		ETH_Handler.Instance=ETH;
		ETH_Handler.Init.AutoNegotiation=ETH_AUTONEGOTIATION_ENABLE;//ʹ����Э��ģʽ 
		ETH_Handler.Init.Speed=ETH_SPEED_100M;						//�ٶ�100M,�����������Э��ģʽ�������þ���Ч
		ETH_Handler.Init.DuplexMode=ETH_MODE_FULLDUPLEX;			//ȫ˫��ģʽ�������������Э��ģʽ�������þ���Ч
		ETH_Handler.Init.PhyAddress=NetCard_PHY_ADDRESS;			//NetCard_PHY��ַ  
		ETH_Handler.Init.MACAddr=macaddress;            			//MAC��ַ  
		ETH_Handler.Init.RxMode=ETH_RXINTERRUPT_MODE;   			//�жϽ���ģʽ 
		ETH_Handler.Init.ChecksumMode=ETH_CHECKSUM_BY_HARDWARE;		//Ӳ��֡У��  
		ETH_Handler.Init.MediaInterface=ETH_MEDIA_INTERFACE_RMII;	//RMII�ӿ�  
		if(HAL_ETH_Init(&ETH_Handler)==HAL_OK)
		{
			break;   //�ɹ�
		}
        
		retry++;
        if(retry>5) {retry=0;return 2;} //��ʼ��ʧ��
    }
	
	lwip_init();			//��ʼ��LWIP�ں�

	#if LWIP_DHCP			//ʹ�ö�̬IP
		ip4_addr_t ipaddr;  //ip��ַ
		ip4_addr_t netmask; //��������
		ip4_addr_t gw;      //Ĭ������ 
		
		ipaddr.addr = 0;
		netmask.addr = 0;
		gw.addr = 0;
	#else								//ʹ�þ�̬IP
		IP4_ADDR(&ipaddr,lwip_inf.ip[0],lwip_inf.ip[1],lwip_inf.ip[2],lwip_inf.ip[3]);
		IP4_ADDR(&netmask,lwip_inf.netmask[0],lwip_inf.netmask[1] ,lwip_inf.netmask[2],lwip_inf.netmask[3]);
		IP4_ADDR(&gw,lwip_inf.gateway[0],lwip_inf.gateway[1],lwip_inf.gateway[2],lwip_inf.gateway[3]);
	#endif
	
	struct netif *Netif_Init_Flag;		//����netif_add()����ʱ�ķ���ֵ,�����ж������ʼ���Ƿ�ɹ�
	Netif_Init_Flag = netif_add(netif,&ipaddr,&netmask,&gw,NULL,&ethernetif_init,&ethernet_input);//�������б������һ������
	
	if(Netif_Init_Flag==NULL)return 3;	//�������ʧ�� 
	
	//������ӳɹ���,����netifΪĬ��ֵ,���Ҵ�netif����
	netif_set_default(netif); 	//����netifΪĬ������
	netif_set_link_up(netif); 	//�򿪽ӿ����ӣ����ܽӿ��Ƿ��Ѿ����ϣ�����һ�¶�DHCP���кô�
	netif_set_up(netif);		//��netif����
	
	netif_set_remove_callback(netif,lwip_comm_destroy); //�������ߵ��ߺ����lwip_comm_destroy�رմ˴�LWIP����
	
	#if LWIP_DHCP				//���ʹ��DHCP�Ļ��������Զ���ȡ����IP���������������
		dhcp_start(netif);		//����DHCP����
		lwip_inf.dhcpstatus = 0;//��
	#endif
	
	return 0;
}

//�ر�LWIP,���ͷ��ڴ�
//�˳�LWIPʱʹ��
//����ʱ���Զ����ã����ߵ������� lwip_comm_destroy(&lwip_handle);
void lwip_comm_destroy(struct netif *netif)
{
	#if LWIP_DHCP
		dhcp_stop(netif); 			//�ر�DHCP
	#endif
	netif_set_link_down(netif);		//����ǿ������
	netif_remove(netif);  			//ɾ��lwip_netif����
	lwip_comm_mem_free();			//�ͷ��ڴ�
 	ETH_Mem_Free();					//�ͷ��ڴ�
	HAL_ETH_DeInit(&ETH_Handler);  	//��λ��̫������
}

//ETH�ײ�������ʱ��ʹ�ܣ���������
//�˺����ᱻHAL_ETH_Init()����
//heth:��̫�����
void HAL_ETH_MspInit(ETH_HandleTypeDef *heth)
{
    GPIO_InitTypeDef GPIO_Initure;
    
    __HAL_RCC_ETH_CLK_ENABLE();             //����ETHʱ��
    __HAL_RCC_GPIOA_CLK_ENABLE();			//����GPIOAʱ��
	__HAL_RCC_GPIOB_CLK_ENABLE();			//����GPIOBʱ��
    __HAL_RCC_GPIOC_CLK_ENABLE();			//����GPIOCʱ��
	__HAL_RCC_GPIOD_CLK_ENABLE();           //����GPIODʱ��
    __HAL_RCC_GPIOG_CLK_ENABLE();			//����GPIOGʱ��
    
    /*������������ RMII�ӿ� 
    ETH_MDIO -------------------------> PA2
    ETH_MDC --------------------------> PC1
    ETH_RMII_REF_CLK------------------> PA1
    ETH_RMII_CRS_DV ------------------> PA7
    ETH_RMII_RXD0 --------------------> PC4
    ETH_RMII_RXD1 --------------------> PC5
    ETH_RMII_TX_EN -------------------> PG11
    ETH_RMII_TXD0 --------------------> PG13
    ETH_RMII_TXD1 --------------------> PG14
    ETH_RESET-------------------------> PD3*/
    
    //PA1,2,7
    GPIO_Initure.Pin=GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_7; 
    GPIO_Initure.Mode=GPIO_MODE_AF_PP;          //���츴��
    GPIO_Initure.Pull=GPIO_NOPULL;              //����������
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;         //����
    GPIO_Initure.Alternate=GPIO_AF11_ETH;       //����ΪETH����
    HAL_GPIO_Init(GPIOA,&GPIO_Initure);         //��ʼ��
    
    //PC1,4,5
    GPIO_Initure.Pin=GPIO_PIN_1|GPIO_PIN_4|GPIO_PIN_5; //PC1,4,5
    HAL_GPIO_Init(GPIOC,&GPIO_Initure);         //��ʼ��
	
    //PG11,13,14
    GPIO_Initure.Pin=GPIO_PIN_11|GPIO_PIN_13|GPIO_PIN_14;   //PG11,PG13,14
    HAL_GPIO_Init(GPIOG,&GPIO_Initure);         //��ʼ��
	
	//����PD3Ϊ�������,NetCard_PHY��λ����
    GPIO_Initure.Pin=GPIO_PIN_3; 				//PD3
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  	//�������
    GPIO_Initure.Pull=GPIO_NOPULL;          	//��������
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     	//����
    HAL_GPIO_Init(GPIOD,&GPIO_Initure);
    
    HAL_NVIC_SetPriority(ETH_IRQn,1,0);         //�����ж����ȼ�Ӧ�ø�һ��
    HAL_NVIC_EnableIRQ(ETH_IRQn);
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



//��ȡ���յ���֡����
//DMARxDesc:����DMA������
//����ֵ:���յ���֡����
u32  ETH_GetRxPktSize(ETH_DMADescTypeDef *DMARxDesc)
{
    u32 frameLength = 0;
    if(((DMARxDesc->Status&ETH_DMARXDESC_OWN)==(uint32_t)RESET) &&
     ((DMARxDesc->Status&ETH_DMARXDESC_ES)==(uint32_t)RESET) &&
     ((DMARxDesc->Status&ETH_DMARXDESC_LS)!=(uint32_t)RESET)) 
    {
        frameLength=((DMARxDesc->Status&ETH_DMARXDESC_FL)>>ETH_DMARXDESC_FRAME_LENGTHSHIFT);
    }
    return frameLength;
}

//�жϷ�����
void ETH_IRQHandler(void)
{
    while(ETH_GetRxPktSize(ETH_Handler.RxDesc))   
    {
        lwip_pkt_handle();//������̫�����ݣ����������ύ��LWIP
    }
    //����жϱ�־λ
    __HAL_ETH_DMA_CLEAR_IT(&ETH_Handler,ETH_DMA_IT_NIS);    //���DMA�жϱ�־λ
    __HAL_ETH_DMA_CLEAR_IT(&ETH_Handler,ETH_DMA_IT_R);      //���DMA�����жϱ�־λ
}




