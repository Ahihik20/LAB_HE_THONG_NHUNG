#include <stdio.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/FreeRTOSConfig.h"
#include "freertos/task.h"
#include "driver/gpio.h"

volatile uint32_t idleTimeCore0 = 0;
volatile uint32_t idleTimeCore1 = 0;

// Custom idle task hook
void vApplicationIdleHook(void) {
    // Determine the current core
    UBaseType_t core = xPortGetCoreID();

    // Increment the idle time for the respective core
    if (core == 0) {
        idleTimeCore0++;
    } else {
        idleTimeCore1++;
    }
}

void task1(void *pvParameter){
    while (1)
    {
        printf("task1\n");
        vTaskDelay(pdMS_TO_TICKS(5000));
    }
    vTaskDelete(NULL);
}

void task2(void *pvParameter){
    while (1)
    {
        printf("task2\n");
        vTaskDelay(pdMS_TO_TICKS(1000)); 
    }
    vTaskDelete(NULL);
}

void calculate(void *pvParameter){
    // float cpuUtilizationCore0 = 100.0 - (idleTimeCore0 * 100.0 / configTICK_RATE_HZ);
    // float cpuUtilizationCore1 = 100.0 - (idleTimeCore1 * 100.0 / configTICK_RATE_HZ);

    // printf("CPU Utilization (Core 0): %.2f%%\n", cpuUtilizationCore0);
    // printf("CPU Utilization (Core 1): %.2f%%\n", cpuUtilizationCore1);
    while (1)
    {
        printf("%ld\n",idleTimeCore0);
        printf("%ld\n",idleTimeCore1);

        vTaskDelay(pdMS_TO_TICKS(1000));
    } 
}

void app_main(void)
{
    printf("configUSE_PREEMPTION = %d\n",configUSE_PREEMPTION);
    printf("configUSE_TIME_SLICING = %d\n",configUSE_TIME_SLICING);
    xTaskCreatePinnedToCore(&task1, "task1", 2048*3, NULL, 1, NULL,1);
    xTaskCreatePinnedToCore(&task2,"task2",2048*3,NULL,0,NULL,1);
    xTaskCreatePinnedToCore(&calculate,"calculate",2048*3,NULL,1,NULL,0);
}

