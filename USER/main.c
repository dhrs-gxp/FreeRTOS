#include "stm32f4xx.h"
#include "delay.h"
#include "usart.h"
#include "FreeRTOS.h"
#include "task.h"
#include "led.h"
#include "string.h"

static TaskHandle_t AppTaskCreate_Handle = NULL;
static TaskHandle_t LED1_Task_Handle = NULL;
static TaskHandle_t LED2_Task_Handle = NULL;

static void LED1_Task(void* parameter)
{
	while(1)
	{
		LED0 = ~LED0;
		vTaskDelay(500);
	}
}

static void LED2_Task(void* parameter)
{
	while(1)
	{
		LED1 = ~LED1;
		vTaskDelay(500);
	}
}

static void AppTaskCreate(void)
{
	BaseType_t xReturn = pdPASS;
	
	taskENTER_CRITICAL();	//进入临界区
	/*创建LED_Task任务*/
	xReturn = xTaskCreate((TaskFunction_t)LED1_Task,
						  (const char*   )"LED1_Task",
						  (uint16_t      )512,
						  (void*		 )NULL,
						  (UBaseType_t   )2,
						  (TaskHandle_t* )&LED1_Task_Handle);
										
	if(xReturn == pdPASS) printf("LED1_Task 任务创建成功!\r\n");
	else printf("LED1_Task 任务创建失败!\r\n");
						  
	xReturn = xTaskCreate((TaskFunction_t)LED2_Task,
						  (const char*   )"LED2_Task",
						  (uint16_t      )512,
						  (void*		 )NULL,
						  (UBaseType_t   )2,
						  (TaskHandle_t* )&LED2_Task_Handle);
										
	if(xReturn == pdPASS) printf("LED2_Task 任务创建成功!\r\n");
	else printf("LED2_Task 任务创建失败!\r\n");
	
	vTaskDelete(AppTaskCreate_Handle);
						  
	taskEXIT_CRITICAL();
}

static StackType_t Idle_Task_Stack[configMINIMAL_STACK_SIZE];
static StackType_t Timer_Task_Stack[configTIMER_TASK_STACK_DEPTH];

static StaticTask_t Idle_Task_TCB;
static StaticTask_t Timer_Task_TCB;

void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer,
								   StackType_t **ppxIdleTaskStackBuffer,
								   uint32_t *pulIdleTaskStackSize)
{
	*ppxIdleTaskTCBBuffer = &Idle_Task_TCB;
	*ppxIdleTaskStackBuffer = Idle_Task_Stack;
	*pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
}

void vApplicationGetTimerTaskMemory(StaticTask_t **ppxTimerTaskTCBBuffer,
									StackType_t **ppxTimerTaskStackBuffer,
									uint32_t *pulTimerTaskStackSize)
{
	*ppxTimerTaskTCBBuffer = &Timer_Task_TCB;
	*ppxTimerTaskStackBuffer = Timer_Task_Stack;
	*pulTimerTaskStackSize = configTIMER_TASK_STACK_DEPTH;
}

int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	uart_init(115200);
	LED_Init();
	
	BaseType_t xReturn = pdPASS;
	
	xReturn = xTaskCreate((TaskFunction_t)AppTaskCreate,
						  (const char*   )"AppTaskCreate",
						  (uint16_t      )512,
						  (void*		 )NULL,
						  (UBaseType_t   )1,
						  (TaskHandle_t* )&AppTaskCreate_Handle);
										
	if(xReturn == pdPASS) vTaskStartScheduler();
	else return -1;
	
	while (1);
  
}

