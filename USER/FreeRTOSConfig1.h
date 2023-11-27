/*
 * FreeRTOS V202212.01
 * Copyright (C) 2020 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * https://www.FreeRTOS.org
 * https://github.com/FreeRTOS
 *
 */


#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

/*-----------------------------------------------------------
 * Application specific definitions.
 *
 * These definitions should be adjusted for your particular hardware and
 * application requirements.
 *
 * THESE PARAMETERS ARE DESCRIBED WITHIN THE 'CONFIGURATION' SECTION OF THE
 * FreeRTOS API DOCUMENTATION AVAILABLE ON THE FreeRTOS.org WEB SITE.
 *
 * See http://www.freertos.org/a00110.html
 *----------------------------------------------------------*/

/* Ensure stdint is only used by the compiler, and not the assembler. */
#if defined (__ICCARM__) || defined(__CC_ARM) || defined(__GNUC__)
	#include <stdint.h>
	extern uint32_t SystemCoreClock;
#endif

/************************************************************************
* FreeRTOS ������������ѡ��
*********************************************************************/
/* �� 1�� RTOS ʹ����ռʽ���������� 0�� RTOS ʹ��Э��ʽ��������ʱ��Ƭ��
*
* ע���ڶ������������ϣ�����ϵͳ���Է�Ϊ��ռʽ��Э��ʽ���֡�
* Э��ʽ����ϵͳ�����������ͷ� CPU ���л�����һ������
* �����л���ʱ����ȫȡ�����������е�����
*/
#define configUSE_PREEMPTION 						1 

//1 ʹ��ʱ��Ƭ����(Ĭ��ʽʹ�ܵ�)
#define configUSE_TIME_SLICING		 				1 

/* ĳЩ���� FreeRTOS ��Ӳ�������ַ���ѡ����һ��Ҫִ�е�����
* ͨ�÷������ض���Ӳ���ķ��������¼�ơ����ⷽ��������
*
* ͨ�÷�����
* 1.configUSE_PORT_OPTIMISED_TASK_SELECTION Ϊ 0 ����Ӳ����֧���������ⷽ����
* 2.������������ FreeRTOS ֧�ֵ�Ӳ��
* 3.��ȫ�� C ʵ�֣�Ч���Ե������ⷽ����
* 4.��ǿ��Ҫ���������������ȼ���Ŀ
* ���ⷽ����
* 1.���뽫 configUSE_PORT_OPTIMISED_TASK_SELECTION ����Ϊ 1��
* 2.����һ�������ض��ܹ��Ļ��ָ�һ�������Ƽ���ǰ����[CLZ]ָ���
* 3.��ͨ�÷�������Ч
* 4.һ��ǿ���޶����������ȼ���ĿΪ 32
*
һ����Ӳ������ǰ����ָ������ʹ�õģ� MCU û����ЩӲ��ָ��Ļ��˺�Ӧ������Ϊ 0��
*/
#define configUSE_PORT_OPTIMISED_TASK_SELECTION 	1 

/* �� 1��ʹ�ܵ͹��� tickless ģʽ���� 0������ϵͳ���ģ�tick���ж�һֱ���� */
#define configUSE_TICKLESS_IDLE 					0 

/*
* д��ʵ�ʵ� CPU �ں�ʱ��Ƶ�ʣ�Ҳ���� CPU ָ��ִ��Ƶ�ʣ�ͨ����Ϊ Fclk
* Fclk Ϊ���� CPU �ں˵�ʱ���źţ�������˵�� cpu ��ƵΪ XX MHz��
* ����ָ�����ʱ���źţ���Ӧ�ģ� 1/Fclk ��Ϊ cpu ʱ�����ڣ�
*/
#define configCPU_CLOCK_HZ 						(SystemCoreClock)

//RTOS ϵͳ�����жϵ�Ƶ�ʡ���һ���жϵĴ�����ÿ���ж� RTOS ��������������
#define configTICK_RATE_HZ 						(( TickType_t )1000) 

