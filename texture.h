#ifndef TEXTURE_H_INCLUDED
#define TEXTURE_H_INCLUDED

#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <SDL2/SDL2_gfxPrimitives.h>

using namespace std;


SDL_Renderer* for_texture;
TTF_Font* for_font;

void class_set_renderer(struct SDL_Renderer *g_Renderer,TTF_Font **main_font){
    ::for_texture=g_Renderer;
    ::for_font=*main_font;
}

void class_set_renderer0(struct SDL_Renderer *g_Renderer){
    ::for_texture=g_Renderer;
}

class LTexture{

    int mWidth;
    int mHeight;
    SDL_Surface* loadedSurface=NULL;
  public:
    SDL_Texture* mTexture;
    TTF_Font *Font = NULL;
    SDL_Renderer *gRenderer=NULL;
    LTexture();
    bool loadFromFile( std::string path );
    void loadFromRenderedText( std::string textureText, SDL_Color textColor , TTF_Font *,int ,struct SDL_Renderer* );
    bool loadFromSurface(struct SDL_Surface *);

    void free();
    void setColor( Uint8 red, Uint8 green, Uint8 blue );
    void setBlendMode( SDL_BlendMode blending );
    void setAlpha( Uint8 alpha );

    void render( int x, int y,struct SDL_Renderer* ga=NULL, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL,
                SDL_RendererFlip flip = SDL_FLIP_NONE);
    int getWidth();
    int getHeight();

    bool lockTexture();
    bool unlockTexture();
    void* getPixels();
    int getPitch();
    void* mPixels;
    int mPitch;

    LTexture* Scale(Uint16 ,Uint16 );
    void file();
    void glow(int ,int ,int );

    SDL_Color color_returner(int ,int );
    SDL_PixelFormat *format_returner();
};

SDL_PixelFormat *LTexture::format_returner(){
    return loadedSurface->format;
}

LTexture::LTexture(){

	mTexture = NULL;
	gRenderer = ::for_texture;
	Font = ::for_font;
	mWidth = 0;
	mHeight = 0;

}

bool LTexture::loadFromFile( std::string path )
{
	free();
    SDL_Texture* newTexture = NULL;

	loadedSurface = IMG_Load( path.c_str() );
    SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );
    //SDL_Surface* formattedSurface = SDL_ConvertSurface( loadedSurface, SDL_GetWindowSurface( gWindow )->format, NULL );
  //  newTexture = SDL_CreateTexture( gRenderer, SDL_GetWindowPixelFormat( gWindow ), SDL_TEXTUREACCESS_STREAMING, formattedSurface->w, formattedSurface->h );
    newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );

    mWidth = loadedSurface->w;
    mHeight = loadedSurface->h;

	mTexture = newTexture;
	SDL_LockSurface(loadedSurface);
	return mTexture != NULL;

}

bool LTexture::loadFromSurface( struct SDL_Surface *loadSurface ){
    free();
    SDL_Texture* newTexture = NULL;

	loadedSurface = loadSurface;
    SDL_SetColorKey( loadSurface, SDL_TRUE, SDL_MapRGB( loadSurface->format, 0, 0xFF, 0xFF ) );
    //SDL_Surface* formattedSurface = SDL_ConvertSurface( loadedSurface, SDL_GetWindowSurface( gWindow )->format, NULL );
  //  newTexture = SDL_CreateTexture( gRenderer, SDL_GetWindowPixelFormat( gWindow ), SDL_TEXTUREACCESS_STREAMING, formattedSurface->w, formattedSurface->h );
    newTexture = SDL_CreateTextureFromSurface( gRenderer, loadSurface );

    mWidth = loadSurface->w;
    mHeight = loadSurface->h;

	mTexture = newTexture;
	SDL_LockSurface(loadedSurface);
	return mTexture != NULL;
}

