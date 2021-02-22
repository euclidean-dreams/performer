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

        src/data/Color.h

        src/ledMatrix/LedMatrix.h
)
list(APPEND TARGETS performer)
add_executable(performer src/main.cpp ${SOURCE_FILES})

# test
set(
        TEST_FILES
        ${SOURCE_FILES}
        test/TestingUtils.h

        test/data/TestColor.cpp
)
list(APPEND TARGETS test-performer)
add_executable(test-performer ${TEST_FILES})
target_include_directories(test-performer PRIVATE test)
target_link_libraries(test-performer PRIVATE gtest_main)

# finalize
foreach (target IN LISTS TARGETS)
    target_include_directories(${target} PRIVATE src)
    target_link_libraries(${target} PRIVATE impresario-serialization)
    target_link_libraries(${target} PRIVATE impresario-utils)
    target_link_libraries(${target} PRIVATE ws2811)
    target_link_libraries(${target} PRIVATE zmq)
endforeach ()
