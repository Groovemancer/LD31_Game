#include "Base.h"

Tile_StonePlatform::Tile_StonePlatform()
{
	// Default tile size 24x24
	width = 24;
	height = 24;

	// What type of tile this is and how it interacts with the player
	type = PLATFORM;

	deleted = false;
}

void Tile_StonePlatform::Load()
{
	texture = new Texture();
	texture->loadFromFile( "Resources/Textures/Tiles/Tile_StonePlatform.png" );
}

Tile_StonePlatform::~Tile_StonePlatform()
{
	if ( !deleted )
	{
		delete texture;
		deleted = true;
	}
}