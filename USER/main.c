#include "stm32f4xx.h"
#include "delay.h"
#include "usart.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "timers.h"
#include "led.h"
#include "key.h"

eTaskState state;

static TaskHandle_t AppTaskCreate_Handle;
static TaskHandle_t LED1_Task_Handle;
static TaskHandle_t LED2_Task_Handle;
static TaskHandle_t Key_Task_Handle;
static TaskHandle_t Uart1_Task_Handle;

static TimerHandle_t xTimer_Key;

static SemaphoreHandle_t Semaphore_Uart1 = NULL;

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

static void Uart1_Task(void* parameter)
{
	while(1)
	{
		if(pdTRUE == xSemaphoreTake(Semaphore_Uart1,portMAX_DELAY))
		{
			LED0 = ~LED0;
		}
	}
}

BaseType_t xTimer_Key_Start_Flag;

static void Key_Task(void* parameter)
{
	while(1)
	{
		if(KEY == 0 && xTimer_Key_Start_Flag != pdTRUE)
		{
			if(xTimerReset(xTimer_Key, 0) == pdPASS) 
			{
				printf("xTimer_Key 定时器任务开启成功!\r\n");
				xTimer_Key_Start_Flag = pdTRUE;
			}
			else printf("xTimer_Key 定时器任务开启失败!\r\n");
		}
		
	}
}

void vTimer_Key_Callback(TimerHandle_t xTimer)
{
	printf("Timer！\r\n");
	
	if(KEY == 0 && pdTRUE == xSemaphoreTake(Semaphore_Uart1,portMAX_DELAY))
	{
		state = eTaskGetState(LED1_Task_Handle);
		if(state != eSuspended)
		{
			vTaskSuspend(LED1_Task_Handle);
			printf("LED1_Task任务挂起成功！");
		}
		else if(state == eSuspended)
		{
			vTaskResume(LED1_Task_Handle);
			printf("LED1_Task任务恢复成功！");
		}
	}
	xTimer_Key_Start_Flag = pdFALSE;
	
}

static void AppTaskCreate(void)
{
	BaseType_t xReturn = pdPASS;
	
	Semaphore_Uart1 = xSemaphoreCreateBinary();
	
	taskENTER_CRITICAL();	//进入临界区
	/*创建LED_Task任务*/
	xReturn = xTaskCreate((TaskFunction_t)LED1_Task,
						  (const char*   )"LED1_Task",
						  (uint16_t      )512,
						  (void*		 )NULL,
						  (UBaseType_t   )9,
						  (TaskHandle_t* )&LED1_Task_Handle);
										
	if(xReturn == pdPASS) printf("LED1_Task 任务创建成功!\r\n");
	else printf("LED1_Task 任务创建失败!\r\n");
						  
	xReturn = xTaskCreate((TaskFunction_t)LED2_Task,
						  (const char*   )"LED2_Task",
						  (uint16_t      )512,
						  (void*		 )NULL,
						  (UBaseType_t   )8,
						  (TaskHandle_t* )&LED2_Task_Handle);
										
	if(xReturn == pdPASS) printf("LED2_Task 任务创建成功!\r\n");
	else printf("LED2_Task 任务创建失败!\r\n");
						  
	xReturn = xTaskCreate((TaskFunction_t)Key_Task,
						  (const char*   )"Key_Task",
						  (uint16_t      )512,
						  (void*		 )NULL,
						  (UBaseType_t   )6,
						  (TaskHandle_t* )&Key_Task_Handle);
										
	if(xReturn == pdPASS) printf("Delete_Task 任务创建成功!\r\n");
	else printf("Delete_Task 任务创建失败!\r\n");
						  
	xReturn = xTaskCreate((TaskFunction_t)Uart1_Task,
						  (const char*   )"Uart1_Task",
						  (uint16_t      )512,
						  (void*		 )NULL,
						  (UBaseType_t   )7,
						  (TaskHandle_t* )&Uart1_Task_Handle);
										
	if(xReturn == pdPASS) printf("Uart1_Task 任务创建成功!\r\n");
	else printf("Uart1_Task 任务创建失败!\r\n");
	
						  
	xTimer_Key = xTimerCreate((const char*		)"Timer_Key",
							   (TickType_t		)20,
							   (BaseType_t		)pdFALSE,
							   (void * 			)0,
							   (TimerCallbackFunction_t)vTimer_Key_Callback);

    if(xTimer_Key == NULL) printf("xTimer_Key 定时器任务创建失败!\r\n");
	else printf("xTimer_Key 定时器任务创建成功!\r\n");
						  
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
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	uart1_init(115200);
	LED_Init();
	KEY_Init();
	
	BaseType_t xReturn = pdPASS;
	
	xReturn = xTaskCreate((TaskFunction_t)AppTaskCreate,
						  (const char*   )"AppTaskCreate",
						  (uint16_t      )512,
						  (void*		 )NULL,
						  (UBaseType_t   )0,
						  (TaskHandle_t* )&AppTaskCreate_Handle);
										
	if(xReturn == pdPASS) vTaskStartScheduler();
	else return -1;
	
	while (1);
  
}

void USART1_IRQHandler(void)                	//串口1中断服务程序
{
	u8 Res;
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	{
//		Res = USART_ReceiveData(USART1);
//		USART_SendData(USART1, Res);
		if(Semaphore_Uart1 != NULL)
		{
			Res = USART_ReceiveData(USART1);
			USART_SendData(USART1, Res);
			xSemaphoreGiveFromISR(Semaphore_Uart1, NULL);
		}
    } 
} 
