#include "Base.h"

GameScreen::GameScreen()
	: Screen()
{
	offsetX = 16;
	offsetY = 12;

	level = new Level();
}

GameScreen::~GameScreen()
{
	delete level;
	Screen::~Screen();
}

void GameScreen::Update( int ticks )
{

}

void GameScreen::Render()
{
	Texture* backgroundTexture = level->GetBackgroundTexture();
	backgroundTexture->render( 0, 0 );
	for ( int y = 0; y < level->GetHeight(); y++ )
	{
		for ( int x = 0; x < level->GetWidth(); x++ )
		{
			Tile* tile = level->GetTile( x, y );

			if ( tile != NULL )
			{
				Texture* tileTexture = tile->GetTexture();
				if ( tileTexture != NULL )
				{
					tileTexture->render( offsetX + x * tile->GetWidth(), offsetY + y * tile->GetHeight() );
				}
			}
		}
	}
}