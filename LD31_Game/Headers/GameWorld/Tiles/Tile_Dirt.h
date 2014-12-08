#pragma once

#ifndef INC_TILEDIRT_H
#define INC_TILEDIRT_H

#include "GameWorld\Tiles\Tile.h"

class Tile_Dirt : public Tile
{
public:
	Tile_Dirt();
	~Tile_Dirt();

	void Load();
	Texture* GetTexture();
	static char GetId() { return 'D'; }
};

#endif