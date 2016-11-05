/*Luckly i found easiest zipping on c++ from net. That goes with Image creator Image.cpp.
So zip.cpp and image.cpp isnt my own code.
Currenty working for find some good algorithm, if i came up some good ones and
make that work, believe that i replace a really Good GUI with working QT. With that
i set my goals
Also My deepest goal is apply that algorithm on videos. Even current method could spare a
little space in videos, probably but needs ton of work.
Also needs memory optimize, when numbers do a actual work it could become a total disaster for RAM
Osman Semi Ceylan17
*/

#include <SDL2/SDL.h>
#include <direct.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include "texture.h"
#include <sstream>
#include "main_loop.h"
#define GetCurrentDir _getcwd


const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 600;

using namespace std;

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
string work_path;

bool initGL();

bool init(){
	bool success = true;

    SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" );

    gWindow = SDL_CreateWindow( "MagIMG", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT,  SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );
    /*Magic Image = MagImg ? */
    gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_TARGETTEXTURE);
    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );


/*    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );         /*No need opengl here, just stands cool.
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 1 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );

    SDL_GLContext gContext = SDL_GL_CreateContext( gWindow );
    if( gContext == NULL ) printf( "OpenGL context could not be created! SDL Error: %s\n", SDL_GetError() );

    if( SDL_GL_SetSwapInterval( 1 ) < 0 ) printf( "Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError() );*/

    int imgFlags = IMG_INIT_PNG;
    IMG_Init( imgFlags ) & imgFlags;

    TTF_Init();
   // initGL();
	return success;
}


int set_path(){
    char cCurrentPath[FILENAME_MAX];
    if (!GetCurrentDir(cCurrentPath, sizeof(cCurrentPath)))  return errno;
    cCurrentPath[sizeof(cCurrentPath) - 1] = '\0';                                  /* not nessesary */
    printf ("%s", cCurrentPath);                                                    /*Gets current dir */
    work_path=cCurrentPath;
}


int main( int argc, char* args[] ){
    set_path();
    init();
                                                                 /*SDL load*/
    TTF_Font *Font;
    Font=TTF_OpenFont("arial.ttf",20);
    class_set_renderer(gRenderer,&Font);                                      /*Texture Load*/

    cout << "All loads should be done" << endl;
    main_loop(gRenderer, work_path);

    return 0;
}
