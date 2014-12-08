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
	void RemoveAll();
	GameObject* GetGameObject( int id );
	std::vector< GameObject* > GetGameObjects();

	int Count() { return (int)gameObjects.size(); }
};

#endif