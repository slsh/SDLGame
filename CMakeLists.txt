cmake_minimum_required(VERSION 3.5)
project(SDLGame)

if (UNIX AND NOT APPLE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -w -lSDL2")
endif (UNIX AND NOT APPLE)

if(UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -w -I/Library/Frameworks/SDL2.framework/Headers -F/Library/Frameworks -framework SDL2")
endif(UNIX)


set(SOURCE_FILES main.cpp)
add_executable(SDL_TEST ${SOURCE_FILES})

