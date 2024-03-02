cmake_minimum_required(VERSION 3.2)
project(cpp_common_so)

set(CMAKE_CXX_STANDARD 11)

if(CMAKE_SYSTEM_PROCESSOR STREQUAL "aarch64")
    # ARM64 架构
    set(TARGET_ARCH "arm64")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=armv8-a")
elseif(CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64")
    # AMD64 架构
    set(TARGET_ARCH "amd64")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=x86-64")
else()
    message(FATAL_ERROR "Unsupported architecture")
endif()

# generate so
add_library(hello_so SHARED src/hello.cc src/hello.h)
add_library(openssl_code_so SHARED src/openssl_code.cc src/openssl_code.h)
add_library(easyloggingpp_so SHARED src/easylogging++.cc src/easylogging++.h)
add_library(mqtt_client_so SHARED src/mqtt_client.cc src/mqtt_client.h)

# SET_TARGET_PROPERTIES(openssl_code_so PROPERTIES VERSION 1.1)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
message("Target Architecture: ${TARGET_ARCH}")

# test
# include_directories(./test)
# include_directories(/usr/local/include)
link_directories(${PROJECT_BINARY_DIR}/lib)

add_executable(main test/main.cpp)
target_link_libraries(main hello_so openssl_code_so mqtt_client_so
                    -lssl -lcrypto -lboost_system)

add_executable(mqtt_demo test/mqtt_demo.cpp)
target_link_libraries(mqtt_demo mqtt_client_so -lmosquitto)