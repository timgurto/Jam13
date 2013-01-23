// (C) 2010-2011 Tim Gurto

#ifndef UPDATE_H
#define UPDATE_H

#include "MessageBox.h"

namespace Game {

struct SDL_Surface;
struct GameState;

//Any processing within the game loop
void updateState(double delta, GameState &state, MessageBox &fpsDisplay);

//Handles events and changes game data accordingly
void handleEvents(GameState &state, MessageBox &fpsDisplay);

} // namespace Game

#endif