#include "Base.h"

Tile_Pipe::Tile_Pipe()
{
	// Default tile size 24x24
	width = 24;
	height = 24;

	// What type of tile this is and how it interacts with the player
	type = EMPTY;

	deleted = false;
	Load();
}

void Tile_Pipe::Load()
{
	//texture = new Texture();
	//texture->loadFromFile( "Resources/Textures/Tiles/Tile_Pipe.png" );
	texture = TextureManager::LoadTexture( "Tile_Pipe", "Resources/Textures/Tiles/FTile_Pipe.png" );
}

Tile_Pipe::~Tile_Pipe()
{
	if ( !deleted )
	{
		//delete texture;
		deleted = true;
	}
}

Texture* Tile_Pipe::GetTexture()
{
	return TextureManager::GetTexture( "Tile_Pipe" );
}