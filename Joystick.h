// (C) 2013 Tim Gurto

#ifndef JOYSTICK_H
#define JOYSTICK_H

#include "SDL.h"

namespace Game {

    //'Death' class: an animation and corpse-image combo.
    class Joystick {

	public:
		void enable();
		void disable();
		void processEvents();

	private:
		SDL_Joystick *joystick;

    };

} //namespace Game

#endif