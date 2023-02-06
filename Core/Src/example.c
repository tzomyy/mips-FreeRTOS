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

void exampleTaskFunc(void *param) {

	while (1) {
		HAL_GPIO_TogglePin(GPIOC, (uint32_t) param);
		vTaskDelay(1000);
	}
}

void exampleInit() {
	xTaskCreate(exampleTaskFunc, "exampleTaskFunc0", 128, (void*) GPIO_PIN_0, 1,
			NULL);
	xTaskCreate(exampleTaskFunc, "exampleTaskFunc1", 128, (void*) GPIO_PIN_1, 1,
			NULL);
}

