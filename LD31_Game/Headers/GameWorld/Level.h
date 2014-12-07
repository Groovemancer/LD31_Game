#pragma once

#ifndef INC_LEVEL_H
#define INC_LEVEL_H

#include <SDL.h>
#include "Tiles\Tile.h"

class Level
{
private:
	Texture* backgroundTexture;

	int width;
	int height;

	Tile** tiles; // Drawn in the Background, before the player(s)
	Tile** fTiles; // Drawn in the Foreground

	void GenerateDefaultLevel();

public:
	Level();
	~Level();
	void LoadLevel( std::string path );

	void ResetTiles();

	Texture* GetBackgroundTexture();
	Tile* GetTile( int x, int y );
	Tile* GetFTile( int x, int y );

	void SetTile( int x, int y, Tile* tile );
	void SetFTile( int x, int y, Tile* tile );

	int GetWidth();
	int GetHeight();
};

#endif