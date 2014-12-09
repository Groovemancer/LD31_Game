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
			for ( int j = 0; j < Game::gameObjectManager.Count(); j++ )
			{
				// Don't collide with self...
				if ( j == i )
					continue;

				GameObject* gameObj2 = Game::gameObjectManager.GetGameObject( i );
				
				if ( Collidable* col2 = dynamic_cast< Collidable* > ( gameObj2 ) )
				{
					// Ignores objects that are in the collidable's ignore list
					if ( col->IsIgnored( col2 ) )
						continue;
					// Collide with other game object
					if ( Collidable::CheckCollision( col->GetColRect(), col2->GetColRect() ) )
					{
						OutputDebugString( "Collision!\n" );
					}
				}
			}

			// Check collision against tiles

			// Convert the collidable object's position to tile coordinates
			int colTileX = col->GetColRect().x / Tile::WIDTH;
			int colTileY = col->GetColRect().y / Tile::HEIGHT;

			std::stringstream str;
			str << "Tile X: " << colTileX << ", Y: " << colTileY << ", W: " << col->GetColRect().w << ", H: " << col->GetColRect().h << "\n";
			OutputDebugString( str.str().c_str() );
			
			// Grabs the tile that the object is touching
			// TODO: Account for objects larger than 1 tile wide/high
			Tile* tile = level->GetTile( colTileX, colTileY );			
			if ( tile != NULL && tile->GetType() != EMPTY )
			{
				SDL_Rect tileRect = tile->GetRect();
				tileRect.x = colTileX * Tile::WIDTH;
				tileRect.y = colTileY * Tile::HEIGHT;
				if ( Collidable::CheckCollision( col->GetColRect(), tileRect ) )
				{
					OutputDebugString( "Collided with tile!\n" );
					col->Collision();
				}
			}
			
			//OutputDebugString( "Collidable!\n" );
		}
	}
	Game::gameObjectManager.RemoveAllPending();
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