/*
    FreeRTOS V9.0.0 - Copyright (C) 2016 Real Time Engineers Ltd.
    All rights reserved

    VISIT http://www.FreeRTOS.org TO ENSURE YOU ARE USING THE LATEST VERSION.

    This file is part of the FreeRTOS distribution.

    FreeRTOS is free software; you can redistribute it and/or modify it under
    the terms of the GNU General Public License (version 2) as published by the
    Free Software Foundation >>>> AND MODIFIED BY <<<< the FreeRTOS exception.

    ***************************************************************************
    >>!   NOTE: The modification to the GPL is included to allow you to     !<<
    >>!   distribute a combined work that includes FreeRTOS without being   !<<
    >>!   obliged to provide the source code for proprietary components     !<<
    >>!   outside of the FreeRTOS kernel.                                   !<<
    ***************************************************************************

    FreeRTOS is distributed in the hope that it will be useful, but WITHOUT ANY
    WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
    FOR A PARTICULAR PURPOSE.  Full license text is available on the following
    link: http://www.freertos.org/a00114.html

    ***************************************************************************
     *                                                                       *
     *    FreeRTOS provides completely free yet professionally developed,    *
     *    robust, strictly quality controlled, supported, and cross          *
     *    platform software that is more than just the market leader, it     *
     *    is the industry's de facto standard.                               *
     *                                                                       *
     *    Help yourself get started quickly while simultaneously helping     *
     *    to support the FreeRTOS project by purchasing a FreeRTOS           *
     *    tutorial book, reference manual, or both:                          *
     *    http://www.FreeRTOS.org/Documentation                              *
     *                                                                       *
    ***************************************************************************

    http://www.FreeRTOS.org/FAQHelp.html - Having a problem?  Start by reading
    the FAQ page "My application does not run, what could be wrong?".  Have you
    defined configASSERT()?

    http://www.FreeRTOS.org/support - In return for receiving this top quality
    embedded software for free we request you assist our global community by
    participating in the support forum.

    http://www.FreeRTOS.org/training - Investing in training allows your team to
    be as productive as possible as early as possible.  Now you can receive
    FreeRTOS training directly from Richard Barry, CEO of Real Time Engineers
    Ltd, and the world's leading authority on the world's leading RTOS.

    http://www.FreeRTOS.org/plus - A selection of FreeRTOS ecosystem products,
    including FreeRTOS+Trace - an indispensable productivity tool, a DOS
    compatible FAT file system, and our tiny thread aware UDP/IP stack.

    http://www.FreeRTOS.org/labs - Where new FreeRTOS products go to incubate.
    Come and try FreeRTOS+TCP, our new open source TCP/IP stack for FreeRTOS.

    http://www.OpenRTOS.com - Real Time Engineers ltd. license FreeRTOS to High
    Integrity Systems ltd. to sell under the OpenRTOS brand.  Low cost OpenRTOS
    licenses offer ticketed support, indemnification and commercial middleware.

    http://www.SafeRTOS.com - High Integrity Systems also provide a safety
    engineered and independently SIL3 certified version for use in safety and
    mission critical applications that require provable dependability.

    1 tab == 4 spaces!
*/


#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

//��Բ�ͬ�ı��������ò�ͬ��stdint.h�ļ�
#if defined(__ICCARM__) || defined(__CC_ARM) || defined(__GNUC__)
    #include <stdint.h>
    extern uint32_t SystemCoreClock;
#endif

//����
#define vAssertCalled(char,int) //printf("Error:%s,%d\r\n",char,int);
#define configASSERT(x) if((x)==0) vAssertCalled(__FILE__,__LINE__)

#include "isUseFreeRTOS.h"
#if SYSTEM_SUPPORT_OS
		#define xPortPendSVHandler 	PendSV_Handler //FreeRTOS���жϷ������йص�����ѡ�ĪҪ�Ҷ���
		#define vPortSVCHandler 	SVC_Handler
#endif

