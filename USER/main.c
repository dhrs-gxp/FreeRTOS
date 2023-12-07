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
static TaskHandle_t Key_Task_Handle;
static TaskHandle_t Uart1_Task_Handle;

static TimerHandle_t xTimer_Key;

static SemaphoreHandle_t Semaphore_Uart1 = NULL;

static void Uart1_Task(void* parameter)
{
	while(1)
	{
		if(pdTRUE == xSemaphoreTake(Semaphore_Uart1,portMAX_DELAY))
		{
			printf("这里是串口中断!\r\n");
		}
	}
}

uint8_t xTimer_Key_State = 0, xTimer_Enter_Flag = 0, Key_Pressed = 0;
uint8_t button_value = 0, k1_4 = 0, k5_8 = 0;

static void Key_Task(void* parameter)
{
	while(1)
	{
		if(Key_Pressed == 0 && xTimer_Enter_Flag == 0)
		{
			if((xTimer_Key_State == 0 && read_key5_8_Bits() != 0) || (xTimer_Key_State == 1 && read_key1_4_Bits() != 0))
			{
				xTimerReset(xTimer_Key, 0); 
				xTimer_Enter_Flag = 1; 
			}
			
			if(xTimer_Key_State == 1 && read_key5_8_Bits() == 0) xTimer_Key_State = 0;
		}
		vTaskDelay(2);
	}
}

void vTimer_Key_Callback(TimerHandle_t xTimer)
{
	switch(xTimer_Key_State)
	{
		case 0:
			k5_8 = read_key5_8_Bits();
			if(k5_8 != 0) 
			{
				KEY1_4_GPIO_Input_Config();
				KEY5_8_GPIO_Output_Config();
				set_key5_8_Bits();
				xTimer_Key_State = 1;
			}
			else xTimer_Key_State = 0;
			break;
		case 1:
			k1_4 = read_key1_4_Bits();
			if(k1_4 != 0)
			{ 
				button_value |= k5_8; 
				button_value |= k1_4; 
				Key_Pressed = 1;
			}
			KEY1_4_GPIO_Output_Config();
			KEY5_8_GPIO_Input_Config();
			set_key1_4_Bits();
			break;
		default: break;
	}
	xTimer_Enter_Flag = 0;
}


static void LED1_Task(void* parameter)
{
	while(1)
	{
		if(Key_Pressed == 1 && read_key5_8_Bits() == 0)
		{
			printf("%d\r\n", button_value); 
			if(button_value == 130)
			{
				LED1 = ~LED1;
				button_value = 0;
			}
			else button_value = 0;
			
			Key_Pressed = 0;
		}
		vTaskDelay(2);
	}
}

static void AppTaskCreate(void)
{
	BaseType_t xReturn = pdPASS;
	
	Semaphore_Uart1 = xSemaphoreCreateBinary();
	
	taskENTER_CRITICAL();	//进入临界区
	
	xReturn = xTaskCreate((TaskFunction_t)LED1_Task,
						  (const char*   )"LED1_Task",
						  (uint16_t      )512,
						  (void*		 )NULL,
						  (UBaseType_t   )8,
						  (TaskHandle_t* )&LED1_Task_Handle);
										
	if(xReturn == pdPASS) printf("LED1_Task 任务创建成功!\r\n");
	else printf("LED1_Task 任务创建失败!\r\n");
						  
	xReturn = xTaskCreate((TaskFunction_t)Key_Task,
						  (const char*   )"Key_Task",
						  (uint16_t      )512,
						  (void*		 )NULL,
						  (UBaseType_t   )7,
						  (TaskHandle_t* )&Key_Task_Handle);
										
	if(xReturn == pdPASS) printf("Delete_Task 任务创建成功!\r\n");
	else printf("Delete_Task 任务创建失败!\r\n");
						  
	xReturn = xTaskCreate((TaskFunction_t)Uart1_Task,
						  (const char*   )"Uart1_Task",
						  (uint16_t      )512,
						  (void*		 )NULL,
						  (UBaseType_t   )6,
						  (TaskHandle_t* )&Uart1_Task_Handle);
										
	if(xReturn == pdPASS) printf("Uart1_Task 任务创建成功!\r\n");
	else printf("Uart1_Task 任务创建失败!\r\n");
	
						  
	xTimer_Key = xTimerCreate((const char*		)"Timer_Key",
							   (TickType_t		)10,
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
	KEY1_4_GPIO_Output_Config();
	KEY5_8_GPIO_Input_Config();
	set_key1_4_Bits();
	
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
	//u8 Res;
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	{
		if(Semaphore_Uart1 != NULL)
		{
			//Res = USART_ReceiveData(USART1);
			//USART_SendData(USART1, Res);
			USART_ReceiveData(USART1);
			xSemaphoreGiveFromISR(Semaphore_Uart1, NULL);
		}
    } 
} 
