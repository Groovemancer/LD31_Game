#pragma once

#ifndef INC_GAMESCREEN_H
#define INC_GAMESCREEN_H

#include "Screen.h"
#include "GameWorld\Level.h"

class GameScreen : public Screen
{
private:
	Level* level;

	// Offsets for where to start drawing to account for the screen border/hud
	int offsetX;
	int offsetY;

	void RenderGameObjects();

public:
	GameScreen();
	~GameScreen();
	void Update( int ticks );
	void Render();
};

#endif