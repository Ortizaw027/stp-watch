#pragma once

#include "esp_lcd_panel_io.h"
 
/*
* Initailzes the GC9A01 LCD display,
* These fucntion set up SPI, configure GPIOs, intializes the panel and LVGL, as well as sets up the.
*/
typedef struct
{
   esp_lcd_panel_handle_t panel;
} display_context_t;

esp_lcd_panel_handle_t lcd_init(void);

void disp_update(lv_display_t * disp, const lv_area_t * area, uint8_t * px_buf);
