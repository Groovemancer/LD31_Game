#pragma once

#ifndef INC_TILEPIPE_H
#define INC_TILEPIPE_H

#include "GameWorld\Tiles\Tile.h"

class Tile_Pipe : public Tile
{
public:
	const char ID = 'P';
	Tile_Pipe();
	~Tile_Pipe();

	void Load();
};

#endif