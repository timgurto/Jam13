// (C) 2013 Tim Gurto

#include "Environment.h"
#include "util.h"
#include "Debug.h"
#include "Person.h"
#include <algorithm>
#include <cmath>

namespace Game {

    extern Debug debug;

	const timer_t Environment::COUNTDOWN_TIME = 150000;

    const size_t Environment::SUN_BAR_FRAMES = 50;
    const size_t Environment::SUN_BAR_COLUMNS = 4;

	Environment::Environment(double startingHealth, double maxHealth) :
		countdownTimer_(COUNTDOWN_TIME),
		healthBar_(startingHealth, maxHealth),
        sunBar(IMAGE_PATH + "sunBar.png", true),
        sunBarLoc(400-256, 600-128),
        sunBarDim(512, 128){

    }


    void Environment::update(double delta){
		const timer_t timeElapsed = static_cast<timer_t>(delta * DELTA_MODIFIER);
		
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
			if (countdownTimer_ < 5000) {
				debug("countdown ", countdownTimer_);
			}
		}
    }

	void Environment::draw(Point offset, Surface &surface) const
	{
		healthBar_.draw(offset, surface);

        size_t frame = size_t(1.0 * SUN_BAR_FRAMES * (COUNTDOWN_TIME - countdownTimer_) / COUNTDOWN_TIME);
        size_t
            row = frame / SUN_BAR_COLUMNS,
            col = frame % SUN_BAR_COLUMNS;
        SDL_Rect srcRect;
        srcRect.x = col * sunBarDim.x;
        srcRect.y = row * sunBarDim.y;
        srcRect.w = sunBarDim.x;
        srcRect.h = sunBarDim.y;
        //screenBuf.fill(CYAN);
        sunBar.draw(screenBuf, &makeRect(sunBarLoc.x, sunBarLoc.y), &srcRect);
	}

	bool Environment::isSunUp() const {
		return (countdownTimer_ == 0);
	}

} //namespace Game