#include "Base.h"

Level::Level()
{
	backgroundTexture = new Texture();
	backgroundTexture->loadFromFile( "Resources/Textures/Level01_background.png" );

	width = 32;
	height = 24;

	tiles = new Tile*[ width * height ];
	fTiles = new Tile*[ width * height ];

	ResetTiles();

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

	for ( int i = 0; i < width * height; i++ )
	{
		delete fTiles[ i ];
	}
	delete [] fTiles;
}

void Level::GenerateDefaultLevel()
{
	int i = 0;
	for ( int y = 0; y < height; y++ )
	{
		for ( int x = 0; x < width; x++ )	
		{
			if ( y >= 23 || x == 0 || x == 31 )
			{
				tiles[ x + y * width ] = new Tile_Dirt();
				tiles[ x + y * width ]->Load();
				i++;
			}
		}
	}
	std::stringstream str;
	str << "Tile Count: " << i << "\n";
	OutputDebugString( str.str().c_str() );
}

void Level::LoadLevel( std::string path )
{
	// TODO Load File

	/*
	for ( int y = 0; y < height; y++ )
	{
		for ( int x = 0; x < width; x++ )
		{
			char c = char_array[y][x];
			switch ( c )
			{
				case Tile_Dirt::
				tileArray[y][x] = TILE_TYPEA
				break;
			case 'x':
				tileArray[y][x] = TILE_TYPEB
				break;
			default:
				break;
			}
		}
	}
	*/
}

void Level::ResetTiles()
{
	for ( int y = 0; y < height; y++ )
	{
		for ( int x = 0; x < width; x++ )	
		{
			tiles[ x + y * width ] = NULL; // Initialize background tile to NULL
			fTiles[ x + y * width ] = NULL; // Initialize foreground tile to NULL
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

Tile* Level::GetFTile( int x, int y )
{
	return fTiles[ x + y * width ];
}

void Level::SetTile( int x, int y, Tile* tile )
{
	tiles[ x + y * width ] = tile;
}

void Level::SetFTile( int x, int y, Tile* tile )
{
	fTiles[ x + y * width ] = tile;
}

int Level::GetWidth()
{
	return width;
}

int Level::GetHeight()
{
	return height;
}