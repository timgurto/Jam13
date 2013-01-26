// (C) 2013 Tim Gurto

#include "Person.h"
#include "util.h"
#include "Debug.h"

namespace Game {

    extern Debug debug;

	const timer_t Person::MAX_AMBLE_TIMER = 3000;
    const double Person::AMBLE_CHANCE = 0.3;
    const double Person::SPEED = .4;

	const int Person::MAX_LIFE = 1;

	Person::Person(Point startPos) :
    Entity(),
    /*heart(beat),*/
    ambling_(1.0*rand()/RAND_MAX < AMBLE_CHANCE),
    ambleTimer_(rand()%MAX_AMBLE_TIMER),
    direction_(rand()%4),
	
	life_(MAX_LIFE) {

        loc_ = startPos;
    }

    SDL_Rect Person::drawRect() const{
        return makeRect(-3, -3, 6, 6);
    }

    SDL_Rect Person::collisionRect() const{
        return makeRect(-3, -3, 6, 6);
    }

    Surface *Person::image() const{
        return 0;
    }

    void Person::draw(Point offset, Surface &surface) const{
        SDL_Rect rect = drawRect();
        SDL_Color color = ambling_ ? WHITE : BLUE;
        surface.fill(color,
			&makeRect(loc_.x-rect.x-offset.x,
				loc_.y-rect.y-offset.y,
				rect.w,
				rect.h));
		Entity::draw(offset, surface);
    }

    void Person::update(double delta, pixels_t distToVamp){

        timer_t timeElapsed = delta * DELTA_MODIFIER;

        //ambling timer
        if (ambleTimer_ <= timeElapsed){
            ambleTimer_ = rand() % MAX_AMBLE_TIMER - (timeElapsed - ambleTimer_);
            ambling_ = 1.0*rand()/RAND_MAX < AMBLE_CHANCE;
            direction_ = rand() % 4;
        }else
            ambleTimer_ -= timeElapsed;

        //ambling
        if (ambling_){
            double distance = SPEED * delta;
            switch (direction_){
            case 0:
                loc_.x -= distance;
                break;
            case 1:
                loc_.x += distance;
                break;
            case 2:
                loc_.y -= distance;
                break;
            case 3:
                loc_.y += distance;
            }
        }
    }

	void Person::hit(int hitLife, bool isBatAttack) {
		life_ = std::max(0, life_ - hitLife);
		debug("argh!");
	}

	bool Person::isDead() const {
		if (life_ <= 0) {
			return true;
		}
		return false;
	}

} //namespace Game