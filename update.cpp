// (C) 2010-2011 Tim Gurto

#include <cassert>
#include <sstream>
#include <ctime>
#include <map>
#include <cmath>
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

    timer_t timeElapsed = delta * DELTA_MODIFIER;

	handleEvents(state, fpsDisplay);

    state.vampire.update(delta);
    
    //determine the closest person, so that their heart is heard
    const Location& vampLoc = state.vampire.getLoc();
    state.closestPerson = 0;
    double closestPersonDist = 0;
    ITERATE(GameState::PersonList::iterator, state.getPersonList(), it){
		Person* p = *it;
		assert(p);
        double dist = distance(p->getLoc(), vampLoc);
        if (!state.closestPerson || dist < closestPersonDist){
            closestPersonDist = dist;
            state.closestPerson = p;
        }
    }

    //heartbeat timer
    const pixels_t MAX_SOUND_DISTANCE = 300;

    if (state.heartTimer <= timeElapsed){
        if (closestPersonDist <= MAX_SOUND_DISTANCE){
            double distance = max(min(1.0 * (closestPersonDist-10) / (MAX_SOUND_DISTANCE-10), 1.0), 0.0);
            state.heartTimer = distance * 1600 + 350;


            double volume = 1 - pow(distance, 0.25);

            //double invDist = 1 - distance;
            //double volume = invDist * invDist; volume *= volume;

            //double volume = (1-distance) * (1-distance);

            //double volume = 1.0 / (x+.1) - .1

            //double volume = 1 - distance;


            state.heartbeat.changeVolume(min<int>(volume*MIX_MAX_VOLUME, MIX_MAX_VOLUME));
            state.heartbeat.play(-1, 0);
        }
        
    }else
        state.heartTimer -= timeElapsed;
	
	GameState::PersonList& personList = state.getPersonList();
	GameState::PersonList& stillAliveList = state.getTmpList();
    ITERATE(GameState::PersonList::iterator, personList, it) {
		Person* p = *it;
		assert(p);
	    pixels_t distToVamp = distance(p->getLoc(), vampLoc);
        p->update(delta, distToVamp);
		state.vampire.applyAttacks(*p);
		if (!p->isDead()) {
			stillAliveList.push_back(p);
		}
		else {
			state.soundScream();
			safe_delete(p);
		}
	}
	state.swapPersonLists();

	// Check for win
	if (state.isAllDead()) {
		state.outcome = WON;
		state.loop = false;
		debug("win");
	}

	else {

		// Game countdown
		state.environment.update(delta);
		if (state.environment.isSunUp()) {
			// Game over
			state.outcome = QUIT;
			state.loop = false;
			debug("lose");
		}

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
