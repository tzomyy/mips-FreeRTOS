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

void exampleTaskFunc(void *function) {

	while(1){
		HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_0);
		vTaskDelay(1000);
	}
}


void exampleInit() {
	xTaskCreate(exampleTaskFunc, "exampleTaskFunc", 128, NULL, 1, NULL);
}