//��ʹ�õ�������ȼ�
#define configMAX_PRIORITIES 					(32) 

//��������ʹ�õĶ�ջ��С
#define configMINIMAL_STACK_SIZE 				((unsigned short)128) 

//���������ַ�������
#define configMAX_TASK_NAME_LE 					(16) 

//ϵͳ���ļ����������������ͣ� 1 ��ʾΪ 16 λ�޷������Σ� 0 ��ʾΪ 32 λ�޷�������
#define configUSE_16_BIT_TICKS 					0 

//����������� CPU ʹ��Ȩ������ͬ���ȼ����û�����
#define configIDLE_SHOULD_YIELD 				1 

//���ö���
#define configUSE_QUEUE_SETS 					1 

//��������֪ͨ���ܣ�Ĭ�Ͽ���
#define configUSE_TASK_NOTIFICATIONS 			1 

//ʹ�û����ź���
#define configUSE_MUTEXES 						1 

//ʹ�õݹ黥���ź���
#define configUSE_RECURSIVE_MUTEXES 			1 

//Ϊ 1 ʱʹ�ü����ź���
#define configUSE_COUNTING_SEMAPHORES 			1 

/* ���ÿ���ע����ź�������Ϣ���и��� */
#define configQUEUE_REGISTRY_SIZE 				10 

#define configUSE_APPLICATION_TASK_TAG 			0


/*****************************************************************
FreeRTOS ���ڴ������й�����ѡ��
*****************************************************************/
//֧�ֶ�̬�ڴ�����
#define configSUPPORT_DYNAMIC_ALLOCATION 		1 
//֧�־�̬�ڴ�
#define configSUPPORT_STATIC_ALLOCATION 		0
//ϵͳ�����ܵĶѴ�С
#define configTOTAL_HEAP_SIZE 					((size_t)(36*1024)) 
/***************************************************************
FreeRTOS �빳�Ӻ����йص�����ѡ��
**************************************************************/
/* �� 1��ʹ�ÿ��й��ӣ�Idle Hook �����ڻص����������� 0�����Կ��й���
*
* ������������һ������������������û���ʵ�֣�
* FreeRTOS �涨�˺��������ֺͲ����� void vApplicationIdleHook(void )��
* ���������ÿ�������������ڶ��ᱻ����
* �����Ѿ�ɾ���� RTOS ���񣬿�����������ͷŷ�������ǵĶ�ջ�ڴ档
* ��˱��뱣֤����������Ա� CPU ִ��
* ʹ�ÿ��й��Ӻ������� CPU ����ʡ��ģʽ�Ǻܳ�����
* �����Ե��û������������������ API ����
*/
#define configUSE_IDLE_HOOK 					0 

/* �� 1��ʹ��ʱ��Ƭ���ӣ�Tick Hook������ 0������ʱ��Ƭ����
*
*
* ʱ��Ƭ������һ������������������û���ʵ�֣�
* FreeRTOS �涨�˺��������ֺͲ����� void vApplicationTickHook(void )
* ʱ��Ƭ�жϿ��������Եĵ���
* ��������ǳ���С�����ܴ���ʹ�ö�ջ��
* ���ܵ����ԡ�FromISR" �� "FROM_ISR����β�� API ����
*/
#define configUSE_TICK_HOOK 					0 

//ʹ���ڴ�����ʧ�ܹ��Ӻ���
#define configUSE_MALLOC_FAILED_HOOK 			0 

/*
* ���� 0 ʱ���ö�ջ�����⹦�ܣ����ʹ�ô˹���
* �û������ṩһ��ջ������Ӻ��������ʹ�õĻ�
* ��ֵ����Ϊ 1 ���� 2����Ϊ������ջ�����ⷽ�� */
#define configCHECK_FOR_STACK_OVERFLOW 			0 


