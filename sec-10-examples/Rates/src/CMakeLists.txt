add_executable(${NAME}
        main.cpp
        Rates.cpp
        Digits.cpp
        Digits6x11.cpp
        PicoGraphics_ExtRGB888.cpp
        )

# Pull in our pico_stdlib which pulls in commonly used features
target_link_libraries(${NAME} 
	 pico_stdlib
     FreeRTOS-Kernel-Heap4 # FreeRTOS kernel and dynamic heap
     freertos_config #FREERTOS_PORT
     LWIP_PORT
     pico_cyw43_arch_lwip_sys_freertos
     coreHTTP
     urilib
     json_maker
     tiny_json
     wolfssl
     picow_wsclient
	 pico_graphics 
	 galactic_unicorn
	 SPNG
	)
	
target_include_directories(${NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
     )
     
if (NOT DEFINED ENV{WIFI_SSID})
	message(FATAL_ERROR "WIFI_SSID Environment variable not defined")
endif()
if (NOT DEFINED ENV{WIFI_PASSWORD})
	message(FATAL_ERROR "WIFI_PASSWORD Environment variable not defined")
endif()

if (NOT DEFINED ENV{EXCHANGERATEKEY})
	message(FATAL_ERROR "EXCHANGERATEKEY Environment variable not defined")
endif()


target_compile_definitions(${NAME} PRIVATE
    WIFI_SSID=\"$ENV{WIFI_SSID}\"
    WIFI_PASSWORD=\"$ENV{WIFI_PASSWORD}\"
    CYW43_HOST_NAME="DrJonEA"
    EXCHANGERATEKEY=\"$ENV{EXCHANGERATEKEY}\"
)

# create map/bin/hex file etc.
pico_add_extra_outputs(${NAME})

# enable usb output, disable uart output
pico_enable_stdio_usb(${NAME} 1)
pico_enable_stdio_uart(${NAME} 0)
