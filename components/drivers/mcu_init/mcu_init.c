#include <driver/spi_master.h>
#include <driver/gpio.h>

#include <esp_task_wdt.h>
#include <esp_log.h>

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "mcu_init.h"

static const char *TAG = "mcu_init";

typedef enum
{
    SPI_MISO_PIN = GPIO_NUM_19,
    SPI_MOSI_PIN = GPIO_NUM_23,
    SPI_CLK_PIN = GPIO_NUM_18,
} spi_pin_e;

/**
 * @brief Subscribe the current task to the watchdog and feed it once.
 */
static void subscribe_and_feed_watchdog(void)
{
    esp_task_wdt_config_t wdt_config = {
        .timeout_ms = WDT_TIMEOUT_MS,
        .trigger_panic = true,
    };
    esp_err_t err = esp_task_wdt_init(&wdt_config);
    if (err == ESP_ERR_INVALID_STATE)
    {
        ESP_LOGW(TAG, "Watchdog timer already initialised.");
    }
    else if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to initialise watchdog timer: %s", esp_err_to_name(err));
        abort();
    }

    if (esp_task_wdt_add(NULL) != ESP_OK)
    {
        ESP_LOGE(TAG, "Could not subscribe task to watchdog timer.");
        abort();
    }
    if (esp_task_wdt_reset() != ESP_OK)
    {
        ESP_LOGW(TAG, "Could not feed watchdog.");
    }
}

/**
 * @brief Initialise the SPI bus with the defined configuration.
 */
static void initialise_spi_bus(void)
{
    spi_bus_config_t bus_config = {
        .miso_io_num = SPI_MISO_PIN,
        .mosi_io_num = SPI_MOSI_PIN,
        .sclk_io_num = SPI_CLK_PIN,
        .quadwp_io_num = -1, // Not used
        .quadhd_io_num = -1, // Not used
        .max_transfer_sz = 4096,
    };

    esp_err_t err = spi_bus_initialize(SPI2_HOST, &bus_config, SPI_DMA_CH_AUTO);
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "Could not initialise SPI bus: %s, exiting.", esp_err_to_name(err));
        abort(); // Cannot continue without SPI bus.
    }

    ESP_LOGI(TAG, "SPI bus initialised successfully.");
}

void mcu_init(void)
{
    ESP_LOGI(TAG, "Starting system initialisation...");

    subscribe_and_feed_watchdog();

    initialise_spi_bus();

    esp_log_level_set("*", ESP_LOG_INFO);

    ESP_LOGI(TAG, "Finished system initialisation.");
}