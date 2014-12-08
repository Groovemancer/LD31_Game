#pragma once

#ifndef INC_TEXTUREMANAGER_H
#define INC_TEXTUREMANAGER_H

#include "Graphics\Texture.h"
#include <map>
#include <string>

class TextureManager
{
private:
	static std::map< std::string, Texture* > textureManager;

public:

	static Texture* LoadTexture( std::string id, std::string path );
	static Texture* GetTexture( std::string id );
	static bool TextureExists( std::string id );

	static void RemoveTexture( std::string id );
	static void RemoveAll();
};

#endif