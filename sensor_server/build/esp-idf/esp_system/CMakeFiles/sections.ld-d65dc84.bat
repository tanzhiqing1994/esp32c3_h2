@echo off
cd /D D:\software\ESP32\IDF5_3\sensor_server\build\esp-idf\esp_system || (set FAIL_LINE=2& goto :ABORT)
d:\TOOL\vs_esp_idf\Tools\python_env\idf5.3_py3.11_env\Scripts\python.exe D:/TOOL/vs_esp_idf/container/v5.3.1/esp-idf/tools/ldgen/ldgen.py --config D:/software/ESP32/IDF5_3/sensor_server/sdkconfig --fragments-list D:/TOOL/vs_esp_idf/container/v5.3.1/esp-idf/components/xtensa/linker.lf;D:/TOOL/vs_esp_idf/container/v5.3.1/esp-idf/components/esp_driver_gpio/linker.lf;D:/TOOL/vs_esp_idf/container/v5.3.1/esp-idf/components/esp_pm/linker.lf;D:/TOOL/vs_esp_idf/container/v5.3.1/esp-idf/components/esp_mm/linker.lf;D:/TOOL/vs_esp_idf/container/v5.3.1/esp-idf/components/spi_flash/linker.lf;D:/TOOL/vs_esp_idf/container/v5.3.1/esp-idf/components/esp_system/linker.lf;D:/TOOL/vs_esp_idf/container/v5.3.1/esp-idf/components/esp_system/app.lf;D:/TOOL/vs_esp_idf/container/v5.3.1/esp-idf/components/esp_common/common.lf;D:/TOOL/vs_esp_idf/container/v5.3.1/esp-idf/components/esp_common/soc.lf;D:/TOOL/vs_esp_idf/container/v5.3.1/esp-idf/components/esp_rom/linker.lf;D:/TOOL/vs_esp_idf/container/v5.3.1/esp-idf/components/hal/linker.lf;D:/TOOL/vs_esp_idf/container/v5.3.1/esp-idf/components/log/linker.lf;D:/TOOL/vs_esp_idf/container/v5.3.1/esp-idf/components/heap/linker.lf;D:/TOOL/vs_esp_idf/container/v5.3.1/esp-idf/components/soc/linker.lf;D:/TOOL/vs_esp_idf/container/v5.3.1/esp-idf/components/esp_hw_support/linker.lf;D:/TOOL/vs_esp_idf/container/v5.3.1/esp-idf/components/esp_hw_support/dma/linker.lf;D:/TOOL/vs_esp_idf/container/v5.3.1/esp-idf/components/esp_hw_support/ldo/linker.lf;D:/TOOL/vs_esp_idf/container/v5.3.1/esp-idf/components/freertos/linker_common.lf;D:/TOOL/vs_esp_idf/container/v5.3.1/esp-idf/components/freertos/linker.lf;D:/TOOL/vs_esp_idf/container/v5.3.1/esp-idf/components/newlib/newlib.lf;D:/TOOL/vs_esp_idf/container/v5.3.1/esp-idf/components/newlib/system_libs.lf;D:/TOOL/vs_esp_idf/container/v5.3.1/esp-idf/components/esp_driver_gptimer/linker.lf;D:/TOOL/vs_esp_idf/container/v5.3.1/esp-idf/components/esp_ringbuf/linker.lf;D:/TOOL/vs_esp_idf/container/v5.3.1/esp-idf/components/esp_driver_uart/linker.lf;D:/TOOL/vs_esp_idf/container/v5.3.1/esp-idf/components/app_trace/linker.lf;D:/TOOL/vs_esp_idf/container/v5.3.1/esp-idf/components/esp_event/linker.lf;D:/TOOL/vs_esp_idf/container/v5.3.1/esp-idf/components/esp_driver_pcnt/linker.lf;D:/TOOL/vs_esp_idf/container/v5.3.1/esp-idf/components/esp_driver_spi/linker.lf;D:/TOOL/vs_esp_idf/container/v5.3.1/esp-idf/components/esp_driver_mcpwm/linker.lf;D:/TOOL/vs_esp_idf/container/v5.3.1/esp-idf/components/esp_driver_ana_cmpr/linker.lf;D:/TOOL/vs_esp_idf/container/v5.3.1/esp-idf/components/esp_driver_dac/linker.lf;D:/TOOL/vs_esp_idf/container/v5.3.1/esp-idf/components/esp_driver_rmt/linker.lf;D:/TOOL/vs_esp_idf/container/v5.3.1/esp-idf/components/esp_driver_sdm/linker.lf;D:/TOOL/vs_esp_idf/container/v5.3.1/esp-idf/components/esp_driver_i2c/linker.lf;D:/TOOL/vs_esp_idf/container/v5.3.1/esp-idf/components/esp_driver_ledc/linker.lf;D:/TOOL/vs_esp_idf/container/v5.3.1/esp-idf/components/driver/twai/linker.lf;D:/TOOL/vs_esp_idf/container/v5.3.1/esp-idf/components/esp_phy/linker.lf;D:/TOOL/vs_esp_idf/container/v5.3.1/esp-idf/components/vfs/linker.lf;D:/TOOL/vs_esp_idf/container/v5.3.1/esp-idf/components/lwip/linker.lf;D:/TOOL/vs_esp_idf/container/v5.3.1/esp-idf/components/esp_netif/linker.lf;D:/TOOL/vs_esp_idf/container/v5.3.1/esp-idf/components/wpa_supplicant/linker.lf;D:/TOOL/vs_esp_idf/container/v5.3.1/esp-idf/components/esp_coex/linker.lf;D:/TOOL/vs_esp_idf/container/v5.3.1/esp-idf/components/esp_wifi/linker.lf;D:/TOOL/vs_esp_idf/container/v5.3.1/esp-idf/components/bt/linker_common.lf;D:/TOOL/vs_esp_idf/container/v5.3.1/esp-idf/components/bt/linker_rw_bt_controller.lf;D:/TOOL/vs_esp_idf/container/v5.3.1/esp-idf/components/esp_adc/linker.lf;D:/TOOL/vs_esp_idf/container/v5.3.1/esp-idf/components/esp_eth/linker.lf;D:/TOOL/vs_esp_idf/container/v5.3.1/esp-idf/components/esp_gdbstub/linker.lf;D:/TOOL/vs_esp_idf/container/v5.3.1/esp-idf/components/esp_psram/linker.lf;D:/TOOL/vs_esp_idf/container/v5.3.1/esp-idf/components/esp_lcd/linker.lf;D:/TOOL/vs_esp_idf/container/v5.3.1/esp-idf/components/espcoredump/linker.lf;D:/TOOL/vs_esp_idf/container/v5.3.1/esp-idf/components/ieee802154/linker.lf;D:/TOOL/vs_esp_idf/container/v5.3.1/esp-idf/components/openthread/linker.lf --input D:/software/ESP32/IDF5_3/sensor_server/build/esp-idf/esp_system/ld/sections.ld.in --output D:/software/ESP32/IDF5_3/sensor_server/build/esp-idf/esp_system/ld/sections.ld --kconfig D:/TOOL/vs_esp_idf/container/v5.3.1/esp-idf/Kconfig --env-file D:/software/ESP32/IDF5_3/sensor_server/build/config.env --libraries-file D:/software/ESP32/IDF5_3/sensor_server/build/ldgen_libraries --objdump D:/TOOL/vs_esp_idf/Tools/tools/xtensa-esp-elf/esp-13.2.0_20240530/xtensa-esp-elf/bin/xtensa-esp32-elf-objdump.exe || (set FAIL_LINE=3& goto :ABORT)
goto :EOF

:ABORT
set ERROR_CODE=%ERRORLEVEL%
echo Batch file failed at line %FAIL_LINE% with errorcode %ERRORLEVEL%
exit /b %ERROR_CODE%