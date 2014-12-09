#include "Base.h"

GameObjectManager::GameObjectManager()
{
	gameObjects.clear();
}

GameObjectManager::~GameObjectManager()
{
	for ( int i = 0; i < Count(); i++ )
	{
		delete gameObjects[ i ];
	}

	gameObjects.clear();
}

void GameObjectManager::AddGameObject( GameObject* gameObject )
{
	bool inserted = false;
	for ( int i = 0; i < Count(); i++ )
	{
		if ( gameObjects[ i ] != NULL )
			continue;

		gameObjects[ i ] = gameObject;
		gameObject->Initialize( i );
		inserted = true;
	}

	if ( !inserted )
	{
		gameObjects.push_back( gameObject );

		int id = Count() - 1;
		gameObject->Initialize( id );
	}
}

void GameObjectManager::RemoveGameObject( int id )
{
	delete gameObjects[ id ];
	gameObjects[ id ] = NULL;
}

void GameObjectManager::RemoveAll()
{
	for ( int i = 0; i < Count(); i++ )
	{
		if ( gameObjects[ i ] != NULL )
		{
			delete gameObjects[ i ];
		}

	}
	gameObjects.clear();
}

void GameObjectManager::SafelyRemoveObject( int id )
{
	removeList.push( id );
}

void GameObjectManager::RemoveAllPending()
{
	while ( !removeList.empty() )
	{
		int id = removeList.top();
		RemoveGameObject( id );
		removeList.pop();
	}
}

GameObject* GameObjectManager::GetGameObject( int id )
{
	if ( id >= Count() || id < 0 )
		return NULL;

	return gameObjects[ id ];
}