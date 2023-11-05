#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/queue.h"
#include "freertos/timers.h"

int counter_timer1 = 0;
int counter_timer2 = 0;

TimerHandle_t Timer_1;
TimerHandle_t Timer_2;

void func_CallBack(TimerHandle_t xTimer)
{
    TickType_t time = pdTICKS_TO_MS(xTaskGetTickCount()) / 1000;

    if (xTimer == Timer_1)
    {
        counter_timer1 ++;
        printf("ahihi: At %lds, print %d times", time, counter_timer1);
        if (counter_timer1 >= 10)
        {
            printf(" ===> Stop printing ahihi.");
            xTimerStop(xTimer, 0);
        }
    }
    if (xTimer == Timer_2)
    {
        counter_timer2 ++;
        printf("ihaha: At %lds, print %d times", time, counter_timer2);
        if (counter_timer2 >= 5)
        {
            printf(" ===> Stop printing ihaha.");
            xTimerStop(xTimer, 0);
        }
    }
    printf("\n");
}

void app_main()
{
    Timer_1 = xTimerCreate("AHIHI", pdMS_TO_TICKS(2000), pdTRUE, (void *)0, func_CallBack);
    Timer_2 = xTimerCreate("IHAHA", pdMS_TO_TICKS(3000), pdTRUE, (void *)1, func_CallBack);
    
    xTimerStart(Timer_1, 0);
    xTimerStart(Timer_2, 0);
}