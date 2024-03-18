# Add library cpp files

if (NOT DEFINED MINIML_PATH)
    set(MINIML_PATH "${CMAKE_CURRENT_LIST_DIR}/lib/miniML-Parser")
endif()



add_library(miniML STATIC)

target_sources(miniML PUBLIC
	${MINIML_PATH}/src/parse_xml.c
	${MINIML_PATH}/src/xml_content.c
	)


# Add include directory
target_include_directories(miniML PUBLIC 
    ${MINIML_PATH}/src
)

# Add the standard library to the build
target_link_libraries(miniML PUBLIC pico_stdlib)