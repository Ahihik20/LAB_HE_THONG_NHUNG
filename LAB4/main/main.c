#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

#define REQUEST_QUEUE_LENGTH 10

typedef struct {
    int requestType;
} Request;

int flag = 0;

QueueHandle_t requestQueue;

void receptionTask(Request newRequest) {
    if (xQueueSend(requestQueue, &newRequest, pdMS_TO_TICKS(100)) != pdPASS) {
            printf("Request queue is full, request dropped!\n");
    }
}

void createRequest(void *pvParameter){
    while (1)
    {
        Request newRequest;
        newRequest.requestType = rand() % 5;
        receptionTask(newRequest);
         vTaskDelay(pdMS_TO_TICKS(1000));
    }
    vTaskDelete(NULL);
}

void functionalTask1(Request Param) {
    if(Param.requestType == 0) {
        printf("functionalTask1\n");
        flag = 1;
    }
}

void functionalTask2(Request Param) {
    if(Param.requestType == 1) {
        printf("functionalTask2\n");
        flag = 1;
    }
}

void functionalTask3(Request Param) {
    if(Param.requestType == 2) {
        printf("functionalTask3\n");
        flag = 1;
    }
}

void functionalIgnoreTask(Request Param){
    printf("Ignore Task\n");
}

void handleTask(void *pvParameter){
    Request receivedRequest;
    while (1) {
        if (xQueueReceive(requestQueue, &receivedRequest, portMAX_DELAY) == pdTRUE) {
            //printf("%d\n",uxQueueMessagesWaiting(requestQueue));
            functionalTask1(receivedRequest);
            functionalTask2(receivedRequest);
            functionalTask3(receivedRequest);
            if(flag == 0) functionalIgnoreTask(receivedRequest);
            flag = 0;
        }
        //if(uxQueueMessagesWaiting(requestQueue) == REQUEST_QUEUE_LENGTH) vTaskDelay(pdMS_TO_TICKS(500));
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
    vTaskDelete(NULL);
}

void app_main() {
    requestQueue = xQueueCreate(REQUEST_QUEUE_LENGTH, sizeof(Request));

    xTaskCreate(createRequest, "Create Request", 2048, NULL, 2, NULL);
    xTaskCreate(handleTask, "Handle Task", 2048, NULL, 1, NULL);  
}

