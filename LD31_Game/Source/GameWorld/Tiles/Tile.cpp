#include "Base.h"

Tile::Tile()
{
	// Default tile size 24x24
	width = 24;
	height = 24;

	// What type of tile this is and how it interacts with the player
	type = EMPTY;
}

void Tile::Load()
{
}

Tile::~Tile()
{
}

TileType Tile::GetType()
{
	return type;
}

SDL_Rect Tile::GetRect()
{
	SDL_Rect rect = { 0, 0, width, height };
	return rect;
}

Texture* Tile::GetTexture()
{
	return NULL;
}

int Tile::GetWidth()
{
	return width;
}

int Tile::GetHeight()
{
	return height;
}

char Tile::GetId()
{
	return '.';
}