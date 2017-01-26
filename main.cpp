//
// Created by johan eriksson on 26/01/2017.
//

#include <SDL2/SDL.h>
#include <stdio.h>

const int SCREENH = 384;
const int SCREENW = 192;

//void updateKey();
//void updateLogic();
void updateWindow();
void close();
void loadMedia();
int main(int argc, char* argv[]);

SDL_Window *window;                    // Declare a pointer
SDL_Surface* screenSurface = NULL;
SDL_Surface* blitSurface = NULL;

/*
void updateKey(){
    if (GetAsyncKeyState(VK_ESCAPE)){
        OutputDebugString("VK_ESCAPE");
        PostQuitMessage(0);
    }
}
*/

void updateWindow(){
    //Apply the image
    SDL_BlitSurface( blitSurface, NULL, screenSurface, NULL );

    SDL_UpdateWindowSurface( window );
}

void close()
{
    //Deallocate surface
    SDL_FreeSurface( screenSurface );
    screenSurface = NULL;

    SDL_FreeSurface( blitSurface );
    blitSurface = NULL;

    //Destroy window
    SDL_DestroyWindow( window );
    window = NULL;

    SDL_Quit();
}

void loadMedia() {
    //Load splash image
    blitSurface = SDL_LoadBMP( "hello_world.bmp" );
    if( blitSurface == NULL )
    {
        printf( "Unable to load image %s! SDL Error: %s\n", "02_getting_an_image_on_the_screen/hello_world.bmp", SDL_GetError() );
    }
}

int main(int argc, char* argv[]) {


    bool gameOn = true;

    SDL_Init(SDL_INIT_VIDEO);              // Initialize SDL2

    // Create an application window with the following settings:
    window = SDL_CreateWindow(
            "An SDL2 window",                  // window title
            SDL_WINDOWPOS_UNDEFINED,           // initial x position
            SDL_WINDOWPOS_UNDEFINED,           // initial y position
            640,                               // width, in pixels
            480,                               // height, in pixels
            SDL_WINDOW_OPENGL                 // flags - see below
    );

    screenSurface = SDL_GetWindowSurface( window );

    // Check that the window was successfully created
    if (window == NULL) {
        // In the case that the window could not be made...
        printf("Could not create window: %s\n", SDL_GetError());
        return 1;
    }

    /*int counter = 0;
    while (gameOn){


        counter++;
        if(counter > 2000){
            gameOn = false;
        }
    }*/
    loadMedia();

    //Main loop flag
    bool quit = false;

    //Event handler
    SDL_Event e;

    //While application is running
    while(!quit) {
        //Handle events on queue
        while(SDL_PollEvent(&e) != 0) {
            //User requests quit
            if(e.type == SDL_QUIT) {
                quit = true;
            }
        }

        //updateKey();
        //updateLogic();

        updateWindow();
    }

    // The window is open: could enter program loop here (see SDL_PollEvent())
    //SDL_Delay(3000);  // Pause execution for 3000 milliseconds, for example


    close();
    return 0;
}