#pragma once

#ifndef INC_COLLIDABLE_H
#define INC_COLLIDABLE_H

#include <SDL.h>
#include <set>

class Collidable
{
protected:
	SDL_Rect colRect;
	bool solid;
	std::set< Collidable* > ignoredObjects;

public:
	Collidable( bool solid = true );

	// Called when collides with another collidable object
	void Collision();

	// Keep colRect up to date based on object's position
	virtual void Update( float elapsedTime );
	
	// Determines if there is a collision or not
	static bool CheckCollision( SDL_Rect colRectA, SDL_Rect colRectB );

	SDL_Rect GetColRect();
	SDL_Rect Bottom();
	SDL_Rect Top();
	SDL_Rect Left();
	SDL_Rect Right();

	bool IsIgnored( Collidable* object );
};

#endif