#include "Base.h"

SDL_Window* Game::window;
SDL_Renderer* Game::renderer;
ScreenManager Game::screenManager;
GameObjectManager Game::gameObjectManager;

bool Game::Initialize()
{
	// Init flag
	bool success = true;

	// Initialize SDL
	if ( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		// Create window
		window = SDL_CreateWindow( "Ludum Dare #31", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if ( window == NULL ) // In-case it failed to create
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{			
			// Sets the window to fullscreen, windowed, or borderless window
			Set_Fullscreen( WINDOW_STATE );
			
			// Create renderer for window
			renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
			if ( renderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				
				// Initialize renderer color
				SDL_SetRenderDrawColor( renderer, 0x64, 0x95, 0xED, 0xFF ); // Good ole cornflower blue from the XNA days

				// Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if ( !( IMG_Init( imgFlags ) & imgFlags ) )
				{

					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

void Game::Clear_Screen( SDL_Color color )
{
	SDL_SetRenderDrawColor( renderer, color.r, color.g, color.b, color.a );
	SDL_RenderClear( renderer );
}

void Game::Update_Screen()
{
	// Update screen
	SDL_RenderPresent( renderer );
}

void Game::Set_Window_Title( std::string title )
{
	SDL_SetWindowTitle( window, title.c_str() );
}

void Game::Set_Fullscreen( int windowState )
{
	if ( windowState == 1 )
	{
		SDL_SetWindowFullscreen( window, SDL_WINDOW_FULLSCREEN );
	}
	else if ( windowState == 2 )
	{
		SDL_SetWindowFullscreen( window, SDL_WINDOW_FULLSCREEN_DESKTOP );
	}
	else
	{
		SDL_SetWindowFullscreen( window, 0 );
	}
}

void Game::Clean_Up()
{
	// Destroy window and renderer
	SDL_DestroyRenderer( renderer );
	SDL_DestroyWindow( window );
	window = NULL;
	renderer = NULL;

	// Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}