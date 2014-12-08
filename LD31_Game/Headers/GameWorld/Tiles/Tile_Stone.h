#pragma once

#ifndef INC_TILESTONE_H
#define INC_TILESTONE_H

#include "GameWorld\Tiles\Tile.h"

class Tile_Stone : public Tile
{
public:
	Tile_Stone();
	~Tile_Stone();

	void Load();
	Texture* GetTexture();
	static char GetId() { return 'S'; }
};

#endif