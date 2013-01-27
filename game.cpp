// (C) 2009-2011 Tim Gurto

#include <cassert>
#include <cstdlib>
#include <map>
#include <string>
#include <fstream>

#include "SDL.h"
#include "SDL_mixer.h"

#include "game.h"
#include "globals.h"
#include "update.h"
#include "render.h"
#include "util.h"
#include "misc.h"
#include "Debug.h"
#include "Point.h"
#include "MessageBox.h"
#include "Surface.h"
#include "Screen.h"
#include "GameState.h"
#include "Sound.h"

namespace Game {

extern Debug debug;
extern bool gameLoop;
extern GameOutcome gameOutcome;

unsigned gameMode(Screen &/*screen*/, const void * data){

   GameState state;


   Surface blankBack(SUR_UNINIT, 1, 1, BLUE);
   MessageBox fpsDisplay(WHITE,
                         Screen::getScreenRes().x / 2 - 40, 2,
                         1,
                         blankBack,
                         FONT_DEBUG, 0,
                         false, DEBUG);

   //SDL_ShowCursor(SDL_DISABLE);

   //flush event queue before accepting game controls,
   //specifically the mouse up event from clicking "Play Game"
   SDL_Event event;
   while(SDL_PollEvent(&event))
      debug("Unhandled event: ", int(event.type));

   timer_t oldTicks = SDL_GetTicks();

   //data tells us which level we're in.
   int level = *(int*)data;
       
   //first: tutorial
    {
        Surface tutImage(IMAGE_PATH + "level" + format2(level) + ".png");
        bool quitTutorial = false;
        while (!quitTutorial){
            screenBuf << tutImage;
            screenBuf.flip();

            //wait for key down or mouse down
            while(SDL_PollEvent(&event)){
                if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_KEYDOWN){
                    quitTutorial = true;
                    break;
                }
            }
        }
    }



   while (state.loop){

      //time stuff
      timer_t newTicks = SDL_GetTicks();
      timer_t delta = newTicks - oldTicks;
      oldTicks = newTicks;

      if (delta > 500)
          continue;

      double deltaMod = 1.0 * delta / DELTA_MODIFIER;
      
      double fps = delta == 0 ? 0 : 1000 / delta;
      fpsDisplay(format3(fps), "fps  |  ", delta, "ms ");

      //force interface refresh
      pushMouseMove();

      //update state
      updateState(deltaMod, state, fpsDisplay);

      //render
      render(state, fpsDisplay);
   }

   //Clean up
   SDL_ShowCursor(SDL_ENABLE);

   GameOutcome outcome = state.outcome;
   return outcome; //return something more meaningful
}

} // namespace Game
