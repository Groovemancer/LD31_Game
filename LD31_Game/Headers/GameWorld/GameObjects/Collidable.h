#pragma once

#ifndef INC_COLLIDABLE_H
#define INC_COLLIDABLE_H

#include <SDL.h>

class Collidable
{
private:
	SDL_Rect colRect;
	bool solid;

public:
	Collidable( SDL_Rect colRect, bool solid = true );

	void Collision();

	bool CheckCollision( SDL_Rect colRectA, SDL_Rect colRectB );

	SDL_Rect GetColRect();
	SDL_Rect Bottom();
	SDL_Rect Top();
	SDL_Rect Left();
	SDL_Rect Right();
};

#endif