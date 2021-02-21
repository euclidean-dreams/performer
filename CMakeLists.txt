cmake_minimum_required(VERSION 3.13)
project(performer)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(lib/rpi_ws281x)
add_subdirectory(lib/impresario-utils)
include_directories(lib/rpi_ws281x)
include_directories(lib/serialization/generated)
include_directories(src)

set(
        SOURCE_FILES
        src/main.cpp
)
add_executable(performer ${SOURCE_FILES})
target_link_libraries(performer LINK_PUBLIC impresario-utils)
target_link_libraries(performer LINK_PUBLIC ws2811)
target_link_libraries(performer LINK_PUBLIC zmq)
