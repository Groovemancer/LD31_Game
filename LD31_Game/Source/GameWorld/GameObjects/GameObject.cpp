#include "Base.h"

GameObject::GameObject()
{
	position = Vector2f::Zero();
	velocity = Vector2f::Zero();
	initialized = false;
}

GameObject::~GameObject()
{
	delete texture;
}

void GameObject::Initialize( int id )
{
	if ( !initialized )
	{
		GameObject::id = id;
		initialized = true;
	}
}

void GameObject::SetId( int id )
{
	GameObject::id = id;
}