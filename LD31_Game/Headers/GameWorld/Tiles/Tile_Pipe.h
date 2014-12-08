#pragma once

#ifndef INC_TILEPIPE_H
#define INC_TILEPIPE_H

#include "GameWorld\Tiles\Tile.h"

class Tile_Pipe : public Tile
{
public:
	Tile_Pipe();
	~Tile_Pipe();

	void Load();
	Texture* GetTexture();
	static char GetId() { return 'P'; }
};

#endif