/***************************************************************************************************************/
/*                                        FreeRTOS������������ѡ��                                              */
/***************************************************************************************************************/
#define configCHECK_FOR_STACK_OVERFLOW			0                       //����0ʱ���ö�ջ�����⹦�ܣ����ʹ�ô˹���
                                                                        //�û������ṩһ��ջ������Ӻ��������ʹ�õĻ�
                                                                        //��ֵ����Ϊ1����2��ʾ�����ַ�����⣬1���ٵ�������©��2�������Ǹ�ȫ��
#define configUSE_TICKLESS_IDLE					0                       //1���õ͹���ticklessģʽ

#define configMINIMAL_STACK_SIZE				((unsigned short)15)   //��������ʹ�õĶ�ջ��С��ʵ��ռ�õ��ֽ���Ϊ�趨�����ı�

/***************************************************************************************************************/
/*                                        ���������»���������������֪�����ڸ�ʲô                              */
/***************************************************************************************************************/
#define configUSE_PREEMPTION					1                       //1ʹ����ռʽ�ںˣ�0ʹ��Э��
#define configUSE_TIME_SLICING					1						//1ʹ��ʱ��Ƭ����(Ĭ��ʽʹ�ܵ�)
#define configUSE_PORT_OPTIMISED_TASK_SELECTION	1                       //1�������ⷽ����ѡ����һ��Ҫ���е�����
                                                                        //һ����Ӳ������ǰ����ָ������ʹ�õ�
                                                                        //MCUû����ЩӲ��ָ��Ļ��˺�Ӧ������Ϊ0��
                                                                        
#define configCPU_CLOCK_HZ						(SystemCoreClock)       //CPUƵ��
#define configTICK_RATE_HZ						(1000)                  //ʱ�ӽ���Ƶ�ʣ���������Ϊ1000�����ھ���1ms
#define configMAX_PRIORITIES					(16)                    //��ʹ�õ�������ȼ�

#define configMAX_TASK_NAME_LEN					(16)                    //���������ַ�������
#define configUSE_16_BIT_TICKS					0                       //ϵͳ���ļ����������������ͣ�
                                                                        //1��ʾΪ16λ�޷������Σ�0��ʾΪ32λ�޷�������
#define configIDLE_SHOULD_YIELD					0                       //Ϊ1ʱ�����������CPUʹ��Ȩ������ͬ���ȼ����û�����
																		//�����������ͷ���ɾ��������ڴ�ȹ����������������һ��ʱ�䣡
#define configENABLE_BACKWARD_COMPATIBILITY     0

#define configUSE_APPLICATION_TASK_TAG			0                       //1�������غ���

#define configUSE_TASK_NOTIFICATIONS            1                       //Ϊ1ʱ��������֪ͨ���ܣ�Ĭ�Ͽ���
#define configUSE_MUTEXES						0                       //Ϊ1ʱʹ�û����ź���
#define configUSE_RECURSIVE_MUTEXES				0                       //Ϊ1ʱʹ�õݹ黥���ź���
#define configUSE_COUNTING_SEMAPHORES			0                       //Ϊ1ʱʹ�ü����ź���
#define configUSE_QUEUE_SETS					1                       //Ϊ1ʱ���ö���
#define configQUEUE_REGISTRY_SIZE				8                       //��Ϊ0ʱ��ʾ���ö��м�¼�������ֵ�ǿ���
                                                                        //��¼�Ķ��к��ź��������Ŀ
/***************************************************************************************************************/
/*                                FreeRTOS���ڴ������й�����ѡ��                                                */
/***************************************************************************************************************/
#define configSUPPORT_DYNAMIC_ALLOCATION        1                       //֧�ֶ�̬�ڴ�����
#define configTOTAL_HEAP_SIZE					((size_t)(30*1024))     //ϵͳ�����ܵĶѴ�С
//->�ȴ�����<-
/*
STN32F207IET6���ڲ�����
				FLASH               RAM
				512K                128K
*/
/***************************************************************************************************************/
/*                                FreeRTOS�빳�Ӻ����йص�����ѡ��                                              */
/***************************************************************************************************************/
#define configUSE_IDLE_HOOK						0                       //1��ʹ�ÿ��й��ӣ�0����ʹ��
#define configUSE_TICK_HOOK						0                       //1��ʹ��ʱ��Ƭ���ӣ�0����ʹ��
#define configUSE_MALLOC_FAILED_HOOK			0                       //1ʹ���ڴ�����ʧ�ܹ��Ӻ���

