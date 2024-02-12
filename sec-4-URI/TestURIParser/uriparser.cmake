# Add library cpp files

if (NOT DEFINED URIPARSER_PATH)
    set(URIPARSER_PATH "${CMAKE_CURRENT_LIST_DIR}/lib/uriparser")
endif()

if (NOT DEFINED URIPARSER_PORT)
    set(URIPARSER_PORT "${CMAKE_CURRENT_LIST_DIR}/port/uriparser")
endif()


add_library(uriparser STATIC)
target_sources(uriparser PUBLIC
    ${URIPARSER_PATH}/src/UriCommon.c
    ${URIPARSER_PATH}/src/UriCommon.h
    ${URIPARSER_PATH}/src/UriCompare.c
    ${URIPARSER_PATH}/src/UriEscape.c
    ${URIPARSER_PATH}/src/UriFile.c
    ${URIPARSER_PATH}/src/UriIp4Base.c
    ${URIPARSER_PATH}/src/UriIp4Base.h
    ${URIPARSER_PATH}/src/UriIp4.c
    ${URIPARSER_PATH}/src/UriMemory.c
    ${URIPARSER_PATH}/src/UriMemory.h
    ${URIPARSER_PATH}/src/UriNormalizeBase.c
    ${URIPARSER_PATH}/src/UriNormalizeBase.h
    ${URIPARSER_PATH}/src/UriNormalize.c
    ${URIPARSER_PATH}/src/UriParseBase.c
    ${URIPARSER_PATH}/src/UriParseBase.h
    ${URIPARSER_PATH}/src/UriParse.c
    ${URIPARSER_PATH}/src/UriQuery.c
    ${URIPARSER_PATH}/src/UriRecompose.c
    ${URIPARSER_PATH}/src/UriResolve.c
    ${URIPARSER_PATH}/src/UriShorten.c
)

# Add include directory
target_include_directories(uriparser PUBLIC 
    ${URIPARSER_PATH}/include
    ${URIPARSER_PORT}
)

# Add the standard library to the build
target_link_libraries(uriparser PUBLIC pico_stdlib)