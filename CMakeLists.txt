cmake_minimum_required(VERSION 3.1.3)
project(signal-processing VERSION 0.1.0)

set(CMAKE_CXX_STANDARD_REQUIRED ON)  # not necessary, but encouraged
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(googletest)

add_library(signal_processing src/FourierTransform.hpp src/FourierTransform.cpp src/TimeSignalProcessor.hpp
            src/TimeSignalProcessor.cpp src/BaseSignalProcessor.hpp src/BaseSignalProcessor.cpp)

add_executable(run_signal_processor run_file.cpp)
target_link_libraries(run_signal_processor signal_processing)

add_executable(test_signal_processor tests/tests.cpp)
target_link_libraries(test_signal_processor gtest_main gtest pthread signal_processing)
