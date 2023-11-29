//Using SDL and standard IO
#include <SDL.h>
#include <SDL_main.h>
#include <SDL_ttf.h>
#include <stdio.h>

//Screen size constants
const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 614;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Loads Test
bool loadText();

//Frees media and shuts down SDL
void close();

//Global variable declaration
//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//The image we will load and show on the screen
SDL_Surface* gHelloWorld = NULL;

//The surface for the text
SDL_Surface* gTextSurface = NULL;

//The font we'll be using
TTF_Font* gFont = NULL;

//The color of the font
SDL_Color textColor = { 255, 255, 255 };

bool init()
{
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
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

    //Initialize SDL_ttf
    if (TTF_Init() == -1)
    {
        printf("SDL_ttf could not initialized. SDL_ttf Error: %s\n", TTF_GetError());
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

        //Streched image apply
        SDL_Rect stretchRect;
        stretchRect.x = 0;
        stretchRect.y = 0;
        stretchRect.w = SCREEN_WIDTH;
        stretchRect.h = SCREEN_HEIGHT;
        SDL_BlitScaled(gHelloWorld, NULL, gScreenSurface, &stretchRect);
    }
    return success;
}

bool loadText()
{
    bool success = true;

    gFont = TTF_OpenFont("IntelOneMono.ttf", 25);
    if (gFont == NULL)
    {
        printf("Failed to load Font. SDL_ttf Error: %s\n", TTF_GetError());
        success = false;
    }
    else
    {
        gTextSurface = TTF_RenderText_Solid(gFont, " Press any key to start...", textColor);
        if (gTextSurface == NULL)
        {
            printf("Unable to render text surface. SDL_ttf Error: %s\n", TTF_GetError());
            success = false;
        }
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
            if (!loadText())
            {
                printf("Failed to load text.");
            }
            else
            {
                //Apply the text
                SDL_BlitSurface(gTextSurface, NULL, gScreenSurface, NULL);

                //Update the surface
                SDL_UpdateWindowSurface(gWindow);

                //Hack to get window to stay up
                SDL_Event e; bool quit = false; while (quit == false) { while (SDL_PollEvent(&e)) { if (e.type == SDL_QUIT) quit = true; } }
            }
        }
    }

    //Free resources and close SDL
    close();

    return 0; 
}
