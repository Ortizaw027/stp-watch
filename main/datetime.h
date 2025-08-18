#pragma once
#include "esp_err.h"
#include <time.h>

esp_err_t datetime_init(void);          // Initializes SNTP and syncs time
time_t datetime_get_current_time(void); // Returns current timestamp
struct tm datetime_get_local_time(void); // Returns struct tm for local time
