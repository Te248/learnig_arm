
#include "driver/gpio.h"
#include "freertos/queue.h"
#include "string.h"
#include "freertos/task.h"
#include "driver/i2c.h"
#include "freertos/FreeRTOS.h"

#define ESP_SLAVE_ADDR 0x68 
#define WRITE_BIT  I2C_MASTER_WRITE /*!< I2C master write */
#define READ_BIT   I2C_MASTER_READ  /*!< I2C master read */
#define ACK_CHECK_EN   0x1     /*!< I2C master will check ack from slave*/
#define ACK_CHECK_DIS  0x0     /*!< I2C master will not check ack from slave */
#define ACK_VAL    0x0         /*!< I2C ack value */
#define NACK_VAL   0x1         /*!< I2C nack value */

uint8_t second,minute,hour,day,date,month,year;

int bcd_to_dec(uint8_t number)
{
    return((number/16*10)+(number%16));
}
int dec_to_bcd(uint8_t number)
{
    return ((number/10*16)+(number%10));
}

static esp_err_t i2c_master_write_slave(i2c_port_t i2c_num, uint8_t *data_wr, size_t size)
{
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    TEST_ESP_OK(i2c_master_write_byte(cmd, ( ESP_SLAVE_ADDR << 1 ) | WRITE_BIT, ACK_CHECK_EN));
    TEST_ESP_OK(i2c_master_write(cmd, data_wr, size, ACK_CHECK_EN));
    TEST_ESP_OK(i2c_master_stop(cmd));
    esp_err_t ret = i2c_master_cmd_begin(i2c_num, cmd, 5000 / portTICK_RATE_MS);
    i2c_cmd_link_delete(cmd);
    return ret;
}
static esp_err_t i2c_master_read_slave(i2c_port_t i2c_num, uint8_t start_add, uint8_t *data_r, size_t size)
{
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    TEST_ESP_OK(i2c_master_write_byte(cmd, ( ESP_SLAVE_ADDR << 1 ) | READ_BIT, ACK_CHECK_EN));
    TEST_ESP_OK(i2c_master_write_byte(cmd, start_add, ACK_CHECK_EN));
    TEST_ESP_OK(i2c_master_read(cmd, data_r, size, ACK_CHECK_EN));
    TEST_ESP_OK(i2c_master_stop(cmd));
    esp_err_t ret = i2c_master_cmd_begin(i2c_num, cmd, 5000 / portTICK_RATE_MS);
    i2c_cmd_link_delete(cmd);
    return ret;
}
void app_main()
{
    i2c_config_t i2c_config =
    {
        .mode=I2C_MODE_MASTER,    // mode
        .sda_io_num=GPIO_NUM_18,     //SDA pin 
        .sda_pullup_en=GPIO_PULLUP_ENABLE, //R kéo lện
        .scl_io_num=GPIO_NUM_19,       // SCL pin
        .scl_pullup_en=GPIO_PULLUP_ENABLE,  //R kéo lên
        .master.clk_speed=100000,/// clock chế độ master (coi datasheet của slave)

    };
    TEST_ESP_OK(i2c_param_config(I2C_NUM_1,&i2c_config));
    // 1 cho master , 0 cho slave

    TEST_ESP_OK(i2c_driver_install(I2C_NUM_1,I2C_MODE_MASTER,1024,1024, 0));

    TEST_ESP_OK(i2c_set_data_mode(I2C_NUM_1, I2C_DATA_MODE_MSB_FIRST, I2C_DATA_MODE_MSB_FIRST));
/////////////////////////////////////////////////
    uint8_t *data_write = (uint8_t *) malloc(256);
    uint8_t *data_read = (uint8_t *) malloc(256);

    for(int i=0; i<7;i++)
    {
        data_write[0]=0x00|dec_to_bcd(i);
        data_write[1]=dec_to_bcd(0x00);
        i2c_master_write_slave(I2C_NUM_1, data_write, 2);
    }
    while(1)
    {
        i2c_master_read_slave(I2C_NUM_1, 0x00,data_read,7);
        second=bcd_to_dec(data_read[0] & 0x7F);
        minute=bcd_to_dec(data_read[1]);
        hour=bcd_to_dec(data_read[2] & 0x3F);
        day=bcd_to_dec(data_read[3]);
        date=bcd_to_dec(data_read[4]);
        month=bcd_to_dec(data_read[5]);
        year=bcd_to_dec(data_read[6]);       
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        
    }
}
