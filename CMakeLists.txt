cmake_minimum_required(VERSION 3.5)
project(SDLGame)

if (APPLE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -w -I/Library/Frameworks/SDL2.framework/Headers -F/Library/Frameworks -framework SDL2")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -w -lSDL2")
endif()

set(SOURCE_FILES main.cpp Debugger.cpp Pieces/TPiece.cpp)
set(HEADER_FILES headers/Debugger.h headers/pieceDatabase.h headers/timer.h headers/Piece.h headers/PieceFactory.h headers/Piece.h)
add_executable(SDLGame ${SOURCE_FILES} ${HEADER_FILES})

