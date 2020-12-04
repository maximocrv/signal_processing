cmake_minimum_required(VERSION 3.1.3)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)  # not necessary, but encouraged
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
cmake_minimum_required(VERSION 3.13)
set(SOURCE_FILES run_file.cpp FourierTransform.hpp FourierTransform.cpp SignalProcessor.hpp SignalProcessor.cpp)
add_executable(ex_1 ${SOURCE_FILES})
