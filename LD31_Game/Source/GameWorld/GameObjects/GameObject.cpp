#include "Base.h"

GameObject::GameObject()
{
	GameObject( new Vector2f( 0, 0 ), new Vector2f( 0, 0 ), NULL );
}

GameObject::GameObject( Vector2f* pos, Vector2f* vel, Texture* tex )
{
	if ( pos != NULL )
		position = *pos;
	else
		position = Vector2f::Zero();

	if ( vel != NULL )
		velocity = *vel;
	else
		velocity = Vector2f::Zero();

	delete pos;
	delete vel;

	origin.x = 12;
	origin.y = 12;
	rotation = 0.0;

	texture = tex;
	initialized = false;
}

GameObject::~GameObject()
{
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

void GameObject::Update( float elapsedTime )
{
}

void GameObject::Render()
{
	if ( texture != NULL )
	{
		texture->render( (int)position.x, (int)position.y, NULL, rotation, &origin );
	}
}

Vector2f GameObject::GetPosition()
{
	return position;
}

Vector2f GameObject::GetVelocity()
{
	return velocity;
}