#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

// Task function for Task 1
void task1(void *pvParameter) {
    while (1) {
        printf("%ld: Task 1 is running.\n", xTaskGetTickCount());
        //vTaskDelay(pdMS_TO_TICKS(1000));  // Simulate some work
        taskYIELD();
    }
}

// Task function for Task 2
void task2(void *pvParameter) {
    while (1) {
        printf("%ld: Task 2 is running.\n", xTaskGetTickCount());
        //vTaskDelay(pdMS_TO_TICKS(1000));  // Simulate some work
        taskYIELD();
    }
}
int count = 0;
int createTask1 = 0;
int createTask2 = 0;
// Task function for Task 3
void task3(void *pvParameter) {
    while (1) {
        // if(xTaskGetTickCount() == 200 && createTask1 == 0) {
        //     xTaskCreate(task1, "Task 1", 2048, NULL, 3, NULL);
        //     createTask1 = 1;
        // }
        // if(xTaskGetTickCount() == 300 && createTask2 == 0) {
        //     xTaskCreate(task2, "Task 2", 2048, NULL, 2, NULL);
        //     createTask2 = 1;
        // }
        // if(xTaskGetTickCount() % 100 == 0) printf("%ld: Task 3 is running.\n", xTaskGetTickCount());
        // if(xTaskGetTickCount() % 500 == 0) {
        //     printf("call task yield\n");
        //     taskYIELD();
        // }
        printf("task3\n");
        count ++;
        if(count == 10){
            count = 0;
            printf("yield\n");
            taskYIELD();
        }
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void app_main() {
    printf("configUSE_PREEMPTION = %d\n",configUSE_PREEMPTION);
     //xTaskCreate(task3, "Task 3", 2048, NULL, 1, NULL);
     //xTaskCreate(task3, "Task 3", 2048, NULL, 1, NULL);
    xTaskCreatePinnedToCore(task3, "Task 3", 2048, NULL, 1, NULL,0);
    // xTaskCreatePinnedToCore(task3, "Task 3", 2048, NULL, 4, NULL,1);
    xTaskCreatePinnedToCore(task1, "Task 1", 2048, NULL, 2, NULL,0);
    xTaskCreatePinnedToCore(task2, "Task 2", 2048, NULL, 3, NULL,0);
    // xTaskCreate(task1, "Task 1", 2048, NULL, 3, NULL);
    // xTaskCreate(task2, "Task 2", 2048, NULL, 2, NULL);
}