#include "Base.h"

Tile_Stone::Tile_Stone()
{
	// Default tile size 24x24
	width = 24;
	height = 24;

	// What type of tile this is and how it interacts with the player
	type = SOLID;

	deleted = false;
	Load();
}

void Tile_Stone::Load()
{
	//texture = new Texture();
	//texture->loadFromFile( "Resources/Textures/Tiles/Tile_Stone.png" );
	texture = TextureManager::LoadTexture( "Tile_Stone", "Resources/Textures/Tiles/Tile_Stone.png" );
}

Tile_Stone::~Tile_Stone()
{
	if ( !deleted )
	{
		//delete texture;
		deleted = true;
	}
}

Texture* Tile_Stone::GetTexture()
{
	return Tile_Stone::texture;
}