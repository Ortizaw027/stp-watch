#include "lvgl.h"
#include "datetime.h"  // Include datetime functions
#include <stdio.h>

// Private time label (not exposed to main.c)
static lv_obj_t *time_label = NULL;

// Private function to update time display
static void update_time_display(lv_timer_t *timer)
{
    if (time_label != NULL) {
        struct tm local_time = datetime_get_local_time();
        static char time_str[64];
        
        // Format: Weekday, day Month (e.g., Monday, 18 Aug)
        strftime(time_str, sizeof(time_str), "%02H:%M:%S\n%A, %d %b", &local_time);
        
        lv_label_set_text(time_label, time_str);
    }
}

//This is the lvgl code that creates the UI
void my_ui()
{
    // --- Start LVGL UI setup here ---
    // Get active screen
    lv_obj_t * scr1 = lv_scr_act();
    // Set background color to deep blue
    lv_obj_set_style_bg_color(scr1, lv_color_hex(0x2104), LV_PART_MAIN);
    
    
    // Create time label
    time_label = lv_label_create(scr1);
    lv_label_set_text(time_label, "Syncing time...");
    lv_obj_set_style_text_color(time_label, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
    lv_obj_set_style_text_align(time_label, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_align(time_label, LV_ALIGN_CENTER, 0, 0);  // Position below the "Hello world" label
    
    // Create timer to update time display every second (handled internally in UI)
    lv_timer_create(update_time_display, 1000, NULL);
    
    // --- End LVGL UI setup ---
}


