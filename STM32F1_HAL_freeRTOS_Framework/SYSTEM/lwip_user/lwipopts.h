#ifndef __LWIPOPTS_H__
#define __LWIPOPTS_H__

/*��Ϊ0ʱ������LWIP������ڴ��FLASHҲ���ᱻ����
	LWIPռ�ô��45k��FLASH��20K(memp)+10K(MEM_SIZE��С)��RAM
	stm32f103c8û���㹻���ڴ�
	��LWIP����ѡ��xEϵ�У�����LWIPʱ����ѡ��xBϵ��
	��������ⲿSRAM�����ñ���mallocΪram_heap�����ڴ�Ҳ���ԣ����ǣ�ת�ۣ���
		һ��СС��stm32f103xBϵ��Ϊ����ETH�������ٶ�������Ҫ�Ʒ��򰺹��SRAM��ETHоƬ�����߶���10Ԫ�𲽣���
		�����㣬����F103���ﲻ����malloc�����ڴ棩
	
	xEϵ��������Ϣ��FLASH:512K(hd)	SRAM:64K
	
	opt.h�������� MEMP_MEM_MALLOC ��Ϊ 1 ��Ĭ�ϣ��Ͳ�Ҫ���ˣ�
		��Ϊ ��memp���ڴ��mem.h��ram_heap�������ȡ��
		������������� MEM_SIZE �Ĵ�СΪ����֮���ٴ�һ�㣬
		Ĭ������Ϊ 30*1024
	
	�� MEM_SIZE			30*1024 
	   InrRAM_MAX_SIZE	20*1024
	������£��������պ�������룬FLASH��SRAM���Ļ��б仯����������ݽ�������Աȣ�
		����LWIP��ı�����Ϣ��			Program Size: Code=21628 RO-data=4060 RW-data=1008 ZI-data=24016	
		��LWIP��ı�����Ϣ��
			MEMP_MEM_MALLOC Ϊ 1 ʱ��	Program Size: Code=66756 RO-data=4608 RW-data=1192 ZI-data=56312	
			MEMP_MEM_MALLOC Ϊ 0 ʱ��	����һ�еĻ����ϣ�FLASH�������䣬SRAM��������Լ20KB������������Ƽ���
*/

#define SYS_SUPPORT_LWIP		0	

#define SYS_Test_LWIP			1	//��ֻ����LWIP�����е������κ�TCP/UDPͨѶʱ�򿪣�����ر�
									//��ʱ��TCP,UDP,HTTP��APP��ش��벻�ᱻ����

#define SYS_LIGHTWEIGHT_PROT    0

//NO_SYS==1:��ʹ�ò���ϵͳ
#define NO_SYS                  1  //��ʹ��UCOS����ϵͳ

//ʹ��4�ֽڶ���ģʽ
#define MEM_ALIGNMENT           4  

//MEM_SIZE:heap�ڴ�Ĵ�С,�����Ӧ�����д������ݷ��͵Ļ����ֵ������ô�һ�� 
#define MEM_SIZE                30*1024 //�ڴ�Ѵ�С
//#define MEM_LIBC_MALLOC			1
//MEMP_NUM_PBUF:memp�ṹ��pbuf����,���Ӧ�ô�ROM���߾�̬�洢�����ʹ�������ʱ,���ֵӦ�����ô�һ��
#define MEMP_NUM_PBUF           10

//MEMP_NUM_UDP_PCB:UDPЭ����ƿ�(PCB)����.ÿ�����UDP"����"��Ҫһ��PCB.
#define MEMP_NUM_UDP_PCB        6

//MEMP_NUM_TCP_PCB:ͬʱ���������TCP����
#define MEMP_NUM_TCP_PCB        10

//MEMP_NUM_TCP_PCB_LISTEN:�ܹ�������TCP��������
#define MEMP_NUM_TCP_PCB_LISTEN 6

//MEMP_NUM_TCP_SEG:���ͬʱ�ڶ����е�TCP������
#define MEMP_NUM_TCP_SEG        20

//MEMP_NUM_SYS_TIMEOUT:�ܹ�ͬʱ�����timeout����
#define MEMP_NUM_SYS_TIMEOUT    5


/* ---------- Pbufѡ��---------- */
//PBUF_POOL_SIZE:pbuf�ڴ�ظ���. 
#define PBUF_POOL_SIZE          10

//PBUF_POOL_BUFSIZE:ÿ��pbuf�ڴ�ش�С. 
#define PBUF_POOL_BUFSIZE       1500


/* ---------- TCPѡ��---------- */
#define LWIP_TCP                1  //Ϊ1��ʹ��TCP
#define TCP_TTL                 255//����ʱ��

/*��TCP�����ݶγ�������ʱ�Ŀ���λ,���豸���ڴ��С��ʱ�����ӦΪ0*/
#define TCP_QUEUE_OOSEQ         0

//���TCP�ֶ�
#define TCP_MSS                 (1500 - 40)	  //TCP_MSS = (MTU - IP��ͷ��С - TCP��ͷ��С

//TCP���ͻ�������С(bytes).
#define TCP_SND_BUF             (4*TCP_MSS)

//TCP_SND_QUEUELEN: TCP���ͻ�������С(pbuf).���ֵ��СΪ(2 * TCP_SND_BUF/TCP_MSS) 
#define TCP_SND_QUEUELEN        (4* TCP_SND_BUF/TCP_MSS)

//TCP���ʹ���
#define TCP_WND                 (2*TCP_MSS)


/* ---------- ICMPѡ��---------- */
#define LWIP_ICMP                 1 //ʹ��ICMPЭ��

/* ---------- DHCPѡ��---------- */
#define LWIP_DHCP               1  //ʹ��DHCP

/* ---------- UDPѡ�� ---------- */ 
#define LWIP_UDP                1 //ʹ��UDP����
#define UDP_TTL                 255 //UDP���ݰ�����ʱ��

/* ---------- DNSѡ�� ---------- */ 
#define LWIP_DNS				1 //ʹ��DNS����
unsigned int Curl_rand(void);
#define LWIP_RAND				Curl_rand //ʹ����ʵ�ֵ�α�����

/* ---------- Statistics options ---------- */
#define LWIP_STATS 0
#define LWIP_PROVIDE_ERRNO 1


/*
   ----------------------------------------------
   ---------- SequentialAPIѡ��----------
   ----------------------------------------------
*/

//LWIP_NETCONN==1:ʹ��NETCON����(Ҫ��ʹ��api_lib.c)
#define LWIP_NETCONN                    0

/*
   ------------------------------------
   ---------- Socket APIѡ��----------
   ------------------------------------
*/
//LWIP_SOCKET==1:ʹ��Socket API(Ҫ��ʹ��sockets.c)
#define LWIP_SOCKET                     0

#define LWIP_COMPAT_MUTEX               1

#define LWIP_SO_RCVTIMEO                1 //ͨ������LWIP_SO_RCVTIMEOʹ��netconn�ṹ����recv_timeout,ʹ��recv_timeout���Ա��������߳�


/*
   ----------------------------------------
   ---------- Lwip����ѡ��----------
   ----------------------------------------
*/
//#define LWIP_DEBUG                     1 //����DEBUGѡ��

#define ICMP_DEBUG                      LWIP_DBG_OFF //����/�ر�ICMPdebug

#endif /* __LWIPOPTS_H__ */

