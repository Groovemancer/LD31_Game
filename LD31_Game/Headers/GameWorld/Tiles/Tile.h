#pragma once

#ifndef INC_TILE_H
#define INC_TILE_H

enum TileType
{
	SOLID, PLATFORM, EMPTY
};

class Tile
{
private:
	Texture* texture;
	int width;
	int height;
	char id;

	TileType type;
public:
	Tile();
	~Tile();

	SDL_Rect GetRect();
	Texture* GetTexture();
	int GetWidth();
	int GetHeight();
	char GetId();
};

#endif