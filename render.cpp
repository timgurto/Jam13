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
#include "Vampire.h"
#include "Person.h"

namespace Game {

extern Debug debug, deltaLog;

void render(const GameState &state, const MessageBox &fpsDisplay){
   Point screenRes = Screen::getScreenRes();

   assert (screenBuf);

   screenBuf.fill();

    state.map.draw(state.offset);

    state.vampire.draw(state.offset);

	if (isKeyPressed(SDLK_z)) {
        ITERATE(GameState::PersonList::const_iterator, state.getPersonList(), it) {
			const Person* p = *it;
			assert(p);
            p->draw(state.offset);
		}
	}

   debug.display();
   fpsDisplay.draw();

   //Finalize
   screenBuf.flip();
}

} // namespace Game
