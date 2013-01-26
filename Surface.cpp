// (C) 2010 Tim Gurto

#include <string>
#include <cassert>

#include "SDL.h"
#include "SDL_image.h"
#include "Debug.h"
#include "Surface.h"
#include "Screen.h"
#include "globals.h"
#include "util.h"

namespace Game {
    
extern Debug debug;

int Surface::surfacesLoaded_ = 0;
int Surface::screensSet_ = 0;

//constructor - from file
Surface::Surface(const std::string fileName, bool alpha):
surface_(0),
isScreen_(false) {
   loadImage(fileName, alpha);
   ++surfacesLoaded_;
}

//constructor - from file, with transparent background
Surface::Surface(const std::string fileName, const SDL_Color &background, bool alpha):
surface_(0),
isScreen_(false) {
   loadImage(fileName, alpha);
   setColorKey(background);
   ++surfacesLoaded_;
}

//constructor - special (blank, screen, or default uninitialized)
Surface::Surface(SpecialSurface special, int width, int height,
                 SDL_Color background):
surface_(0),
isScreen_(false) {
   switch(special){

   case SUR_SCREEN:
      if (screensSet_ != 0) //don't make duplicate screen buffers
         break;

      surface_ = SDL_SetVideoMode(Screen::getScreenRes().x,
                                  Screen::getScreenRes().y,
                                  SCREEN_BPP,
#ifndef __APPLE__
                                  SDL_HWSURFACE | (Screen::getWindowedMode() ?
                                  0 :
                                  SDL_FULLSCREEN));
#else
                                  SDL_HWSURFACE |
                                  (Screen::getWindowedMode() ? 0 : SDL_FULLSCREEN) |
                                  SDL_DOUBLEBUF);
#endif
                                  
      SDL_WM_SetCaption("[ Game name here ]", 0);
      isScreen_ = true;
      assert (screensSet_ == 0);
      screensSet_ = 1;
      break;

   case SUR_BLANK:
      if (width == -1)
         width = Screen::getScreenRes().x;
      if (height == -1)
         height = Screen::getScreenRes().y;
      surface_ = SDL_CreateRGBSurface(SDL_HWSURFACE,
                                   width, height, SCREEN_BPP,
                                   0, 0, 0, 0);
      setColorKey(background);
      break;
   case SUR_UNINIT:
       break;
   }
   if (surface_ && !isScreen_)
      ++surfacesLoaded_;
}

//constructor - text
Surface::Surface(TTF_Font *font, std::string message, SDL_Color color):
surface_(TTF_RenderText_Solid(font, message.c_str(), color)),
isScreen_(false){
   if (surface_)
      ++surfacesLoaded_;
}

Surface::Surface(const Surface &original):
surface_(0),
isScreen_(false){
   if (!original)
      return;

   else
      if (original.isScreen_){
         surface_ = original.surface_;
         isScreen_ = true;
         ++screensSet_;
      }else{
         surface_ = SDL_ConvertSurface(original.surface_,
                                       original.surface_->format,
                                       SDL_HWSURFACE);
         ++surfacesLoaded_;
      }
}

Surface::~Surface(){
   if (surface_){
      if (isScreen_) {
         --screensSet_;
	  }
      else{
         SDL_FreeSurface(surface_);
		 surface_ = 0;
         --surfacesLoaded_;
      }
   }
}

Surface &Surface::operator=(const Surface &rhs){
   if (this == &rhs)
      return *this;

   if (surface_){
      SDL_FreeSurface(surface_);
      --surfacesLoaded_;
   }
   
   assert (rhs.surface_);
   if (rhs.isScreen_){
      surface_ = rhs.surface_;
      isScreen_ = true;
      ++screensSet_;
   }else if (rhs.surface_){
      surface_ = SDL_ConvertSurface(rhs.surface_,
                                    rhs.surface_->format,
                                    SDL_HWSURFACE);
      ++surfacesLoaded_;
   }
   return *this;
}

Surface::operator bool() const{
   //return surface_;
   return surface_ != 0;
}

