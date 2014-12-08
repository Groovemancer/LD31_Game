#include "Base.h"

GameScreen::GameScreen()
	: Screen()
{
	offsetX = 16;
	offsetY = 12;

	level = new Level();
	level->LoadLevel( "Resources/Levels/level_01.lvl" );
}

GameScreen::~GameScreen()
{
	delete level;
	Screen::~Screen();
}

void GameScreen::Update( float elapsedTime )
{
	for ( int i = 0; i < Game::gameObjectManager.Count(); i++ )
	{
		GameObject* gameObj = Game::gameObjectManager.GetGameObject( i );
		
		if ( gameObj == NULL )
			continue;

		gameObj->Update( elapsedTime );

		// TODO: Check collisions here!
		if ( Collidable* col = dynamic_cast< Collidable* >( gameObj ) )
		{
		}
	}
}

void GameScreen::Render()
{
	Texture* backgroundTexture = level->GetBackgroundTexture();
	backgroundTexture->render( 0, 0 );

	// Render background tiles
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
	
	// Render Game Objects
	RenderGameObjects();

	// TODO: Add player rendering here
	
	// Render foreground tiles
	for ( int y = 0; y < level->GetHeight(); y++ )
	{
		for ( int x = 0; x < level->GetWidth(); x++ )
		{
			Tile* tile = level->GetFTile( x, y );

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

void GameScreen::RenderGameObjects()
{
	for ( int i = 0; i < Game::gameObjectManager.Count(); i++ )
	{
		GameObject* gameObj = Game::gameObjectManager.GetGameObject( i );
		
		if ( gameObj == NULL )
			continue;

		gameObj->Render();
	}
}