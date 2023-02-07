/*
 * example.c
 *
 *  Created on: Feb 6, 2023
 *      Author: Laptop
 */

#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "example.h"
#include "gpio.h"

TaskHandle_t controllerHandle, defferedHandle;

void callBackDeffered(void *p1, uint32_t p2);

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	if (GPIO_Pin == GPIO_PIN_0) {
		BaseType_t woken = pdFALSE;
		xTimerPendFunctionCallFromISR(callBackDeffered, NULL, 0, &woken);
		portYIELD_FROM_ISR(woken);
	}
}

void exampleInit() {

}

void callBackDeffered(void *p1, uint32_t p2) {
	HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_0);
}

