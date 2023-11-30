//Using SDL and standard IO
#include <SDL.h>
#include <SDL_main.h>
#include <SDL_ttf.h>
#include <stdio.h>

//Screen size constants
const int SCREEN_WIDTH = 1550;
const int SCREEN_HEIGHT = 815;

//Starts up SDL and creates window
bool init();

void stretchImageSize();

//Loads media
bool loadMedia();

//Loads Test
bool loadText();

//Frees media and shuts down SDL
void close();



//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//The image we will load and show on the screen
SDL_Surface* gimage = NULL;

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
        printf("SDL could not initialize. SDL_ttf Error: %s\n", TTF_GetError());
        success = false;
    }
    else
    {
        //Create window
        gWindow = SDL_CreateWindow("Want to go home...", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL)
        {
            printf("Window could not be created. SDL_Error: %s\n", SDL_GetError());
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

void stretchImageSize() {

    //Streched image apply
    SDL_Rect stretchedSize;
    stretchedSize.x = 0;
    stretchedSize.y = 0;
    stretchedSize.w = SCREEN_WIDTH;
    stretchedSize.h = SCREEN_HEIGHT;
    SDL_BlitScaled(gimage, NULL, gScreenSurface, &stretchedSize);
}

bool loadMedia()
{
    //Loading success flag
    bool success = true;
    
    //Load splash image
    gimage = SDL_LoadBMP("usable_image/Start_2.bmp");
    if (gimage == NULL)
    {
        printf("Unable to load image %s. SDL Error: %s\n", "usable_image/image.bmp", SDL_GetError());
        success = false;
    }
    else
    {
        // Resize the image to fit the window size
        gimage = SDL_ConvertSurface(gimage, gScreenSurface->format, 0);
        stretchImageSize();
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
        SDL_BlitSurface(gTextSurface, NULL, gScreenSurface, NULL);
    }
    return success;
}

void close()
{
    //Deallocate surface
    SDL_FreeSurface(gimage);
    gimage = NULL;

    //Destroy window
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    //Quit SDL subsystems
    SDL_Quit();
}

int main(int argc, char* args[])
{
    if (!init())
    {
        printf("Failed to initialize.\n");
    }
    else
    {
        if (!loadMedia())
        {
            printf("Failed to load media.\n");
        }
        else
        {
            if (!loadText())
            {
                printf("Failed to load text.");
            }
            else
            {
                SDL_UpdateWindowSurface(gWindow);

                SDL_Event e;
                bool quit = false;
                Uint32 lastTime = 0;
                int showInterval = 900; // visible period
                int hideInterval = 600; // invisible period
                bool showText = true;
                int changed = 0; // to update the window only at the end of the period

                while (!quit)
                {
                    //end case
                    while (SDL_PollEvent(&e) != 0)
                    {
                        if (e.type == SDL_QUIT)
                        {
                            quit = true;
                        }
                    }

                    Uint32 currentTime = SDL_GetTicks();


                    if (currentTime - lastTime > (showText ? showInterval : hideInterval))
                    {
                        lastTime = currentTime;
                        showText = !showText;
                        changed = 1;
                    }

                    //when time is over && have to show text
                    if((changed == 1) && showText)
                    { 
                        SDL_BlitSurface(gTextSurface, NULL, gScreenSurface, NULL);
                        SDL_UpdateWindowSurface(gWindow);
                        changed = 0;
                    }
                    //when time is over && have to hide text
                    else if((changed == 1) && !showText)
                    {
                        stretchImageSize();
                        SDL_UpdateWindowSurface(gWindow);
                        changed = 0;
                    }


                }
            }
        }
    }

    close();

    return 0;
}
