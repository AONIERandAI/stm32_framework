#ifndef __MALLOC_H
#define __MALLOC_H
#include "sys.h"

//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������V3
//�ڴ���� ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2019/9/19
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////
/*���ļ���� ALIENTEKս��STM32������V3 �ڴ���� ��Դ����*/

/*______________________�û�����___________________________*/
#define RAM_Num 	2	//����֧�ֵ�SRAM����

/*______________________�û�����___________________________*/
//���������ڴ��
#define InrRAM	 	0		//�ڲ��ڴ��
#if ((SYSTEM_FSMC_ENABLE) && (SYSTEM_FSMC_use4SRAM)) && ((STM32F103xG) || (STM32F103xE))
#define ExRAM1   	1		//�ⲿ�ڴ��1
#endif

/*______________________�û�����___________________________*/
//InrRAM�ڴ�����趨��InrRAM��ȫ�����ڲ�SRAM����
#define InrRAM_BLOCK_SIZE			32  	  							//�ڴ���СΪ32�ֽڣ�һ�㲻�ö�������Ĭ�Ͼͺã�
#if ((STM32F103xG) || (STM32F103xE))
	#define InrRAM_MAX_SIZE			40*1024  								//�������ڴ� 40K ��ע��FreeRTOS���ڴ�����С����������
#else
	#define InrRAM_MAX_SIZE			5*1024  								//�������ڴ� 5K ��ע��FreeRTOS���ڴ�����С����������
#endif
#define InrRAM_ALLOC_TABLE_SIZE	(InrRAM_MAX_SIZE/InrRAM_BLOCK_SIZE) 	//�ڴ���С

/*______________________�û�����___________________________*/
//ExRAM1�ڴ�����趨��ExRAM1���ڴ�ش����ⲿSRAM���棨����1M�ռ���ⲿRAM�����ﱣ��Ĭ�Ͼͺã�
#define ExRAM1_BLOCK_SIZE			32  	  							//�ڴ���СΪ32�ֽڣ�һ�㲻�ö�������Ĭ�Ͼͺã�
#define ExRAM1_MAX_SIZE			960*1024  								//�������ڴ�960K������1M�ռ���ⲿRAM�����ﱣ��Ĭ�Ͼͺã�
#define ExRAM1_ALLOC_TABLE_SIZE	(ExRAM1_MAX_SIZE/ExRAM1_BLOCK_SIZE) 	//�ڴ���С����ExRAM1_MAX_SIZEΪ960K����£����ռ30K
		 
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













