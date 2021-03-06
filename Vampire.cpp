// (C) 2013 Tim Gurto
#include <cassert>
#include <cmath>
#include "Joystick.h"
#include "Vampire.h"
#include "util.h"
#include "Debug.h"
#include "GameState.h"

namespace Game {

	extern Joystick joystick;
    extern Debug debug;

    GameState *Vampire::gameState = 0;

    const double Vampire::SPEED = 3;
	const double Vampire::MAX_HEALTH = 30;

    const Surface *Vampire::idleE = 0;
    const Surface *Vampire::idleF = 0;
    const Surface *Vampire::idleG = 0;
    const Surface *Vampire::idleH = 0;
    const Surface *Vampire::movingE = 0;
    const Surface *Vampire::movingF = 0;
    const Surface *Vampire::movingG = 0;
    const Surface *Vampire::movingH = 0;
    const Surface *Vampire::attackingE = 0;
    const Surface *Vampire::attackingF = 0;
    const Surface *Vampire::attackingG = 0;
    const Surface *Vampire::attackingH = 0;
    const Surface *Vampire::burningL = 0;
    const Surface *Vampire::burningR = 0;

    const size_t Vampire::idleColumns = 16;
    const size_t Vampire::idleFrames = 65;
    const size_t Vampire::movingColumns = 8;
    const size_t Vampire::movingFrames = 30;
    const size_t Vampire::attackingColumns = 4;
    const size_t Vampire::attackingFrames = 15;
    const size_t Vampire::burningColumns = 8;
    const size_t Vampire::burningFrames = 37;

	const int START_BLOOD = 10;

    Vampire::Vampire(const Location &loc) :
		frameTime(rand()%42),
		frame(rand()%idleFrames),
		state(IDLE),
		smallAttack(),
		batAttack(),
		totalBlood_(START_BLOOD),
		cooldownTimer_(0),
		lastUpDown(DIR_D),
		lastLeftRight(DIR_R),
		dir(DIR_F),
        visible(true)
	{

        loc_ = loc;
    }

	double Vampire::getTotalBlood() const {
		return totalBlood_;
	}

	double Vampire::getBloodPercent() const {
		return (totalBlood_ / MAX_HEALTH);
	}

	bool Vampire::isDead() const {
		return getTotalBlood() <= 0;
	}

	bool Vampire::isBloodFull() const {
		return getTotalBlood() >= MAX_HEALTH;
	}

	void Vampire::die() {
		totalBlood_ = 0;
	}

    SDL_Rect Vampire::drawRect() const{
        return makeRect(-64, -120, 128, 128);
    }

    SDL_Rect Vampire::collisionRect() const{
        return makeRect(-20, -20, 40, 40);
    }

    Surface *Vampire::image() const{
        return 0;
    }

    void Vampire::draw(Point offset, Surface &surface) const{

        if (!visible)
            return;

		// Draw attack under vampire sprite
		smallAttack.draw(offset, surface);
		batAttack.draw(offset, surface);

		// Vampire sprite
        const Surface *image = 0;
        switch (dir){
        case DIR_E:
            switch (state){
            case IDLE:
                image = idleE; break;
            case MOVING:
                image = movingE; break;
            case ATTACKING:
                image = attackingE; break;
            case BURNING:
                image = burningR; break;
            }
            break;
        case DIR_F:
            switch (state){
            case IDLE:
                image = idleF; break;
            case MOVING:
                image = movingF; break;
            case ATTACKING:
                image = attackingF; break;
            case BURNING:
                image = burningR; break;
            }
            break;
        case DIR_G:
            switch (state){
            case IDLE:
                image = idleG; break;
            case MOVING:
                image = movingG; break;
            case ATTACKING:
                image = attackingG; break;
            case BURNING:
                image = burningL; break;
            }
            break;
        case DIR_H:
            switch (state){
            case IDLE:
                image = idleH; break;
            case MOVING:
                image = movingH; break;
            case ATTACKING:
                image = attackingH; break;
            case BURNING:
                image = burningL; break;
            }
            break;
		default:
			// Should not happen
			assert(false);
			break;
        }

		assert(image);
        size_t col = 0, row = 0;
        switch (state){
        case IDLE:
            row = frame / idleColumns;
            col = frame % idleColumns;
            break;
        case MOVING:
            row = frame / movingColumns;
            col = frame % movingColumns;
            break;
        case ATTACKING:
            row = frame / attackingColumns;
            col = frame % attackingColumns;
			break;
        case BURNING:
            row = frame / burningColumns;
            col = frame % burningColumns;
            debug("Burning; frame=", frame);
            break;
		default:
			// Should not happen
			assert(false);
			break;
        }
        SDL_Rect srcRect;
        srcRect.w = srcRect.h = 128;
        
        image->draw(screenBuf, &getDrawRect(offset), &makeRect(col * 128, row * 128, 128, 128));

		// Entity debug
		Entity::draw(offset, surface);
    }

