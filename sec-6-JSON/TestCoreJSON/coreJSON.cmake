# Add library cpp files

if (NOT DEFINED COREJSON_PATH)
    set(COREJSON_PATH "${CMAKE_CURRENT_LIST_DIR}/lib/coreJSON")
endif()



add_library(coreJSON STATIC)
target_sources(coreJSON PUBLIC
    ${COREJSON_PATH}/source/core_json.c
    )


# Add include directory
target_include_directories(coreJSON PUBLIC 
    ${COREJSON_PATH}/source/include
)

target_link_libraries(coreJSON PUBLIC pico_stdlib)