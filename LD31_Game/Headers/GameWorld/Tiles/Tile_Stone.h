#pragma once

#ifndef INC_TILESTONE_H
#define INC_TILESTONE_H

#include "GameWorld\Tiles\Tile.h"

class Tile_Stone : public Tile
{
public:
	const char ID = 'S';
	Tile_Stone();
	~Tile_Stone();

	void Load();
};

#endif