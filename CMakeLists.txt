cmake_minimum_required(VERSION 2.8)

project(${PROJECT_NAME} cdr_sca CXX)

SET(CMAKE_CXX_FLAGS "-lrt")

file(GLOB HEADERS include/*.h*)
source_group ("Header Files" FILES ${HEADERS})

aux_source_directory(. SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST})


set( boost_URL "http://sourceforge.net/projects/boost/files/boost/1.65.1/boost_1_65_1.tar.bz2" )
set( boost_SHA1 "9f1dd4fa364a3e3156a77dc17aa562ef06404ff6" )
set( boost_INSTALL ${CMAKE_CURRENT_BINARY_DIR}/boost )
set( boost_INCLUDE_DIR ${boost_INSTALL}/include )
set( boost_LIB_DIR ${boost_INSTALL}/lib )

set(BOOST_ROOT ${boost_INSTALL})
set(BOOST_INCLUDE_DIRS "${BOOST_ROOT}/include")
set(BOOST_LIBRARY_DIRS "${BOOST_ROOT}/lib")
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME ON)
find_package(Boost COMPONENTS system log thread filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})


add_subdirectory(cnora_cpp)
target_link_libraries(${PROJECT_NAME} cnora_service)
### coren library
add_subdirectory(coren_cpp)
target_link_libraries(${PROJECT_NAME} coren_interface)

