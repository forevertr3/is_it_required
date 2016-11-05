#ifndef YAN_CUBUK_H
#define YAN_CUBUK_H
#include <string.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <stdio.h>
#include "sub_screen.h"
#define capx 230
#define capy 60

using namespace std;

struct members{
    int x,y,no;
    char names[50];
    struct members *next;
    bool mouse_over;
    bool clicked;
};

struct members *add_button(int x, int y,int sayi, string name,int number){
    struct members *gecici;
    gecici=(struct members *)malloc(sizeof(struct members));
    gecici->x=x;
    gecici->y=y;
    gecici->no=number;

    char *cstr = new char[name.length() + 1];
    strcpy(cstr, name.c_str());
    strcpy(gecici->names, cstr);
    delete []cstr;

    gecici->next=NULL;
    gecici->no=sayi;
    gecici->mouse_over= false;
    if (number==1) gecici->clicked=true;
    else gecici->clicked=false;

    return gecici;
}

void button_ekle(int x, int y,int sayi, string name, struct members **liste_basi,int number){
    struct members *a=add_button(x,y,sayi,name,number);
    a->next=*liste_basi;
    *liste_basi=a;
}

class yan_cubuk{
    SDL_Renderer *gRenderer;
    struct members *buttons=NULL;
    LTexture cptn;
    SDL_Rect bttn;
    int clicked_number;
    public:
        int last_click();
        void handle_events(union SDL_Event *);
        void render();
        yan_cubuk(struct SDL_Renderer *);
        int font_size;
        TTF_Font *font;
};

int yan_cubuk::last_click(){ return clicked_number;}

yan_cubuk::yan_cubuk(struct SDL_Renderer *gRenderer){
    this->gRenderer = gRenderer;

    button_ekle(42,75,1,"New LSI",&buttons,1);
    button_ekle(42,225,2,"Convert from LSI",&buttons,2);
    button_ekle(42,375,3,"Settings",&buttons,3);
    clicked_number=1;

    font_size=22;
    font=TTF_OpenFont( "arial.ttf", font_size );
    bttn.w=capx;
    bttn.h=capy;

}

void yan_cubuk::render(){
    SDL_Rect wp;
    wp.x=0;
    wp.w=225;
    wp.y=76;
    wp.h=525;
    SDL_SetRenderDrawColor(gRenderer,0,0,0,0);
    SDL_RenderSetViewport(gRenderer,&wp);
    wp.y=0;
    wp.h=600;
    SDL_RenderFillRect(gRenderer,&wp);
    SDL_SetRenderDrawColor(gRenderer,115,160,255,0);
    SDL_Rect line;
    line.x=220;
    line.w=3;
    line.y=5;
    line.h=450;
    SDL_RenderFillRect(gRenderer,&line);
    SDL_SetRenderDrawColor(gRenderer,120,180,200,0);

    struct members *tmp= NULL;
    tmp=buttons;
    SDL_Color textColor = {255, 255, 255, 255 };

    while (tmp!=NULL){

        if (!tmp->clicked && tmp->mouse_over){
            bttn.x= tmp->x-50;
            bttn.y= tmp->y-20;
            SDL_RenderFillRect(gRenderer,&bttn);

        }

        if (tmp->clicked){
            bttn.x= tmp->x-50;
            bttn.y= tmp->y-20;
            SDL_SetRenderDrawColor(gRenderer,0,0,255,0);
            SDL_RenderFillRect(gRenderer,&bttn);
        }

        string button_name(tmp->names);
        //cout << button_name.c_str() << endl;
        cptn.loadFromRenderedText(tmp->names, textColor, font);
        cptn.render(tmp->x,tmp->y);
        cptn.free();
        button_name = "";

        tmp=tmp->next;
    }

}

void yan_cubuk::handle_events(union SDL_Event *ev){
    int motion_x;
    int motion_y;

    if ( ev->type == SDL_MOUSEMOTION ){
        motion_x = ev->motion.x;
        motion_y = ev->motion.y;

        struct members *tmp= NULL;
        tmp=buttons;

        while (tmp!=NULL){
            if( ( motion_x > tmp->x - 50) && ( motion_x < tmp->x + 170 ) && ( motion_y > tmp->y+55 ) && ( motion_y < tmp->y +110  ) ){
                tmp->mouse_over=true;
            }
            else
                tmp->mouse_over=false;

            tmp=tmp->next;
        }
    }

    if( ev->type == SDL_MOUSEBUTTONDOWN ){
        if( ev->button.button == SDL_BUTTON_LEFT){
            struct members *tmp= NULL;
            tmp=buttons;

            while (tmp!=NULL){

                if (tmp->mouse_over){

                    clicked_number= tmp->no;
                    tmp->clicked=true;
                }

                tmp=tmp->next;
            }

            tmp=buttons;
            while (tmp!=NULL){
                if (tmp->clicked && clicked_number!=tmp->no){
                    tmp->clicked=false;
                }
                tmp=tmp->next;
            }
        }
    }
}




#endif // YAN_CUBUK_H
