#include <stdio.h>
#include "esp_log.h"
#include "esp_err.h"
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "freertos/xtensa_api.h"
#include "freertos/task.h"
#include "soc/gpio_periph.h"
#include "driver/mcpwm.h"
#include "driver/periph_ctrl.h"
#include "sdkconfig.h"
#include "hal/mcpwm_hal.h"
#include "soc/soc_caps.h"
#include "hal/mcpwm_types.h"
#include "soc/mcpwm_caps.h"
#include "soc/soc.h"

void app_main()
{
    mcpwm_config_t mcpwm_conf=
    {
        .frequency=10000,
        .cmpr_a = 25,
        .cmpr_b=0,
        .duty_mode= 0,
        .counter_mode=1,

    };

    mcpwm_gpio_init(MCPWM_UNIT_0,MCPWM0A, GPIO_NUM_2);
    mcpwm_init(MCPWM_UNIT_0, MCPWM_TIMER_0, &mcpwm_conf);
    mcpwm_start(MCPWM_UNIT_0, MCPWM_TIMER_0 );
    while(1)
    {}
}