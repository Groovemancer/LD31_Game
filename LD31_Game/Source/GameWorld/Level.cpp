#include "Base.h"

Level::Level()
{
	backgroundTexture = new Texture();
	backgroundTexture->loadFromFile( "Resources/Textures/testBackground.png" );

	width = 32;
	height = 24;

	GenerateDefaultLevel();
}

Level::~Level()
{
	delete backgroundTexture;
	for ( int i = 0; i < width * height; i++ )
	{
		delete tiles[ i ];
	}
	delete [] tiles;
}

void Level::GenerateDefaultLevel()
{
	tiles = new Tile*[ width * height ];

	for ( int y = 0; y < height; y++ )
	{
		for ( int x = 0; x < width; x++ )	
		{
			tiles[ x + y * width ] = NULL;
			if ( y >= 23 || x == 0 || x == 31 )
				tiles[ x + y * width ] = new Tile();
		}
	}
}

Texture* Level::GetBackgroundTexture()
{
	return backgroundTexture;
}

Tile* Level::GetTile( int x, int y )
{
	return tiles[ x + y * width ];
}

int Level::GetWidth()
{
	return width;
}

int Level::GetHeight()
{
	return height;
}