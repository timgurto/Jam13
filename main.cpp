// (C) 2009-2011 Tim Gurto

#include <cassert>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <cmath>

#ifdef __APPLE__
#include "SDLMain.h"
#endif

#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include "game.h"
#include "globals.h"
#include "Debug.h"
#include "Joystick.h"
#include "Screen.h"
#include "Surface.h"
#include "Point.h"
#include "ScreenElement.h"
#include "Sound.h"
#include "main.h"
#include "globals.h"
#include "util.h"
#include "misc.h"

// Keep main in default namespace
namespace Game {
    int main(int argc, char **argv);
}
#ifdef __APPLE__
int SDL_main(int argc, char **argv) {
#else
int main(int argc, char **argv) {
#endif // __APPLE__
    return Game::main(argc, argv);
}

namespace Game {

//global screen buffer
Surface screenBuf; //uninitialized

// global joystick
Joystick joystick;

//general debug messages
Debug debug(YELLOW, 0, 0, 59);

//can be reused for whichever screens; the useful bit is the name
enum ButtonID{
   //ScreenElement::NO_ID = -1
   BUTTON_QUIT = 0,
   BUTTON_NEW,
   BUTTON_CREDITS,
};

// Keep main in default namespace
int main(int argc, char **argv){

   //seed random generator
//#ifdef DEBUG
//	srand(1);
//#else
   srand(unsigned(time(0)));
//#endif

   //SDL initialization
   int sdlInit(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK));
   assert (sdlInit == 0);
   int ttfInit(TTF_Init());
   assert (ttfInit >= 0);
   int mixInit(Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 256));//256));
   assert (mixInit >= 0);

   debug.initFont(FONT_DEBUG, 0);
   

   //initialize screen buffer
   screenBuf = Surface(SUR_SCREEN);

	// Print joysticks
	debug(SDL_NumJoysticks(), " joysticks were found.");
    debug("The names of the joysticks are:");
		
    for(int i = 0; i < SDL_NumJoysticks(); ++i) 
    {
        debug(SDL_JoystickName(i));
    }

	joystick.enable();
   
   {//new scope for surfaces

      //init with surfaces
      Screen::init();
      Screen
         mainMenu(BUTTON_NEW, BUTTON_QUIT),
         game(&gameMode),
         credits(BUTTON_QUIT, BUTTON_QUIT);
      buildScreens(mainMenu, credits);


      if (!DEBUG){

         //main menu
         bool loop = true;
         do{
            switch(mainMenu()){
            case BUTTON_QUIT:
               loop = false;
               break;

            case BUTTON_CREDITS:
               credits();
               break;

            case BUTTON_NEW:
               {
                  GameOutcome outcome;
                  while ((outcome = (GameOutcome)game()) == RESTART)
                     ;
                  if (outcome == ALT_F4)
                     loop = false;
               }
               break;
            }
         }while(loop);

      }else
         while (game() == RESTART);

   }

   //Quit
   joystick.disable();
   //TTF_Quit() happens at debug dtor
   Mix_CloseAudio();
   SDL_Quit();
   Surface::quit();
   Sound::quit();
   return 0;
}

void buildScreens(Screen &mainMenu,
                  Screen &credits){
   
   //Main menu
   mainMenu.addElement(ScreenElement
      (ELEM_LABEL, "[ Game name here ]", ANCHOR_CENTER, Point(0, -150)));
   mainMenu.addElement(ScreenElement
      (ELEM_BUTTON, "Begin", ANCHOR_CENTER, Point(0, -60), BUTTON_NEW));
   mainMenu.addElement(ScreenElement
      (ELEM_BUTTON, "Credits",    ANCHOR_CENTER, Point(0, 0),   BUTTON_CREDITS));
   mainMenu.addElement(ScreenElement
      (ELEM_BUTTON, "Quit",       ANCHOR_CENTER, Point(0, 60),  BUTTON_QUIT));

   //Credits
   credits.addElement(ScreenElement
      (ELEM_BUTTON, "Back", ANCHOR_TOP_RIGHT, Point(-30, 30), BUTTON_QUIT));

   int yPos = CREDITS_OFFSET;

   //addCreditTitle(credits, yPos, "Title");
   addCredit     (credits, yPos, "(C) 2011 Tim Gurto");
   //addCreditGap(yPos);
}

void addCreditTitle(Screen &creditsScreen, int &yPos, std::string text){
   creditsScreen.addElement(ScreenElement(ELEM_LABEL, text, ANCHOR_LEFT,
                                          Point(CREDITS_X_OFFSET, yPos), ScreenElement::NO_ID,
                                          0, 0, 22, CREDITS_HEADING_COLOR));
   yPos += CREDITS_INCREMENT;
}

void addCredit(Screen &creditsScreen, int &yPos, std::string text){
   creditsScreen.addElement(ScreenElement(ELEM_LABEL, text, ANCHOR_LEFT,
                                          Point(CREDITS_X_OFFSET, yPos), ScreenElement::NO_ID,
                                          0, 0, 18));
   yPos += CREDITS_INCREMENT;
}

void addCreditGap(int &yPos){
   yPos += CREDITS_GAP;
}

} // namespace Game
