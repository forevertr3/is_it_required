#ifndef SUB_SCREEN_H_INCLUDED
#define SUB_SCREEN_H_INCLUDED
#include "elements.h"
#include <SDL2/SDL.h>
#include <stdlib.h>
#include "win_events.h"
#include <string>
#include "converter.h"

class sub{
    SDL_Renderer *rndr;
    SDL_Rect area;
    SDL_Color fill_color;
    struct elements *page=NULL;
    LTexture button_arka;
    int no;
    SDL_Rect button;
    LTexture radio_off;
    LTexture radio_img;
    bool special;
    bool special_mouse_over =false;
    bool special_clicked =false;
    string special_caption;
    int radio_events(union SDL_Event *);
    bool change_radio;
    LTexture special_cap_tex;
    TTF_Font *font;
    SDL_Rect frame;
    LTexture text,text1,text2;
    LTexture question;

  public:
    sub(struct SDL_Renderer *, int);
    void render();
    void handle_events(union SDL_Event *, string );
    void open(const char *);
};

sub::sub(struct SDL_Renderer *rndr, int no){
    this->rndr = rndr;
    button.x =675;
    button.w =100;
    button.y =470;
    button.h =30;

    frame.x =673;
    frame.w =104;
    frame.y =468;
    frame.h =34;

    SDL_Color red={255,0,0};
    font = TTF_OpenFont("arial.ttf", 14);
    string txt="Use SPACE to change convert option!";
    string txt1="Matris=Fast, reliable, up to 350x350pixel(Actually decides your PC hardware and OS)";
    string txt2="Image=Slow, not fully reliable, no limit size";

    text.loadFromRenderedText(txt,red,font);
    text1.loadFromRenderedText(txt1,red,font);
    text2.loadFromRenderedText(txt2,red,font);

    area.x=230;
    area.w=1080-230;
    area.y=76;
    area.h=524;

    this->no=no;
    special = true;
    special_caption = "Add";
    SDL_Color textcolor = {255,255,255,0};
    change_radio=false;
    font = TTF_OpenFont("arial.ttf", 18);
    special_cap_tex.loadFromRenderedText(special_caption.c_str(),textcolor,font);
    button_arka.loadFromFile("b1.png");
    if (no==2){
        question.loadFromFile("quest.png");
    }
    radio_img.loadFromFile("radio_on.png");
    radio_off.loadFromFile("radio.png");
}

void sub::render(){
    SDL_RenderSetViewport(rndr,&area);
    SDL_SetRenderDrawColor(rndr,95,95,94,0);
    fill_color = {95,95,95};
    SDL_Rect fill_rect;
    fill_rect.x=0;
    fill_rect.w=775;
    fill_rect.y=5;
    fill_rect.h=450;
    SDL_RenderFillRect(rndr,&fill_rect);

    struct elements *tmp;
    tmp=page;
    int sirala_x=0;
    int sirala_y=0;
    if (tmp!=NULL){
        while (tmp!=NULL){
            button_arka.render(10+sirala_x,10+sirala_y);
            if (no==1){
                tmp->imgs.render(50+sirala_x,20+sirala_y);
                radio_off.render(200+sirala_x,20+sirala_y);

                if (tmp->tercih==1) radio_img.render(200+sirala_x,20+sirala_y);
                if (tmp->tercih==0) radio_img.render(200+sirala_x,40+sirala_y);

            }
            if (no==2) question.render(50+sirala_x,20+sirala_y);
            tmp->button->render_button(rndr, 200+ sirala_x,80+sirala_y);

            sirala_x+=370;
            if (sirala_x>600){
                sirala_x=0;
                sirala_y+=140;

                if (sirala_y > 400) break;
            }

            tmp=tmp->next;
        }
    }

    if (no==1 || no==2){
        if (!special_clicked)
            SDL_SetRenderDrawColor(rndr,255,60,20,0);
        else
            SDL_SetRenderDrawColor(rndr,0,255,0,0);

        SDL_RenderFillRect(rndr,&button);
        special_cap_tex.render(705,475);

        if (!special_mouse_over)
            SDL_SetRenderDrawColor(rndr,255,60,20,0);
        else
            SDL_SetRenderDrawColor(rndr,0,255,0,0);
        SDL_RenderDrawRect(rndr,&frame);

        text.render(0,460);
        text1.render(0,480);
        text2.render(0,500);

    }
}

void sub::open(const char *image_path){
    element_ekle(0,false,image_path,false,&page);
    LTexture tmp;

    struct elements *tmp_el;
    tmp_el=page;
    if (tmp_el!=NULL){
        while (tmp_el!=NULL){
            if (no==1){
                if (tmp_el->no==0){
                    tmp.free();
                    tmp.loadFromFile(tmp_el->image_path);
                    tmp.Scale(100,100);
                    tmp_el->imgs = tmp;
                    tmp_el->no=1;
                }
            }

            if (no==2){
                tmp=question;
                tmp_el->imgs = tmp;
            }

            tmp_el=tmp_el->next;

        }
    }
}

void sub::handle_events(union SDL_Event *ev, string work_path){
    int motion_x;
    int motion_y;
    //cout << motion_x << " , " << motion_y << endl;

    if ( ev->type == SDL_MOUSEMOTION ){
        motion_x = ev->motion.x;
        motion_y = ev->motion.y;

        if( ( motion_x > button.x+225) && ( motion_x < button.x + button.w +230 ) && ( motion_y > button.y + 70) && ( motion_y < button.y + button.h + 85) ){
            special_mouse_over=true;
        }
        else
           special_mouse_over=false;
    }

    if (ev->type == SDL_KEYDOWN){
        if( ev->key.keysym.sym == SDLK_SPACE ){
            change_radio=true;
        }
    }

    if( ev->type == SDL_MOUSEBUTTONDOWN ){
        if( ev->button.button == SDL_BUTTON_LEFT){
            if (special_mouse_over){
                special_clicked=true;
            }
        }
    }

    if(ev->type == SDL_MOUSEBUTTONUP ){
        if( ev->button.button == SDL_BUTTON_LEFT){
            if (special_mouse_over && special_clicked){
                if (no==1) open(win_event_openfiledialog("Image Files(*.jpg, *.png)\0*.jpg;*.png\0","Open Image"));
                if (no==2) open(win_event_openfiledialog("LSI Files(*.zip, *.lsi, *.txt)\0*.txt;*.lsi;*.zlsi\0","Open LSI"));

            }
            special_clicked=false;
        }
    }

    int l=0;
    struct elements *tmp_el;
    tmp_el=page;
    if (tmp_el!=NULL){
        while (tmp_el!=NULL){
            l=tmp_el->button->handle_event(ev);
            if (change_radio){
                if (tmp_el->tercih==1)
                    tmp_el->tercih=0;
                else
                    tmp_el->tercih=1;
                change_radio=false;
            }
            if (l==1){
                if (no==1) converter_main(tmp_el->image_path, work_path, tmp_el->tercih);
                if (no==2) ters_convert(tmp_el->image_path, work_path);
                break;
            }

            tmp_el=tmp_el->next;
        }
    }
}

#endif // SUB_SCREEN_H_INCLUDED
