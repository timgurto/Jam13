// (C) 2013 Tim Gurto

#ifndef JOYSTICK_H
#define JOYSTICK_H

#include "SDL.h"
#include <vector>

namespace Game {

    //'Death' class: an animation and corpse-image combo.
    class Joystick {

	public:
		Joystick();
		void enable();
		void disable();
		void processEvents(SDL_Event& event);

		bool enabled() { return joystick != 0; }
		double getUpDownAxis() const;
		double getLeftRightAxis() const;

		bool isPressed(int button);

		void update();

	private:
		SDL_Joystick *joystick;

		int numAxes;
		int numButtons;
		int numBalls;
		int numHats;

		double axisLR;
		double axisUD;

		std::vector<bool> buttons;
    };

} //namespace Game

#endif