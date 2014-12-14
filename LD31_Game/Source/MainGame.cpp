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

	game.Set_Fullscreen( Game::WINDOW_STATE );
	
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
	Game::GameObjectManager.RemoveAll();

	OutputDebugString( "Removing all screens...\n" );
	Game::ScreenManager.CleanUp();

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
	Game::ScreenManager.AddScreen( new GameScreen() );

	Texture* axeTexture = TextureManager::LoadTexture( "Item_Axe", "Resources/Textures/Items/Axe.png" );
	Projectile* axe = new Projectile( NULL, NULL, axeTexture, Vector2f( 400, 400 ), 300, Vector2f( 0, 5 ), -60, 720, -30 );

	Game::GameObjectManager.AddGameObject( axe );

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

		Game::ScreenManager.Update( elapsedTime );

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

	Game::ScreenManager.CleanUp();

	// Clean up
	game.Clean_Up();
}

void MainGame::Render()
{
	SDL_Color color = { 0x64, 0x95, 0xED };

	// Clear screen for rendering
	game.Clear_Screen( color );

	// Render the top screen
	Game::ScreenManager.Render();

	game.Update_Screen();
}