#ifndef BUTTON_H_INCLUDED
#define BUTTON_H_INCLUDED

#include <sstream>
#include <string>
#include <iostream>

using namespace std;

class standard_button{                                         /*Hope someday i could use def-windows button*/
    stringstream button;
    bool clicking=false;
    bool mouse_over=false;
    int x,y,cmd;
    int cap_x, cap_y;
    SDL_Rect len;
    bool some_files=true;
  public:
    LTexture ctpn;
    TTF_Font *font;
    int font_size;
    void standard_button_iki(string ,int ,int,int );
    standard_button(string ,int ,int,int );
    void render_button(struct SDL_Renderer *, int ,int );
    void show_at_console();
    int handle_event(union SDL_Event *,bool );
    void over_anim(struct SDL_Renderer *);
    void clicking_anim(struct SDL_Renderer *);

};

standard_button::standard_button(string name,int x ,int y,int cmd){
    button.str(name);
    this->x=x;
    this->y=y;
    this->cmd=cmd;
    len.x=x;
    len.y=y;
    font_size=18;
    font=TTF_OpenFont( "arial.ttf", font_size );                                            /*Bad idea*/
    SDL_Color textColor = { 0, 0, 0, 255 };
    ctpn.loadFromRenderedText(button.str().c_str(), textColor, font);
}

void standard_button::render_button(struct SDL_Renderer *gRenderer, int x, int y){
    this->x=x;
    this->y=y;

    len.x=x;
    len.y=y;
    len.h=30;

    if (button.str().length()<10) len.w=font_size*6;
    else len.w=(font_size*6 + button.str().length()*5);
    cap_y=len.h;
    cap_x=len.w;

   // SDL_RenderSetScale(gRenderer,1.02,1.02);
    if (!some_files && cmd==2) SDL_SetRenderDrawColor( gRenderer,40, 60, 50, 0);
    else SDL_SetRenderDrawColor( gRenderer,60, 127, 167, 0);
    SDL_RenderDrawRect(gRenderer,&len);
    if (!some_files && cmd==2) SDL_SetRenderDrawColor( gRenderer,30, 20, 48, 0);
    else SDL_SetRenderDrawColor( gRenderer,68, 209, 245, 0);
    len.x+=1;
    len.y+=1;
    len.h-=2;
    len.w-=2;
    SDL_RenderDrawRect(gRenderer,&len);
    SDL_SetRenderDrawColor( gRenderer, 235, 238, 239 ,255);
    len.x+=1;
    len.y+=1;
    len.w-=2;
    len.h=len.h/2;
    SDL_RenderFillRect(gRenderer,&len);
    SDL_SetRenderDrawColor( gRenderer, 210, 214, 216 ,255);
    len.y+=len.h-2;
    SDL_RenderFillRect(gRenderer,&len);

    if (some_files){
        if (mouse_over) over_anim(gRenderer);
        if (clicking && mouse_over) clicking_anim(gRenderer);
    }
    ctpn.render((x+(cap_x/2)-(button.str().length()*5.2)),y+((cap_y-font_size)/2));

}

int standard_button::handle_event(union SDL_Event *ev, bool html5=true){
    int motion_x;
    int motion_y;

    if ( ev->type == SDL_MOUSEMOTION ){
        if (html5){

            motion_x = ev->motion.x;
            motion_y = ev->motion.y;

           // cout<<  this->x << " , " << this->y << endl;
           // cout<<  motion_x << " , " << motion_y << endl;

            if( ( motion_x > this->x + 230) && ( motion_x < this->x + cap_x +230 ) && ( motion_y > this->y + 65) && ( motion_y < this->y + cap_y +75) ){
                mouse_over=true;

            }
            else
                mouse_over=false;
        }
    }

    if( ev->type == SDL_MOUSEBUTTONDOWN ){
        if( ev->button.button == SDL_BUTTON_LEFT){
            clicking=true;
        }
    }

    if(ev->type == SDL_MOUSEBUTTONUP ){
        if( ev->button.button == SDL_BUTTON_LEFT){
            clicking=false;
            if (mouse_over){
                return cmd;
            }
        }
    }
    return 11;
}

void standard_button::show_at_console(){
  cout << button.str() << endl ;
  cout << ""<< button.str().length();

}

void standard_button::over_anim(struct SDL_Renderer *gRenderer){
    SDL_SetRenderDrawColor( gRenderer, 0, 0, 0 ,255);

    for (int i=0; i<=cap_x; i+=15){
        if (i+10 > cap_x){
            SDL_RenderDrawLine(gRenderer, x+i, y+1, x+cap_x, y+1);
            SDL_RenderDrawLine(gRenderer, x+i, y+cap_y-2, x+cap_x, y+cap_y-2);
            break;
        }
        SDL_RenderDrawLine(gRenderer, x+i, y+1, x+i+10, y+1);
        SDL_RenderDrawLine(gRenderer, x+i, y+cap_y-2, x+i+10, y+cap_y-2);
    }

    for (int i=0; i<=cap_y; i+=15){
        if (i+10 > cap_y){
            SDL_RenderDrawLine(gRenderer, x+1, y+i, x+1, y+cap_y);
            SDL_RenderDrawLine(gRenderer, x+cap_x-2, y+i, x+cap_x-2, y+cap_y);
            break;
        }
        SDL_RenderDrawLine(gRenderer, x+1, y+i, x+1, y+i+10);
        SDL_RenderDrawLine(gRenderer, x+cap_x-2, y+i, x+cap_x-2, y+i+10);
    }
}

void standard_button::clicking_anim(struct SDL_Renderer *gRenderer){
    SDL_Rect click_white;
    click_white.x=x+2;
    click_white.y=y+2;
    click_white.w=cap_x-4;
    click_white.h=(cap_y-4)/2+1;

    SDL_SetRenderDrawColor( gRenderer, 210, 214, 216 ,255);
    SDL_RenderFillRect(gRenderer, &click_white);
    SDL_SetRenderDrawColor( gRenderer, 235, 238, 239 ,255);
    click_white.y=y+(cap_y-4)/2+1;
    SDL_RenderFillRect(gRenderer, &click_white);
}
#endif // BUTTON_H_INCLUDED
