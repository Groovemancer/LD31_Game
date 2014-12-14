#include "Base.h"
#include <math.h>

#define PI 3.14159265

Projectile::Projectile( GameObject* baseItem, Player* source, Texture* tex, Vector2f launchPos, float launchSpeed, Vector2f accel, double launchAngle, double rotSpeed, double rotAngle, SDL_RendererFlip flip )
	: Collidable( true )
{
	baseObject = baseItem;
	Projectile::source = source;
	texture = tex;
	position = launchPos;
	acceleration = accel;
	velocity = Vector2f::Zero();
	velocity.x = (float)cos( launchAngle * PI / 180.0 ) * launchSpeed;
	velocity.y = (float)sin( launchAngle * PI / 180.0 ) * launchSpeed;
	rotation = rotAngle;
	Projectile::rotSpeed = rotSpeed;
	Projectile::flip = flip;

	origin.x = tex->getWidth() / 2;
	origin.y = tex->getHeight() / 2;

	ignoredObjects.insert( (Collidable*)source );

	colRect.x = (int)position.x;
	colRect.y = (int)position.y;
	colRect.w = texture->getWidth();
	colRect.h = texture->getHeight();

	initialized = false;
}

void Projectile::Collision()
{
	Game::GameObjectManager.SafelyRemoveObject( id );
	// TODO: When it collides with somthing, kill the projectile and place a "Weapon Pickup" on the ground
}

void Projectile::Update( float elapsedTime )
{
	velocity += acceleration;
	position += velocity * elapsedTime;
	
	UpdateRect();

	rotation += rotSpeed * elapsedTime;
}

void Projectile::UpdateRect()
{
	colRect.x = (int)position.x;
	colRect.y = (int)position.y;
}

void Projectile::Render()
{
	if ( texture != NULL )
	{
		texture->render( (int)position.x, (int)position.y, NULL, rotation, &origin, flip );
	}
}