    void Vampire::update(double delta){
		const timer_t timeElapsed = static_cast<timer_t>(delta * DELTA_MODIFIER);

        if (state != BURNING){


		    VampireState oldState = state;

            //movement through arrow keys
		    bool up = false;
		    bool down = false;
		    bool left = false;
		    bool right = false;
		    double distance = 0.0;
		    {
			    up |= isKeyPressed(SDLK_UP);
			    down |= isKeyPressed(SDLK_DOWN);
			    left |= isKeyPressed(SDLK_LEFT);
			    right |= isKeyPressed(SDLK_RIGHT);

			    if (up && down)
				    up = down = false;
			    if (left && right)
				    left = right = false;

			    distance = delta * SPEED;
			    if ((up || down) && (left || right))
				    //diagonal movement
				    distance *= INV_SQRT2; //for each of the two directions

			    if (up){
				    loc_.y -= distance;
				    lastUpDown = DIR_U;
			    }else if (down){
				    loc_.y += distance;
				    lastUpDown = DIR_D;
			    }
			    if (left){
				    loc_.x -= distance;
				    lastLeftRight = DIR_L;
			    }else if (right){
				    loc_.x += distance;
				    lastLeftRight = DIR_R;
			    }
		    }

		    // Movement through joystick
		    if (joystick.enabled())
		    {
			    const double JOY_SPEED = 0.55;
			    const double distanceX = joystick.getLeftRightAxis() * JOY_SPEED;
			    const double distanceY = joystick.getUpDownAxis() * JOY_SPEED;

			    up |= distanceY < 0;
			    down |= distanceY > 0;
			    left |= distanceX < 0;
			    right |= distanceX > 0;

			    const double dx = distanceX * delta * JOY_SPEED;
			    const double dy = distanceY * delta * JOY_SPEED;

			    if (up){
				    loc_.y += dy;
				    lastUpDown = DIR_U;
			    }
			    if (down){
				    loc_.y += dy;
				    lastUpDown = DIR_D;
			    }
			    if (left){
				    loc_.x += dx;
				    lastLeftRight = DIR_L;
			    }
			    if (right){
				    loc_.x += dx;
				    lastLeftRight = DIR_R;
			    }
		    }


            if (loc_.x < gameState->leftBound)
                loc_.x = gameState->leftBound;
            if (loc_.x > gameState->rightBound)
                loc_.x = gameState->rightBound;
            if (loc_.y < gameState->topBound)
                loc_.y = gameState->topBound;
            if (loc_.y > gameState->bottomBound)
                loc_.y = gameState->bottomBound;

		    if (state != ATTACKING)
			    state = MOVING;
		    if (up && right)
			    updateDirection(DIR_E);
		    else if (down && right)
			    updateDirection(DIR_F);
		    else if (down && left)
			    updateDirection(DIR_G);
		    else if (up && left)
			    updateDirection(DIR_H);
		    else if (up)
			    updateDirection(DIR_U);
		    else if (down)
			    updateDirection(DIR_D);
		    else if (left)
			    updateDirection(DIR_L);
		    else if (right)
			    updateDirection(DIR_R);
		    else
			    if (state != ATTACKING)
				    state = IDLE;

            //debug(loc_.x, ",", loc_.y);

            if (state != oldState){
                if (state == IDLE)
                    frame = rand() % idleFrames;
                else if (state == MOVING)
                    frame = rand() % movingFrames;
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
		        //debug("cooldown ", cooldownTimer_);
	        }

			// Update attack animations etc
			smallAttack.update(delta);
			batAttack.update(delta);
        }

        //animation
        if (timeElapsed >= frameTime){
            frameTime = max<int>(42 - (timeElapsed - frameTime), 0);
            ++frame;
            if (state == IDLE && frame >= idleFrames ||
                state == MOVING && frame >= movingFrames ||
                state == ATTACKING && frame >= attackingFrames ||
                state == BURNING && frame >= burningFrames){
                frame = 0;
                if (state == ATTACKING)
                    state = MOVING;
                else if (state == BURNING){
                    visible=false;
                }
            }
                
        }
		else {
            frameTime = max<int>(frameTime - timeElapsed, 0);
		}
    }

