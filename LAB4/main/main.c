#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
//length of queue
#define REQUEST_QUEUE_LENGTH 10

typedef struct {
    int requestType;
} Request;
//Check if the function receives the request or not
//flag = 1: functions receive the request and flag = 0: functions don't receive the request
int flag = 0;
//declare queue
QueueHandle_t requestQueue;
//send request to queue
void receptionTask(Request newRequest) {
    if (xQueueSend(requestQueue, &newRequest, pdMS_TO_TICKS(100)) != pdPASS) {
            printf("Request queue is full, request dropped!\n");
    }
    else{
        printf("Add a request to queue successfully!!!\n");
    }
}
//create request
void createRequest(void *pvParameter){
    while (1)
    {
        Request newRequest;
        newRequest.requestType = rand() % 4;
        receptionTask(newRequest);
        vTaskDelay(pdMS_TO_TICKS(1000*(rand()%4+1)));
    }
    vTaskDelete(NULL);
}
//handle function1
void functionalTask1(Request Param) {
    if(Param.requestType == 0) {
        printf("functionalTask1\n");
        flag = 1;
    }
}
//handle function2
void functionalTask2(Request Param) {
    if(Param.requestType == 1) {
        printf("functionalTask2\n");
        flag = 1;
    }
}
//handle function3
void functionalTask3(Request Param) {
    if(Param.requestType == 2) {
        printf("functionalTask3\n");
        flag = 1;
    }
}
//handle when no functions receives request
void functionalIgnoreTask(Request Param){
    printf("Ignore Task\n");
}
//receive request and handle
void handleTask(void *pvParameter){
    Request receivedRequest;
    while (1) {
        if (xQueueReceive(requestQueue, &receivedRequest, portMAX_DELAY) == pdTRUE) {
            functionalTask1(receivedRequest);
            functionalTask2(receivedRequest);
            functionalTask3(receivedRequest);
            if(flag == 0) functionalIgnoreTask(receivedRequest);
            flag = 0;
        }
        vTaskDelay(pdMS_TO_TICKS(1000*(rand()%4+1)));
    }
    vTaskDelete(NULL);
}

void app_main() {
    requestQueue = xQueueCreate(REQUEST_QUEUE_LENGTH, sizeof(Request));
    //create task
    xTaskCreate(createRequest, "Create Request", 2048, NULL, 2, NULL);
    xTaskCreate(handleTask, "Handle Task", 2048, NULL, 1, NULL);  
}

