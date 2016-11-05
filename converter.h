#ifndef CONVERTER_H_INCLUDED
#define CONVERTER_H_INCLUDED
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <sstream>
#include <fstream>
#include "Image.h"
#include <SDL2/SDL_ttf.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "texture.h"
#include "zip.h"

int SCREEN_WIDTH_A = 500;
int SCREEN_HEIGHT_A = 500;

SDL_Window* gaWindow = NULL;
SDL_Renderer* gaRenderer = NULL;

void window_new(struct SDL_Surface *_ret, const char *symbol, string work_path){                    /*POPout win*/
     cout << "Pop up Screen" << endl;

    if (symbol=="M") gaWindow = SDL_CreateWindow( "SUCSESS", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH_A, SCREEN_HEIGHT_A,  SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );
    if (symbol=="S") gaWindow = SDL_CreateWindow( "SUCSESS", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 400, 100,  SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );
    if (symbol=="Q") gaWindow = SDL_CreateWindow( "Method", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 400, 100,  SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );
    gaRenderer = SDL_CreateRenderer( gaWindow, -1, SDL_RENDERER_TARGETTEXTURE);

    SDL_Event ev;
    work_path+="\\";

    SDL_Rect all_screen;
    all_screen.x=0;
    all_screen.w=600;
    all_screen.y=0;
    all_screen.h=600;

    if (symbol=="M") SDL_SetRenderDrawColor(gaRenderer,0,0,0,0);
    if (symbol=="S") SDL_SetRenderDrawColor(gaRenderer,255,255,255,0);

    bool quit=false;
    SDL_Rect renderQuad;
    if (_ret!=NULL) renderQuad = { 0, 0, _ret->h, _ret->w };
    SDL_Texture *out=NULL;
    if (_ret!=NULL) out= SDL_CreateTextureFromSurface( gaRenderer, _ret);
    int b=0;
    standard_button button_sucsess("DONE!",200,50,1);          /*"DONE" never show up why? need a proper button*/
    cout << "Pop up Main module"<< endl;
    LTexture pres_esc;
    SDL_Color green={0,255,0};
    string esc="SUCCESS! Press ESC!";
    pres_esc.loadFromRenderedText(esc,green,NULL,0,gaRenderer);


    while (!quit){
        SDL_RenderFillRect(gaRenderer,&all_screen);

        if ( SDL_PollEvent( &ev ) != 0){
             if (ev.type==SDL_QUIT){                            /*Event handler kinda broken dont know why*/
                 quit=true;                                     /*even though this if block wont be using*/
             }                                                  /*When i delete this block event handler wont work and crash*/
        }

        if (ev.type == SDL_WINDOWEVENT) {
            if (ev.window.event == SDL_WINDOWEVENT_CLOSE) {
                SDL_DestroyWindow(gaWindow);
                quit=true;

            }
        }

        if (ev.type == SDL_KEYDOWN){
            if( ev.key.keysym.sym == SDLK_ESCAPE ){
                SDL_DestroyWindow(gaWindow);
                quit=true;
            }
        }


        if (_ret==NULL){ button_sucsess.handle_event(&ev);  button_sucsess.render_button(gaRenderer,150,50);}
        if (_ret!=NULL)
                SDL_RenderCopyEx( gaRenderer, out, NULL, &renderQuad, 0.0, NULL, SDL_FLIP_NONE  );
        if (_ret==NULL) pres_esc.render(100,20,gaRenderer);

        SDL_RenderPresent(gaRenderer);
    }

}


