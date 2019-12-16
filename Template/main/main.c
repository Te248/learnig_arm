
#include "driver/gpio.h"
#include "driver/uart.h"
#include "freertos/queue.h"
#include "string.h"
#include "freertos/task.h"

#define UART1 (UART_NUM_1)
#define UART0 (UART_NUM_0)
#define UART2 (UART_NUM_2)

#define UART2_RX_PIN (GPIO_NUM_16)
#define UART2_TX_PIN (GPIO_NUM_17)

#define UART1_RX_PIN (GPIO_NUM_22)
#define UART1_TX_PIN (GPIO_NUM_23)

#define UART0_RX_PIN (GPIO_NUM_3)
#define UART0_TX_PIN (GPIO_NUM_1)

#define UART_BAUND_115200 (115200)
#define UART_BAUND_9600 (9600)

#define BUF_SIZE (100)

uint32_t Store[256];


void app_main()
{
    ////////////cấu hình uart/////////////////
    uart_config_t  uart_config = 
    {
        .baud_rate = UART_BAUND_115200,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
    };
//////////////////chọn UART và kiểm tra cấu hình có lỗi không////////
    ESP_ERROR_CHECK(uart_param_config(UART1, &uart_config));
    ///////////////chọn chân Tx, Rx//////////
    ESP_ERROR_CHECK(uart_set_pin(UART1,UART1_TX_PIN,UART1_RX_PIN,0,0));
    //////////////////chọn buffer cho Tx bộ đệm Tx, Rx///////////////
    ESP_ERROR_CHECK(uart_driver_install(UART1, BUF_SIZE * 2, BUF_SIZE * 2, 20, NULL, 0));
//////////////////////////////////////////////

    char* data_send = (char *) malloc(256);
    char* data_receive = (char *) malloc(256);
    char message[15]="hello \n\r";
    data_send=message;
    //int *a ; a="hdfat"//a đang trõ tới chuỗi
    while(1)
    {
        
        uart_write_bytes(UART1, (const char*) data_send,strlen(data_send));
        uart_wait_tx_done(UART1, 0);
        // đợi chuyền xong////
        //////////////////////////////////////////
        uart_read_bytes(UART1,(uint8_t *) data_receive, 20,0);
        printf("\n\r");
        for (int i=0;i<20;i++)
        {
            if(((*(data_receive+i)>=48)&&(*(data_receive+i)<=57))||((*(data_receive+i)>=97)&&(*(data_receive+i)<=122))||((*(data_receive+i)>=65)&&(*(data_receive+i)<=90)))
             {
                 printf("%c",*(data_receive+i));
             }
             else
             {
                 printf(" ");
             }
             
        }
        printf("\n\r");
        uart_flush(UART1);
        
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        
    }
}
