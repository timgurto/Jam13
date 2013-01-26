// (C) 2013 Tim Gurto

#include "Person.h"
#include "util.h"
#include "Debug.h"
#include <cmath>

namespace Game {

    extern Debug debug;

	const timer_t Person::MAX_AMBLE_TIMER = 3000;
    const double Person::AMBLE_CHANCE = 0.3;
    const double Person::SPEED = .4;
    Sound *Person::heartbeat;

    const pixels_t Person::MAX_SOUND_DISTANCE = 300;

    const int Person::MAX_HEARTBEATS = 1;

	const int Person::MAX_LIFE = 1;

	Person::Person(Point startPos) :
    Entity(),
    /*heart(beat),*/
    ambling_(1.0*rand()/RAND_MAX < AMBLE_CHANCE),
    ambleTimer_(rand()%MAX_AMBLE_TIMER),
    direction_(rand()%4),
    
    heartTimer_(rand()%200 + 900),
	
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

        
        //heartbeat timer
        if (heartTimer_ <= timeElapsed){
            heartTimer_ = rand()%200 + 900 - (timeElapsed - heartTimer_);
            if (isClosest && distToVamp <= MAX_SOUND_DISTANCE){
                //close enough; play sound
                double distance = max(min(1.0 * (distToVamp-30) / (MAX_SOUND_DISTANCE-30), 1.0), 0.0);


                double volume = 1 - pow(distance, 0.25);

                //double invDist = 1 - distance;
                //double volume = invDist * invDist; volume *= volume;

                //double volume = (1-distance) * (1-distance);

                //double volume = 1.0 / (x+.1) - .1

                //double volume = 1 - distance;


                heartbeat->changeVolume(min<int>(volume*MIX_MAX_VOLUME, MIX_MAX_VOLUME));
                heartbeat->play(-1, 0);
                debug("Playing sound; volume=", volume*MIX_MAX_VOLUME);
            }
        }else
            heartTimer_ -= timeElapsed;
    }

	void Person::hit(int hitLife) {
		life_ = std::max(0, life_ - hitLife);
	}

	bool Person::isDead() const {
		if (life_ <= 0) {
			return true;
		}
		return false;
	}

} //namespace Game