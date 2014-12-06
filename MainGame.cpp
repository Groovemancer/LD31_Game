#include "Base.h"

Game MainGame::game;
bool MainGame::quit;
Timer MainGame::delta;

bool MainGame::Initialize()
{
	// Initialize
	if ( game.Initialize() == false )
	{
		return false;
	}

	// Game title goes in here
	game.Set_Window_Title( "Ludum Dare #31" );

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
	game.ScreenManager().CleanUp();
	quit = true;
	OutputDebugString( "Quitting...\n" );
}

bool MainGame::LoadFiles()
{
	// TODO: Add Game Screen
	//game.GetScreenManager().AddScreen( new GameScreen() );

	// If everything loaded fine
	return true;
}

void MainGame::GameLoop()
{
	// While the user hasn't quit
	while ( !quit )
	{

		// Update input manager. Returns true if game is quit
		quit = InputManager::Update();
		
		game.ScreenManager().Update( delta.Get_Ticks() );

		if ( quit )
			break;

		// Restart delta timer
		delta.Start();
		
		// Renders screen
		Render();
	}

	// Clean up
	game.Clean_Up();
}

void MainGame::Render()
{
	SDL_Color color = { 0x64, 0x95, 0xED };

	// Clear screen for rendering
	game.Clear_Screen( color );

	// Render the top screen
	game.ScreenManager().Render();

	game.Update_Screen();
}