bool algorithm0_directly_image(const char *img){
    int b=0,c=0;

    SDL_Surface *_temporary;
    _temporary = IMG_Load( img );
    //SDL_SetColorKey( _temporary, SDL_TRUE, SDL_MapRGBA( _temporary->format, 0, 0xFF, 0xFF, 0 ));

    string  img_name=img;
    size_t found = img_name.find_last_of("/\\");
    img_name=img_name.substr(found+1);
    found = img_name.find_last_of(".");
    img_name = img_name.substr(0,found);
    img_name+=".lsi";
    cout << "Name: "  << img_name <<endl;


    int main_w, main_h;
    int big;
    main_w=_temporary->w;
    main_h=_temporary->h;

    big=main_w;
    if (main_h>main_w)
        big=main_h;

    SDL_Surface *normalize=NULL;
    normalize=SDL_CreateRGBSurface(1,big,big,24,0x0000FF,0x00FF00,0xFF0000,0);


    FILE *a;
    a=fopen(img_name.c_str(),"w+b");
    fprintf(a,"%d %d",_temporary->h,_temporary->w);

    b=0; c=0;
    bool done=false;
    SDL_Color clr;
    int r,g,bl,some,some1,some2;

    puts("\n");
    cout << "Width: " << main_w << "   Height: " << main_h << endl;

    while (c<main_h){
        while (b<main_w){
            clr=color_returner_surface(_temporary,b,c);
            r=clr.r;
            g=clr.g;
            bl=clr.b;

                                                                   ///Get color
            if (r<=10 || r==33 || r==34) r=35;                                         ///SKIP these color ? :S
            if (g<=10 || g==33 || g==34) g=35;
            if (bl<=10 || bl==33 || bl==34) bl=35;

            if (r>=48 && r<=57) r=47;                             ///SKIP THE ALREADY NUMBER CHARS Have no solition 9+12 pixels skipped
            if (g>=48 && g<=57) g=47;                               ///Need a solition
            if (bl>=48 && bl<=57) bl=47;                            ///2 763 909 of 16 581 375 color lost here,
                                                                      ///Not noticeable anyway


            DrawPixel(&normalize,b,c,SDL_MapRGBA(normalize->format,r,g,bl,0));
            b++;
        }
        c++;
        b=0;
    }

    cout << "normalized" << endl;

   // window_new(more_normalized,"M","sd");

    c=0; b=0;
    bool right=false;
    bool down=false;
    int right_row=0;
    int down_row=0;
    int current_b;
    int current_c;
    int i;
    int verim=0;

///****************************RED********////

    while (c<main_h){
        while (b<main_w){
            some = static_cast<int>((color_returner_surface(normalize,b,c).r));
            if (some!=34){
                ///*Check Right*//
                if (b<main_w-2){

                    some = static_cast<int>((color_returner_surface(normalize,b,c).r));
                    some1 = static_cast<int>((color_returner_surface(normalize,b+1,c).r));
                    some2 = static_cast<int>((color_returner_surface(normalize,b+2,c).r));

                    if (some == some1 && some == some2){
                        /*DEBUG
                        if (matrix[0][c][b] != matrix[0][c][b+1] || matrix[0][c][b] != matrix[0][c][b+2]){
                            cout << "Cnt: " << cnt << "  ColorM: " << matrix[0][c][b] << "  ColorI: "
                                << some  << "  ColorM1: " << matrix[0][c][b+1] << "  ColorI1: " << some1 << endl;
                        }*/

                        //cout << "M: " << matrix[0][c][b] << "  Sur: " << static_cast<int>((color_returner_surface(normalize,b+2,c).r)) << endl;
                        //getchar();

                        right=true;
                    }
                    else
                        right=false;
                }

                else
                    right=false;

                ///*Count Right*///
                if (right){
                    right_row=2;
                    i=3;

                    clr= color_returner_surface(normalize,b+1,c);
                    DrawPixel(&normalize,b+1,c,SDL_MapRGBA(_temporary->format,34,clr.g,clr.b,0));
                    clr= color_returner_surface(normalize,b+2,c);
                    DrawPixel(&normalize,b+2,c,SDL_MapRGBA(_temporary->format,34,clr.g,clr.b,0));

                    verim+=2;                                   ///Lock 2

                    while (b+i<main_w){                                  ///Until Rightest Number
                        some = static_cast<int>((color_returner_surface(normalize,b,c).r));
                        some1 = static_cast<int>((color_returner_surface(normalize,b+i,c).r));

                        if (some==some1){
                            clr= color_returner_surface(normalize,b+i,c);
                            DrawPixel(&normalize,b+i,c,SDL_MapRGBA(_temporary->format,34,clr.g,clr.b,0));
                            verim++;
                            right_row++;
                        }
                        else
                            break;
                        i++;
                    }
                }

                else
                    right_row=0;

                ///*Check Colomn*///
                if (c<main_h-2){
                    some = static_cast<int>((color_returner_surface(normalize,b,c).r));
                    some1 = static_cast<int>((color_returner_surface(normalize,b,c+1).r));
                    some2 = static_cast<int>((color_returner_surface(normalize,b,c+2).r));

                    if (some==some1 && some==some2){
                        down=true;                                                     ///Check
                    }
                    else
                        down=false;
                }

                else
                    down=false;

               ///*Count Down*///
                if (down){
                    down_row=2;
                    i=3;

                    clr= color_returner_surface(normalize,b,c+1);
                    DrawPixel(&normalize,b,c+1,SDL_MapRGBA(_temporary->format,34,clr.g,clr.b,0));
                    clr= color_returner_surface(normalize,b,c+2);
                    DrawPixel(&normalize,b,c+2,SDL_MapRGBA(_temporary->format,34,clr.g,clr.b,0));

                    verim+=2;                                   ///Lock 2

                    while (c+i<main_h){                                  ///Until Downest Number
                        some = static_cast<int>((color_returner_surface(normalize,b,c).r));
                        some1 = static_cast<int>((color_returner_surface(normalize,b,c+i).r));

                        if (some==some1){
                            clr= color_returner_surface(normalize,b,c+i);
                            DrawPixel(&normalize,b,c+i,SDL_MapRGBA(_temporary->format,34,clr.g,clr.b,0));              ///Lock
                            verim++;
                            down_row++;
                        }
                        else
                            break;
                        i++;
                    }
                }

                else
                    down_row=0;

                /*//Then Write Console DEBUG
                if (c+1==main_h && b+1==main_w){
                    //getchar();
                    system("cls");

                    printf("   ");
                    for (i=0; i<main_w; i++){
                       printf("%4d",i);
                    }
                    printf("\n");
                    printf("--------------------------------------------------------------------------------------\n");

                    for (i=0; i<main_h; i++){
                        if (i<10) printf("%d| ",i);
                        else printf("%d|",i);
                        for (int j=0; j<main_w; j++){
                            printf("%4d",matrix[i][j]);
                        }
                        printf("\n");
                    }

                    printf("Pos= [%d, %d]\n",c,b);
                    if (right) printf("Right: True, %d\n",right_row);
                    if (!right) printf("Right: False, %d\n",right_row);
                    if (down) printf("Down: True, %d",down_row);
                    if (!down) printf("Down: False, %d",down_row);
                    printf("\nVerim: %d/%d\n",verim,main_h*main_w);
                    printf("%c\n",matrix[c][b]);
                    if (right) printf("%c%d",33,right_row);
                    if (down)  printf("%c%d",34,down_row);
                }
                */
                ///Write in the File
                some = static_cast<int>((color_returner_surface(normalize,b,c).r));
                fprintf(a,"%c",some);
                if (right) fprintf(a,"%c%d",33,right_row);
                if (down)  fprintf(a,"%c%d",34,down_row);

            }
            b++;
        }
        b=0;
        c++;
    }
///*************************GREEEN*****///
    fprintf(a,"\n");
    b=0; c=0;
    while (c<main_h){
        while (b<main_w){
                 some = static_cast<int>((color_returner_surface(normalize,b,c).g));
            if (some!=34){
                ///*Check Right*//
                if (b<main_w-2){
                    some = static_cast<int>((color_returner_surface(normalize,b,c).g));
                    some1 = static_cast<int>((color_returner_surface(normalize,b+1,c).g));
                    some2 = static_cast<int>((color_returner_surface(normalize,b+2,c).g));                                                        ///Skip end of row
                    if (some==some1 && some==some2){
                        right=true;                                                     ///Check
                    }
                    else
                        right=false;
                }

                else
                    right=false;

                ///*Count Right*///
                if (right){
                    right_row=2;
                    i=3;
                    clr= color_returner_surface(normalize,b+1,c);
                    DrawPixel(&normalize,b+1,c,SDL_MapRGBA(_temporary->format,clr.r,34,clr.b,0));
                    clr= color_returner_surface(normalize,b+2,c);
                    DrawPixel(&normalize,b+2,c,SDL_MapRGBA(_temporary->format,clr.r,34,clr.b,0));

                    verim+=2;                                   ///Lock 2
                    while (b+i<main_w){                                  ///Until Rightest Number
                        some = static_cast<int>((color_returner_surface(normalize,b,c).g));
                        some1 = static_cast<int>((color_returner_surface(normalize,b+i,c).g));

                        if (some==some1){
                            clr= color_returner_surface(normalize,b+i,c);
                            DrawPixel(&normalize,b+i,c,SDL_MapRGBA(_temporary->format,clr.r,34,clr.b,0));                           ///Lock
                            verim++;
                            right_row++;
                        }
                        else
                            break;
                        i++;
                    }
                }

                else
                    right_row=0;

                ///*Check Colomn*///
                if (c<main_h-2){
                    some = static_cast<int>((color_returner_surface(normalize,b,c).g));
                    some1 = static_cast<int>((color_returner_surface(normalize,b,c+1).g));
                    some2 = static_cast<int>((color_returner_surface(normalize,b,c+2).g));

                    if (some == some1 && some == some2){
                        down=true;                                                     ///Check
                    }
                    else
                        down=false;
                }

                else
                    down=false;

               ///*Count Down*///
                if (down){
                    down_row=2;
                    i=3;

                    clr= color_returner_surface(normalize,b,c+1);
                    DrawPixel(&normalize,b,c+1,SDL_MapRGBA(_temporary->format,clr.r,34,clr.b,0));
                    clr= color_returner_surface(normalize,b,c+2);
                    DrawPixel(&normalize,b,c+2,SDL_MapRGBA(_temporary->format,clr.r,34,clr.b,0));
                    verim+=2;                                   ///Lock 2

                    while (c+i<main_h){
                        some = static_cast<int>((color_returner_surface(normalize,b,c).g));
                        some1 = static_cast<int>((color_returner_surface(normalize,b,c+i).g));
                        if (some==some1){
                            clr= color_returner_surface(normalize,b,c+i);
                            DrawPixel(&normalize,b,c+i,SDL_MapRGBA(_temporary->format,clr.r,34,clr.b,0));                          ///Lock
                            verim++;
                            down_row++;
                        }
                        else
                            break;
                        i++;
                    }
                }

                else
                    down_row=0;

                ///Write in the File
                some = static_cast<int>((color_returner_surface(normalize,b,c).g));
                fprintf(a,"%c",some);
                if (right) fprintf(a,"%c%d",33,right_row);
                if (down)  fprintf(a,"%c%d",34,down_row);

            }
            b++;
        }
        b=0;
        c++;
    }

///*******************BLUE**************///
    fprintf(a,"\n");
    b=0; c=0;
    while (c<main_h){
        while (b<main_w){
            some = static_cast<int>((color_returner_surface(normalize,b,c).b));
            if (some!=34){
                ///*Check Right*//
                if (b<main_w-2){
                    some = static_cast<int>((color_returner_surface(normalize,b,c).b));
                    some1 = static_cast<int>((color_returner_surface(normalize,b+1,c).b));
                    some2 = static_cast<int>((color_returner_surface(normalize,b+2,c).b));       ///Skip end of row

                    if (some == some1 && some == some2){
                        right=true;                                                     ///Check
                    }
                    else
                        right=false;
                }

                else
                    right=false;

                ///*Count Right*///
                if (right){
                    right_row=2;
                    i=3;

                    DrawPixel(&normalize,b+1,c,SDL_MapRGBA(_temporary->format,clr.r,clr.g,34,0));
                    DrawPixel(&normalize,b+2,c,SDL_MapRGBA(_temporary->format,clr.r,clr.g,34,0));
                    verim+=2;                                   ///Lock 2

                    while (b+i<main_w){                                  ///Until Rightest Number
                        some = static_cast<int>((color_returner_surface(normalize,b,c).b));
                        some1 = static_cast<int>((color_returner_surface(normalize,b+i,c).b));

                        if (some==some1){
                            DrawPixel(&normalize,b+i,c,SDL_MapRGBA(_temporary->format,clr.r,clr.g,34,0));
                            verim++;
                            right_row++;
                        }
                        else
                            break;
                        i++;
                    }
                }

                else
                    right_row=0;

                ///*Check Colomn*///
                if (c<main_h-2){
                    some = static_cast<int>((color_returner_surface(normalize,b,c).b));
                    some1 = static_cast<int>((color_returner_surface(normalize,b,c+1).b));
                    some2 = static_cast<int>((color_returner_surface(normalize,b,c+2).b));

                    if (some == some1 && some == some2){
                        down=true;                                                     ///Check
                    }
                    else
                        down=false;
                }

                else
                    down=false;

               ///*Count Down*///
                if (down){
                    down_row=2;
                    i=3;
                    DrawPixel(&normalize,b,c+1,SDL_MapRGBA(_temporary->format,clr.r,clr.g,34,0));
                    DrawPixel(&normalize,b,c+2,SDL_MapRGBA(_temporary->format,clr.r,clr.g,34,0));
                    verim+=2;

                    while (c+i<main_h){                                  ///Until Downest Number
                        some = static_cast<int>((color_returner_surface(normalize,b,c).b));
                        some1 = static_cast<int>((color_returner_surface(normalize,b,c+i).b));
                        if (some==some1){
                            DrawPixel(&normalize,b,c+i,SDL_MapRGBA(_temporary->format,clr.r,clr.g,34,0));                         ///Lock
                            verim++;
                            down_row++;
                        }
                        else
                            break;
                        i++;
                    }
                }

                else
                    down_row=0;


                ///Write in the File
                some = static_cast<int>((color_returner_surface(normalize,b,c).b));
                fprintf(a,"%c",some);
                if (right) fprintf(a,"%c%d",33,right_row);
                if (down)  fprintf(a,"%c%d",34,down_row);

            }
            b++;
        }
        b=0;
        c++;
    }

///******************************************//////////////////////

    fclose(a);
    //delete matrix;
    cout << "Writing Done, Verim: " << verim <<endl ;
    return true;
}

