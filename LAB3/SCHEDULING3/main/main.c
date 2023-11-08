#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

int counter_task3 = 0;

void task1(void *pvParameter) {
    while (1) {
        printf("counter_task3 = %d : run task1.\n",counter_task3);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
    vTaskDelete(NULL);
}

void task2(void *pvParameter) {
    while (1) {
        printf("counter_task3 = %d : run task2.\n",counter_task3);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
    vTaskDelete(NULL);
}

void task3(void *pvParameter) {
    while (1) {
        counter_task3 ++;
        if(counter_task3  == 2){
            xTaskCreate(task2, "Task 2", 2048, NULL, 2, NULL);
        }
        if (counter_task3  == 4){
            xTaskCreate(task1, "Task 1", 2048, NULL, 3, NULL);
        }
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
    vTaskDelete(NULL);
}

void app_main() {
    printf("configUSE_PREEMPTION = %d\n",configUSE_PREEMPTION);
    printf("configUSE_TIME_SLICING = %d\n",configUSE_TIME_SLICING);
    xTaskCreate(task3, "Task 3", 2048, NULL, 1, NULL);
}