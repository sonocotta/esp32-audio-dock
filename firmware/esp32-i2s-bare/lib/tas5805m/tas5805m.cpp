#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "nvs.h"
#include "nvs_flash.h"
#include "esp_system.h"
#include "esp_log.h"

#include "driver/i2c.h"
#include "tas5805m.hpp"

void tas5805m::begin()
{
    /* sound is ready */
    log_d("I2S is ready, setup of the audio amp begin");
    vTaskDelay(1000 / portTICK_RATE_MS);

    /* set PDN to 1 */
    gpio_set_level(TAS5806M_GPIO_PDN, 1);
    vTaskDelay(100 / portTICK_RATE_MS);

    log_i("Setting to HI Z");
    ESP_ERROR_CHECK(_write_byte(0x03, 0x02));
    vTaskDelay(100 / portTICK_RATE_MS);

    log_i("Setting to PLAY");
    ESP_ERROR_CHECK(_write_byte(0x03, 0x03));

    vTaskDelay(100 / portTICK_RATE_MS);

    int ret;
    uint8_t h70 = 0, h71 = 0, h72 = 0;
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, TAS5806M_ADDRESS << 1 | WRITE_BIT, ACK_CHECK_EN);
    i2c_master_write_byte(cmd, 0x70, ACK_CHECK_EN);
    i2c_master_stop(cmd);
    ret = i2c_master_cmd_begin(I2C_TAS5806M_MASTER_NUM, cmd, 1000 / portTICK_RATE_MS);
    i2c_cmd_link_delete(cmd);
    if (ret != ESP_OK)
    {
        log_e("I2C ERROR");
    }
    vTaskDelay(1 / portTICK_RATE_MS);
    cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, TAS5806M_ADDRESS << 1 | READ_BIT, ACK_CHECK_EN);
    i2c_master_read_byte(cmd, &h70, ACK_VAL);
    i2c_master_read_byte(cmd, &h71, ACK_VAL);
    i2c_master_read_byte(cmd, &h72, NACK_VAL);
    i2c_master_stop(cmd);
    ret = i2c_master_cmd_begin(I2C_TAS5806M_MASTER_NUM, cmd, 1000 / portTICK_RATE_MS);
    i2c_cmd_link_delete(cmd);

    log_d("0x70 Register: %d", h70);
    log_d("0x71 Register: %d", h71);
    log_d("0x72 Register: %d", h72);
}

esp_err_t tas5805m::init()
{
    /* Register the PDN pin as output and write 1 to enable the TAS chip */
    gpio_config_t io_conf;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = TAS5806M_GPIO_PDN_MASK;
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
    gpio_config(&io_conf);
    gpio_set_level(TAS5806M_GPIO_PDN, 0);
    vTaskDelay(20 / portTICK_RATE_MS);
    gpio_set_level(TAS5806M_GPIO_PDN, 1);
    vTaskDelay(200 / portTICK_RATE_MS);

    /* initialize I2C to drive the TAS5806M */
    // ret = i2c_master_init();
    // if (ret != ESP_OK)
    // {
    //     ESP_LOGE(TAS5806M_TAG, "I2C could not be initialized.");
    //     return ret;
    // }

    return ESP_OK;
}

esp_err_t tas5805m::_read(uint8_t register_name, uint8_t *data_rd, size_t size)
{
    if (size == 0)
    {
        return ESP_OK;
    }
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (TAS5806M_ADDRESS << 1) | READ_BIT, ACK_CHECK_EN);
    i2c_master_write_byte(cmd, register_name, ACK_CHECK_EN);
    if (size > 1)
    {
        i2c_master_read(cmd, data_rd, size - 1, ACK_VAL);
    }
    i2c_master_read_byte(cmd, data_rd + size - 1, NACK_VAL);
    i2c_master_stop(cmd);
    esp_err_t ret = i2c_master_cmd_begin(I2C_TAS5806M_MASTER_NUM, cmd, 1000 / portTICK_RATE_MS);
    i2c_cmd_link_delete(cmd);
    return ret;
}

esp_err_t tas5805m::_write_byte(uint8_t register_name, uint8_t value)
{
    esp_err_t ret;
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, TAS5806M_ADDRESS << 1 | WRITE_BIT, ACK_CHECK_EN);
    i2c_master_write_byte(cmd, register_name, ACK_CHECK_EN);
    i2c_master_write_byte(cmd, value, ACK_CHECK_EN);
    i2c_master_stop(cmd);
    ret = i2c_master_cmd_begin(I2C_TAS5806M_MASTER_NUM, cmd, 1000 / portTICK_RATE_MS);
    i2c_cmd_link_delete(cmd);

    return ret;
}
