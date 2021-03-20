cmake_minimum_required(VERSION 3.13)
project(performer VERSION 0.1)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_compile_options(-Wno-psabi)

include(lib/cmake-utils/dependency-integrator.cmake)
integrate_cmake_dependency(
        NAME googletest
        GIT_URL git@github.com:google/googletest.git
        GIT_TAG 703bd9caab50b139428cea1aaff9974ebee5742e
)
integrate_cmake_dependency(
        NAME rpi_ws281x
        GIT_URL git@github.com:jgarff/rpi_ws281x.git
        GIT_TAG 3a20f1bdd740a144de180a07d8d3317920459d2d
)
integrate_cmake_dependency(
        NAME impresario-utils
        GIT_URL git@github.com:impresario-systems/impresario-utils.git
        GIT_TAG origin/dev
)

# performer
set(
        SOURCE_FILES
        src/Config.h
        src/Bootstrapper.cpp src/Bootstrapper.h

        src/color/HSLColor.cpp src/color/HSLColor.h
        src/color/RGBColor.h

        src/ledMatrix/LedMatrix.h
        src/ledMatrix/LedMatrixProxy.cpp src/ledMatrix/LedMatrixProxy.h
        src/ledMatrix/LedMatrixRenderer.cpp src/ledMatrix/LedMatrixRenderer.h
        src/ledMatrix/Ws2812bLedMatrix.cpp src/ledMatrix/Ws2812bLedMatrix.h

        src/performance/Performance.h
        src/performance/LedPerformance.cpp src/performance/LedPerformance.h

        src/performance/timeline/Timeline.h
        src/performance/timeline/TimelineManager.cpp src/performance/timeline/TimelineManager.h
        src/performance/timeline/OnsetTimeline.cpp src/performance/timeline/OnsetTimeline.h
        src/performance/timeline/PitchTimeline.cpp src/performance/timeline/PitchTimeline.h

        src/performance/movement/Movement.h
        src/performance/movement/LoggingMovement.cpp src/performance/movement/LoggingMovement.h
        src/performance/movement/ledMatrixMovement/LedMatrixMovement.cpp src/performance/movement/ledMatrixMovement/LedMatrixMovement.h
        src/performance/movement/ledMatrixMovement/FlashOnOnsetMovement.cpp src/performance/movement/ledMatrixMovement/FlashOnOnsetMovement.h

        src/performance/action/Action.h
        src/performance/action/ActionCollection.cpp src/performance/action/ActionCollection.h
        src/performance/action/ledMatrixAction/LedMatrixAction.cpp src/performance/action/ledMatrixAction/LedMatrixAction.h
        src/performance/action/ledMatrixAction/Flash.cpp src/performance/action/ledMatrixAction/Flash.h

        src/event/Event.cpp src/event/Event.h
        src/event/EventReceiver.cpp src/event/EventReceiver.h
        src/event/EventCollection.cpp src/event/EventCollection.h
        src/event/InvalidUnserializationException.h

)
list(APPEND TARGETS performer)
add_executable(performer src/main.cpp ${SOURCE_FILES})

# test
set(
        TEST_FILES
        ${SOURCE_FILES}
        test/TestingUtils.h

        test/color/TestHSLColor.cpp

)
list(APPEND TARGETS test-performer)
add_executable(test-performer ${TEST_FILES})
target_include_directories(test-performer PRIVATE test)
target_link_libraries(test-performer PRIVATE gtest_main)

# finalize
foreach (target IN LISTS TARGETS)
    target_include_directories(${target} PRIVATE src)
    target_include_directories(${target} PRIVATE ${CMAKE_BINARY_DIR}/rpi_ws281x-src)
    target_link_libraries(${target} PRIVATE impresario-utils)
    target_link_libraries(${target} PRIVATE ws2811)
    target_link_libraries(${target} PRIVATE zmq)
    target_link_libraries(${target} PRIVATE pthread)
endforeach ()
