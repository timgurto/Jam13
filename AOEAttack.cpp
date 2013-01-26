// (C) 2013 Tim Gurto

#include "AOEAttack.h"
#include "util.h"
#include "Debug.h"
#include "Person.h"
#include "GameState.h"
#include <algorithm>
#include <cassert>
#include <cmath>

namespace Game {

    extern Debug debug;

    GameState *AOEAttack::state = 0;

	AOEAttack::AOEAttack() :
		Entity(),
		missSound1_(SOUND_PATH + "Miss.wav"),
		missSound2_(SOUND_PATH + "Miss2.wav"),
		playing_(false),
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
		if (!playing_) {
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
    void AOEAttack::update(double delta) {
		// Do nothing
    }

	// Hit attack with person
	void AOEAttack::hitAttacks(Person& person) {
		
		if (!isPlaying()) {
			return;
		}

		// if within radius
		const pixels_t dist = distance(person.getLoc(), this->getLoc());
		if (dist <= getRadius())
		{
			// Kill person
			const int power = Person::MAX_LIFE;
			debug("Hit: ", isBatAttack() ? "Bat attack!" : "Normal attack!");
			person.hit(power, isBatAttack());

			// Mark that we hit something for scoring when attack ends
			attackHitSomething_ = true;
		}
	}

	bool AOEAttack::attackSucceeded() const {
		return attackHitSomething_;
	}

	void AOEAttack::playAttackSuccess() {
		
        //shake screen
        if (isBatAttack())
            state->shakeScreen(250, 10);
        else
            state->shakeScreen(400, 35);

		getHitSound().play(-1, 0);

		playing_ = false;
	}

	void AOEAttack::playAttackFail() {
		assert(!attackSucceeded());

		const int choice = rand() % 2;
		if (choice == 0) {
			missSound1_.play(-1, 0);
		}
		else {
			missSound2_.play(-1, 0);
		}

		playing_ = false;
	}

	void AOEAttack::operator()(Person& person) {
		hitAttacks(person);
	}

	void AOEAttack::play(const Location& loc) {
		if (playing_) { return; }
 		
		loc_ = loc;
		playing_ = true;
	}

    bool AOEAttack::isBatAttack() const{
        return false;
    }

	bool AOEAttack::isPlaying() const {
		return playing_;
	}

} //namespace Game