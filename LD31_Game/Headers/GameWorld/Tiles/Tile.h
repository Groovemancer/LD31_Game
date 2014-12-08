#pragma once

#ifndef INC_TILE_H
#define INC_TILE_H

enum TileType
{
	SOLID, PLATFORM, EMPTY
};

class Tile
{
protected:
	bool deleted;
	Texture* texture;
	int width;
	int height;

	TileType type;

	bool initialized;
	
public:
	Tile();
	virtual ~Tile();
	virtual void Load();

	TileType GetType();
	SDL_Rect GetRect();
	virtual Texture* GetTexture();
	int GetWidth();
	int GetHeight();
	static char GetId();
};

#endif