bool algorithm0_use_matris(const char *img){
    int b=0,c=0;
    LTexture temporary;
    temporary.loadFromFile(img);

    string  img_name=img;
    size_t found = img_name.find_last_of("/\\");
    img_name=img_name.substr(found+1);
    found = img_name.find_last_of(".");
    img_name = img_name.substr(0,found);
    img_name+=".lsi";
    cout << "Name: "  << img_name <<endl;

    int main_w=temporary.getWidth();
    int main_h=temporary.getHeight();

    std::cout << main_h <<" , "<< main_w << std::endl;
    FILE *a;
    a=fopen(img_name.c_str(),"w+b");
    fprintf(a,"%d %d",main_h,main_w);

    short matrix[3][main_h][main_w];

    b=0;
    bool done=false;
    SDL_Color clr;
    int r,g,bl;

    while (c<main_h){
        while (b<main_w){
            clr=temporary.color_returner(b,c);
            r=clr.r;
            g=clr.g;
            bl=clr.b;                                            
            if (r<35) r=35;                                         
            if (g<35) g=35;
            if (bl<35) bl=35;

            if (r>=48 && r<=57) r=47;                             
            if (g>=48 && g<=57) g=47;                              
            if (bl>=48 && bl<=57) bl=47;                            
                                                                   

            matrix[0][c][b]=r;
            matrix[1][c][b]=g;
            matrix[2][c][b]=bl;

            b++;
        }
        c++;
        b=0;
    }

    c=0; b=0;
    bool right=false;
    bool down=false;
    int right_row=0;
    int down_row=0;
    int current_b;
    int current_c;
    int i;
    int verim=0;

///****************************RED********////

    while (c<main_h){
        while (b<main_w){
            if (matrix[0][c][b]!=-1){
                ///*Check Right*//
                if (b<main_w-2){                                                        ///Skip end of row
                    if (matrix[0][c][b]==matrix[0][c][b+1] && matrix[0][c][b]==matrix[0][c][b+2]){
                        right=true;                                                     ///Check
                    }
                    else
                        right=false;
                }

                else
                    right=false;

                ///*Count Right*///
                if (right){
                    current_b=b;
                    right_row=2;
                    i=3;
                    matrix[0][c][b+1]=-1;
                    matrix[0][c][b+2]=-1;
                    verim+=2;                                   ///Lock 2

                    while (b+i<main_w){                                  ///Until Rightest Number
                        if (matrix[0][c][b]==matrix[0][c][b+i]){
                            matrix[0][c][b+i]=-1;                           ///Lock
                            verim++;
                            right_row++;
                        }
                        else
                            break;
                        i++;
                    }
                }

                else
                    right_row=0;

                ///*Check Colomn*///
                if (c<main_h-2){
                    if (matrix[0][c][b]==matrix[0][c+1][b] && matrix[0][c][b]==matrix[0][c+2][b]){
                        down=true;                                                     ///Check
                    }
                    else
                        down=false;
                }

                else
                    down=false;

               ///*Count Down*///
                if (down){
                    current_c=c;
                    down_row=2;
                    i=3;
                    matrix[0][c+1][b]=-1;
                    matrix[0][c+2][b]=-1;
                    verim+=2;                                   ///Lock 2

                    while (c+i<main_h){                                  ///Until Downest Number
                        if (matrix[0][c][b]==matrix[0][c+i][b]){
                            matrix[0][c+i][b]=-1;                           ///Lock
                            verim++;
                            down_row++;
                        }
                        else
                            break;
                        i++;
                    }
                }

                else
                    down_row=0;

                /*//Then Write Console
                if (c+1==main_h && b+1==main_w){
                    //getchar();
                    system("cls");

                    printf("   ");
                    for (i=0; i<main_w; i++){
                       printf("%4d",i);
                    }
                    printf("\n");
                    printf("--------------------------------------------------------------------------------------\n");

                    for (i=0; i<main_h; i++){
                        if (i<10) printf("%d| ",i);
                        else printf("%d|",i);
                        for (int j=0; j<main_w; j++){
                            printf("%4d",matrix[i][j]);
                        }
                        printf("\n");
                    }

                    printf("Pos= [%d, %d]\n",c,b);
                    if (right) printf("Right: True, %d\n",right_row);
                    if (!right) printf("Right: False, %d\n",right_row);
                    if (down) printf("Down: True, %d",down_row);
                    if (!down) printf("Down: False, %d",down_row);
                    printf("\nVerim: %d/%d\n",verim,main_h*main_w);
                    printf("%c\n",matrix[c][b]);
                    if (right) printf("%c%d",33,right_row);
                    if (down)  printf("%c%d",34,down_row);
                }
                */
                ///Write in the File
                fprintf(a,"%c",matrix[0][c][b]);
                if (right) fprintf(a,"%c%d",33,right_row);
                if (down)  fprintf(a,"%c%d",34,down_row);

            }
            b++;
        }
        b=0;
        c++;
    }
///*************************GREEEN*****///
    fprintf(a,"\n");
    b=0; c=0;
    while (c<main_h){
        while (b<main_w){
            if (matrix[1][c][b]!=-1){
                ///*Check Right*//
                if (b<main_w-2){                                                        ///Skip end of row
                    if (matrix[1][c][b]==matrix[1][c][b+1] && matrix[1][c][b]==matrix[1][c][b+2]){
                        right=true;                                                     ///Check
                    }
                    else
                        right=false;
                }

                else
                    right=false;

                ///*Count Right*///
                if (right){
                    current_b=b;
                    right_row=2;
                    i=3;
                    matrix[1][c][b+1]=-1;
                    matrix[1][c][b+2]=-1;
                    verim+=2;                                   ///Lock 2

                    while (b+i<main_w){                                  ///Until Rightest Number
                        if (matrix[1][c][b]==matrix[1][c][b+i]){
                            matrix[1][c][b+i]=-1;                           ///Lock
                            verim++;
                            right_row++;
                        }
                        else
                            break;
                        i++;
                    }
                }

                else
                    right_row=0;

                ///*Check Colomn*///
                if (c<main_h-2){
                    if (matrix[1][c][b]==matrix[1][c+1][b] && matrix[1][c][b]==matrix[1][c+2][b]){
                        down=true;                                                     ///Check
                    }
                    else
                        down=false;
                }

                else
                    down=false;

               ///*Count Down*///
                if (down){
                    current_c=c;
                    down_row=2;
                    i=3;
                    matrix[1][c+1][b]=-1;
                    matrix[1][c+2][b]=-1;
                    verim+=2;                                   ///Lock 2

                    while (c+i<main_h){                                  ///Until Downest Number
                        if (matrix[1][c][b]==matrix[1][c+i][b]){
                            matrix[1][c+i][b]=-1;                           ///Lock
                            verim++;
                            down_row++;
                        }
                        else
                            break;
                        i++;
                    }
                }

                else
                    down_row=0;

                ///Write in the File
                fprintf(a,"%c",matrix[1][c][b]);
                if (right) fprintf(a,"%c%d",33,right_row);
                if (down)  fprintf(a,"%c%d",34,down_row);

            }
            b++;
        }
        b=0;
        c++;
    }

///*******************BLUE**************///
    fprintf(a,"\n");
    b=0; c=0;
    while (c<main_h){
        while (b<main_w){
            if (matrix[2][c][b]!=-1){
                ///*Check Right*//
                if (b<main_w-2){                                                        ///Skip end of row
                    if (matrix[2][c][b]==matrix[2][c][b+1] && matrix[2][c][b]==matrix[2][c][b+2]){
                        right=true;                                                     ///Check
                    }
                    else
                        right=false;
                }

                else
                    right=false;

                ///*Count Right*///
                if (right){
                    current_b=b;
                    right_row=2;
                    i=3;
                    matrix[2][c][b+1]=-1;
                    matrix[2][c][b+2]=-1;
                    verim+=2;                                   ///Lock 2

                    while (b+i<main_w){                                  ///Until Rightest Number
                        if (matrix[2][c][b]==matrix[2][c][b+i]){
                            matrix[2][c][b+i]=-1;                           ///Lock
                            verim++;
                            right_row++;
                        }
                        else
                            break;
                        i++;
                    }
                }

                else
                    right_row=0;

                ///*Check Colomn*///
                if (c<main_h-2){
                    if (matrix[2][c][b]==matrix[2][c+1][b] && matrix[2][c][b]==matrix[2][c+2][b]){
                        down=true;                                                     ///Check
                    }
                    else
                        down=false;
                }

                else
                    down=false;

               ///*Count Down*///
                if (down){
                    current_c=c;
                    down_row=2;
                    i=3;
                    matrix[2][c+1][b]=-1;
                    matrix[2][c+2][b]=-1;
                    verim+=2;                                   ///Lock 2

                    while (c+i<main_h){                                  ///Until Downest Number
                        if (matrix[2][c][b]==matrix[2][c+i][b]){
                            matrix[2][c+i][b]=-1;                           ///Lock
                            verim++;
                            down_row++;
                        }
                        else
                            break;
                        i++;
                    }
                }

                else
                    down_row=0;


                ///Write in the File
                fprintf(a,"%c",matrix[2][c][b]);
                if (right) fprintf(a,"%c%d",33,right_row);
                if (down)  fprintf(a,"%c%d",34,down_row);

            }
            b++;
        }
        b=0;
        c++;
    }

///******************************************//////////////////////

    fclose(a);
    //delete matrix;
    free(matrix);
    temporary.free();
    cout << "Writing Done, Verim: " << verim <<endl ;
    return true;
}

