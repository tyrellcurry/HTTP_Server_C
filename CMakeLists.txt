cmake_minimum_required(VERSION 3.10)
project(Server C)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Directories
set(INC ${CMAKE_SOURCE_DIR}/include)
set(SRC ${CMAKE_SOURCE_DIR}/src)
set(TEST_DIR ${CMAKE_SOURCE_DIR}/test)
set(UNITY_DIR ${CMAKE_SOURCE_DIR}/lib/Unity/src)

# Server library (all source files except main.c)
file(GLOB LIB_SOURCES "${SRC}/*.c")
list(FILTER LIB_SOURCES EXCLUDE REGEX "main\\.c$")
add_library(server_lib STATIC ${LIB_SOURCES})
target_include_directories(server_lib PUBLIC ${INC})

# Main executable
add_executable(Server ${SRC}/main.c)
target_include_directories(Server PRIVATE ${INC})
target_link_libraries(Server PRIVATE server_lib)

# Unity library
add_library(unity STATIC ${UNITY_DIR}/unity.c)
target_include_directories(unity PUBLIC ${UNITY_DIR})

# Enable testing
enable_testing()

# Test executable
file(GLOB TEST_SOURCES "${TEST_DIR}/*.c")
add_executable(test_runner ${TEST_SOURCES})
target_include_directories(test_runner PRIVATE ${INC} ${UNITY_DIR})
target_link_libraries(test_runner PRIVATE unity server_lib)

# Add test to CTest
add_test(NAME ServerTests COMMAND test_runner)