/***************************************************************************************************************/
/*                                FreeRTOS������ʱ�������״̬�ռ��йص�����ѡ��                                 */
/***************************************************************************************************************/
#define configGENERATE_RUN_TIME_STATS	        0                       //Ϊ1ʱ��������ʱ��ͳ�ƹ��ܣ�Ĭ������
#define configUSE_TRACE_FACILITY				1                       //Ϊ1���ÿ��ӻ����ٵ��ԣ�Ĭ������
#define configUSE_STATS_FORMATTING_FUNCTIONS	1                       //���configUSE_TRACE_FACILITYͬʱΪ1ʱ���������3������
                                                                        //prvWriteNameToBuffer(),vTaskList(),
                                                                        //vTaskGetRunTimeStats()
//#define portCONFIGURE_TIMER_FOR_RUN_TIME_STATS()	ConfigureTimeForRunTimeStats()/*��ȡ����������Ϣ��������ϸ�÷�����ԭ��F1��FreeRTOS�ֲ�172ҳ����û����ȫ���úã���Ҫ˽������Ŷ*/
//#define portALT_GET_RUN_TIME_COUNTER_VALUE
/***************************************************************************************************************/
/*                                FreeRTOS��Э���йص�����ѡ��                                                  */
/***************************************************************************************************************/
#define configUSE_CO_ROUTINES 			        0                       //Ϊ1ʱ����Э�̣�����Э���Ժ���������ļ�croutine.c
#define configMAX_CO_ROUTINE_PRIORITIES         ( 2 )                   //Э�̵���Ч���ȼ���Ŀ

/***************************************************************************************************************/
/*                                FreeRTOS��������ʱ���йص�����ѡ����ö���                                  */
/***************************************************************************************************************/
#define configUSE_TIMERS				        1                               //Ϊ1ʱ����������ʱ��
#define configTIMER_TASK_PRIORITY		        (configMAX_PRIORITIES-1)        //������ʱ�����ȼ�
#define configTIMER_QUEUE_LENGTH		        5                               //������ʱ�����г���
#define configTIMER_TASK_STACK_DEPTH	        (configMINIMAL_STACK_SIZE*2)    //������ʱ�������ջ��С����λΪ�֣����ݻص���������
//->�ȴ�����<-
/***************************************************************************************************************/
/*                                FreeRTOS��ѡ��������ѡ�����ĺ�����Ҫ����Ҫ�����������ҳ�BUG��             */
/***************************************************************************************************************/
#define INCLUDE_xTaskGetSchedulerState          1                       
#define INCLUDE_vTaskPrioritySet		        1
#define INCLUDE_uxTaskPriorityGet		        1
#define INCLUDE_vTaskDelete				        1
#define INCLUDE_vTaskCleanUpResources	        1
#define INCLUDE_vTaskSuspend			        1
#define INCLUDE_vTaskDelayUntil			        1
#define INCLUDE_vTaskDelay				        1
#define INCLUDE_eTaskGetState			        1
#define INCLUDE_xTimerPendFunctionCall	        1
#define INCLUDE_xTaskGetCurrentTaskHandle		1
#define INCLUDE_xTaskGetHandle					1

/***************************************************************************************************************/
/*                                FreeRTOS���ж��йص�����ѡ��                                                  */
/***************************************************************************************************************/
#ifdef __NVIC_PRIO_BITS
	#define configPRIO_BITS       		__NVIC_PRIO_BITS
#else
	#define configPRIO_BITS       		4                  
#endif

#define configLIBRARY_LOWEST_INTERRUPT_PRIORITY			15                      //�ж�������ȼ�
#define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY	5                       //ϵͳ�ɹ���������ж����ȼ�
//->�ȴ�����<-
#define configKERNEL_INTERRUPT_PRIORITY 		( configLIBRARY_LOWEST_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )
#define configMAX_SYSCALL_INTERRUPT_PRIORITY 	( configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )

#endif /* FREERTOS_CONFIG_H */
