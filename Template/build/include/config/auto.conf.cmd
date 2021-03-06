deps_config := \
	/home/thuan/esp/esp-idf/components/app_trace/Kconfig \
	/home/thuan/esp/esp-idf/components/aws_iot/Kconfig \
	/home/thuan/esp/esp-idf/components/bt/Kconfig \
	/home/thuan/esp/esp-idf/components/driver/Kconfig \
	/home/thuan/esp/esp-idf/components/efuse/Kconfig \
	/home/thuan/esp/esp-idf/components/esp32/Kconfig \
	/home/thuan/esp/esp-idf/components/esp_adc_cal/Kconfig \
	/home/thuan/esp/esp-idf/components/esp_event/Kconfig \
	/home/thuan/esp/esp-idf/components/esp_http_client/Kconfig \
	/home/thuan/esp/esp-idf/components/esp_http_server/Kconfig \
	/home/thuan/esp/esp-idf/components/esp_https_ota/Kconfig \
	/home/thuan/esp/esp-idf/components/espcoredump/Kconfig \
	/home/thuan/esp/esp-idf/components/ethernet/Kconfig \
	/home/thuan/esp/esp-idf/components/fatfs/Kconfig \
	/home/thuan/esp/esp-idf/components/freemodbus/Kconfig \
	/home/thuan/esp/esp-idf/components/freertos/Kconfig \
	/home/thuan/esp/esp-idf/components/heap/Kconfig \
	/home/thuan/esp/esp-idf/components/libsodium/Kconfig \
	/home/thuan/esp/esp-idf/components/log/Kconfig \
	/home/thuan/esp/esp-idf/components/lwip/Kconfig \
	/home/thuan/esp/esp-idf/components/mbedtls/Kconfig \
	/home/thuan/esp/esp-idf/components/mdns/Kconfig \
	/home/thuan/esp/esp-idf/components/mqtt/Kconfig \
	/home/thuan/esp/esp-idf/components/nvs_flash/Kconfig \
	/home/thuan/esp/esp-idf/components/openssl/Kconfig \
	/home/thuan/esp/esp-idf/components/pthread/Kconfig \
	/home/thuan/esp/esp-idf/components/spi_flash/Kconfig \
	/home/thuan/esp/esp-idf/components/spiffs/Kconfig \
	/home/thuan/esp/esp-idf/components/tcpip_adapter/Kconfig \
	/home/thuan/esp/esp-idf/components/unity/Kconfig \
	/home/thuan/esp/esp-idf/components/vfs/Kconfig \
	/home/thuan/esp/esp-idf/components/wear_levelling/Kconfig \
	/home/thuan/esp/esp-idf/components/wifi_provisioning/Kconfig \
	/home/thuan/esp/esp-idf/components/app_update/Kconfig.projbuild \
	/home/thuan/esp/esp-idf/components/bootloader/Kconfig.projbuild \
	/home/thuan/esp/esp-idf/components/esptool_py/Kconfig.projbuild \
	/home/thuan/esp/esp-idf/components/partition_table/Kconfig.projbuild \
	/home/thuan/esp/esp-idf/Kconfig

include/config/auto.conf: \
	$(deps_config)

ifneq "$(IDF_TARGET)" "esp32"
include/config/auto.conf: FORCE
endif
ifneq "$(IDF_CMAKE)" "n"
include/config/auto.conf: FORCE
endif

$(deps_config): ;
