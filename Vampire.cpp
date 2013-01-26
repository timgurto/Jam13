// (C) 2013 Tim Gurto
#include <cassert>
#include <cmath>
#include "Vampire.h"
#include "util.h"
#include "Debug.h"

namespace Game {

    extern Debug debug;

    const double Vampire::SPEED = 3;
	const double Vampire::MAX_HEALTH = 10;

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

    const size_t Vampire::idleColumns = 16;
    const size_t Vampire::idleFrames = 65;
    const size_t Vampire::movingColumns = 8;
    const size_t Vampire::movingFrames = 30;
    const size_t Vampire::attackingColumns = 4;
    const size_t Vampire::attackingFrames = 15;

	const int START_BLOOD = 4;

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
		dir(DIR_F)
	{

        loc_ = loc;
    }

	double Vampire::getTotalBlood() const {
		return totalBlood_;
	}

	bool Vampire::isDead() const {
		return getTotalBlood() <= 0;
	}

	bool Vampire::isBloodFull() const {
		return getTotalBlood() >= MAX_HEALTH;
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

		// Draw attack under vampire sprite
		smallAttack.draw(offset, surface);
		batAttack.draw(offset, surface);

		// Red square
        //SDL_Rect rect = collisionRect();
        //surface.box(RED, &getCollisionRect(offset));

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
        //movement through arrow keys
        bool
            up =    isKeyPressed(SDLK_UP),
            down =  isKeyPressed(SDLK_DOWN),
            left =  isKeyPressed(SDLK_LEFT),
            right = isKeyPressed(SDLK_RIGHT);

        if (up && down)
            up = down = false;
        if (left && right)
            left = right = false;

        double distance = delta * SPEED;
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

        VampireState oldState = state;
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

        if (state != oldState){
            if (state == IDLE)
                frame = rand() % idleFrames;
            else if (state == MOVING)
                frame = rand() % movingFrames;
        }

		// Tick time for cooldown
		const timer_t timeElapsed = static_cast<timer_t>(delta * DELTA_MODIFIER);
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

        //animation
        if (timeElapsed >= frameTime){
            frameTime = max<int>(42 - (timeElapsed - frameTime), 0);
            ++frame;
            if (state == IDLE && frame >= idleFrames ||
                state == MOVING && frame >= movingFrames ||
                state == ATTACKING && frame >= attackingFrames){
                frame = 0;
                if (state == ATTACKING)
                    state = MOVING;
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
		if (isKeyPressed(attack.getKey())) {

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
		if (cooldownTimer_ > 0) {
			return;
		}
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
			suckedBlood += attack.getSuccessBonus();
			attack.playAttackSuccess();
		}
		else {
			suckedBlood += attack.getFailureCost();
			attack.playAttackFail();
		}

		// There was a change
		if (fabs(suckedBlood) > 0.0) {
			totalBlood_ += suckedBlood;

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

    SDL_Rect Vampire::getDrawRect(Point offset) const{
        return drawRect() + loc_ - offset;
    }

    SDL_Rect Vampire::getCollisionRect(Point offset) const{
        return collisionRect() + loc_ - offset;
    }

} //namespace Game