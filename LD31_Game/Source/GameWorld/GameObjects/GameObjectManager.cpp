#include "Base.h"

GameObjectManager::GameObjectManager()
{
	gameObjects.clear();
}

GameObjectManager::~GameObjectManager()
{
	for ( int i = 0; i < gameObjects.size(); i++ )
	{
		delete gameObjects[ i ];
	}

	gameObjects.clear();
}

void GameObjectManager::AddGameObject( GameObject* gameObject )
{
	bool inserted = false;
	for ( int i = 0; i < gameObjects.size(); i++ )
	{
		if ( gameObjects[ i ] != NULL )
			continue;

		gameObjects[ i ] = gameObject;
		inserted = true;
	}

	if ( !inserted )
	{
		gameObjects.push_back( gameObject );
	
		int id = gameObjects.size() - 1;
		gameObject->Initialize( id );
	}
}

void GameObjectManager::RemoveGameObject( int id )
{
	gameObjects[ id ] = NULL;
}

GameObject* GameObjectManager::GetGameObject( int id )
{
	if ( gameObjects.size() >= id )
		return NULL;

	if ( gameObjects[ id ] !=
}