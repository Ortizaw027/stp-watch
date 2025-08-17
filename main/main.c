#include <stdio.h>
#include "lvgl.h"
#include "UI.h"
#include "lvgl_tick.h"
#include "esp_log.h"
#include "lcd_driver.h"

#define DISP_HOR_RES    240
#define DISP_VER_RES    240
#define DISP_BUF_FACTOR  10
#define BYTES_PER_PIXEL   2

#define DISP_BUF_SIZE     ((DISP_HOR_RES * DISP_VER_RES) / DISP_BUF_FACTOR * BYTES_PER_PIXEL)

void my_flush_cb();

void app_main(void)
{

     esp_lcd_panel_handle_t panel_handle = lcd_init(); // Initializes lcd screen(GC9A01)
    
     lv_init(); //Needed before anything can be done with lvgl
     ESP_LOGI("LVGL", "LVGL initialized.");

     //Checks if lvgl is intialized correctly and outputs and error message if not
     if (!lv_is_initialized())
     {
        ESP_LOGE("LVGL", "LVGL failed to initialize.");
        return;
     }

     lv_display_t * display1 = lv_display_create(240, 240);

     display_context_t * ctx = malloc(sizeof(display_context_t));
     ctx -> panel = panel_handle;

     lv_display_set_user_data(display1, ctx);

     uint8_t *buf1 = heap_caps_malloc(DISP_BUF_SIZE, MALLOC_CAP_DMA);
     uint8_t *buf2 = heap_caps_malloc(DISP_BUF_SIZE, MALLOC_CAP_DMA);
     lv_display_set_buffers(display1, buf1, buf2, DISP_BUF_SIZE, LV_DISPLAY_RENDER_MODE_PARTIAL);

     lv_display_set_flush_cb(display1, my_flush_cb);

     init_lvgl_tick(); //Starts millisecond timer for lvgl tick

     my_ui();
     
     while(1){
      lv_timer_handler();
      vTaskDelay(pdMS_TO_TICKS(5));
     }
     
}


void my_flush_cb(lv_display_t * disp, const lv_area_t * area, uint8_t * px_buf)
{
  disp_update(disp, area, px_buf);

   lv_display_flush_ready(disp);
}