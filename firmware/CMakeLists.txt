cmake_minimum_required(VERSION 3.13)

# Get the sdk from the submodule pico-sdk
include(pico-sdk/pico_sdk_init.cmake)

project(tig-welder-firmware)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

# rest of your project

add_executable(tig_welder
  src/main.cpp
  src/lcd_display.cpp
  src/rotary_encoder.cpp
  src/spi_adc.cpp
  src/buzzer.cpp)

# Generates header for pio
pico_generate_pio_header(tig_welder ${CMAKE_CURRENT_LIST_DIR}/pio/rotary_encoder.pio)

# Add pico_stdlib library which aggregates commonly used features
target_include_directories(tig_welder PUBLIC include)
target_link_libraries(tig_welder pico_stdlib hardware_i2c hardware_spi hardware_pio hardware_pwm)

# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(tig_welder)

# add uart
pico_enable_stdio_usb(tig_welder 1)
pico_enable_stdio_uart(tig_welder 0)
