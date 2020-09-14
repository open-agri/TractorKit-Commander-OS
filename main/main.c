/**
 * @file main.c
 * @author Riccardo Persello (riccardo.persello@icloud.com)
 * @brief Main.
 * @version 0.1
 * @date 2020-09-11
 * 
 * 
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_freertos_hooks.h"
#include "freertos/semphr.h"
#include "esp_system.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "esp_ota_ops.h"
#include "esp_heap_trace.h"

#include "tkos.h"

#define TAG "main"

#define NUM_RECORDS 100
static heap_trace_record_t trace_record[NUM_RECORDS];

/**********************
 *   APPLICATION MAIN
 **********************/
void app_main() {

    ESP_ERROR_CHECK(heap_trace_init_standalone(trace_record, NUM_RECORDS));

    esp_log_level_set("*", ESP_LOG_INFO);

    esp_app_desc_t *desc = esp_ota_get_app_description();

    ESP_LOGI(TAG, "Commander boot. %s %s for ESP32 (compiled on %s %s) with ESP-IDF %s.", desc->project_name, desc->version, desc->date, desc->time, desc->idf_ver);
    
    /* If you want to use a task to create the graphic, you NEED to create a Pinned task
     * Otherwise there can be problem such as memory corruption and so on.
     * NOTE: When not using Wi-Fi nor Bluetooth you can pin the guiTask to core 0 */
    xTaskCreatePinnedToCore(guiTask, "main", 4096*10, NULL, 0, NULL, 1);
}