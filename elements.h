#ifndef ELEMENTS_H_INCLUDED
#define ELEMENTS_H_INCLUDED
#include <iostream>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "button.h"

using namespace std;

struct elements{
    int no;
    int tercih;
    LTexture imgs;
    bool converted;
    bool clicked;
    const char *image_path;
    struct elements *next;
    standard_button *button;
};

struct elements *add_element(int no, bool converted, const char *image,bool clicked){
    struct elements *gecici;
    gecici=(struct elements *)malloc(sizeof(struct elements));
    gecici->converted=converted;
    gecici->image_path=image;
    gecici->clicked=clicked;
    gecici->next=NULL;
    gecici->no=0;
    gecici->tercih=1;
    gecici->button = new standard_button("Convert",50,50,1);
    return gecici;
}

void element_ekle(int no, bool coverted, const char *image,bool clicked, struct elements **liste_basi){
    struct elements *a=add_element(no,coverted,image,clicked);
    a->next=*liste_basi;
    *liste_basi=a;
}


#endif // ELEMENTS_H_INCLUDED
