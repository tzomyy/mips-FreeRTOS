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

void callBackDeffered(void *p1, uint32_t p2);

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {

	uint32_t itemToQueue = GPIO_Pin;
	BaseType_t woken = pdFALSE;
	xQueueSendToBackFromISR(queueHandle, &itemToQueue, &woken);
	portYIELD_FROM_ISR(woken);

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

}

