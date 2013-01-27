// (C) 2013 Tim Gurto

#include <cassert>
#include <cmath>
#include "Hunter.h"
#include "Point.h"
#include "Debug.h"
#include "util.h"

namespace Game {

extern Debug debug;

	const pixels_t SOUND_RADIUS = 250;
	const pixels_t KILL_RADIUS = 120;
    Hunter::Hunter(Point startPos) :
		Person(startPos),
		hunterSound(SOUND_PATH + "Hunter.wav"),
		gunShotSound(SOUND_PATH + "GUNSHOT2.WAV"),
		attacking_(false),
		attackingTimer_(0)
	{
	}

	void Hunter::update(double delta, pixels_t distToVamp)
	{
		Person::update(delta, distToVamp);

		// Tick time for attack
		if (attackingTimer_ > 0) {
			const timer_t timeElapsed = static_cast<timer_t>(delta * DELTA_MODIFIER + 0.5);

			// Prevent underflow
			if (attackingTimer_ < timeElapsed) {
				// Clamp to 0
				attackingTimer_ = 0;
			}
			else {
				// Subtract time
				attackingTimer_ -= timeElapsed;
			}
		}

		if ((distToVamp < SOUND_RADIUS) && (attackingTimer_ <= 0)){
			hunterSound.play(-1, 0);

			attackingTimer_ = static_cast<timer_t>( distToVamp * 10 + 1000 + 0.5 );

			double volume = (1 - pow(distToVamp, 0.25))*0.8;
			hunterSound.changeVolume(min<int>(
				static_cast<int>(volume*MIX_MAX_VOLUME+0.5), MIX_MAX_VOLUME));
		}
		if (distToVamp < KILL_RADIUS) {
			attacking_ = true;
			gunShotSound.play(-1, 0);
		}
	}

    void Hunter::draw(Point offset, Surface &surface) const
	{
		if (DEBUG) {
			SDL_Rect rect = makeRect(0, 0, KILL_RADIUS, KILL_RADIUS);
			
			SDL_Color color = RED;
			surface.box(color,
				&makeRect(loc_.x-rect.x-offset.x,
					loc_.y-rect.y-offset.y,
					rect.w,
					rect.h));

			Person::draw(offset, surface);
		}
	}

} //namespace Game