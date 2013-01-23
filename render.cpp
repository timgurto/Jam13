// (C) 2010-2011 Tim Gurto

#include <cassert>
#include "globals.h"
#include "render.h"
#include "update.h"
#include "Debug.h"
#include "MessageBox.h"
#include "Surface.h"
#include "Screen.h"
#include "GameState.h"
#include "util.h"
#include "misc.h"

extern Debug debug, deltaLog;

void render(const GameState &state, const MessageBox &fpsDisplay){
   Point screenRes = Screen::getScreenRes();

   assert (screenBuf);

   screenBuf.fill();




   debug.display();
   fpsDisplay.draw();

   //Finalize
   screenBuf.flip();
}