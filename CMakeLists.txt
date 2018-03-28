cmake_minimum_required(VERSION 2.8)

project(pars)
set(PostgresSQL_LIBRARIES ${PROJECT_SOURCE_DIR}/usr/lib/x86_64-linux-gnu/libpq.a)

set(PosgresSQL_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/usr/include/postgresql)
include_directories(${PosgresSQL_INCLUDE_DIRS})
include_directories("${PROJECT_SOURCE_DIR}" ${PostgreSQL_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES} ${PROTOBUF_LIBRARIES} ${PostgresSQL_LIBRARIES} )
add_executable(${PROJECT_NAME} "main.cpp")
