set(TEST_NAME "test")
set(PICO_CXX_ENABLE_EXCEPTIONS 1)

include(${FREERTOS_CONFIG_FILE_DIRECTORY}/freertos_unit.cmake)

# CppUTest
include(FetchContent)
FetchContent_Declare(
    CppUTest
    GIT_REPOSITORY https://github.com/cpputest/cpputest.git
    GIT_TAG        master # or use release tag, eg. v4.0
)
# Set this to ON if you want to have the CppUTests in your project as well.
set(TESTS OFF CACHE BOOL "Switch off CppUTest Test build")
set(CPPUTEST_STD_CPP_LIB_DISABLED OFF CACHE BOOL "OFF")
set(CPPUTEST_PLATFORM OFF CACHE BOOL "Providing FreeRTOS platform")
FetchContent_MakeAvailable(CppUTest)

add_executable(${TEST_NAME}
    test_main.cpp
    dummy.cpp
    http.cpp
    https.cpp
    
    UtestPlatform.cpp
)

# Pull in our pico_stdlib which pulls in commonly used features
target_link_libraries(${TEST_NAME} 
	 pico_stdlib
     FreeRTOS-Kernel-Heap4 # FreeRTOS kernel and dynamic heap
     freertos_unit #FREERTOS_PORT
     LWIP_PORT
     pico_cyw43_arch_lwip_sys_freertos
     coreHTTP
     urilib
     json_maker
     tiny_json
     wolfssl
     picow_wsclient
     CppUTest::CppUTest
     CppUTest::CppUTestExt
)
	
target_include_directories(${TEST_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
)
     
if (NOT DEFINED ENV{WIFI_SSID})
	message(FATAL_ERROR "WIFI_SSID Environment variable not defined")
endif()
if (NOT DEFINED ENV{WIFI_PASSWORD})
	message(FATAL_ERROR "WIFI_PASSWORD Environment variable not defined")
endif()


target_compile_definitions(${TEST_NAME} PRIVATE
    WIFI_SSID=\"$ENV{WIFI_SSID}\"
    WIFI_PASSWORD=\"$ENV{WIFI_PASSWORD}\"
    CYW43_HOST_NAME="DrJonEA"
)

target_compile_definitions(${TEST_NAME} PRIVATE
    PICO_CXX_DISABLE_ALLOCATION_OVERRIDES
    CPPUTEST_HAVE_EXCEPTIONS=1
    TEST_SERVER="vmu22a.local.jondurrant.com"
    TEST_PORT="5000"
    TEST_TLS_PORT="5443"
)

# create map/bin/hex file etc.
pico_add_extra_outputs(${TEST_NAME})

# enable usb output, disable uart output
pico_enable_stdio_usb(${TEST_NAME} 1)
pico_enable_stdio_uart(${TEST_NAME} 1)
target_compile_definitions(${TEST_NAME} PRIVATE
    PICO_DEFAULT_UART_RX_PIN=16
    PICO_DEFAULT_UART_TX_PIN=17
)