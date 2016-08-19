cmake_minimum_required(VERSION 3.5)
project(live)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY, "${CMAKE_CURRENT_BINARY_DIR}/bin")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib)

set(SOURCE_FILES main.cpp libr/graphic.h src/graphic.cpp src/live.cpp libr/live.h src/engine.cpp libr/engine.h)
add_executable(live ${SOURCE_FILES})

target_link_libraries(live SDL2main SDL2) #-lmingw32