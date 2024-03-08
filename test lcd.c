#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/adc.h"
#include "hal/lcd_types.h"
#include <driver/i2c.h>
#include <driver/ledc.h>
// Define the I2C address of your device
#define EXAMPLE_I2C_HW_ADDR 0x3C






#define SDA_PIN GPIO_NUM_21 // Change as needed
#define SCL_PIN GPIO_NUM_22 // Change as needed

void app_main() {
    
    // Initialize the I2C master driver
    i2c_config_t i2c_conf = {
    .mode = I2C_MODE_MASTER, // I2C LCD is a master node
    .sda_io_num = SDA_PIN,
    .scl_io_num = SCL_PIN,
    .sda_pullup_en = GPIO_PULLUP_ENABLE,
    .scl_pullup_en = GPIO_PULLUP_ENABLE,
    .master.clk_speed = 10,
};
    i2c_param_config(I2C_NUM_0, &i2c_conf);
    i2c_driver_install(I2C_NUM_0, I2C_MODE_MASTER, 0, 0, 0, &i2c_conf);

    
    esp_lcd_panel_io_handle_t io_handle = NULL;
    esp_lcd_panel_io_i2c_config_t io_config = {
        .dev_addr = EXAMPLE_I2C_HW_ADDR,
        .control_phase_bytes = 1, // refer to LCD spec
        .dc_bit_offset = 6,       // refer to LCD spec
        .lcd_cmd_bits = 12,
        .lcd_param_bits = 12,
    };

    // Define the I2C configuration structure for SSD1306
    ssd1306_i2c_config_t ssd1306_i2c_config = {
        .dev_addr = EXAMPLE_I2C_HW_ADDR,
        .clk_speed = 100000,  // Adjust this value based on your device's requirements
    };
    
    ssd1306_handle_t ssd1306 = ssd1306_i2c_init(&ssd1306_i2c_config);

    // Clear the display
    ssd1306_clear_screen(ssd1306);

    // Display "Hello, World!" at coordinates (0,0)
    ssd1306_text(ssd1306, 0, 0, "Hello, World!", 12);

    // Update the display
    ssd1306_refresh(ssd1306);
    
}
 
