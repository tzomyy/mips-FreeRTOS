/*
 * example.c
 *
 *  Created on: Feb 6, 2023
 *      Author: Laptop
 */
#include "FreeRTOS.h"
#include "task.h"
#include "example.h"
#include "gpio.h"

TaskHandle_t controllerHandle, defferedHandle;

void defferedTask(void *param) {
	while (1) {
		ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
		HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_0);
	}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	if (GPIO_Pin == GPIO_PIN_0) {
		BaseType_t woken = pdFALSE;
		vTaskNotifyGiveFromISR(defferedHandle, &woken);
		portYIELD_FROM_ISR(woken);
	}
}

void exampleInit() {
	xTaskCreate(defferedTask, "defferedTask", 128, (void*) GPIO_PIN_0, 2,
			&defferedHandle);
}

