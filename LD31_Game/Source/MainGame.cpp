#include "Base.h"

Game MainGame::game;
bool MainGame::quit;
Timer MainGame::delta;
Timer MainGame::capTimer;
int MainGame::countedFrames;

bool MainGame::Initialize()
{
	// Initialize
	if ( game.Initialize() == false )
	{
		OutputDebugString("Game Initialize?\n");
		return false;
	}

	// Game title goes in here
	game.Set_Window_Title( "Ludum Dare #31" );

	game.Set_Fullscreen( 1 );
	
	// Load the files
	if ( !LoadFiles() )
	{
		return false;
	}
	
	// Start delta timer
	countedFrames = 0;
	delta.Start();

	return true;
}

void MainGame::Quit()
{
	OutputDebugString( "Removing all game objects...\n" );
	game.gameObjectManager.RemoveAll();

	OutputDebugString( "Removing all screens...\n" );
	game.screenManager.CleanUp();

	OutputDebugString( "Removing all textures...\n" );
	TextureManager::RemoveAll();

	quit = true;
	OutputDebugString( "Quitting...\n" );
}

bool MainGame::LoadFiles()
{
	// Success flag
	bool success = true;
	
	// TODO: Add Game Screen
	game.screenManager.AddScreen( new GameScreen() );

	Texture* axeTexture = TextureManager::LoadTexture( "Item_Axe", "Resources/Textures/Items/Axe.png" );
	Projectile* axe = new Projectile( NULL, NULL, axeTexture, Vector2f( 100, 100 ), 300, Vector2f( 0, 5 ), -60, 720, -30 );
	game.gameObjectManager.AddGameObject( axe );

	// If everything loaded fine
	return success;
}

void MainGame::GameLoop()
{
	// While the user hasn't quit
	while ( !quit )
	{
		// Start cap timer
		capTimer.Start();

		// Update input manager. Returns true if game is quit
		quit = InputManager::Update();

		// Elapsed time in seconds
		float elapsedTime = delta.Get_Ticks() / 1000.f;

		game.screenManager.Update( elapsedTime );

		if ( InputManager::IsKeyDown( KEY_ESCAPE ) )
			MainGame::Quit();

		// If we quit, break, we don't want to continue rendering
		if ( quit )
			break;

		// Restart delta timer
		delta.Start();

		// Renders screen
		Render();

		countedFrames++;
		// If frame finished early
		int frameTicks = capTimer.Get_Ticks();
		if ( frameTicks < Game::SCREEN_TICKS_PER_FRAME )
		{
			// Wait remaining time
			SDL_Delay( Game::SCREEN_TICKS_PER_FRAME - frameTicks );
		}
	}

	game.screenManager.CleanUp();

	// Clean up
	game.Clean_Up();
}

void MainGame::Render()
{
	SDL_Color color = { 0x64, 0x95, 0xED };

	// Clear screen for rendering
	game.Clear_Screen( color );

	// Render the top screen
	game.screenManager.Render();

	game.Update_Screen();
}