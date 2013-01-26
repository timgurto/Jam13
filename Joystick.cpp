// (C) 2013 Tim Gurto

#include "Joystick.h"

namespace Game {

void Joystick::enable() {
	int result =  SDL_JoystickEventState(SDL_ENABLE);
    joystick = SDL_JoystickOpen(0);

	
/*SDL_JoystickNumAxes	Returns the number of joysitck axes
SDL_JoystickNumButtons	Returns the number of joysitck buttons
SDL_JoystickNumBalls	Returns the number of joysitck balls
SDL_JoystickNumHats	Returns the number of joysitck hats*/
}

void Joystick::disable() {
	SDL_JoystickClose(joystick);
}

void Joystick::processEvents() {

	/*// Handle Joystick Motion
	case SDL_JOYAXISMOTION:  
    if ( ( event.jaxis.value < -3200 ) || (event.jaxis.value > 3200 ) ) 
    {
        if( event.jaxis.axis == 0) 
        {
            // Left-right movement code goes here
        }

        if( event.jaxis.axis == 1) 
        {
            // Up-Down movement code goes here
        }
    }
    break;

	 // Handle Hat Motion
	case SDL_JOYHATMOTION:
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
    break;

	 // Handle Joystick Button Presses
	case SDL_JOYBUTTONDOWN:
    if ( event.jbutton.button == 0 ) 
    {
        // code goes here
    }
    break;*/

}
} //namespace Game