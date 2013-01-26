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
		attackingTimer_(0),
		missSound1_(SOUND_PATH + "Miss.wav"),
		missSound2_(SOUND_PATH + "Miss2.wav"),
		attacking_(false),
		attackHitSomething_(false),
		attackSucceeded_(false),
		attackMissed_(false),
		hitSoundPtr_(0) {

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
        surface.box(color, &rect);
		Entity::draw(offset, surface);
    }

	// Animate attack
	// When attack finishes, mark if it failed or succeeded
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
			//debug("attacking ", attackingTimer_);

			// Attack has finished
			if (attackingTimer_ == 0) {
				attacking_ = false;

				// Check if attack hit anything
				// Apply a punishment for missing
				if (!attackHitSomething_) {
					attackMissed_ = true;
					attackSucceeded_ = false;
				}
				else {
					attackSucceeded_ = true;
					attackMissed_ = false;
				}
				attackHitSomething_ = false;
			}
		}
    }

	void AOEAttack::attack(Person& person) {
		
		if (!attacking_) {
			return;
		}

		// if within radius
		const pixels_t dist = distance(person.getLoc(), this->getLoc());
		if (dist <= getRadius())
		{
			// kill
			const int power = Person::MAX_LIFE;
            debug("Hit: ", isBatAttack() ? "Bat attack!" : "Normal attack!");
			person.hit(power, isBatAttack());

			if (hitSoundPtr_) {
				hitSoundPtr_->play(-1, 0);
			}

			// Mark that we hit something for scoring when attack ends
			attackHitSomething_ = true;
		}
	}

	void AOEAttack::operator()(Person& person) {
		attack(person);
	}

	void AOEAttack::activateFromPlayerInput(const Location& loc) {
		if (attacking_) { return; }
 		
		loc_ = loc;
		attacking_ = true;
		attackingTimer_ = getAttackingTime();
		//sound_.play(-1, 0);
		//debug("die!");
	}

    bool AOEAttack::isBatAttack() const{
        return false;
    }

	bool AOEAttack::isAttacking() const {
		return attacking_;
	}

	bool AOEAttack::attackSucceeded() const {
		return attackSucceeded_;
	}

	bool AOEAttack::attackFailed() const {
		// TODO put in better spot
		if (attackMissed_) {
			const int choice = rand() % 2;
			if (choice == 0) {
				missSound1_.play(-1, 0);
			}
			else {
				missSound2_.play(-1, 0);
			}
		}
		return attackMissed_;
	}

	void AOEAttack::resetAttackState() {
		attacking_ = false;
		attackHitSomething_ = false;
		attackSucceeded_ = false;
		attackMissed_ = false;
	}

} //namespace Game