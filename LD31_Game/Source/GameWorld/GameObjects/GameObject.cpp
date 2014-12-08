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

void GameObject::Update( int ticks )
{
	float gameTime = ticks / 1000.f;

	std::stringstream str;
	str << "Ticks: " << gameTime << "\n";
	OutputDebugString( str.str().c_str() );

	position += velocity * gameTime;
}

void GameObject::Render()
{
	if ( texture != NULL )
	{
		texture->render( (int)position.x, (int)position.y );
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