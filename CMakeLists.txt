cmake_minimum_required(VERSION 3.13)
project(performer VERSION 0.1)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_compile_options(-Wno-psabi)

add_subdirectory(lib/googletest)
add_subdirectory(lib/impresario-serialization)
add_subdirectory(lib/impresario-utils)
add_subdirectory(lib/rpi_ws281x)

# performer
set(
        SOURCE_FILES
        src/Config.h

        src/color/HSLColor.cpp src/color/HSLColor.h
        src/color/RGBColor.h

        src/ledMatrix/LedMatrix.h
        src/ledMatrix/Ws2812bLedMatrix.cpp src/ledMatrix/Ws2812bLedMatrix.h
)
list(APPEND TARGETS performer)
add_executable(performer src/main.cpp ${SOURCE_FILES})

# test
set(
        TEST_FILES
        ${SOURCE_FILES}
        test/TestingUtils.h

        test/color/TestHSLColor.cpp
        test/color/TestRGBColor.cpp
)
list(APPEND TARGETS test-performer)
add_executable(test-performer ${TEST_FILES})
target_include_directories(test-performer PRIVATE test)
target_link_libraries(test-performer PRIVATE gtest_main)

# finalize
foreach (target IN LISTS TARGETS)
    target_include_directories(${target} PRIVATE src)
    target_include_directories(${target} PRIVATE lib/rpi_ws281x)
    target_link_libraries(${target} PRIVATE impresario-serialization)
    target_link_libraries(${target} PRIVATE impresario-utils)
    target_link_libraries(${target} PRIVATE ws2811)
    target_link_libraries(${target} PRIVATE zmq)
endforeach ()
