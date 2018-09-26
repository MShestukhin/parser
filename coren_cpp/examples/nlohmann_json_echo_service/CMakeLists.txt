cmake_minimum_required(VERSION 2.6)

project(nlohmann_json_echo_service CXX)

## Find out build type #########################################################
set(CMAKE_CONFIGURATION_TYPES Debug Release)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

message("Current configuration type: ${CMAKE_BUILD_TYPE}")

### Boost ###
set(Boost_COMPONENTS program_options filesystem random thread system)
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost COMPONENTS ${Boost_COMPONENTS} REQUIRED)

### Threads ###
set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
find_package(Threads REQUIRED)

## Find out compiller's flags ##################################################

### Compiller options ###
set(CMAKE_CXX_FLAGS "-Wall -Wextra")

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++14" COMPILER_SUPPORTS_CXX14)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX14)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
elseif(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
    message(FATAL_ERROR "Compiler ${CMAKE_CXX_COMPILER} has no C++11 support.")
endif()

set(CMAKE_CXX_FLAGS_DEBUG "-g3 -O0 -fno-inline -D_DEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

set(CMAKE_C_FLAGS "-Wall -Wextra -std=gnu99")

set(CMAKE_C_FLAGS_DEBUG "-g3 -O0 -fno-inline -D_DEBUG")
set(CMAKE_C_FLAGS_RELEASE "-O2")

## Examples ####################################################################

### JSON Echo Service ###
add_executable(${PROJECT_NAME} json_echo_service.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${Boost_INCLUDE_DIR}
)
target_link_libraries(${PROJECT_NAME} coren_interface)
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})
if(UNIX AND NOT APPLE)
    target_link_libraries(${PROJECT_NAME} rt)
endif()

