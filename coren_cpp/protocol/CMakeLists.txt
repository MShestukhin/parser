cmake_minimum_required(VERSION 2.6)

project("coren_protocol" C)

file(GLOB ASN1_FILES *.asn*)

set(CMAKE_CONFIGURATION_TYPES Debug Release)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

find_program(ASN1C_PATH asn1c HINTS ${ASN1C_ROOT})

if(NOT ASN1C_PATH)
    message(FATAL_ERROR "Can't find asn1c compiler")
endif()

execute_process(
    COMMAND ${ASN1C_PATH} -v
    ERROR_FILE ${CMAKE_CURRENT_BINARY_DIR}/asn1c_version.txt
    OUTPUT_QUIET
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)
execute_process(
    COMMAND head -n 1
    COMMAND awk "{ print $3; }"
    COMMAND sed -e "s/v//g"
    INPUT_FILE ${CMAKE_CURRENT_BINARY_DIR}/asn1c_version.txt
    OUTPUT_VARIABLE ASN1C_VERSION
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)
message(${PROJECT_NAME} " asn1c version " ${ASN1C_VERSION})

if (${ASN1C_VERSION} VERSION_LESS "0.9.26")
    message(FATAL_ERROR "asn1c >= 0.9.26 required")
endif()

set(ASN1C_FLAGS "")
if (${ASN1C_VERSION} VERSION_GREATER "0.9.26")
    set(ASN1C_FLAGS "-fwide-types")
endif()

FOREACH (ASN1_FILE ${ASN1_FILES})
    execute_process(COMMAND ${ASN1C_PATH} ${ASN1C_FLAGS} ${ASN1_FILE} WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
ENDFOREACH()

file(GLOB SOURCES ${CMAKE_CURRENT_BINARY_DIR}/*.c)
list(REMOVE_ITEM SOURCES ${CMAKE_CURRENT_BINARY_DIR}/converter-sample.c)
list(REMOVE_ITEM SOURCES ${CMAKE_CURRENT_BINARY_DIR}/converter-example.c)
list(APPEND SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/asn_autoexpand_buffer.c)
source_group ("Source Files" FILES ${SOURCES})

file(GLOB HEADERS ${CMAKE_CURRENT_BINARY_DIR}/*.h)
source_group ("Header Files" FILES ${HEADERS})

add_library(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
)
