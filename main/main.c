#include <stdio.h>
#include "lvgl.h"
#include "esp_log.h"
#include "esp_timer.h"
#include "lcd_driver.h"

#define DISP_HOR_RES    240
#define DISP_VER_RES    240
#define DISP_BUF_FACTOR  10
#define BYTES_PER_PIXEL   2

uint32_t my_millis(void);
void my_flush_cb();

void app_main(void)
{

     esp_lcd_panel_handle_t panel_handle = lcd_init(); // Initializes lcd screen
    
     lv_init(); //Needed before anything can be done with lvgl

     //Checks if lvgl is intialized correctly and outputs and error message if not
     if (!lv_is_initialized())
     {
        ESP_LOGE("LVGL", "LVGL failed to initialize.");
        return;
     }

     lv_tick_set_cb(my_millis);

     lv_display_t * display1 = lv_display_create(240, 240);

     display_context_t * ctx = malloc(sizeof(display_context_t));
     ctx -> panel = panel_handle;

     lv_display_set_user_data(display1, ctx);

     static uint8_t buf[DISP_HOR_RES * DISP_VER_RES / DISP_BUF_FACTOR * BYTES_PER_PIXEL];
     lv_display_set_buffers(display1, buf, NULL, sizeof(buf), LV_DISPLAY_RENDER_MODE_FULL);

     lv_display_set_flush_cb(display1, my_flush_cb);

         // --- Start LVGL UI setup here ---

    // Get active screen
    lv_obj_t * scr = lv_scr_act();

    // Set background color to deep blue
    lv_obj_set_style_bg_color(scr, lv_color_hex(0x003a57), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(scr, LV_OPA_COVER, LV_PART_MAIN);

    // Create a white label and center it
    lv_obj_t * label = lv_label_create(scr);
    lv_label_set_text(label, "Hello world");
    lv_obj_set_style_text_color(label, lv_color_hex(0xffffff), LV_PART_MAIN);
    lv_obj_align(label, LV_ALIGN_CENTER, 0, 1);

    // --- End LVGL UI setup ---

     while(1){
      lv_timer_handler();
      vTaskDelay(pdMS_TO_TICKS(5));
     }
     
}

uint32_t my_millis()
{
   return esp_timer_get_time() / 1000;
}

       
  
void my_flush_cb(lv_display_t * disp, const lv_area_t * area, uint8_t * px_buf)
{
  disp_update(disp, area, px_buf);

   lv_display_flush_ready(disp);
}