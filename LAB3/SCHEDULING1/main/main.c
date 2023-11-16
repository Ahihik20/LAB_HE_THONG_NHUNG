#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
//task1 print every 5 seconds
void task1(void *pvParameter){
    while (1)
    {
        printf("task1\n");
        vTaskDelay(pdMS_TO_TICKS(5000));
    }
    vTaskDelete(NULL);
}
//task2 print every 1 second
void task2(void *pvParameter){
    while (1)
    {
        printf("task2\n");
        vTaskDelay(pdMS_TO_TICKS(1000)); 
    }
    vTaskDelete(NULL);
}

void app_main(void)
{
    printf("configUSE_PREEMPTION = %d\n",configUSE_PREEMPTION);
    printf("configUSE_TIME_SLICING = %d\n",configUSE_TIME_SLICING);
    //create task1
    xTaskCreate(&task1, "task1", 2048, NULL, 1, NULL);
    //create task2
    xTaskCreate(&task2,"task2",2048,NULL,0,NULL);
}