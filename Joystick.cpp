// (C) 2013 Tim Gurto

#include <cassert>
#include "Joystick.h"
#include "Debug.h"

namespace Game {

extern Debug debug;

Joystick::Joystick() :
	joystick(0),
	numAxes(0),
	numButtons(0),
	numBalls(0),
	numHats(0),
	axisLR(0.0),
	axisUD(0.0) {}

void Joystick::enable() {
    joystick = SDL_JoystickOpen(0);

	if (!joystick) {
		debug("Could not get joystick");
	}

	int result = SDL_JoystickEventState(SDL_ENABLE);
	if (!result) {
		debug("Could not enable joystick");
		SDL_JoystickClose(joystick);
		joystick = 0;
		return;
	}

	numAxes = SDL_JoystickNumAxes(joystick);
	numButtons = SDL_JoystickNumButtons(joystick);
	numBalls = SDL_JoystickNumBalls(joystick);
	numHats = SDL_JoystickNumHats(joystick);

    if (numButtons == -1)
        numButtons = 0;
	buttons.resize(numButtons);

	debug("numAxes ", numAxes);
	debug("numButtons ", numButtons);
	debug("numBalls ", numBalls);
	debug("numHats ", numHats);
}

void Joystick::disable() {
	if (!joystick) {
		return;
	}
	SDL_JoystickEventState(SDL_DISABLE);
	SDL_JoystickClose(joystick);
	joystick = 0;
	axisLR = 0.0;
	axisUD = 0.0;
}

double Joystick::getUpDownAxis() const { return axisUD; }

double Joystick::getLeftRightAxis() const { return axisLR; }

bool Joystick::isPressed(int button) {
	assert( button >= 0 );
    if (buttons.size() == 0)
        return false;
	return buttons[button];
}

void Joystick::update() {
	for (size_t i = 0; i < numButtons; ++i) {
		buttons[i] = false;
	}
}

void Joystick::processEvents(SDL_Event& event) {

	// Check if joystick is unplugged
	int open = SDL_JoystickOpened(0);
	if (open && !joystick) {
		enable();
	}
	else if (!open && joystick) {
		disable();
		return;
	}
	else if (!joystick) {
		return;
	}

	// Handle Joystick Motion
	if (event.type == SDL_JOYAXISMOTION) {

		const int AXIS_MIN = -32768;
		const int AXIS_MAX = 32767;
		const int AXIS_MIN_VALUE = 3200;
		//const int AXIS_MIN_VALUE = 20000;
		const double AXIS_MIN_PERCENT = AXIS_MIN_VALUE / AXIS_MAX;

		if (event.jaxis.axis == 0) 
		{
			// Left-right movement code goes here
			axisLR = event.jaxis.value / AXIS_MIN_VALUE;
			//if (fabs(axisLR) < AXIS_MIN_PERCENT) { axisLR = 0.0; }
			//debug("Left-right ", axisLR);
		}

		if (event.jaxis.axis == 1) 
		{
			axisUD = event.jaxis.value / AXIS_MIN_VALUE;
			//if (fabs(axisUD) < AXIS_MIN_PERCENT) { axisUD = 0.0; }
			//debug("Up-down ", axisUD);
		}
	}

	 // Handle Hat Motion
	else if (event.type == SDL_JOYHATMOTION) {
		if ( event.jhat.value & SDL_HAT_UP )
		{
			// Do up stuff here
		}

		if ( event.jhat.value & SDL_HAT_LEFT )
		{
			// Do left stuff here
		}

		if ( event.jhat.value & SDL_HAT_RIGHTDOWN )
		{
			// Do right and down together stuff here
		}
	}

	 // Handle Joystick Button Presses
	else if (event.type == SDL_JOYBUTTONDOWN) {
		//debug("event.jbutton.button ", (int)event.jbutton.button);
		//debug("event.jbutton.state ", (int)event.jbutton.state);
		buttons[(size_t)event.jbutton.button] = (bool)event.jbutton.state;
	}

}
} //namespace Game