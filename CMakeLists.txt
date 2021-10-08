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
        GIT_TAG 5d0041eba608e3a52aa637122a72396d3336d91b
)
integrate_cmake_dependency(
        NAME impresario-utils
        GIT_URL git@github.com:impresario-systems/impresario-utils.git
        GIT_TAG origin/dev
)
SET(YAML_CPP_BUILD_TESTS OFF)
SET(YAML_CPP_INSTALL OFF)
SET(YAML_MSVC_SHARED_RT OFF)
SET(YAML_CPP_BUILD_TOOLS OFF)
SET(YAML_CPP_BUILD_CONTRIB OFF)
integrate_cmake_dependency(
        NAME yaml
        GIT_URL git@github.com:jbeder/yaml-cpp.git
        GIT_TAG 9a3624205e8774953ef18f57067b3426c1c5ada6
)

# performer
set(
        SOURCE_FILES
        src/Bootstrapper.cpp src/Bootstrapper.h

        src/color/HSLColor.cpp src/color/HSLColor.h
        src/color/RGBColor.h

        src/ledMatrix/LedMatrixProxy.cpp src/ledMatrix/LedMatrixProxy.h
        src/ledMatrix/Ws2812bLedStripRenderer.cpp src/ledMatrix/Ws2812bLedStripRenderer.h
        src/ledMatrix/Ws2812bLedStrip.cpp src/ledMatrix/Ws2812bLedStrip.h

        src/performance/Performance.h
        src/performance/LedPerformance.cpp src/performance/LedPerformance.h

        src/performance/movement/Movement.h
        src/performance/movement/ledMatrixMovement/LedMatrixMovement.cpp src/performance/movement/ledMatrixMovement/LedMatrixMovement.h

        src/performance/action/Action.h
        src/performance/action/ActionCollection.cpp src/performance/action/ActionCollection.h
        src/performance/action/ledMatrixAction/LedMatrixAction.cpp src/performance/action/ledMatrixAction/LedMatrixAction.h

        src/performance/movement/ledMatrixMovement/SandboxMovement.cpp src/performance/movement/ledMatrixMovement/SandboxMovement.h
        src/Config.cpp src/Config.h src/performance/movement/ledMatrixMovement/DisplaySignalMovement.cpp src/performance/movement/ledMatrixMovement/DisplaySignalMovement.h src/performance/action/ledMatrixAction/DisplaySignalAction.cpp src/performance/action/ledMatrixAction/DisplaySignalAction.h src/performance/action/ledMatrixAction/RectangleGrowthAction.cpp src/performance/action/ledMatrixAction/RectangleGrowthAction.h src/performance/movement/ledMatrixMovement/RectanglandMovement.cpp src/performance/movement/ledMatrixMovement/RectanglandMovement.h
        src/performance/action/ledMatrixAction/entity/shape/Rectangle.cpp src/performance/action/ledMatrixAction/entity/shape/Rectangle.h src/ledMatrix/Coordinate.cpp src/ledMatrix/Coordinate.h src/performance/action/ledMatrixAction/entity/shape/Circle.cpp src/performance/action/ledMatrixAction/entity/shape/Circle.h src/performance/movement/ledMatrixMovement/EntitySpawner.cpp src/performance/movement/ledMatrixMovement/EntitySpawner.h src/ledMatrix/LedGizmos.cpp src/ledMatrix/LedGizmos.h src/performance/action/ledMatrixAction/entity/Entity.h src/performance/action/ledMatrixAction/entity/shape/Shape.h src/performance/action/ledMatrixAction/entity/shape/Shape.cpp src/performance/action/ledMatrixAction/CircleGrowthAction.cpp src/performance/action/ledMatrixAction/CircleGrowthAction.h src/performance/action/ledMatrixAction/entity/parametro/Parametro.cpp src/performance/action/ledMatrixAction/entity/parametro/Parametro.h src/performance/action/ledMatrixAction/entity/parametro/Sinusoid.cpp src/performance/action/ledMatrixAction/entity/parametro/Sinusoid.h src/performance/action/ledMatrixAction/SinusoidScatterAction.cpp src/performance/action/ledMatrixAction/SinusoidScatterAction.h src/performance/movement/ledMatrixMovement/SinusoidaleryMovement.cpp src/performance/movement/ledMatrixMovement/SinusoidaleryMovement.h src/performance/action/ledMatrixAction/entity/Entity.cpp src/performance/movement/ledMatrixMovement/FlameoHotmanMovement.cpp src/performance/movement/ledMatrixMovement/FlameoHotmanMovement.h src/performance/action/ledMatrixAction/entity/shape/Flame.cpp src/performance/action/ledMatrixAction/entity/shape/Flame.h src/performance/action/ledMatrixAction/FlameAction.cpp src/performance/action/ledMatrixAction/FlameAction.h)
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
    target_link_libraries(${target} PRIVATE yaml-cpp)
endforeach ()
