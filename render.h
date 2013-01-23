// (C) 2010-2011 Tim Gurto

#ifndef RENDER_H
#define RENDER_H

#include "MessageBox.h"

namespace Game {

struct CoreData;
struct GameData;
struct SDL_Surface;
struct GameState;

//Draws everything to the screen
void render(const GameState &state, const MessageBox &fpsDisplay);

} // namespace Game

#endif