#ifndef INC_BASE_H
#define INC_BASE_H

#include <SDL.h>
#include <SDL_image.h>

#include "MainGame.h"
#include "Game.h"

#include "Helpers\InputManager.h"
#include "Helpers\Helpers.h"
#include "Helpers\Timer.h"
#include "Helpers\Vector2f.h"
#include "Graphics\Texture.h"

#include "Screens\Screen.h"
#include "Screens\ScreenManager.h"
#include "Screens\GameScreen.h"

#include "GameWorld\Level.h"
#include "GameWorld\Tiles\Tile.h"

#include <string>
#include <sstream>
#include <cmath>
#include <vector>
#include <map>
#include <hash_map>
//#include <windows.h>
//#include <stdio.h>

// RELEASE: Don't forget to remove VLD!
#include <vld.h> // Memory Leak Detector... Remove when ship

#endif