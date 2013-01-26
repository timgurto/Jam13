// (C) 2013 Tim Gurto

#include "Environment.h"
#include "util.h"
#include "Debug.h"
#include "Person.h"
#include "util.h"
#include "GameState.h"
#include <algorithm>
#include <cmath>

namespace Game {

    extern Debug debug;

    GameState *Environment::state = 0;

	const timer_t Environment::COUNTDOWN_TIME = 5000;

    const size_t Environment::SUN_BAR_FRAMES = 50;
    const size_t Environment::SUN_BAR_COLUMNS = 4;

	Environment::Environment(double startingHealth, double maxHealth) :
		countdownTimer_(COUNTDOWN_TIME),
		healthBar_(startingHealth, maxHealth),
        sunBar(IMAGE_PATH + "Time/BlackWhite.png", true),
        sunBarColor(IMAGE_PATH + "Time/ColourBar.png", true),
        sunBarLoc(0, 600-107),
        sunBarDim(800, 107),
        wisp(IMAGE_PATH + "wisp.png", true),
        wispTimer(rand()){

        overlay[0] = Surface(IMAGE_PATH + "Time/1.png", true);
        overlay[1] = Surface(IMAGE_PATH + "Time/2.png", true);
        overlay[2] = Surface(IMAGE_PATH + "Time/3.png", true);
        overlay[3] = Surface(IMAGE_PATH + "Time/4.png", true);
        overlay[4] = Surface(IMAGE_PATH + "Time/5.png", true);
    }


    void Environment::update(double delta){
		const timer_t timeElapsed = static_cast<timer_t>(delta * DELTA_MODIFIER);

        wispTimer += timeElapsed;
		
		// Tick time for cooldown
		if (countdownTimer_ > 0) {
			// Prevent underflow
			if (countdownTimer_ < timeElapsed) {
				// Clamp to 0
				countdownTimer_ = 0;
			}
			else {
				// Subtract time
				const timer_t dt = countdownTimer_ - timeElapsed;
				countdownTimer_ = std::max<timer_t>(0, dt);
			}
			if (countdownTimer_ < 1000){
				state->shakeScreen(1000, 20);
            }else if (countdownTimer_ < 4000){
                state->shakeScreen(4000, 10);
            }else if (countdownTimer_ < 10000){
                state->shakeScreen(10000, 5);
            }
		}
    }

	void Environment::draw(Point offset, Surface &surface) const
	{
        //wisp
        pixels_t xMap = state->map.mapSize.x * state->map.tileSize.x;
        pixels_t yMap = state->map.mapSize.y * state->map.tileSize.y;
        pixels_t xMargin = 1430; //(wisp->w - xMap) / 2;
        pixels_t yMargin = 215; //(wisp->h - yMap) / 2;

        SDL_Rect drawRect;
        drawRect.x = -xMargin + (xMargin * cos(wispTimer/6000)) - state->offset.x;
        drawRect.y = -yMargin + (yMargin * sin(wispTimer/6000)) - state->offset.y;
        wisp.draw(screenBuf, &drawRect);

        //overlay
        double progress = 1.0 * (COUNTDOWN_TIME - countdownTimer_) / COUNTDOWN_TIME;
        size_t overlayIndex = progress * 5;
        if (overlayIndex == 5)
            overlayIndex = 4;
        overlay[overlayIndex].draw();

        //blood bar
		healthBar_.draw(offset, surface);

        //sun bar
        SDL_Rect srcRect;
        srcRect.x = 0;
        srcRect.y = 0;
        srcRect.w = progress * (743-79) + 79;
        srcRect.h = sunBarDim.y;
        sunBar.draw(screenBuf, &makeRect(sunBarLoc.x, sunBarLoc.y));
        sunBarColor.draw(screenBuf, &makeRect(sunBarLoc.x, sunBarLoc.y), &srcRect);

	}

	bool Environment::isSunUp() const {
		return (countdownTimer_ == 0);
	}

} //namespace Game