cmake_minimum_required(VERSION 3.5)
project(live)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY, "${CMAKE_CURRENT_SOURCE_DIR}/bin")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 ")#-lmingw32 -lSDL2main -lSDL2 -lSDL2_image -Wall


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib)


set(SOURCE_FILES main.cpp libr/graphic.h src/graphic.cpp src/live.cpp libr/live.h src/engine.cpp libr/engine.h hello.bmp)
add_executable(live ${SOURCE_FILES})

target_link_libraries(live mingw32 SDL2main SDL2 SDL2_image )