SDL_Surface *Surface::operator->(){
   return surface_;
}

const SDL_Surface *Surface::operator->() const{
   return surface_;
}

//needs to be called once, in main or wherever
void Surface::init(){}

//needs to be called once, in main or wherever
void Surface::quit(){
   assert((/*screensSet_ +*/ surfacesLoaded_) == 0);
}

//load a surface from an image file
void Surface::loadImage(const std::string &fileName, bool alpha){
   SDL_Surface *load = IMG_Load(fileName.c_str());
   //assert(load);
   surface_ = alpha ?
      SDL_DisplayFormatAlpha(load) :
      SDL_DisplayFormat(load);
   assert(surface_);
   SDL_FreeSurface(load);
}

//set the surface's transparent color
void Surface::setColorKey(const SDL_Color &color){
   if (color != NO_COLOR)
      SDL_SetColorKey(surface_,
                      SDL_SRCCOLORKEY,
                      SDL_MapRGB(surface_->format,
                                 color.r,
                                 color.g,
                                 color.b));
}

//fills a part of the surface with color
void Surface::fill(const SDL_Color color, SDL_Rect *rect){
   fill(colorToUInt(color), rect);
}

//fills a part of the surface with color
void Surface::fill(Uint32 color, SDL_Rect *rect){
	/*if (!rect) { return; }
   assert(rect->w > 0);
   assert(rect->h > 0);*/          
   SDL_FillRect(surface_, rect, color);
}

//draws an empty box onto the surface
void Surface::box(const SDL_Color color, SDL_Rect *rect, int thickness){
   box(colorToUInt(color), rect, thickness);
}

void Surface::box(Uint32 color, SDL_Rect *rect, int thickness){
   if (!rect)
      return;

   SDL_Rect &r = *rect;
   int half = thickness/2;

   SDL_Rect r1 = makeRect(r.x       - half, r.y       - half, r.w + thickness,   thickness);
   SDL_Rect r2 = makeRect(r.x       - half, r.y + r.h - half, r.w + thickness,       thickness);
   SDL_Rect r3 = makeRect(r.x       - half, r.y       - half,       thickness, r.h + thickness);
   SDL_Rect r4 = makeRect(r.x + r.w - half, r.y       - half,       thickness, r.h + thickness);
   SDL_FillRect(surface_, &r1, color); //u
   SDL_FillRect(surface_, &r2, color); //d
   SDL_FillRect(surface_, &r3, color); //l
   SDL_FillRect(surface_, &r4, color); //r
}

//draw onto another surface
void Surface::draw(Surface &dst,
                   SDL_Rect *dstRect, SDL_Rect *srcRect) const{
   SDL_BlitSurface(surface_, srcRect, dst.surface_, dstRect);
}

//dst << src: draw
Surface &operator<<(Surface &dst, const Surface &src){
   src.draw(dst);
   return dst;
}

//sets the surface's alpha value (0-ff)
void Surface::setAlpha(Uint8 alpha){
   SDL_SetAlpha(surface_, SDL_SRCALPHA, alpha);
}

//flips the screen buffer
void Surface::flip(){
   assert(isScreen_);
   bool test;
   test = SDL_Flip(surface_) == 0;
   assert(test);
}

//saves the surface as an image file
void Surface::saveToBitmap(std::string fileName) const{
   SDL_SaveBMP(surface_, fileName.c_str());
}

Point Surface::getDim() const{
   return Point(surface_->w, surface_->h);
}

//pixel getters
Uint32 Surface::pixel(int index) const{
   return ((Uint32 *)surface_->pixels) [index];
}
Uint32 Surface::pixel(int x, int y) const{
   return ((Uint32 *)surface_->pixels) [y * surface_->w + x];
}

//pixel setters
Uint32 &Surface::pixel(int index){
   return ((Uint32 *)surface_->pixels) [index];
}
Uint32 &Surface::pixel(int x, int y){
   return ((Uint32 *)surface_->pixels) [y * surface_->w + x];
}

} // namespace Game
