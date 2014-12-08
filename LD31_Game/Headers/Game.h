#ifndef INC_GAME_H
#define INC_GAME_H

#include <SDL.h>
#include "Screens\ScreenManager.h"
#include "GameWorld\GameObjects\GameObjectManager.h"
#include <string>

class Game
{
private:
	// The window being rendered to
	static SDL_Window* window;

	// The renderer which renders textures
	static SDL_Renderer* renderer;

	
public:
	// Dimensions of the screen
	static const int SCREEN_WIDTH = 800;
	static const int SCREEN_HEIGHT = 600;

	// Windowed = 0, Fullscreen = 1, Borderless Window = 2
	static const int WINDOW_STATE = 0;

	// Game FPS
	static const int SCREEN_FPS = 60;
	static const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

	// Manages all the different types of "screens"
	static ScreenManager screenManager;
	static GameObjectManager gameObjectManager;

	bool Initialize();
	void Clear_Screen( SDL_Color color );
	void Update_Screen();
	void Set_Window_Title( std::string title );

	/// Windowed = 0, Fullscreen = 1, Borderless Window = 2
	void Set_Fullscreen( int windowState );
	void Clean_Up();

	static SDL_Window* Window() { return window; }
	static SDL_Renderer* Renderer() { return renderer; }
	//static ScreenManager ScreenManager() { return screenManager; }
};

#endif