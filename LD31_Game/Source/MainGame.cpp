#include "Base.h"

Game MainGame::game;
bool MainGame::quit;
Timer MainGame::delta;

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

	// Set to Windowed!
	game.Set_Fullscreen( 0 );

	// Load the files
	if ( !LoadFiles() )
	{
		return false;
	}
	
	// Start delta timer
	delta.Start();

	return true;
}

void MainGame::Quit()
{
	game.screenManager.CleanUp();
	quit = true;
	OutputDebugString( "Quitting...\n" );
}

bool MainGame::LoadFiles()
{
	// Success flag
	bool success = true;

	// TODO: Add Game Screen
	game.screenManager.AddScreen( new GameScreen() );
	
	// If everything loaded fine
	return success;
}

void MainGame::GameLoop()
{
	// While the user hasn't quit
	while ( !quit )
	{
		// Update input manager. Returns true if game is quit
		quit = InputManager::Update();
				
		game.screenManager.Update( delta.Get_Ticks() );

		if ( InputManager::IsKeyDown( KEY_ESCAPE ) )
			MainGame::Quit();

		// If we quit, break, we don't want to continue rendering
		if ( quit )
			break;

		// Restart delta timer
		delta.Start();

		// Renders screen
		Render();
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