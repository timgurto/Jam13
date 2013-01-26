// (C) 2013 Tim Gurto

#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "types.h"
#include "HealthBar.h"

namespace Game {

    struct GameState;

    class Environment{

		// Time until game ends
		timer_t countdownTimer_;

        Surface sunBar, sunBarColor;
        static const size_t SUN_BAR_FRAMES;
        static const size_t SUN_BAR_COLUMNS;
        Point sunBarLoc;
        Point sunBarDim;

        Surface overlay[5];

        Surface wisp;

        double wispTimer;
		

    public:
        static GameState *state;

		static const timer_t COUNTDOWN_TIME;

		Environment(double startingHealthPercent);

		void update(double delta);
		void draw(Point offset = Point(), Surface &surface = screenBuf) const;

		bool isSunUp() const;

		HealthBar healthBar_;
	};

} //namespace Game

#endif