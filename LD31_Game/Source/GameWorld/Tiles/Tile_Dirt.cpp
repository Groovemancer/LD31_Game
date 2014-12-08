#include "Base.h"

Tile_Dirt::Tile_Dirt()
{
	// Default tile size 24x24
	width = 24;
	height = 24;

	// What type of tile this is and how it interacts with the player
	type = SOLID;

	deleted = false;
	Load();
}

void Tile_Dirt::Load()
{
	Tile_Dirt::texture = TextureManager::LoadTexture( "Tile_Dirt", "Resources/Textures/Tiles/Tile_Dirt.png" );
}

Tile_Dirt::~Tile_Dirt()
{
	if ( !deleted )
	{
		//delete texture;
		deleted = true;
	}
}

Texture* Tile_Dirt::GetTexture()
{
	return TextureManager::GetTexture( "Tile_Dirt" );
}