int get_file_size(std::string filename) // path to file
{
    cout << "Get file size" << endl;
    FILE *p_file = NULL;
    p_file = fopen(filename.c_str(),"rb");
    fseek(p_file,0,SEEK_END);
    int size = ftell(p_file);
    fclose(p_file);
    return size;
}


void zip_and_choose_file(string Path, string work){
    int size_f,size_zf;
    string path_txt;
    size_t found = Path.find_last_of(".");
    Path=Path.substr(0,found);
    path_txt=Path;

    path_txt+= ".lsi";
    Path+=".zip";

    string name;
    name = path_txt;

    found = name.find_last_of("/\\");
    name = name.substr(found+1);
    found = name.find_last_of(".");
    name = name.substr(0,found);
    name += ".lsi";
    //cout << path_txt << "   " << Path << "  " << name << endl;

/*    HZIP hz = CreateZip(Path.c_str(),0);
    ZipAdd(hz,name.c_str(), path_txt.c_str());
    CloseZip(hz);

    size_zf=get_file_size(Path);
    size_f=get_file_size(path_txt);*/

    //if (size_zf>size_f) remove(Path.c_str());            /*cHOOSE ZIP or not currenty not working good*/
    //else remove(path_txt.c_str());

}

int converter_main(const char *img, string work_path, int chooser){

   // algorithm0_directly_image_CMYK(img);

    if (chooser==1){
    if (algorithm0_use_matris(img)){
        SDL_Surface *_ret=NULL;
        window_new(_ret, "S", work_path);
        zip_and_choose_file(img, work_path);
        cout << "Matris encode Done" << endl;
    }
    }

    if (chooser==0){
    if (algorithm0_directly_image(img)){
        SDL_Surface *_ret=NULL;
        window_new(_ret, "S", work_path);
        zip_and_choose_file(img, work_path);
        cout << "Direct Encode Done" << endl;
    }
    }





}

