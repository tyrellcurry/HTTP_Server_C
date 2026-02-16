cmake_minimum_required(VERSION 3.10)

project(Server)

set(CMAKE_C_STANDARD 90)
set(CMAKE_C_COMPILER gcc)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(TARGET Server)
set(INC include)

file(GLOB SOURCES "src/*.c")

add_executable(${TARGET} ${SOURCES})

target_include_directories(${TARGET} PRIVATE ${INC})

target_link_libraries(${TARGET})
