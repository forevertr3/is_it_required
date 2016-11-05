#ifndef MAIN_LOOP_H_INCLUDED
#define MAIN_LOOP_H_INCLUDED
#pragma once
#define SCREEN_H 680
#define SCREEN_W 1250
#define PI 3.14159265

#include <SDL2/SDL_mixer.h>
#include "SDL2/SDL2_gfxPrimitives.h"
#include <SDL2/SDL.h>
#include <sstream>
#include <SDL2/SDL_ttf.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "yan_cubuk.h"
#include "sub_screen.h"

void main_loop(struct SDL_Renderer *gRenderer, string work_path){
    SDL_Event ev;

    LTexture logo;
    LTexture logo1;
    LTexture black;
    //cout << work_path;
    black.loadFromFile("black.png");                                      /*Need a data dir*/
    logo.loadFromFile("logo1.jpg");

    yan_cubuk tab(gRenderer);
    SDL_Rect all_screen, rect1;
    all_screen.x=0;
    all_screen.w=1080;
    all_screen.y=0;
    all_screen.h=76;

    rect1.x=230;
    rect1.w=775;
    rect1.y=73;
    rect1.h=3;
    int k=0;
    sub for_no_1(gRenderer,1);                                           /*Needs 3 sub screen */
    sub for_no_2(gRenderer,2);

    bool quit=false;
    cout << "Main Loop" << endl;
    while (!quit){
        k=tab.last_click();
        SDL_SetRenderDrawColor(gRenderer,165,200,250,0);
        SDL_RenderSetViewport(gRenderer,&all_screen);
        black.render(0,0);
        SDL_RenderFillRect(gRenderer,&rect1);
        tab.render();

        if (k==1) for_no_1.render();
        if (k==2) for_no_2.render();

        if ( SDL_PollEvent( &ev ) != 0){

             tab.handle_events(&ev);

             if (k==1) for_no_1.handle_events(&ev, work_path);
             if (k==2) for_no_2.handle_events(&ev, work_path);

             if (ev.type==SDL_QUIT){
                 quit=true;
             }
        }

        SDL_RenderPresent(gRenderer);
    }
}

#endif // MAIN_LOOP_H_INCLUDED
