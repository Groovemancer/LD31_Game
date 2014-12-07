#include "Base.h"

Tile_Dirt::Tile_Dirt()
{
	// Default tile size 24x24
	width = 24;
	height = 24;

	// What type of tile this is and how it interacts with the player
	type = SOLID;

	deleted = false;
}

void Tile_Dirt::Load()
{
	texture = new Texture();
	texture->loadFromFile( "Resources/Textures/Tiles/Tile_Dirt.png" );
}

Tile_Dirt::~Tile_Dirt()
{
	if ( !deleted )
	{
		delete texture;
		deleted = true;
	}
}