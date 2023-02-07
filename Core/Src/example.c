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

TaskHandle_t controllerHandle, togglerHandle;

void exampleTaskFunc(void *param) {

	while (1) {
		HAL_GPIO_TogglePin(GPIOC, (uint32_t) param);

		for (int i = 0; i < 1000000; i++){
			i++;
		}
	}
}

void taskController(void *param){
	while(1){
		xTaskNotifyGive(togglerHandle);
		vTaskDelay(pdMS_TO_TICKS(1000));
	}

}

void taskToggler(void* param){
	while(1){
		ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
		HAL_GPIO_TogglePin(GPIOC, (uint32_t) param);
	}
}

void exampleInit() {
	xTaskCreate(exampleTaskFunc, "controller", 128, (void*) GPIO_PIN_0, 2,
			&controllerHandle);
	xTaskCreate(exampleTaskFunc, "toggler", 128, (void*) GPIO_PIN_1, 2,
			&togglerHandle);
}

