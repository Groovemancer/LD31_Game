#pragma once

#ifndef INC_TILESTONEPLATFORM_H
#define INC_TILESTONEPLATFORM_H

#include "GameWorld\Tiles\Tile.h"

class Tile_StonePlatform : public Tile
{
public:
	Tile_StonePlatform();
	~Tile_StonePlatform();

	void Load();
	Texture* GetTexture();
	static char GetId() { return 's'; }
};

#endif