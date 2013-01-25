// (C) 2010-2011 Tim Gurto

#include <cassert>
#include <sstream>
#include <ctime>
#include <map>
#include "update.h"
#include "game.h"
#include "util.h"
#include "misc.h"
#include "globals.h"
#include "Debug.h"
#include "MessageBox.h"
#include "Screen.h"
#include "GameState.h"
#include "Person.h"

namespace Game {

extern Debug debug;

void updateState(double delta, GameState &state, MessageBox &fpsDisplay){

	handleEvents(state, fpsDisplay);

    state.vampire.update(delta);
    
    //determine the closest persons, so that their hearts are heard
    typedef std::multimap<pixels_t, Person *> closestPersons_t;
    closestPersons_t closestPersons;
    const Location& vampLoc = state.vampire.getLoc();
    ITERATE(GameState::PersonList::iterator, state.personList, it){
        it->isClosest = false;
        closestPersons.insert(std::pair<pixels_t, Person *>(distance(it->getLoc(), vampLoc), &*it));
    }

    int i = 0;
    ITERATE(closestPersons_t::iterator, closestPersons, it){
        if (i != Person::MAX_HEARTBEATS){
            (it->second)->isClosest = true;
            ++i;
        }
    }
	
    ITERATE(GameState::PersonList::iterator, state.personList, it) {

        

	    pixels_t distToVamp = distance(it->getLoc(), vampLoc);
        it->update(delta, distToVamp);
	}
}

void handleEvents(GameState &state, MessageBox &fpsDisplay){
   SDL_Event event;
   while (SDL_PollEvent(&event))
      switch (event.type){



      //Window is exited
      case SDL_QUIT:
         state.outcome = QUIT;
         state.loop = false;
         break;



      //Mouse is moved
      case SDL_MOUSEMOTION:
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

            case SDLK_F4:
               //Alt+F4: Exit program immediately
               if (isKeyPressed(SDLK_LALT) || isKeyPressed(SDLK_RALT)){
                  state.outcome = ALT_F4;
                  state.loop = false;
                  return;
               }
               break;

            case SDLK_F9:
               //F9: Restart level (debug)
               if (DEBUG){
                  state.outcome = RESTART;
                  state.loop = false;
               }
               break;

            case SDLK_F11:
               //Alt+F11: Toggle FPS display
               fpsDisplay.toggleVisibility();
               break;

            case SDLK_ESCAPE:
               //Esc: exit game (debug mode only)
               if (DEBUG || true){
                  state.outcome = QUIT;
                  state.loop = false;
                  return;
               }
               break;

            default:
               break;

            }

            break;
         }
                  


      //A mouse button is pressed
      case SDL_MOUSEBUTTONDOWN:
         debug("Mouse down: ", int(event.button.button));
         switch (event.button.button){
         case MOUSE_BUTTON_LEFT:
            break;
         case MOUSE_BUTTON_RIGHT:
            break;
         }// switch mouse button
         pushMouseMove();
         break;



      //A mouse button is released
      case SDL_MOUSEBUTTONUP:
         switch (event.button.button){

         case MOUSE_BUTTON_RIGHT:
            break;

         case MOUSE_BUTTON_LEFT:
            break;
         }
         pushMouseMove();
         break;



      } //switch event
}

} // namespace Game
