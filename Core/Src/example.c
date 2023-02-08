/*
 * example.c
 *
 *  Created on: Feb 6, 2023
 *      Author: Laptop
 */

#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "queue.h"
#include "example.h"
#include "gpio.h"

TaskHandle_t controllerHandle, defferedHandle;
QueueHandle_t queueHandle;
TimerHandle_t timer1Handle, timer2Handle;

void callBackDeffered(void *p1, uint32_t p2);

void callBack(TimerHandle_t timerHandle) {
	uint32_t GPIO_Pin = (uint32_t) pvTimerGetTimerID(timerHandle);
	HAL_GPIO_TogglePin(GPIOC, GPIO_Pin);
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	if (GPIO_Pin == GPIO_PIN_2 || GPIO_Pin == GPIO_PIN_3) {
		uint32_t itemToQueue = GPIO_Pin;
		BaseType_t woken = pdFALSE;
		xQueueSendToBackFromISR(queueHandle, &itemToQueue, &woken);
		portYIELD_FROM_ISR(woken);
	}
}

void taskToggler(void *param) {
	uint32_t bufferForPinIndex;

	while (1) {
		xQueueReceive(queueHandle, &bufferForPinIndex, portMAX_DELAY);
		HAL_GPIO_TogglePin(GPIOC, bufferForPinIndex);
	}

}

void exampleInit() {
	queueHandle = xQueueCreate(10, sizeof(uint32_t));
	xTaskCreate(taskToggler, "taskToggler", 128, NULL, 1, NULL);

	timer1Handle = xTimerCreate("timer1s", pdMS_TO_TICKS(1000), pdTRUE, (void*) GPIO_PIN_0,
			&callBack);
	timer2Handle = xTimerCreate("timer2s", pdMS_TO_TICKS(2000), pdTRUE, (void*) GPIO_PIN_1,
			&callBack);

	xTimerStart(timer1Handle, portMAX_DELAY);
	xTimerStart(timer2Handle, portMAX_DELAY);
}

