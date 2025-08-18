#include "screen.h"
#include "labels.h"
#include "time_sync.h"
#include "lvgl.h"

static lv_obj_t *time_label = NULL;
static lv_obj_t *date_label = NULL;

//Timer callback
static void timer_cb(lv_timer_t *t) {
    update_time_label(time_label, date_label);
}

//Update labels immediately
void update_home_screen_time(void)
{
    update_time_label(time_label, date_label);
}

void create_home_screen(void) {
    lv_obj_t *scr = lv_scr_act();
    lv_obj_set_style_bg_color(scr, lv_color_hex(0x2104), LV_PART_MAIN);

    // Create labels
    time_label = create_time_label(scr);
    date_label = create_date_label(scr);

    // Update immediately
    update_time_label(time_label, date_label);

    // Create timer for updating every minute
    lv_timer_create(timer_cb, 60000, NULL);
}
