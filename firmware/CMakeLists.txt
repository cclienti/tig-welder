cmake_minimum_required(VERSION 3.13)

# initialize pico-sdk from GIT
# (note this can come from environment, CMake cache etc)
set(PICO_SDK_FETCH_FROM_GIT on)

# pico_sdk_import.cmake is a single file copied from this SDK
# note: this must happen before project()
include(pico_sdk_import.cmake)

project(my_project)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

# rest of your project

add_executable(tig_welder src/main.cpp)

# Add pico_stdlib library which aggregates commonly used features
target_include_directories(tig_welder PUBLIC include)
target_link_libraries(tig_welder pico_stdlib hardware_i2c)

# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(tig_welder)

# add uart
pico_enable_stdio_usb(tig_welder 1)
pico_enable_stdio_uart(tig_welder 0)
