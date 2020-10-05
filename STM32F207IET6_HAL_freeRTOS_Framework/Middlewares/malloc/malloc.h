#ifndef __MALLOC_H
#define __MALLOC_H
#include "PeriphConfigCore.h"

/*���ļ���� ALIENTEKս��STM32������V3 �ڴ���� ��Դ����*/
/*�����ַ��֣�Ӳʯ��YSFxϵ�п�������������ڴ����Դ���������ļ���һģһ�������Ҷ�˵�Լ�������...*/

/*______________________�û�����___________________________*/
#define RAM_Num 	2	//����֧�ֵ�SRAM����
/*��������˵������ڴ棬������Ҫ�պ�«��ư������Ӧ������Ϣ*/

/*______________________�û�����___________________________*/
//�����ڴ�ر�־
#define InrRAM	 	0		//�ڲ��ڴ��
#define ExRAM1   	1		//�ⲿ�ڴ��1
#define ExRAM2   	2		//�ⲿ�ڴ��2���������ʱû�õ���

/*______________________�û����ã�InrRAM___________________________*/
//InrRAM�ڴ�����趨��InrRAM��ȫ�����ڲ�SRAM����
#define InrRAM_BLOCK_SIZE			32  	  							//�ڴ���СΪ32�ֽڣ�һ�㲻�ö�������Ĭ�Ͼͺã�
#define InrRAM_MAX_SIZE			50*1024  								//�������ڴ� 50K ��ע��FreeRTOS���ڴ�����С����������

#define InrRAM_ALLOC_TABLE_SIZE	(InrRAM_MAX_SIZE/InrRAM_BLOCK_SIZE) 	//�ڴ���С�������ĪҪ�Ҷ�����

/*______________________�û����ã�ExRAM1___________________________*/
//ExRAM1�ڴ�����趨��ExRAM1���ڴ�ش����ⲿSRAM���棨����1M�ռ���ⲿRAM�����ﱣ��Ĭ�Ͼͺã�
#define ExRAM1_BLOCK_SIZE			32  	  							//�ڴ���СΪ32�ֽڣ�һ�㲻�ö�������Ĭ�Ͼͺã�
#define ExRAM1_MAX_SIZE			960*1024  								//�������ڴ�960K������1M�ռ���ⲿRAM�����ﱣ��Ĭ�Ͼͺã�
#define ExRAM1_ALLOC_TABLE_SIZE	(ExRAM1_MAX_SIZE/ExRAM1_BLOCK_SIZE) 	//�ڴ���С����ExRAM1_MAX_SIZEΪ960K����£����ռ30K
/*��������˵������ڴ棬Ȼ��Ҫȥ.c�ļ��޸�Ҫ�޸ĵĲ���*/


 /*________________________����Ĭ�ϵĲ��ö�________________________*/
//�ڴ���������
struct _m_malloc_dev
{
	void (*init)(u8);					//��ʼ��
	u8 (*perused)(u8);		  	    	//�ڴ�ʹ����
	u8 	*membase[RAM_Num];				//�ڴ�� ����SRAMBANK��������ڴ�
	u16 *memmap[RAM_Num]; 				//�ڴ����״̬��
	u8  memrdy[RAM_Num]; 				//�ڴ�����Ƿ����
};
extern struct _m_malloc_dev malloc_dev;	 //��malloc.c���涨��
    
void my_mem_init(u8 memx);				//�ڴ�����ʼ������(��/�ڲ�����)
u32 my_mem_malloc(u8 memx,u32 size);	//�ڴ����(�ڲ�����)
u8 my_mem_free(u8 memx,u32 offset);		//�ڴ��ͷ�(�ڲ�����)
u8 my_mem_perused(u8 memx);				//����ڴ�ʹ����(��/�ڲ�����) 
////////////////////////////////////////////////////////////////////////////////
//�û����ú���
void myfree(u8 memx,void *ptr);  			//�ڴ��ͷ�(�ⲿ����)
void *mymalloc(u8 memx,u32 size);			//�ڴ����(�ⲿ����)
void *myrealloc(u8 memx,void *ptr,u32 size);//���·����ڴ�(�ⲿ����)
#endif













