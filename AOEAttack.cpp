// (C) 2013 Tim Gurto

#include "AOEAttack.h"
#include "util.h"
#include "Debug.h"
#include "Person.h"
#include <algorithm>
#include <cmath>

namespace Game {

    extern Debug debug;

	AOEAttack::AOEAttack() :
		Entity(),
		active_(false),
		attacking_(false),
		attackingTimer_(0),
		cooldownTimer_(0),
		sound_(SOUND_PATH + "boom1.wav"),
		blood_(0),
		attackHitSomething_(false) {

    }

    SDL_Rect AOEAttack::drawRect() const{
        return makeRect(-getRadius(), -getRadius(), getRadius()*2, getRadius()*2);
    }

    SDL_Rect AOEAttack::collisionRect() const{
        return makeRect(-getRadius(), -getRadius(), getRadius()*2, getRadius()*2);
    }

    Surface *AOEAttack::image() const{
        return 0;
    }

    void AOEAttack::draw(Point offset, Surface &surface) const{
		if (!attacking_) {
			return;
		}
        SDL_Rect rect = drawRect();
		rect.x = static_cast<Sint16>(loc_.x - (rect.w / 2));
		rect.y = static_cast<Sint16>(loc_.y - (rect.h / 2));
		rect.x -= offset.x;
		rect.y -= offset.y;
        SDL_Color color = MAGENTA;
        surface.fill(color, &rect);
		Entity::draw(offset, surface);
    }

    void AOEAttack::update(double delta){
		const timer_t timeElapsed = static_cast<timer_t>(delta * DELTA_MODIFIER);

		// Tick time for attack
		if (attacking_ && (attackingTimer_ > 0)) {
			// Prevent underflow
			if (attackingTimer_ < timeElapsed) {
				// Clamp to 0
				attackingTimer_ = 0;
			}
			else {
				// Subtract time
				const timer_t dt = attackingTimer_ - timeElapsed;
				attackingTimer_ = std::max<timer_t>(0, dt);
			}
			debug("attacking ", attackingTimer_);

			// Attack has finished
			if (attackingTimer_ == 0) {
				attacking_ = false;

				// Check if attack hit anything
				// Apply a punishment for missing
				if (!attackHitSomething_) {
					blood_ += getFailureCost();
				}
				attackHitSomething_ = false;
			}
		}
		
		// Tick time for cooldown
		if (cooldownTimer_ > 0) {
			// Prevent underflow
			if (cooldownTimer_ < timeElapsed) {
				// Clamp to 0
				cooldownTimer_ = 0;
			}
			else {
				// Subtract time
				const timer_t dt = cooldownTimer_ - timeElapsed;
				cooldownTimer_ = std::max<timer_t>(0, dt);
			}
			debug("cooldown ", cooldownTimer_);
		}
    }

	void AOEAttack::attack(Person& person) {
		
		if (!active_) {
			return;
		}

		// if within radius
		const pixels_t dist = distance(person.getLoc(), this->getLoc());
		if (dist <= getRadius())
		{
			// kill
			const int power = Person::MAX_LIFE;
			person.hit(power);

			// add to score
			blood_ += getSuccessBonus();

			// Mark that we hit something and so don't take a punishment
			attackHitSomething_ = true;
		}
	}

	int AOEAttack::getBlood() const {
		return blood_;
	}
	void AOEAttack::resetBlood() {
		blood_ = 0;
	}

	void AOEAttack::operator()(Person& person) {
		attack(person);
	}

	void AOEAttack::activate(const Location& loc) {
		if (active_) { return; }
		if (attacking_) { return; }
 		if (cooldownTimer_ > 0) {
			return;
		}
		loc_ = loc;
		active_ = true;
		attacking_ = true;
		attackingTimer_ = getAttackingTime();
		cooldownTimer_ = getCooldownTime();
		sound_.play(-1, 0);
		debug("die!");
	}

	void AOEAttack::deactivate() {
		active_ = false;
	}

    bool AOEAttack::isBatAttack() const{
        return false;
    }

} //namespace Game