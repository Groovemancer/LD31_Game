#pragma once

#ifndef INC_TILESTONEPLATFORM_H
#define INC_TILESTONEPLATFORM_H

#include "GameWorld\Tiles\Tile.h"

class Tile_StonePlatform : public Tile
{
public:
	const char ID = 's';
	Tile_StonePlatform();
	~Tile_StonePlatform();

	void Load();
};

#endif