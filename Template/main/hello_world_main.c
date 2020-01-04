#include <stdio.h>

#include "esp_wifi.h"
#include "esp_interface.h"

#include <string.h>


void app_main()
{
    wifi_init_config_t my_config =  WIFI_INIT_CONFIG_DEFAULT();

    wifi_sta_config_t my_sta=
    {
        .ssid="lau101",
        .password="999999999",
        .channel=0,

    };

    wifi_config_t a=
    {
        .sta=my_sta,
    };
      


    esp_wifi_init(&my_config);
    esp_wifi_set_mode(WIFI_MODE_STA);
    esp_wifi_set_config(ESP_IF_WIFI_STA,&a);


    esp_wifi_start();

    while(1)
    {}
}