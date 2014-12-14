#pragma once

#ifndef INC_LEVEL_H
#define INC_LEVEL_H

#include <SDL.h>
#include "Tiles\Tile.h"
#include "Helpers\Vector2f.h"
#include <vector>

class Level
{
private:
	Texture* backgroundTexture;

	int width;
	int height;

	Tile** tiles; // Drawn in the Background, before the player(s)
	Tile** fTiles; // Drawn in the Foreground
	
	// Reads char data, interpretting it and inserting the appropriate tile into the tile array
	void InsertCharTile( int x, int y, char charTile );

	// Whether or not the level was loaded
	bool loaded;

	std::vector< Vector2f > spawnPoints;

	Vector2f FindOpenSpawnPoint();

public:
	Level();
	~Level();

	// Loads a level from a text file, converting character data to tile data
	void LoadLevel( std::string path );

	// Load background texture
	bool LoadBackgroundTexture( std::string id, std::string path );

	// Generates a default level with a floor and a wall on each side
	void GenerateDefaultLevel();

	// Resets tile arrays to NULL all values
	void ResetTiles();

	// The image that is displayed behind all tiles
	Texture* GetBackgroundTexture();

	// Get background tile
	Tile* GetTile( int x, int y );

	// Get foreground tile
	Tile* GetFTile( int x, int y );

	// Set background tile
	void SetTile( int x, int y, Tile* tile );
	// Set foreground tile
	void SetFTile( int x, int y, Tile* tile );

	// Get map width in number of tiles
	int GetWidth();
	// Get map height in number of tiles
	int GetHeight();
};

#endif