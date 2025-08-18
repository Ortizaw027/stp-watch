#include "datetime.h"
#include "esp_log.h"
#include "esp_sntp.h"
#include "lwip/err.h"
#include "lwip/sys.h"
#include "wifi.h"  
#include <sys/time.h>
#include <string.h>

static const char *TAG = "DATETIME";

// SNTP callback (optional, you can log sync events)
static void time_sync_cb(struct timeval *tv) {
    ESP_LOGI(TAG, "Time synchronized from SNTP");
}

// Initializes SNTP and waits for time to sync
esp_err_t datetime_init(void)
{
    // Make sure Wi-Fi is connected first
    if (connect_wifi() != ESP_OK) {
        ESP_LOGE(TAG, "Wi-Fi not connected. Cannot sync time.");
        return ESP_FAIL;
    }

    // Initialize SNTP
    esp_sntp_setoperatingmode(SNTP_OPMODE_POLL);
    esp_sntp_setservername(0, "pool.ntp.org");
    esp_sntp_set_time_sync_notification_cb(time_sync_cb);
    esp_sntp_init();

    // Wait for SNTP sync
    time_t now = 0;
    struct tm timeinfo = {0};
    int retry = 0;
    const int retry_count = 10;
    
    while (sntp_get_sync_status() == SNTP_SYNC_STATUS_RESET && ++retry < retry_count) {
        ESP_LOGI(TAG, "Waiting for SNTP time sync... (%d/%d)", retry, retry_count);
        vTaskDelay(2000 / portTICK_PERIOD_MS);
    }

    // Set timezone after SNTP sync
    setenv("TZ", "EST5EDT,M3.2.0/2,M11.1.0", 1);
    tzset();
    
    if (retry >= retry_count) {
        ESP_LOGW(TAG, "SNTP sync timeout, but continuing...");
    }

    time(&now);
    localtime_r(&now, &timeinfo);
    ESP_LOGI(TAG, "Current date/time: %04d-%02d-%02d %02d:%02d:%02d",
             timeinfo.tm_year + 1900, timeinfo.tm_mon + 1, timeinfo.tm_mday,
             timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);

    return ESP_OK;
}

// Returns current timestamp
time_t datetime_get_current_time(void)
{
    time_t now;
    time(&now);
    return now;
}

// Returns current local time struct
struct tm datetime_get_local_time(void)
{
    time_t now = datetime_get_current_time();
    struct tm local_time;
    localtime_r(&now, &local_time);
    return local_time;
}