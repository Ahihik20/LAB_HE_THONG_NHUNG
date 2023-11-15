// #include <stdio.h>
// #include <string.h>

// #include "freertos/FreeRTOS.h"
// #include "freertos/FreeRTOSConfig.h"
// #include "freertos/task.h"
// #include "driver/gpio.h"

// #define configUSE_PREEMPTION 1
// volatile uint32_t ulIdleCycleCount = 0UL;
// volatile uint32_t ulIdleTask1Count = 0UL;
// volatile uint32_t ulIdleTask2Count = 0UL;

// char s[1024] = {0};

// void vApplicationTickHook(void){

// }

// void vApplicationIdleHook(void) {
//     ulIdleCycleCount ++;
//     if(ulIdleCycleCount % 10 == 0){
//         vTaskGetRunTimeStats(s);
//         printf("%s\n",s);
//     }
// }

// void task1(void *pvParameter){
//     while (1)
//     {
//         printf("%ld\n",ulIdleCycleCount);
//         printf("task1: %ld\n", ulIdleTask1Count);
//         ulIdleTask1Count ++;
//         vTaskDelay(pdMS_TO_TICKS(5000));
//     }
    
// }

// void task2(void *pvParameter){
//     while (1)
//     {
//         printf("%ld\n",ulIdleCycleCount);
//         printf("task2: %ld\n", ulIdleTask2Count);
//         ulIdleTask2Count ++;
//         vTaskDelay(pdMS_TO_TICKS(1000));
//     }
    
// }

// void app_main(void)
// {
//     printf("configUSE_PREEMPTION = %d\n",configUSE_PREEMPTION);
//     printf("configUSE_TIME_SLICING = %d\n",configUSE_TIME_SLICING);
//     xTaskCreatePinnedToCore(&task1, "task1", 2048, NULL, 2, NULL,1);
//     xTaskCreatePinnedToCore(&task2, "task2", 2048, NULL, 0, NULL,0);
// }

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

// Variable to store idle time
uint64_t idleTime = 0;

// Custom idle task hook
void vApplicationIdleHook(void) {
    // Increment idle time
    idleTime++;
}

void cal(void *pvParameter){
    while (1) {
        // Calculate CPU utilization
        float cpuUtilization = 100.0 - (idleTime * 100.0 / configTICK_RATE_HZ);

        printf("CPU Utilization: %.2f%%\n", cpuUtilization);

        // Delay to control the printing rate
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void app_main() {
    // Start the FreeRTOS scheduler
    xTaskCreate(&cal, "cal", 2048, NULL, 1, NULL);
}


