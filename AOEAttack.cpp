// (C) 2013 Tim Gurto

#include "AOEAttack.h"
#include "util.h"
#include "Debug.h"
#include "Person.h"
#include <cmath>

namespace Game {

    extern Debug debug;

	AOEAttack::AOEAttack() :
		Entity(),
		active_(false) {

    }

    SDL_Rect AOEAttack::drawRect() const{
        return makeRect(-40, -40, 80, 80);
    }

    SDL_Rect AOEAttack::collisionRect() const{
        return makeRect(-40, -40, 80, 80);
    }

    Surface *AOEAttack::image() const{
        return 0;
    }

    void AOEAttack::draw(Point offset, Surface &surface) const{
		if (!active_) {
			return;
		}
        SDL_Rect rect = drawRect();
        SDL_Color color = MAGENTA;
        surface.fill(color,
			&makeRect(loc_.x-rect.x-offset.x,
				loc_.y-rect.y-offset.y,
				rect.w,
				rect.h));
    }

    void AOEAttack::update(double delta){
    }

	void AOEAttack::attack(Person& person) const {
		// if within radius
		// kill
		if (!active_) {
			return;
		}
		person.hit(Person::MAX_LIFE);
	}

	void AOEAttack::operator()(Person& person) const {
		attack(person);
	}

	void AOEAttack::activate() {
		active_ = true;
	}

	void AOEAttack::deactivate() {
		active_ = false;
	}

} //namespace Game