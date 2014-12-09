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
#include "Graphics\TextureManager.h"

#include "Screens\Screen.h"
#include "Screens\ScreenManager.h"
#include "Screens\GameScreen.h"

#include "GameWorld\Tiles\Tile.h"
#include "GameWorld\Tiles\Tile_Dirt.h"
#include "GameWorld\Tiles\Tile_Stone.h"
#include "GameWorld\Tiles\Tile_StonePlatform.h"
#include "GameWorld\Tiles\Tile_Pipe.h"
#include "GameWorld\Level.h"

#include "GameWorld\GameObjects\GameObject.h"
#include "GameWorld\GameObjects\Collidable.h"
#include "GameWorld\GameObjects\Projectile.h"
#include "GameWorld\GameObjects\Player.h"
#include "GameWorld\GameObjects\GameObjectManager.h"

#include <string>
#include <sstream>
#include <cmath>
#include <vector>
#include <map>
#include <hash_map>
#include <sstream>

// RELEASE: Don't forget to remove VLD!
#include <vld.h> // Memory Leak Detector... Remove when ship

#endif