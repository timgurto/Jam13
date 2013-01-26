// (C) 2009, 2010 Tim Gurto

#ifndef NDEBUG

#ifdef WIN32
#define NOMINMAX
#define LEAN_AND_MEAN
#include <Windows.h>
#else
#include <cstdio>
#endif
#include <queue>
#include <cassert>

#include "SDL_ttf.h"

#include "util.h"
#include "types.h"
#include "Debug.h"
#include "Surface.h"
#include "Screen.h"

namespace Game {

extern Surface screenBuf;

int Debug::debugCount_ = 0;

Debug::Debug(SDL_Color color, pixels_t x, pixels_t y,
             unsigned short count):
color_(color),
x_(x),
y_(y),
count_(count),
font_(0),
height_(0){
   ++debugCount_;
}

Debug::~Debug(){
   --debugCount_;
   if (font_)
      TTF_CloseFont(font_);
   if (debugCount_ == 0)
      TTF_Quit();
}

void Debug::initFont(std::string name, int size){
   font_ = TTF_OpenFont(name.c_str(), size);
   assert (font_);
   height_ = TTF_FontHeight(font_);
   unsigned short maxCount = Screen::getScreenRes().y / height_;
   if (count_ > maxCount)
      count_ = maxCount;
}

void Debug::add(std::string message){
#ifdef WIN32
	std::string s = message + "\n";
	OutputDebugString(s.c_str());
#else
	printf("%s\n", message.c_str());
#endif
   messages.push(message);
   if (messages.size() > count_)
      messages.pop();
}

void Debug::display() const{
   std::queue<std::string> copy(messages);
   int lat = 0;
   while (copy.size() != 0){
      std::string message = copy.front();
      copy.pop();

      //draw shadow
      Surface blackSurface(font_, message, BLACK);
      SDL_Rect rect1 = makeRect(x_+1, y_+1 + lat);
      blackSurface.draw(screenBuf, &rect1);
      
      //draw text
      Surface surface(font_, message, color_);
      SDL_Rect rect2 = makeRect(x_, y_ + lat);
      surface.draw(screenBuf, &rect2);

      lat += height_;
   }
}

} // namespace Game

#endif