bool de_algorith0(const char *path, string work_path){   /*Not used*/

    FILE *re;
    re=fopen(path,"rb");
    string name=path;
    string uz;

    size_t found = name.find_last_of("/\\");
    name=name.substr(found+1);
    found = name.find_last_of(".");
    uz = name.substr(found+1);
    name = name.substr(0,found);
    cout << "U: " << uz ;

    if (uz=="zip" || uz== "ZIP") cout << "Needs unzip" << endl;

    int main_w;
    int main_h;
    int b=0; int c=0;
    fscanf(re,"%d %d",&main_h,&main_w);
    short matrix[3][main_h][main_w];

    if (main_w<main_h || main_w>400 || main_h>400)
        return false;

    SDL_Surface *_ret=NULL;
    _ret=SDL_CreateRGBSurface(0,main_h,main_w,32,0,0,0,0);
    int i=0;
    int k;
    if (re==NULL) cout << "ER1" << endl;
    int pixel=0;
    int j=0;
    int first,temp,number;
    int point_c,point_b;

    while (c<main_h){
        while (b<main_w){                         ///Fill matrix 0
            matrix[0][c][b]=0;
            matrix[1][c][b]=0;
            matrix[2][c][b]=0;
            b++;
        }
        b=0;
        c++;
    }

///**********************RED*******************

    bool quit=false;

    c=0; b=0;
    while (!quit){
         if (matrix[0][c][b]==0){
            first=fgetc(re);

            if (first==33){
                fscanf(re,"%d",&number);
                for (i=0;i<number; i++){
                    matrix[0][c][b+i]=temp;
                }
            }

            else if (first==34){
                fscanf(re,"%d",&number);
                b--;
                for (i=0;i<=number; i++){
                    matrix[0][point_c+i][point_b]=temp;
                }
            }

            else {
                matrix[0][c][b]=first;
                temp=first;
                point_c=c;
                point_b=b;
            }

        }
        j++;
        b++;

        if (b!=0 && b%main_w==0){
            b=0;
            c++;
        }
        if (c!=0 && c%(main_h)==0){
            quit=true;

           /* Write
            system("cls");
            printf("   ");
            for (i=0; i<main_w; i++){
                printf("%4d",i);
            }
            printf("\n");
            printf("--------------------------------------------------------------------------------------\n");

            for (i=0; i<main_h; i++){
                if (i<10) printf("%d| ",i);
                else printf("%d|",i);
                for (int j=0; j<main_w; j++){
                    printf("%4d",matrix[i][j]);
                }
                printf("\n");
            }
            printf("\nPos: [%d, %d]\n",b,c);
            if (first==33) printf("Ch= Row\n");
            else if (first==34) printf("Ch= Column\n");
            else printf("Ch= %c\n",first);
            printf("Num: %d\n",number);
            printf("Temp= %d\n",temp);*/
        }
    }

//*************GREEEN************
    quit=false;
    first=fgetc(re);
    printf("CH: %c, %d\n",first,first);


    c=0; b=0;
    while (!quit){
         if (matrix[1][c][b]==0){
            first=fgetc(re);

            if (first==33){
                fscanf(re,"%d",&number);
                for (i=0;i<number; i++){
                    matrix[1][c][b+i]=temp;
                }
            }

            else if (first==34){
                fscanf(re,"%d",&number);
                b--;
                for (i=0;i<=number; i++){
                    matrix[1][point_c+i][point_b]=temp;
                }
            }

            else {
                matrix[1][c][b]=first;
                temp=first;
                point_c=c;
                point_b=b;
            }

        }
        j++;
        b++;

        if (b!=0 && b%main_w==0){
            b=0;
            c++;
        }
        if (c!=0 && c%main_h==0){
            quit=true;
        }
    }

///***************************BLUE********************

   quit=false;
   first=fgetc(re);
   printf("CH: %c, %d\n",first,first);

   c=0; b=0;
   while (!quit){
         if (matrix[2][c][b]==0){
            first=fgetc(re);

            if (first==33){
                fscanf(re,"%d",&number);
                for (i=0;i<number; i++){
                    matrix[2][c][b+i]=temp;
                }
            }

            else if (first==34){
                fscanf(re,"%d",&number);
                b--;
                for (i=0;i<=number; i++){
                    matrix[2][point_c+i][point_b]=temp;
                }
            }

            else {
                matrix[2][c][b]=first;
                temp=first;
                point_c=c;
                point_b=b;
            }

        }
        b++;

        if (b!=0 && b%main_w==0){
            b=0;
            c++;
        }
        if (c!=0 && c%main_h==0){
            quit=true;
        }
    }

/////

    for (i=0; i<main_h; i++){
        for (j=0; j<main_w; j++){
            DrawPixel(&_ret,j,i,SDL_MapRGBA(_ret->format,matrix[0][j][i],matrix[1][j][i],matrix[2][j][i],0));
        }
    }

    TGAImage *img = new TGAImage(main_w,main_h);
    Colour tmp;

    for(int x=0; x<main_h; x++)
		for(int y=0; y<main_w; y++)
		{
			tmp.r = matrix[0][x][y];
			tmp.g = matrix[1][x][y];
			tmp.b = matrix[2][x][y];
			tmp.a = 255;
			img->setPixel(tmp,x,y);
		}

    name+=".tga";
    img->WriteImage(name);

    window_new(_ret,"M", work_path);
    return true;

}

