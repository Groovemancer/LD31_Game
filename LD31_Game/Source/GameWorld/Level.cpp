#include "Base.h"
#include <fstream>

Level::Level()
{
	width = 32;
	height = 24;

	tiles = new Tile*[ width * height ];
	fTiles = new Tile*[ width * height ];

	ResetTiles();

	loaded = false;
}

Level::~Level()
{
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
}

void Level::LoadLevel( std::string path )
{
	if ( !loaded )
	{
		// Load the file
		std::string line;
		char** lvlChars = new char*[ height ];
		for ( int i = 0; i < height; i++ )
			lvlChars[ i ] = new char[ width ];
		
		std::ifstream infile( path );

		int y = 0;
		bool getTextureId = false;
		bool getTexture = false;
		std::string backgroundTextureId;
		while ( std::getline( infile, line ) )
		{
			if ( !getTextureId )
			{
				backgroundTextureId = line;

				getTextureId = true;
				continue;
			}
			else if ( !getTexture )
			{
				if ( !LoadBackgroundTexture( backgroundTextureId, line ) )
				{
					printf( "Error loading level: %s\n", path );
					break;
				}

				getTexture = true;
				continue;
			}
			else
			{
				for ( int x = 0; x < width; x++ )
				{
					lvlChars[ y ][ x ] = line[ x ];
				}
			}
			y++;
		}
		infile.close();
		
		// Interpret character data, inserting game tiles into tile array
		for ( y = 0; y < height; y++ )
		{
			for ( int x = 0; x < width; x++ )
			{
				char cData = lvlChars[ y ][ x ];
				InsertCharTile( x, y, cData );
			}
		}

		// Delete lvlChars from memory
		for ( int i = 0; i < height; i++ )
		{
			// Delete inner array
			delete [] lvlChars[ i ];
		}
		// Delete outer array
		delete [] lvlChars;
	}

	loaded = true;
}

bool Level::LoadBackgroundTexture( std::string id, std::string path )
{
	bool success = true;
	backgroundTexture = TextureManager::LoadTexture( id, path );
	if ( backgroundTexture == NULL )
	{
		printf( "Error loading level background texture | %s |: %s\n", id, path );
		success = false;
	}

	return success;
}

void Level::InsertCharTile( int x, int y, char charTile )
{
	if ( charTile == Tile_Dirt::GetId() )
		SetTile( x, y, new Tile_Dirt() );
	else if ( charTile == Tile_Pipe::GetId() )
		SetFTile( x, y, new Tile_Pipe() );
	else if ( charTile == Tile_Stone::GetId() )
		SetTile( x, y, new Tile_Stone() );
	else if ( charTile == Tile_StonePlatform::GetId() )
		SetTile( x, y, new Tile_StonePlatform() );
	else if ( charTile == '$' )
	{
		// Create a spawn point and it add it to the list of spawn points
		Vector2f spawn = Vector2f::Zero();
		spawn.x = x * Tile::WIDTH;
		spawn.y = y * Tile::HEIGHT;
		spawnPoints.push_back( spawn );
	}
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

Vector2f Level::FindOpenSpawnPoint()
{

}

Texture* Level::GetBackgroundTexture()
{
	return backgroundTexture;
}

Tile* Level::GetTile( int x, int y )
{
	if ( x < 0 || x >= width || y < 0 || y >= height )
		return NULL;
	return tiles[ x + y * width ];
}

Tile* Level::GetFTile( int x, int y )
{
	if ( x < 0 || x >= width || y < 0 || y >= height )
		return NULL;
	return fTiles[ x + y * width ];
}

void Level::SetTile( int x, int y, Tile* tile )
{
	if ( x < 0 || x >= width || y < 0 || y >= height )
		return;
	tiles[ x + y * width ] = tile;
}

void Level::SetFTile( int x, int y, Tile* tile )
{
	if ( x < 0 || x >= width || y < 0 || y >= height )
		return;
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