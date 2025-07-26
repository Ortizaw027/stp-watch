
#include "esp_log.h"
#include "esp_check.h"
#include "lvgl.h"
#include "lcd_driver.h"
#include "driver/gpio.h"
#include "esp_lcd_gc9a01.h"
#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_ops.h" 
#include "driver/spi_master.h"
#include "esp_idf_version.h"


#define PIN_NUM_LCD_CLK   10
#define PIN_NUM_LCD_MOSI  11
#define PIN_NUM_LCD_CS     9
#define PIN_NUM_LCD_DC     8
#define PIN_NUM_LCD_RST   14
#define LCD_H_RES         240
#define LCD_HOST          SPI2_HOST


void lcd_init()
{

    ESP_LOGI("LCD", "Turn on LCD Backlight");

     gpio_set_direction(GPIO_NUM_2, GPIO_MODE_OUTPUT);
     gpio_set_level(GPIO_NUM_2, 1);

    ESP_LOGI("LCD", "Initialize SPI bus");

    const spi_bus_config_t bus_config = GC9A01_PANEL_BUS_SPI_CONFIG(
            PIN_NUM_LCD_CLK,
            PIN_NUM_LCD_MOSI,
            LCD_H_RES * 80 * sizeof(uint16_t));

    ESP_ERROR_CHECK(spi_bus_initialize(LCD_HOST, &bus_config, SPI_DMA_CH_AUTO));

    ESP_LOGI("LCD", "Install panel IO");

    esp_lcd_panel_io_handle_t io_handle = NULL;

    const esp_lcd_panel_io_spi_config_t io_config = GC9A01_PANEL_IO_SPI_CONFIG(
        PIN_NUM_LCD_CS, 
        PIN_NUM_LCD_DC,
        NULL,
        NULL
    );

    ESP_ERROR_CHECK(esp_lcd_new_panel_io_spi((esp_lcd_spi_bus_handle_t)LCD_HOST, &io_config, &io_handle));

/**
 * Uncomment these lines if use custom initialization commands.
 * The array should be declared as "static const" and positioned outside the function.
 */
// static const gc9a01_lcd_init_cmd_t lcd_init_cmds[] = {
// //  {cmd, { data }, data_size, delay_ms}
//     {0xfe, (uint8_t []){0x00}, 0, 0},
//     {0xef, (uint8_t []){0x00}, 0, 0},
//     {0xeb, (uint8_t []){0x14}, 1, 0},
//     ...
// };

    ESP_LOGI("LCD", "Install GC9A01 panel driver");
    esp_lcd_panel_handle_t panel_handle = NULL;
    // gc9a01_vendor_config_t vendor_config = {  // Uncomment these lines if use custom initialization commands
    //     .init_cmds = lcd_init_cmds,
    //     .init_cmds_size = sizeof(lcd_init_cmds) / sizeof(gc9a01_lcd_init_cmd_t),
    // };
    const esp_lcd_panel_dev_config_t panel_config = {
        .reset_gpio_num = PIN_NUM_LCD_RST,      // Set to -1 if not use
#if ESP_IDF_VERSION < ESP_IDF_VERSION_VAL(5, 0, 0)
        .color_space = ESP_LCD_COLOR_SPACE_RGB,
#else
        .rgb_endian = LCD_RGB_ENDIAN_RGB,
#endif
        .bits_per_pixel = 16,                           // Implemented by LCD command `3Ah` (16/18)
        // .vendor_config = &vendor_config,            // Uncomment this line if use custom initialization commands
    };
    ESP_ERROR_CHECK(esp_lcd_new_panel_gc9a01(io_handle, &panel_config, &panel_handle));
    ESP_ERROR_CHECK(esp_lcd_panel_reset(panel_handle));
    ESP_ERROR_CHECK(esp_lcd_panel_init(panel_handle));
#if ESP_IDF_VERSION < ESP_IDF_VERSION_VAL(5, 0, 0)
    ESP_ERROR_CHECK(esp_lcd_panel_disp_off(panel_handle, false));
#else
    ESP_ERROR_CHECK(esp_lcd_panel_disp_on_off(panel_handle, true));
#endif


}

void lvgl_init()
{
 void lv_init(void);

if(!lv_is_initialized())
{
    ESP_LOGE("LVGL", "Install GC9A01 panel driver");
}


}