project(PerceptualDiff)

cmake_minimum_required(VERSION 2.4)

add_executable(
  perceptualdiff
  PerceptualDiff.cpp LPyramid.cpp RGBAImage.cpp CompareArgs.cpp Metric.cpp lodepng.cpp)

install(TARGETS perceptualdiff DESTINATION bin)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_BUILD_TYPE Debug)

#nset(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -Wall -Wextra -pedantic -Wcast-qual -Wpointer-arith -Winit-self -Wswitch-default -Wmissing-include-dirs -Wold-style-cast -Wnon-virtual-dtor -Wshadow -Wno-unknown-pragmas")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -Wall")

enable_testing()
add_test(run_tests.bash, "${PROJECT_SOURCE_DIR}/test/run_tests.bash")
add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND}
                  DEPENDS "perceptualdiff")
