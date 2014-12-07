#pragma once

#ifndef INC_TILEDIRT_H
#define INC_TILEDIRT_H

#include "GameWorld\Tiles\Tile.h"

class Tile_Dirt : public Tile
{
public:
	const char ID = 'D';
	Tile_Dirt();
	~Tile_Dirt();

	void Load();
};

#endif