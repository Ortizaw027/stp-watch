#include "lvgl.h"

//This is the lvgl code that creates the UI
void my_ui() 
{
        // --- Start LVGL UI setup here ---

    // Get active screen
    lv_obj_t * scr1 = lv_scr_act();

    // Set background color to deep blue
    lv_obj_set_style_bg_color(scr1, lv_color_hex(0x2104), LV_PART_MAIN);

    // Create a white label and center it
    lv_obj_t * label = lv_label_create(scr1);
    lv_label_set_text(label, "Hello world");
    lv_obj_set_style_text_color(label, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
    lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);

    // --- End LVGL UI setup ---
}