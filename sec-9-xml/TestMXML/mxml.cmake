# Add library cpp files

if (NOT DEFINED MXML_PATH)
    set(MXML_PATH "${CMAKE_CURRENT_LIST_DIR}/lib/mxml")
endif()

if (NOT DEFINED MXML_PORT)
	SET(MXML_PORT "${CMAKE_CURRENT_LIST_DIR}/port/mxml" CACHE STRING "Common Lib")
endif()


add_library(mxml STATIC)

target_sources(mxml PRIVATE
	${MXML_PATH}/mxml-attr.c
	${MXML_PATH}/mxml-entity.c
	${MXML_PATH}/mxml-file.c
	${MXML_PATH}/mxml-get.c
	${MXML_PATH}/mxml-index.c
	${MXML_PATH}/mxml-node.c
	${MXML_PATH}/mxml-private.c
	${MXML_PATH}/mxml-search.c
	${MXML_PATH}/mxml-set.c
	${MXML_PATH}/mxml-string.c
#	${MXML_PATH}/testmxml.c
	)


# Add include directory
target_include_directories(mxml PUBLIC 
    ${MXML_PATH}/
)

target_include_directories(mxml PRIVATE 
    ${MXML_PORT}/
)

# Add the standard library to the build
target_link_libraries(mxml PUBLIC pico_stdlib)