cmake_minimum_required(VERSION 3.12)

# Change your executable name to something creative!
set(NAME TestXML)

include(pico_sdk_import.cmake)


project(${NAME} C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(PICO_CXX_ENABLE_EXCEPTIONS 1)

# Initialize the SDK
pico_sdk_init()

SET(MXML_PATH "${CMAKE_CURRENT_LIST_DIR}/../../lib/mxml" CACHE STRING "Common Lib")
SET(MXML_PORT "${CMAKE_CURRENT_LIST_DIR}/port/mxml" CACHE STRING "Common Lib")
include(mxml.cmake)

add_subdirectory(src)

#Set up files for the release packages
install(CODE "execute_process(COMMAND $ENV{HOME}/bin/picoDeploy.sh ${CMAKE_CURRENT_BINARY_DIR}/src/${NAME}.elf)")

# Set up files for the release packages
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/src/${NAME}.uf2
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
)

set(CPACK_INCLUDE_TOPLEVEL_DIRECTORY OFF)
set(CPACK_GENERATOR "ZIP" "TGZ")
include(CPack)
