#include "Base.h"

Collidable::Collidable( bool solid )
{
	Collidable::solid = solid;
}

void Collidable::Update( float elapsedTime )
{
}

bool Collidable::CheckCollision( SDL_Rect colRectA, SDL_Rect colRectB )
{
	// The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	// Calculate the sides of rect A
	leftA = colRectA.x;
	rightA = colRectA.x + colRectA.w;
	topA = colRectA.y;
	bottomA = colRectA.y + colRectA.h;

	// Calculate the sides of rect B
	leftB = colRectB.x;
	rightB = colRectB.x + colRectB.w;
	topB = colRectB.y;
	bottomB = colRectB.y + colRectB.h;

	// If any of the sides from A are outside of B
	if ( bottomA <= topB )
	{
		return false;
	}

	if ( topA >= bottomB )
	{
		return false;
	}

	if ( rightA <= leftB )
	{
		return false;
	}

	if ( leftA >= rightB )
	{
		return false;
	}

	// If none of the sides from A are outside B
	return true;
}

SDL_Rect Collidable::GetColRect()
{
	return colRect;
}

SDL_Rect Collidable::Bottom()
{
	SDL_Rect bottom = colRect;
	bottom.y = colRect.y * 3 / 4;
	bottom.h = colRect.h / 4;

	return bottom;
}

SDL_Rect Collidable::Top()
{
	SDL_Rect top = colRect;
	top.h = colRect.h / 4;

	return top;
}

SDL_Rect Collidable::Left()
{
	SDL_Rect left = colRect;
	left.w = colRect.w / 4;

	return left;
}

SDL_Rect Collidable::Right()
{
	SDL_Rect right = colRect;
	right.x = colRect.x * 3 / 4;
	right.w = colRect.w / 4;

	return right;
}

bool Collidable::IsIgnored( Collidable* object )
{
	return ignoredObjects.find( object ) != ignoredObjects.end();
}