#include <iostream>
#include <string>
#include <SDL2/SDL.h>
//#include <SDL2/SDL_image.h>

const unsigned int WINDOW_WIDTH  = 640;
const unsigned int WINDOW_HEIGHT = 480;


enum KeyPressSurface {
    PRESS_KEY_DEFAULT,
    PRESS_KEY_UP,
    PRESS_KEY_DOWN,
    PRESS_KEY_RIGHT,
    PRESS_KEY_LEFT,
    PRESS_KEY_TOTAL
};

SDL_Surface *images[PRESS_KEY_TOTAL];
SDL_Surface *gScreenSurface  = NULL;
SDL_Surface *gCurrentSurface = NULL;
SDL_Window  *gWindow         = NULL;

bool         init        ();
SDL_Surface *loadSurface ( std::string path );
bool         loadMedia   ();
void         close       ();




int main( int argc, char *argv[] )
{
    if ( !init() ){
        std::cout << "Filed to initialize" << std::endl;
    }
    else{
        if ( !loadMedia() ){
            std::cout << "Failed to load media" << std::endl;
        }
        else{
            bool quit = false;

            SDL_Event e;

            gCurrentSurface = images[PRESS_KEY_DEFAULT];

            while( !quit ){

                while ( SDL_PollEvent( &e ) != 0){
                    if ( e.type == SDL_QUIT ){
                        quit = true;
                    }
                    else if ( e.type == SDL_KEYDOWN ){

                        switch ( e.key.keysym.sym ){
                            case SDLK_DOWN:
                                gCurrentSurface = images[PRESS_KEY_DOWN];
                                break;

                            case SDLK_UP:
                                gCurrentSurface = images[PRESS_KEY_UP];
                                break;

                            case SDLK_LEFT:
                                gCurrentSurface = images[PRESS_KEY_LEFT];
                                break;

                            case SDLK_RIGHT:
                                gCurrentSurface = images[PRESS_KEY_RIGHT];
                                break;

                            default:
                                gCurrentSurface = images[PRESS_KEY_DEFAULT];
                                break;
                        }
                    }
                }

                SDL_BlitSurface(gCurrentSurface, NULL, gScreenSurface, NULL);

                SDL_UpdateWindowSurface( gWindow );
            }
        }
    }

    close();

    return 0;
}

bool init()
{
    bool success = true;

    if ( SDL_Init(SDL_INIT_VIDEO) < 0 ){
        std::cout << "SDL couldn't initialize. SDL Error: " << SDL_GetError() << std::endl;
        success = false;
    }
    else{
        gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

        if ( gWindow == NULL ){
            std::cout << "Window couldn't be to created. SDL Error: " << SDL_GetError() << std::endl;
            success = false;
        }
        else{
            gScreenSurface = SDL_GetWindowSurface( gWindow );
        }
    }

    return success;
}

bool loadMedia()
{
    bool success = true;

    images[PRESS_KEY_DEFAULT] = loadSurface( "press.bmp" );
    if ( images[PRESS_KEY_DEFAULT] == NULL ){
        std::cout << "Failed to load default image" << std::endl;
        success = false;
    }

    images[PRESS_KEY_UP] = loadSurface( "up.bmp" );
    if( images[PRESS_KEY_UP] == NULL ){
        std::cout << "Failed to load up image" << std::endl;
        success = false;
    }

    images[PRESS_KEY_DOWN] = loadSurface( "down.bmp" );
    if ( images[PRESS_KEY_DOWN] == NULL ){
        std::cout << "Failed to load down image" << std::endl;
        success = false;
    }

    images[PRESS_KEY_LEFT] = loadSurface( "left.bmp" );
    if ( images[PRESS_KEY_LEFT] == NULL ){
        std::cout << "Failed to load left image" << std::endl;
        success = false;
    }

    images[PRESS_KEY_RIGHT] = loadSurface( "right.bmp" );
    if( images[PRESS_KEY_RIGHT] == NULL ){
        std::cout << "Failed to load right image" << std::endl;
        success = false;
    }

    return success;
}

SDL_Surface *loadSurface( std::string path )
{
    SDL_Surface *optimizedSurface = NULL;
    SDL_Surface *loadedSurface   = SDL_LoadBMP( path.c_str() );

    if ( loadedSurface == NULL ){
        std::cout << "Unable to load image " << path << " SDL Error: " << SDL_GetError() << std::endl;
    }
    else{
        optimizedSurface = SDL_ConvertSurface( loadedSurface, gScreenSurface->format, NULL );

        if ( optimizedSurface == NULL ){
            std::cout << "Unable to convert image " << path << " SDL Error: " << SDL_GetError() << std::endl;
        }

        SDL_FreeSurface( loadedSurface );
    }

    return optimizedSurface;
}

void close()
{
    for (int i = 0; i < PRESS_KEY_TOTAL; i++){
        SDL_FreeSurface( images[i] );
        images[i] = NULL;
    }

    SDL_DestroyWindow( gWindow );
    gWindow = NULL;

    SDL_Quit();
}