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

	Tile** tiles;

	void GenerateDefaultLevel();

public:
	Level();
	~Level();
	void LoadLevel( std::string path );

	Texture* GetBackgroundTexture();
	Tile* GetTile( int x, int y );

	int GetWidth();
	int GetHeight();
};

#endif