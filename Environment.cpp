// (C) 2013 Tim Gurto

#include "Environment.h"
#include "util.h"
#include "Debug.h"
#include "Person.h"
#include <algorithm>
#include <cmath>

namespace Game {

    extern Debug debug;

	const timer_t Environment::COUNTDOWN_TIME = 100000;

	Environment::Environment() :
		countdownTimer_(COUNTDOWN_TIME) {

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
	}

	bool Environment::isSunUp() const {
		return (countdownTimer_ == 0);
	}

} //namespace Game