#include "Base.h"

Tile::Tile()
{
	id = 'x';

	// Default tile size 24x24
	width = 24;
	height = 24;

	// What type of tile this is and how it interacts with the player
	type = SOLID;
	
	deleted = false;
}

void Tile::Load()
{
	texture = new Texture();
	texture->loadFromFile( "Resources/Textures/Tiles/Tile_Test.png" );
	OutputDebugString( "Default\n" );
}

Tile::~Tile()
{
	if ( !deleted )
	{
		OutputDebugString( "Delete Tile\n" );
		delete texture;

		deleted = true;
	}
}

SDL_Rect Tile::GetRect()
{
	SDL_Rect rect = { 0, 0, width, height };
	return rect;
}

Texture* Tile::GetTexture()
{
	return texture;
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
	return id;
}