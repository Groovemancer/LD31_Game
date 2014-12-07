#pragma once

#ifndef INC_GAMEOBJECTMANAGER_H
#define INC_GAMEOBJECTMANAGER_H

#include "GameObject.h"
#include <vector>

class GameObjectManager
{
private:
	std::vector< GameObject* > gameObjects;
public:
	GameObjectManager();
	~GameObjectManager();

	void AddGameObject( GameObject* gameObject );
	void RemoveGameObject( int id );
	GameObject* GetGameObject( int id );
	std::vector< GameObject* > GetGameObjects();
};

#endif