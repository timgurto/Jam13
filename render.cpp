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

    Location offset = state.shakeOffset();

    state.map.draw(offset);

    ITERATE(victims_t::const_iterator, state.victims, it)
        it->draw(true, offset);

    state.vampire.draw(offset);

    ITERATE(victims_t::const_iterator, state.victims, it)
        it->draw(false, offset);

	if (isKeyPressed(SDLK_SPACE)) {
        ITERATE(GameState::PersonList::const_iterator, state.getPersonList(), it) {
			const Person* p = *it;
			assert(p);
            p->draw(offset);
		}
	}

	state.environment.draw(Point(), screenBuf);

   debug.display();
   fpsDisplay.draw();

   //Finalize
   screenBuf.flip();
}

} // namespace Game
