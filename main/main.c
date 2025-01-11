#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_task_wdt.h>
#include <esp_log.h>

#include "mcu_init.h"

static const char *TAG = "main";

void main_task()
{
    mcu_init();

    for (;;)
    {
        printf("Hello, world!\n");

        vTaskDelay(pdMS_TO_TICKS(50));
        if (esp_task_wdt_reset() != ESP_OK)
        {
            ESP_LOGW(TAG, "Could not feed watchdog.");
        }
    }
}

void app_main(void)
{
    xTaskCreate(main_task, "Main_Task", 2048, NULL, 10, NULL);
}