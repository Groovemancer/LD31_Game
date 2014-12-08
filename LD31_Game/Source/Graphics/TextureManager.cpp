#include "Base.h"

std::map< std::string, Texture* > TextureManager::textureManager;

Texture* TextureManager::LoadTexture( std::string id, std::string path )
{
	Texture* texture;

	if ( !TextureExists( id ) )
	{
		texture = new Texture();
		if ( !texture->loadFromFile( path ) )
		{
			printf( "Failed to load texture: %s\n", path );
			texture = NULL;
		}
		else
		{
			textureManager[ id ] = texture;
		}
	}

	texture = textureManager[ id ];
	
	return texture;
}

Texture* TextureManager::GetTexture( std::string id )
{
	if ( !TextureExists( id ) )
		return NULL;
	return textureManager[ id ];
}

void TextureManager::RemoveTexture( std::string id )
{
	if ( !TextureExists( id ) )
		return;

	delete textureManager.find( id )->second;
	textureManager.erase( id );
}

void TextureManager::RemoveAll()
{
	for ( std::map< std::string, Texture* >::iterator itr = textureManager.begin(); itr != textureManager.end(); itr++ )
	{
		delete itr->second;
	}
	textureManager.clear();
}

bool TextureManager::TextureExists( std::string id )
{
	return textureManager.find( id ) != textureManager.end();
}