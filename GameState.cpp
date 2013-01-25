// (C) 2010-2011 Tim Gurto

#include <cassert>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <list>
#include "globals.h"
#include "util.h"
#include "GameState.h"
#include "misc.h"
#include "Person.h"
#include "Screen.h"

namespace Game {

GameState::GameState():
loop(true),
outcome(IN_PROGRESS),

vampire(Location(400, 300)),
numPeople(10)
{}

// Called after Screen is initialised
void GameState::init() {

	// Populate people
	const Point& screenRes = Screen::getScreenRes();

	personList.resize(numPeople);
	for (size_t i = 0; i < numPeople; ++i) {
		const Point pos(rand() % screenRes.x, rand() % screenRes.y);
		personList[i] = new Person(pos);
	}
}

GameState::~GameState() {
	while (!personList.empty()) {
		Person* p = personList.back();
		personList.pop_back();
		safe_delete(p);
	}
}

void GameState::draw() const {
	PersonList::const_iterator itr;
	for (itr = personList.begin(); itr != personList.end(); ++itr) {
		const Person* p = *itr;
		assert(p);
		p->draw();
	}
}

} // namespace Game
