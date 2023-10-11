#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define BUTTON 17
#define STUDENT_ID_1 2014946
#define STUDENT_ID_2 2015107

int btn_cnt = 0;

void task1(void *pvParameter)
{
    while (1)
    {
        printf("%d %d\n",STUDENT_ID_1, STUDENT_ID_2);
         vTaskDelay (1000 / portTICK_PERIOD_MS ) ;
    }
    vTaskDelete(NULL);
}

void task2(void *pvParameter)
{
    esp_rom_gpio_pad_select_gpio(BUTTON);
    gpio_set_direction(BUTTON,GPIO_MODE_INPUT);
    gpio_set_pull_mode(BUTTON,GPIO_PULLUP_ONLY);
    while (1) // 
    {
        if (gpio_get_level(BUTTON) == 0)    btn_cnt++;
        else btn_cnt = 0;

        if (btn_cnt >= 3)    printf("ESP32\n");
        vTaskDelay (100 / portTICK_PERIOD_MS ) ;
    }
    vTaskDelete(NULL);
}

void app_main()
{
    xTaskCreate(&task1,"print_student_id",2048,NULL,0,NULL);
    xTaskCreate(&task2,"print_esp32",2048,NULL,1,NULL);
}
