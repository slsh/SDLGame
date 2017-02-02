cmake_minimum_required(VERSION 3.5)
project(SDLGame)

if (APPLE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -w -I/Library/Frameworks/SDL2.framework/Headers -I/Library/Frameworks/SDL2_ttf.framework/Headers -F/Library/Frameworks -framework SDL2 -framework SDL2_ttf")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -w -lSDL2 -lSDL2_ttf")
endif()


set(SOURCE_FILES
        sources/main.cpp
        sources/Debugger.cpp
        sources/Game.cpp
        sources/pieces/Piece.cpp
        sources/pieces/InvertedLPiece.cpp
        sources/pieces/IPiece.cpp
        sources/pieces/LPiece.cpp
        sources/pieces/SPiece.cpp
        sources/pieces/SquarePiece.cpp
        sources/pieces/TPiece.cpp
        sources/pieces/ZPiece.cpp
        sources/pieces/factories/StandardPieceFactory.cpp
        sources/GraphicManager.cpp)

set(HEADER_FILES
        headers/Debugger.h
        headers/timer.h
        headers/Game.h
        headers/pieces/factories/PieceFactory.h
        headers/pieces/Piece.h
        headers/pieces/InvertedLPiece.h
        headers/pieces/IPiece.h
        headers/pieces/LPiece.h
        headers/pieces/SPiece.h
        headers/pieces/SquarePiece.h
        headers/pieces/TPiece.h
        headers/pieces/ZPiece.h
        headers/pieces/factories/StandardPieceFactory.h
        headers/Colors.h
        headers/GraphicManager.h)

add_executable(SDLGame ${SOURCE_FILES} ${HEADER_FILES})