/********************************************************************
FreeRTOS ������ʱ�������״̬�ռ��йص�����ѡ��
**********************************************************************/
//��������ʱ��ͳ�ƹ���
#define configGENERATE_RUN_TIME_STATS 			0 
//���ÿ��ӻ����ٵ���
#define configUSE_TRACE_FACILITY 				0 
/* ��� configUSE_TRACE_FACILITY ͬʱΪ 1 ʱ��������� 3 ������
* prvWriteNameToBuffer()
* vTaskList(),
* vTaskGetRunTimeStats()
*/
#define configUSE_STATS_FORMATTING_FUNCTIONS 	0


/********************************************************************
FreeRTOS ��Э���йص�����ѡ��
*********************************************************************/
//����Э�̣�����Э���Ժ��������ļ� croutine.c
#define configUSE_CO_ROUTINES 					0 
//Э�̵���Ч���ȼ���Ŀ
#define configMAX_CO_ROUTINE_PRIORITIES 		( 2 ) 


/***********************************************************************
FreeRTOS �������ʱ���йص�����ѡ��
**********************************************************************/
//���������ʱ��
#define configUSE_TIMERS 						1 
//�����ʱ�����ȼ�
#define configTIMER_TASK_PRIORITY 				(configMAX_PRIORITIES-1) 
//�����ʱ�����г���
#define configTIMER_QUEUE_LENGTH 				10 
//�����ʱ�������ջ��С
#define configTIMER_TASK_STACK_DEPTH 			(configMINIMAL_STACK_SIZE*2)

/************************************************************
FreeRTOS ��ѡ��������ѡ��
************************************************************/
#define INCLUDE_xTaskGetSchedulerState 		1 
#define INCLUDE_vTaskPrioritySet 			1 
#define INCLUDE_uxTaskPriorityGet 			1 
#define INCLUDE_vTaskDelete 				1 
#define INCLUDE_vTaskCleanUpResources 		1
#define INCLUDE_vTaskSuspend 				1
#define INCLUDE_vTaskDelayUntil 			1
#define INCLUDE_vTaskDelay 					1
#define INCLUDE_eTaskGetState 				1
#define INCLUDE_xTimerPendFunctionCall 		1

/* Cortex-M specific definitions. */
#ifdef __NVIC_PRIO_BITS
	/* __BVIC_PRIO_BITS will be specified when CMSIS is being used. */
	#define configPRIO_BITS       		__NVIC_PRIO_BITS
#else
	#define configPRIO_BITS       		4        /* 15 priority levels */
#endif

/* The lowest interrupt priority that can be used in a call to a "set priority"
function. */
#define configLIBRARY_LOWEST_INTERRUPT_PRIORITY			0xf

/* The highest interrupt priority that can be used by any interrupt service
routine that makes calls to interrupt safe FreeRTOS API functions.  DO NOT CALL
INTERRUPT SAFE FREERTOS API FUNCTIONS FROM ANY INTERRUPT THAT HAS A HIGHER
PRIORITY THAN THIS! (higher priorities are lower numeric values. */
#define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY	5

/* Interrupt priorities used by the kernel port layer itself.  These are generic
to all Cortex-M ports, and do not rely on any particular library functions. */
#define configKERNEL_INTERRUPT_PRIORITY 		( configLIBRARY_LOWEST_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )
/* !!!! configMAX_SYSCALL_INTERRUPT_PRIORITY must not be set to zero !!!!
See http://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html. */
#define configMAX_SYSCALL_INTERRUPT_PRIORITY 	( configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )

/* Normal assert() semantics without relying on the provision of an assert.h
header file. */
#define configASSERT( x ) if( ( x ) == 0 ) { taskDISABLE_INTERRUPTS(); for( ;; ); }

/* Definitions that map the FreeRTOS port interrupt handlers to their CMSIS
standard names. */
#define vPortSVCHandler SVC_Handler
#define xPortPendSVHandler PendSV_Handler
#define xPortSysTickHandler SysTick_Handler

#endif /* FREERTOS_CONFIG_H */