void LTexture::free()
{
	if( mTexture != NULL )
	{
	    //SDL_FreeSurface(mSurface);
		SDL_DestroyTexture( mTexture );
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void LTexture::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
	SDL_SetTextureColorMod( mTexture, red, green, blue );
}

void LTexture::setBlendMode( SDL_BlendMode blending )
{

	SDL_SetTextureBlendMode( mTexture, blending );
}

void LTexture::setAlpha( Uint8 alpha )
{
	SDL_SetTextureAlphaMod( mTexture, alpha );
}

void LTexture::render( int x, int y, struct SDL_Renderer *ga, SDL_Rect* clip
                      ,double angle, SDL_Point* center, SDL_RendererFlip flip)
{

	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

    if (clip!=NULL){
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

	if (ga==NULL) SDL_RenderCopyEx( gRenderer, mTexture, clip, &renderQuad, angle, center, flip );
	else SDL_RenderCopyEx( ga, mTexture, clip, &renderQuad, angle, center, flip );
}

int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}

void LTexture::loadFromRenderedText( std::string textureText, SDL_Color textColor ,TTF_Font *Font0=NULL, int i=0,
                                    struct SDL_Renderer* ga=NULL)
{

	free();
	if (Font0!=NULL) Font=Font0;
	else Font = for_font;

	SDL_Surface* textSurface = TTF_RenderText_Solid( Font, textureText.c_str(), textColor );
	if( textSurface == NULL ){
		printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
	}
	else{
        if (ga==NULL) mTexture = SDL_CreateTextureFromSurface( gRenderer, textSurface );
		else mTexture = SDL_CreateTextureFromSurface( ga, textSurface );
		if( mTexture == NULL )
			printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
		else{
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		SDL_FreeSurface( textSurface );
	}

}

void DrawPixel(SDL_Surface **target, Sint32 x, Sint32 y, Uint32 Color){
    int bbp = (*target)->format->BytesPerPixel ;
    Uint8 *p = (Uint8 *)(*target)->pixels + y*(*target)->pitch + x*bbp;

    switch (bbp){
       case 1:
          *p=Color;
          break;
       case 2:
          *(Uint16 *)p = Color;
          break;
       case 3:
          if (SDL_BYTEORDER == SDL_BIG_ENDIAN){
             p[0] = (Color >> 16) & 0xff;
             p[1] = (Color >> 8) & 0xff;
             p[2] = Color & 0xff;
          }
          else{
            p[0] = Color & 0xff;
            p[1] = (Color >> 8) & 0xff;
            p[2] = (Color >> 16) & 0xff;
          }
          break;
       case 4:
          *(Uint32 *)p =Color;
          break;
    }

}

Uint32 ReadPixel(SDL_Surface *source, Sint32 x, Sint32 y){
    int bbp = source->format->BytesPerPixel;
    Uint8 *p = (Uint8 *)source->pixels + y*source->pitch + x*bbp ;

    switch (bbp){
       case 1:
          return *p;
          break;
       case 2:
          return *(Uint16 *)p;
          break;
       case 3:
          if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
              return p[0] << 16 | p[1] << 8 | p[2];
          else
              return p[0] | p[1] << 8 | p[2] << 16;
          break;
       case 4:
          return *(Uint32 *)p;
          break;
       default:
          return 0;

    }
}

LTexture *LTexture::Scale(Uint16 width, Uint16 height){
    SDL_Surface *mSurface;
    mSurface=loadedSurface;

    SDL_LockSurface(loadedSurface);

    if (!width || !height)
        std::cout << "Empty";

    SDL_Surface *_ret=NULL;
    _ret=SDL_CreateRGBSurface(mSurface->flags,height,width,mSurface->format->BitsPerPixel,mSurface->format->Rmask,
                                           mSurface->format->Gmask,mSurface->format->Bmask,mSurface->format->Amask);

    if (_ret==NULL)
        cout << "Cant create surface" << endl;

    double _stretch_factor_x = (static_cast<double>(width) / static_cast<double>(mSurface->w));
    double _stretch_factor_y = (static_cast<double>(height) / static_cast<double>(mSurface->h));

    for (Sint32 y=0; y<mSurface->h; y++){
        for (Sint32 x=0; x<mSurface->w; x++){
            for (Sint32 o_y=0; o_y <_stretch_factor_y; ++o_y){
                for (Sint32 o_x=0; o_x < _stretch_factor_x; ++o_x){
                    DrawPixel(&_ret,static_cast<Sint32>(_stretch_factor_x * x)+o_x, static_cast<Sint32>(_stretch_factor_y * y)+o_y,
                              ReadPixel(mSurface,x,y));

                }
            }
        }
    }

    free();
    mTexture = SDL_CreateTextureFromSurface( gRenderer,_ret);
    mWidth = width;
    mHeight = height;
}

void LTexture::glow(int w, int h, int k=0){

    free();
    SDL_Color asd={141,214,255,0};
    int a=0;

    SDL_Surface *_ret=NULL;
    _ret=SDL_CreateRGBSurface(0,w,h,32,0,0,0,0);

    if (_ret==NULL)
        cout << "Cant create surface" << endl;

    asd={10,35,65,200};

    if (k==0){
    for (int y=0; y<=h/2; y++){
        if (y==1){asd.r+=0;  asd.g+=6;  asd.b+=15; a=5;}
        if (y==2){asd.r+=16; asd.g+=41; asd.b+=51; a=4;}
        if (y==3){asd.r+=40; asd.g+=54; asd.b+=64; a=3;}
        if (y==4){asd.r+=45; asd.g+=42; asd.b+=44; a=2;}
        if (y==5){asd.r+=28; asd.g+=28; asd.b+=16; a=1;}
        if (y==6){asd.r+=12; asd.g+=8;  asd.b+=0; a=0;}
        if (y==7){asd.r+=5; asd.g+=5;  asd.b+=0; a=0;}
        for (int x=0+a; x<w-a; x++){
            DrawPixel(&_ret,x,y,SDL_MapRGBA(_ret->format,asd.r,asd.g,asd.b,0));
        }

    }

    for (int y=h/2+1; y<=h; y++){
         if (y==14){asd.r-=0;  asd.g-=6;  asd.b-=15; a=5;}
         if (y==13){asd.r-=16; asd.g-=41; asd.b-=51; a=4;}
         if (y==12){asd.r-=40; asd.g-=54; asd.b-=64; a=3;}
         if (y==11){asd.r-=45; asd.g-=42; asd.b-=44; a=2;}
         if (y==10){asd.r-=28; asd.g-=28; asd.b-=16; a=1;}
         if (y==9){asd.r-=12; asd.g-=8;  asd.b-=0; a=0;}
         if (y==8){asd.r-=5; asd.g-=5;  asd.b-=0; a=0;}
         for (int x=0+a; x<w-a; x++){
            DrawPixel(&_ret,x,y,SDL_MapRGBA(_ret->format,asd.r,asd.g,asd.b,0));
        }
    }
    }

    free();
    SDL_SetSurfaceBlendMode(_ret, SDL_BLENDMODE_ADD);
    mTexture = SDL_CreateTextureFromSurface( gRenderer,_ret);
    mWidth = w;
    mHeight = h;
}

SDL_Color translate_color(Uint32 int_color){
    SDL_Color color;
    if (SDL_BYTEORDER == SDL_BIG_ENDIAN){
        color={(int_color & 0x00ff0000)/0x10000,(int_color &
0x0000ff00)/0x100,(int_color & 0x000000ff),0};
    }
    else{
        color={(int_color & 0x000000ff),(int_color &
0x0000ff00)/0x100,(int_color & 0x00ff0000)/0x10000,0};}

    return color;
}

void LTexture::file(){
    SDL_Surface *mSurface=NULL;
    mSurface=loadedSurface;
    SDL_LockSurface(mSurface);

    SDL_SetSurfaceBlendMode(mSurface, SDL_BLENDMODE_ADD);

       SDL_Color a;

       for (Sint32 y=0; y<mSurface->h; y++){
           for (Sint32 x=0; x<mSurface->w; x++){
               a= translate_color(ReadPixel(mSurface,x,y));
               std::cout << static_cast<int>(a.r) << " " << static_cast<int>(a.g) << " " << static_cast<int>(a.b) << "-" ;

           }
           std::cout << std::endl;
       }


}

SDL_Color LTexture::color_returner(int x, int y){

    SDL_Color a;
    a= translate_color(ReadPixel(loadedSurface,x,y));
    return a;


}

SDL_Color color_returner_surface(struct SDL_Surface *sfc, int x, int y){

    SDL_Color a;
    a= translate_color(ReadPixel(sfc,x,y));
    return a;


}


#endif // TEXTURE_H_INCLUDED
