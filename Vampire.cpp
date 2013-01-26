// (C) 2013 Tim Gurto
#include <cassert>
#include "Vampire.h"
#include "util.h"
#include "Debug.h"

namespace Game {

    extern Debug debug;

    const double Vampire::SPEED = 3;

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

    SDL_Rect Vampire::drawRect() const{
        return makeRect(-64, -100, 128, 128);
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
        SDL_Rect rect = collisionRect();
        surface.box(RED, &getCollisionRect(offset));

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
			debug("cooldown ", cooldownTimer_);
		}

		// Check for key press and update attacks that are attacking
		updateAttack(smallAttack, delta);
		updateAttack(batAttack, delta);

        //animation
        if (timeElapsed >= frameTime){
            frameTime = 42 - (timeElapsed - frameTime);
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
            frameTime -= timeElapsed;
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

	// Check for key press and update attacks that are attacking
	void Vampire::updateAttack(AOEAttack& attack, double delta) {

		// Update attack animations etc
		attack.update(delta);

		// Block input while attacking
		// Block input while cooling down
		if (attack.isAttacking() || (cooldownTimer_ > 0)) {
			// Do nothing
		}

		// Not attacking
		else {

			// Add up score if attack just finished
			int suckedBlood = 0;
			if (attack.attackSucceeded()) {
				suckedBlood += attack.getSuccessBonus();
				attack.resetAttackState();
			}
			else if (attack.attackFailed()) {
				suckedBlood += attack.getFailureCost();
				attack.resetAttackState();
			}
			// There was a change
			if (abs(suckedBlood) > 0) {
				totalBlood_ += suckedBlood;
			}

			// Process input
			if (isKeyPressed(attack.getKey())) {

				assert(!attack.isAttacking());

				// Attack
				attack.activateFromPlayerInput(loc_);

				// Set cooldown timer
				cooldownTimer_ = attack.getCooldownTime();

				// Update animation state for small attack
				// because vampire animates whild doing the attack
				if (!attack.isBatAttack() && state != ATTACKING){
					debug("resetting combat animation");
					frame = 0;
					state = ATTACKING;
					frameTime = 42;
				}
			}
		}
	}

	// Applies attack to player and check if it hit
	// Does not apply if not attacking
	void Vampire::applyAttacks(Person& p) {
		if (smallAttack.isAttacking()) {
			smallAttack(p);
		}
		else if (batAttack.isAttacking()) {
			batAttack(p);
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