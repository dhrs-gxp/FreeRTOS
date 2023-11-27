#include "stm32f4xx.h"
#include "delay.h"
#include "usart.h"
#include "FreeRTOS.h"
#include "task.h"
#include "led.h"
#include "string.h"

static TaskHandle_t AppTaskCreate_Handle;
static TaskHandle_t LED_Task_Handle;

static StackType_t AppTaskCreate_Stack[128];
static StackType_t LED_Task_Stack[128];

static StaticTask_t AppTaskCreate_TCB;
static StaticTask_t LED_Task_TCB;

static void LED_Task(void* parameter)
{
	while(1)
	{
		LED0 = ~LED0;
		vTaskDelay(500);
	}
}

static void AppTaskCreate(void)
{
	taskENTER_CRITICAL();	//进入临界区
	/*创建LED_Task任务*/
	LED_Task_Handle = xTaskCreateStatic((TaskFunction_t)LED_Task,			//任务函数
										(const char*)"LED_Task",			//任务名称
										(uint32_t)128,						//任务堆栈大小
										(void*)NULL,						//传递给任务函数的参数
										(UBaseType_t)4,						//任务优先级
										(StackType_t*)LED_Task_Stack,		//任务堆栈
										(StaticTask_t*)&LED_Task_TCB);		//任务控制块
	if(LED_Task_Handle != NULL) printf("LED_Task 任务创建成功!\r\n");
	else if(LED_Task_Handle == NULL) printf("LED_Task 任务创建失败!\r\n");
	
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
	
	AppTaskCreate_Handle = xTaskCreateStatic((TaskFunction_t)AppTaskCreate,		//任务函数
										(const char*)"AppTaskCreate",			//任务名称
										(uint32_t)128,							//任务堆栈大小
										(void*)NULL,							//传递给任务函数的参数
										(UBaseType_t)3,							//任务优先级
										(StackType_t*)AppTaskCreate_Stack,		//任务堆栈
										(StaticTask_t*)&AppTaskCreate_TCB);		//任务控制块
										
	if(AppTaskCreate_Handle != NULL) vTaskStartScheduler();
	
	while (1);
  
}

