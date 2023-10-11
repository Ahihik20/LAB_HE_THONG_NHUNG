#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

QueueHandle_t school;

typedef struct
{
    int ID;
    int score;
    int error;
}Student;

void reception(void* pvParameter){
    Student data_send;
    int id = 0;
    while (1)
    {
        data_send.ID = id;
        id ++;
        data_send.score = rand() % 15;
        xQueueSend(school,&data_send, portMAX_DELAY);
        printf("Add Student: %d and Score: %d into queue\n",data_send.ID, data_send.score);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
    
}

void function1(void* pvParameter){
    Student data_receive;
    while (1)
    {
        if(xQueueReceive(school,&data_receive,portMAX_DELAY)){
            if(data_receive.score>=8 && data_receive.score<=10){
                printf("Student %d: A\n",data_receive.ID);
            }
            else if(data_receive.score>=5 && data_receive.score<8){
                printf("Student %d: B\n",data_receive.ID);
            }
            else if(data_receive.score>=0 && data_receive.score<5){
                printf("Student %d: C\n",data_receive.ID);
            }
            else{
                printf("Ignore Student: %d\n", data_receive.ID);
            }
        }
        else{
            printf("Ignore Student: %d\n", data_receive.ID);
        }
    }  
}

void app_main()
{
    school = xQueueCreate(10, sizeof(Student));
    xTaskCreate(&reception, "reception",2048,NULL,2,NULL);
    xTaskCreate(&function1, "function1",2048,NULL,1,NULL);
}