bool de_algorith0_image(const char *path, string work_path){

    FILE *re;
    re=fopen(path,"rb");
    string name=path;
    string uz;

   // SDL_Surface *dummy;
    //dummy=IMG_Load("radio.png");

    size_t found = name.find_last_of("/\\");
    name=name.substr(found+1);
    found = name.find_last_of(".");
    uz = name.substr(found+1);
    name = name.substr(0,found);
    cout << "U: " << uz ;

    if (uz=="zip" || uz== "ZIP") cout << "Needs unzip" << endl;

    int main_w;
    int main_h;
    int b=0; int c=0;
    int some,big;
    fscanf(re,"%d %d",&main_h,&main_w);
   // short matrix[3][main_h][main_w];

    cout << main_h << " , " << main_w << endl;

    SDL_Surface *_ret=NULL;

    big=main_h;
    if (main_w>main_h)
        big=main_w;

    _ret=SDL_CreateRGBSurface(1,big,big,24,0x0000FF,0x00FF00,0xFF0000,0);
    //SDL_SetColorKey( _ret, SDL_TRUE, SDL_MapRGBA( dummy->format, 0, 0xFF, 0xFF, 0 ));

   // _ret=SDL_CreateRGBSurface(mSurface->flags,width,height,mSurface->format->BitsPerPixel,mSurface->format->Rmask,
        //                                   mSurface->format->Gmask,mSurface->format->Bmask,mSurface->format->Amask);


    int i=0;
    int k;
    if (re==NULL) cout << "File Error" << endl;
    int pixel=0;
    int j=0;
    int first,temp,number;
    int point_c,point_b;
    SDL_Color clr;


    while (c<main_h){
        while (b<main_w){                         ///Fill image 0
            DrawPixel(&_ret,b,c,SDL_MapRGBA(_ret->format,0,0,0,0));
            b++;
        }
        b=0;
        c++;
    }

    SDL_Surface *dummy;
    dummy=_ret;
    //window_new(dummy,"M","asd");
    cout << "Zero Fill" << endl;

///**********************RED*******************

    bool quit=false;

    c=0; b=0;
    while (!quit){
         clr = color_returner_surface(_ret,b,c);

         if (clr.r==0){
            first=fgetc(re);

            if (first==33){
                fscanf(re,"%d",&number);
                for (i=0;i<number; i++){
                    //matrix[0][c][b+i]=temp;
                    DrawPixel(&_ret,b+i,c,SDL_MapRGBA(dummy->format,temp,0,0,0));

                }
            }

            else if (first==34){
                fscanf(re,"%d",&number);
                b--;
                for (i=0;i<=number; i++){
                    //matrix[0][point_c+i][point_b]=temp;
                    DrawPixel(&_ret,point_b,point_c+i,SDL_MapRGBA(dummy->format,temp,0,0,0));
                }
            }

            else {
             //   matrix[0][c][b]=first;
                DrawPixel(&_ret,b,c,SDL_MapRGBA(dummy->format,first,0,0,0));
                temp=first;
                point_c=c;
                point_b=b;

            }

        }
        b++;

        if (b!=0 && b%main_w==0){
            b=0;
            c++;
        }

        if (c!=0 && c%(main_h)==0){
            quit=true;
        }

           // DEBUG Write
           /* system("cls");
            printf("   ");
            for (i=0; i<main_w; i++){
                printf("%4d",i);
            }
            printf("\n");
            printf("--------------------------------------------------------------------------------------\n");

            for (i=0; i<main_h; i++){
                if (i<10) printf("%d| ",i);
                else printf("%d|",i);
                for (int j=0; j<main_w; j++){
                    clr = color_returner_surface(_ret,j,i);
                    printf("%4d",clr.r);
                }
                printf("\n");
            }
            printf("\nPos: [%d, %d]\n",b,c);
            if (first==33) printf("Ch= Row\n");
            else if (first==34) printf("Ch= Column\n");
            else printf("Ch= %c\n",first);
            printf("Num: %d\n",number);
            printf("Temp= %d\n",temp);
            getchar();*/
        }

//*************GREEEN************
    quit=false;
    first=fgetc(re);
    printf("CH: %c, %d\n",first,first);


    c=0; b=0;
    while (!quit){
        some = static_cast<int>((color_returner_surface(_ret,b,c).g));
            if (some==0){
            first=fgetc(re);

            if (first==33){
                fscanf(re,"%d",&number);
                for (i=0;i<number; i++){
                    //matrix[1][c][b+i]=temp;
                     clr=color_returner_surface(_ret,b+i,c);
                     DrawPixel(&_ret,b+i,c,SDL_MapRGBA(dummy->format,clr.r,temp,0,0));
                }
            }

            else if (first==34){
                fscanf(re,"%d",&number);
                b--;
                for (i=0;i<=number; i++){
                    //matrix[1][point_c+i][point_b]=temp;
                     clr=color_returner_surface(_ret,point_b,point_c+i);
                     DrawPixel(&_ret,point_b,point_c+i,SDL_MapRGBA(dummy->format,clr.r,temp,0,0));
                }
            }

            else {
                //matrix[1][c][b]=first;
                clr=color_returner_surface(_ret,b,c);
                DrawPixel(&_ret,b,c,SDL_MapRGBA(dummy->format,clr.r,first,0,0));

                temp=first;
                point_c=c;
                point_b=b;
            }

        }
        b++;

        if (b!=0 && b%main_w==0){
            b=0;
            c++;
        }
        if (c!=0 && c%main_h==0){
            quit=true;
        }
    }

///***************************BLUE********************

   quit=false;
   first=fgetc(re);
   printf("CH: %c, %d\n",first,first);

   c=0; b=0;
   while (!quit){
         some = static_cast<int>((color_returner_surface(_ret,b,c).b));
         if (some==0){
            first=fgetc(re);

            if (first==33){
                fscanf(re,"%d",&number);
                for (i=0;i<number; i++){
                   // matrix[2][c][b+i]=temp;
                   clr=color_returner_surface(_ret,b+i,c);
                   DrawPixel(&_ret,b+i,c,SDL_MapRGBA(dummy->format,clr.r,clr.g,temp,0));
                }
            }

            else if (first==34){
                fscanf(re,"%d",&number);
                b--;
                for (i=0;i<=number; i++){
                    //matrix[2][point_c+i][point_b]=temp;
                    clr=color_returner_surface(_ret,point_b,point_c+i);
                    DrawPixel(&_ret,point_b,point_c+i,SDL_MapRGBA(dummy->format,clr.r,clr.g,temp,0));
                }
            }

            else {
                //matrix[2][c][b]=first;
                clr=color_returner_surface(_ret,b,c);
                DrawPixel(&_ret,b,c,SDL_MapRGBA(dummy->format,clr.r,clr.g,first,0));

                temp=first;
                point_c=c;
                point_b=b;
            }

        }
        b++;

        if (b!=0 && b%main_w==0){
            b=0;
            c++;
        }
        if (c!=0 && c%main_h==0){
            quit=true;
        }
    }

/////

    /*for (i=0; i<main_h; i++){
        for (j=0; j<main_w; j++){
            DrawPixel(&_ret,j,i,SDL_MapRGBA(_ret->format,matrix[0][j][i],matrix[1][j][i],matrix[2][j][i],0));
        }
    }*/

    TGAImage *img = new TGAImage(main_w,main_h);
    Colour tmp;

    for(int y=0; y<main_h; y++){
		for(int x=0; x<main_w; x++)
		{
			tmp.r = (color_returner_surface(dummy,x,y).r);
			tmp.g = (color_returner_surface(dummy,x,y).g);
			tmp.b = (color_returner_surface(dummy,x,y).b);
			tmp.a = 0;
			img->setPixel(tmp,y,x);
		}
   }

    name+=".tga";
    img->WriteImage(name);

    cout << "Cretaed IMage tga" << endl;
    SCREEN_HEIGHT_A=main_h;
    SCREEN_WIDTH_A=main_w;
    window_new(_ret,"M", work_path);
    return true;

}

int ters_convert(const char *path, string work_path){
       de_algorith0_image(path,work_path);
}

#endif // CONVERTER_H_INCLUDED
