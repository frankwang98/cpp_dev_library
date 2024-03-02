cmake_minimum_required(VERSION 3.5)
project(HelloWorldExample)

set(CMAKE_CXX_STANDARD 11)

find_package(fastcdr REQUIRED)
find_package(fastrtps REQUIRED)

# generate idl_gen
file(GLOB IDL_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.idl")

foreach(IDL_FILE ${IDL_SOURCES})
    get_filename_component(IDL_BASE_NAME ${IDL_FILE} NAME_WE)
    set(GENERATED_SOURCES "${CMAKE_CURRENT_BINARY_DIR}/${IDL_BASE_NAME}.cxx" "${CMAKE_CURRENT_BINARY_DIR}/${IDL_BASE_NAME}.h")
    add_custom_command(
        OUTPUT ${GENERATED_SOURCES}
        COMMAND fastddsgen -d ./ ${IDL_FILE}
        DEPENDS ${IDL_FILE}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating C++ files from ${IDL_FILE}"
    )
    list(APPEND GENERATED_CPP_SOURCES ${GENERATED_SOURCES})
endforeach()

include_directories(${CMAKE_CURRENT_BINARY_DIR})

# generate lib
file(GLOB DDS_HELLOWORLD_SOURCES_CXX "./build/*.cxx")
add_library(HelloWorld_IDL_lib ${DDS_HELLOWORLD_SOURCES_CXX})

add_executable(HelloWorldPublisher HelloWorldPublisher.cpp ${GENERATED_CPP_SOURCES})
target_link_libraries(HelloWorldPublisher HelloWorld_IDL_lib fastcdr fastrtps)

add_executable(HelloWorldSubscriber HelloWorldSubscriber.cpp ${GENERATED_CPP_SOURCES})
target_link_libraries(HelloWorldSubscriber HelloWorld_IDL_lib fastcdr fastrtps)