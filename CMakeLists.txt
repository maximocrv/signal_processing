cmake_minimum_required(VERSION 3.1.3)
project(signal-processing VERSION 0.1.0)

set(CMAKE_CXX_STANDARD_REQUIRED ON)  # not necessary, but encouraged
set(CMAKE_CXX_STANDARD 17)

# https://cmake.org/cmake/help/latest/guide/tutorial/index.html
# https://www.jetbrains.com/help/clion/quick-cmake-tutorial.html

# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
    message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
    message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
        ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
        EXCLUDE_FROM_ALL)


# Now simply link against gtest or gtest_main as needed. Eg
add_executable(tests tests/tests.cpp)
target_link_libraries(tests gtest_main)
add_test(NAME example_test COMMAND tests)

# main executable
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
set(SOURCE_FILES run_file.cpp FourierTransform.hpp FourierTransform.cpp SignalProcessor.hpp SignalProcessor.cpp)
add_executable(ex_1 ${SOURCE_FILES})