    void Vampire::updateDirection(Direction newDir){
        switch (newDir){
        case DIR_E:
        case DIR_F:
        case DIR_G:
        case DIR_H:
            dir = newDir;
            break;

        case DIR_U:
            dir = (lastLeftRight == DIR_R ? DIR_E : DIR_H);
            break;

        case DIR_D:
            dir = (lastLeftRight == DIR_R ? DIR_F : DIR_G);
            break;

        case DIR_L:
            dir = (lastUpDown == DIR_D ? DIR_G : DIR_H);
            break;

        case DIR_R:
            dir = (lastUpDown == DIR_U? DIR_E : DIR_F);
            break;
        }
    }

	bool Vampire::checkInputForAttacks() {

		// Block input while cooling down
		if (cooldownTimer_ > 0) {
			return false;
		}

		// Block input while animations finish
		if (state == ATTACKING) {
			return false;
		}

		// Check input
		bool attacking = false;
		attacking |= checkInputForAttack(smallAttack);
		attacking |= checkInputForAttack(batAttack);
		return attacking;
	}

	// Check for key press and update attacks that are attacking
	bool Vampire::checkInputForAttack(AOEAttack& attack) {

		bool result = false;

		// Process input
		if (isKeyPressed(attack.getKey()) ||
			joystick.isPressed(attack.getJoyButton())) {

			assert(!attack.isPlaying());

			result = true;

			// Start attack playing
			attack.play(loc_);

			// Set cooldown timer on ourself
			cooldownTimer_ = attack.getCooldownTime();

			// Reset animation state for small attack
			// because vampire animates whild doing the attack
			if (!attack.isBatAttack() && (state != ATTACKING)) {
				debug("resetting combat animation");
				frame = 0;
				state = ATTACKING;
				frameTime = 42;
			}
		}

		return result;
	}

	// Applies attack to player and check if it hit
	// Does not apply if not attacking
	void Vampire::hitAttacks(Person& p) {
		if (smallAttack.isPlaying()) {
			smallAttack(p);
		}
		else if (batAttack.isPlaying()) {
			batAttack(p);
		}
	}

	void Vampire::scoreAttacks() {
		scoreAttack(smallAttack);
		scoreAttack(batAttack);
	}

	void Vampire::scoreAttack(AOEAttack& attack) {
		// Not playing, skip
		if (!attack.isPlaying()) {
			return;
		}

		// Add up score if attack just finished
		double suckedBlood = 0;
		if (attack.attackSucceeded()) {
			suckedBlood += attack.getSuccessBonus() * attack.getNumHit();
			attack.playAttackSuccess();
		}
		else {
			suckedBlood += attack.getFailureCost();
			attack.playAttackFail();
		}

		// There was a change
		if (fabs(suckedBlood) > 0.0) {
			totalBlood_ = std::max(0.0, std::min(totalBlood_ + suckedBlood, MAX_HEALTH));

			// Died from blood loss
			if (isDead()) {
				return;
			}
		}
	}

    void Vampire::setIdleImages(const Surface *e,
                                const Surface *f,
                                const Surface *g,
                                const Surface *h){
        idleE = e;
        idleF = f;
        idleG = g;
        idleH = h;
    }

    void Vampire::setMovingImages(const Surface *e,
                                  const Surface *f,
                                  const Surface *g,
                                  const Surface *h){
        movingE = e;
        movingF = f;
        movingG = g;
        movingH = h;
    }

    void Vampire::setAttackingImages(const Surface *e,
                                     const Surface *f,
                                     const Surface *g,
                                     const Surface *h){
        attackingE = e;
        attackingF = f;
        attackingG = g;
        attackingH = h;
    }

    void Vampire::setBurningImages(const Surface *l,
                                      const Surface *r){
        burningL = l;
        burningR = r;
    }

    SDL_Rect Vampire::getDrawRect(Point offset) const{
        return drawRect() + loc_ - offset;
    }

    SDL_Rect Vampire::getCollisionRect(Point offset) const{
        return collisionRect() + loc_ - offset;
    }

} //namespace Game