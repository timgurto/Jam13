// (C) 2009-2011 Tim Gurto

#ifndef GLOBALS_H
#define GLOBALS_H

#include <string>
#include "Point.h"
#include "types.h"

//DEBUG means:
// -The displaying of debug messages
// -The automatic display of delta/FPS
// -Automatic windowed mode
#ifdef NDEBUG //VS: Debug vs. Release mode
#define DEBUG false
#else
#ifdef DEBUG
#undef DEBUG
#endif
#define DEBUG true
#endif

namespace Game {

//higher = slower game speed.
//Game is normalized around this delta.
const int DELTA_MODIFIER = 40;

const double PI = 3.14159265358979323846;

//bits per pixel
const int SCREEN_BPP = 32;

//unfortunately, different SDL functions use different
//color formats
const SDL_Color BLACK   = {   0,    0,    0};
const SDL_Color BLUE    = {   0,    0, 0xff};
const SDL_Color GREEN   = {   0, 0xff,    0};
const SDL_Color CYAN    = {   0, 0xff, 0xff};
const SDL_Color RED     = {0xff,    0,    0};
const SDL_Color MAGENTA = {0xff,    0, 0xff};
const SDL_Color YELLOW  = {0xff, 0xff,    0};
const SDL_Color WHITE   = {0xff, 0xff, 0xff};
const SDL_Color GRAY    = {0x7f, 0x7f, 0x7f};
const Uint32 BLACK_UINT   = 0x000000;
const Uint32 BLUE_UINT    = 0x0000ff;
const Uint32 GREEN_UINT   = 0x00ff00;
const Uint32 CYAN_UINT    = 0x00ffff;
const Uint32 RED_UINT     = 0xff0000;
const Uint32 MAGENTA_UINT = 0xff00ff;
const Uint32 YELLOW_UINT  = 0xffff00;
const Uint32 WHITE_UINT   = 0xffffff;

//arbitrary dummy value, using "unused" fourth element
const SDL_Color NO_COLOR = {0xde, 0xca, 0xfb, 0xad};

const SDL_Color ENTITY_BACKGROUND = GREEN;
const SDL_Color ENTITY_MASK       = MAGENTA;

//const std::string IMAGE_SUFFIX = ".png";
const std::string IMAGE_PATH = "Images/";
const std::string SOUND_PATH = "Sounds/";
const std::string DATA_PATH = "Data/";
const std::string SCREENSHOTS_PATH = "Screenshots/";

//font filenames
const std::string FONT_DEBUG = "Dina.fon";
const std::string FONT_GAME = "Dina.fon";

//Not enum:
//Never used as a type, and values are fixed in SDL
const Uint8 MOUSE_BUTTON_LEFT        = 1;
const Uint8 MOUSE_BUTTON_MIDDLE      = 2;
const Uint8 MOUSE_BUTTON_RIGHT       = 3;
const Uint8 MOUSE_BUTTON_SCROLL_UP   = 4;
const Uint8 MOUSE_BUTTON_SCROLL_DOWN = 5;

//Layout of credits screen
const int CREDITS_OFFSET = 0; //initial y offset from center
const int CREDITS_INCREMENT = 27;
const int CREDITS_GAP = 19;
const int CREDITS_X_OFFSET = 0;
const SDL_Color CREDITS_HEADING_COLOR = WHITE;

enum GameOutcome{
   IN_PROGRESS,
   ALT_F4, //immediately exit entire program
   QUIT,
   RESTART,
   WON
};

} // namespace Game

//for more terse iterating
#define ITERATE(TYPE, CONTAINER, ITERATOR) \
   for (TYPE ITERATOR = (CONTAINER).begin(); \
        ITERATOR != (CONTAINER).end(); \
        ++ ITERATOR)

#endif
