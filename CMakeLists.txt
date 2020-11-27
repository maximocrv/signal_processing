include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_CXX_STANDARD 17)

add_executable(utils utils.cpp SignalProcesser.cpp AudioFile/AudioFile.h)
