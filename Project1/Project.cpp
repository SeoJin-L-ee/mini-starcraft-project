//Using SDL and standard IO
#include <SDL.h>
#include <SDL_main.h>
#include <stdio.h>

//Screen dimension constants
const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 614;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//The image we will load and show on the screen
SDL_Surface* gHelloWorld = NULL;

bool init()
{
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        //Create window
        gWindow = SDL_CreateWindow("Want to go home...", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL)
        {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            //Get window surface
            gScreenSurface = SDL_GetWindowSurface(gWindow);
        }
    }

    return success;
}

bool loadMedia()
{
    //Loading success flag
    bool success = true;
    
    //Load splash image
    gHelloWorld = SDL_LoadBMP("usable_image/image.bmp");
    if (gHelloWorld == NULL)
    {
        printf("Unable to load image %s! SDL Error: %s\n", "usable_image/image.bmp", SDL_GetError());
        success = false;
    }
    else
    {
        // Resize the image to fit the window size
        gHelloWorld = SDL_ConvertSurface(gHelloWorld, gScreenSurface->format, 0);

        //늘린 이미지 적용
        SDL_Rect stretchRect;
        stretchRect.x = 0;
        stretchRect.y = 0;
        stretchRect.w = SCREEN_WIDTH;
        stretchRect.h = SCREEN_HEIGHT;
        SDL_BlitScaled(gHelloWorld, NULL, gScreenSurface, &stretchRect);
    }
    return success;
}

void close()
{
    //Deallocate surface
    SDL_FreeSurface(gHelloWorld);
    gHelloWorld = NULL;

    //Destroy window
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    //Quit SDL subsystems
    SDL_Quit();
}

int main(int argc, char* args[])
{
    //Start up SDL and create window
    if (!init())
    {
        printf("Failed to initialize!\n");
    }
    else
    {
        //Load media
        if (!loadMedia())
        {
            printf("Failed to load media!\n");
        }
        else
        {
            //Update the surface
            SDL_UpdateWindowSurface(gWindow);

            //Hack to get window to stay up
            SDL_Event e; bool quit = false; while (quit == false) { while (SDL_PollEvent(&e)) { if (e.type == SDL_QUIT) quit = true; } }
        }
    }

    //Free resources and close SDL
    close();

    return 0; 
}


//#include <stdio.h>
//#include "SDL.h"
//
//#pragma comment(lib, "SDL2main.lib")
//#pragma comment(lib, "SDL2.lib")
//
//SDL_Window* window;
//SDL_Renderer* renderer;
//
//int SDL_main(int argc, char* argv[])
//{
//	printf("Start\n");
//
//	// Initialize SDL
//	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
//		printf("Could not initialize SDL! (%s)\n", SDL_GetError());
//		return -1;
//	}
//
//	// Create window
//	window = SDL_CreateWindow("", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_OPENGL);
//	if (window == NULL) {
//		printf("Could not create window! (%s)\n", SDL_GetError());
//		return -1;
//	}
//
//	// Create renderer
//	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);
//	if (renderer == NULL) {
//		printf("Could not create renderer! (%s)\n", SDL_GetError());
//		return -1;
//	}
//
//	// Clear renderer (white)
//	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
//	SDL_RenderClear(renderer);
//
//	// Draw rect (red)
//	SDL_Rect r = { 50, 50, 100, 100 };
//	SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
//	SDL_RenderDrawRect(renderer, &r);
//
//	// Update screen
//	SDL_RenderPresent(renderer);
//
//	SDL_Event event;
//	int done = 0;
//
//	while (!done) {
//		SDL_PollEvent(&event);
//
//		if (event.type == SDL_QUIT) {
//			done = 1;
//		}
//	}
//
//	SDL_DestroyRenderer(renderer);
//	SDL_DestroyWindow(window);
//	SDL_Quit();
//
//	printf("End\n");
//
//	return 0;
//}
