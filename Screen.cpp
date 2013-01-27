// (C) 2010 Tim Gurto

#include <cassert>
#include <sstream>
#include <ctime>
#include <vector>
#include "Screen.h"
#include "Surface.h"
#include "Debug.h"
#include "Point.h"
#include "ScreenElement.h"
#include "globals.h"
#include "util.h"

namespace Game {

extern Debug debug;

//TODO remove

Surface *Screen::cursor_ = 0;
Point Screen::screenRes_(800, 600);
Point Screen::mousePos = screenRes_ / 2;
bool Screen::windowedMode_ = true || DEBUG;

//Default screen functionality.  Accepts input and renders until a button is pushed.
unsigned Screen::goDefault_(Screen &thisScreen, const void *data){
   assert(!data);

   //clear all rollover
   ITERATE(elements_t::iterator, thisScreen.elements_, it)
      it->rollover_ = false;

   while(thisScreen.loop_){
      int result = thisScreen.handleEventsDefault_();
      //if a button was clicked
      if (result != ScreenElement::NO_ID)
         return result;
      thisScreen.drawDefault_();
   }
   return 0;
}

//-inspect SDL's event queue and deal accordingly
//-return the ID of any button pushed
//-used by goDefault
int Screen::handleEventsDefault_(){
   SDL_Event event;
   while (SDL_PollEvent(&event)){
      switch (event.type){

      //Window is exited
      case SDL_QUIT:
         return returnEscape_;

      //Mouse is moved
      case SDL_MOUSEMOTION:
         mousePos.x = event.motion.x;
         mousePos.y = event.motion.y;

         //check whether over any buttons, for rollover color
         { //new scope for found
            bool found = false;
            ITERATE(elements_t::iterator, elements_, it){
               it->rollover_ = false;
               if (!found) //only consider one collision
                  if (collision(it->image_->clip_rect + it->loc_,
                                mousePos)){
                     it->rollover_ = true;
                     //debug("rollover: ", it->text_);
                     found = true;
                  }
            }
         }

         //TODO context help?

         break;

      //A key is pressed
      case SDL_KEYDOWN:
         {//new scope for key
            SDLKey key = event.key.keysym.sym;
            switch (key){
            case SDLK_PRINT:
               { //new scope for os
                  std::ostringstream os;
                  os << SCREENSHOTS_PATH << "shot" << time(0) << ".bmp";
                  screenBuf.saveToBitmap(os.str());
               }
               break;

            case SDLK_ESCAPE:
               if (returnEscape_ != ScreenElement::NO_ID)
                  return returnEscape_;
               break;

            case SDLK_RETURN:
            case SDLK_KP_ENTER:
               if (returnEnter_ != ScreenElement::NO_ID)
                  return returnEnter_;
               break;
            default:
                break;
            }
         }
         break;

      //A mouse button is pressed
      case SDL_MOUSEBUTTONDOWN:
         switch (event.button.button){
         case MOUSE_BUTTON_LEFT:
            //check whether a button was clicked
            ITERATE(std::vector<ScreenElement>::const_iterator,
                    elements_, it)
               if (it->type_ == ELEM_BUTTON &&
                  collision(it->image_->clip_rect + it->loc_,
                            mousePos))
                     return it->id_;
            break;
         }
         break;

      default:
         debug("Uncaught event: ", int(event.type));

      } //event switch

   } //event while

   //nothing to report
   return ScreenElement::NO_ID;
}

//-draw the screen
//-used by goDefault
void Screen::drawDefault_() const{
   assert(screenBuf);
   screenBuf.fill();

   //background
   if (background_){
      pixels_t
         sizeX = (*background_)->clip_rect.w,
         sizeY = (*background_)->clip_rect.h;
      int
         xTiles = screenRes_.x / sizeX + 1,
         yTiles = screenRes_.y / sizeY + 1;
      for (int x = 0; x != xTiles; ++x) {
         for (int y = 0; y != yTiles; ++y) {
            SDL_Rect rect = makeRect(x * sizeX, y * sizeY);
            background_->draw(screenBuf, &rect);
         }
      }
   }

   //elements
   ITERATE(std::vector<ScreenElement>::const_iterator, elements_, it)
      it->draw();

   //cursor
   if (cursor_) {
      SDL_Rect rect = makeRect(mousePos);
      cursor_->draw(screenBuf, &rect);
   }

   //debug log
   if (DEBUG)
      debug.display();

   //flip buffer
   screenBuf.flip();
}

void Screen::init(Surface *cursor){
   if (cursor)
      cursor_ = cursor;
   else
      SDL_ShowCursor(SDL_ENABLE); //default cursor
}

void Screen::setBackground(const Surface &backImage){
   background_ = &backImage;
}

Screen::Screen(GoFun go):
go_(go),
loop_(true),
returnEnter_(ScreenElement::NO_ID),
returnEscape_(ScreenElement::NO_ID),
background_(0){}

Screen::Screen(int returnEnter, int returnEscape):
go_(goDefault_),
loop_(true),
returnEnter_(returnEnter),
returnEscape_(returnEscape),
background_(0){}

//begin screen behavior
int Screen::operator()(const void *data){
   return (*go_)(*this, data);
}

//Create a new screen element
void Screen::addElement(const ScreenElement &element){
   elements_.push_back(element);
}

const Point &Screen::getScreenRes(){
   return screenRes_;
}

bool Screen::getWindowedMode(){
   return windowedMode_;
}

} // namespace Game
