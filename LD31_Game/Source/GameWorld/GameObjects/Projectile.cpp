#include "Base.h"
#include <math.h>

#define PI 3.14159265

Projectile::Projectile( GameObject* baseItem, Player* source, Texture* tex, Vector2f launchPos, float launchSpeed, Vector2f accel, double launchAngle, double rotSpeed, double rotAngle )
	: Collidable( true )
{
	baseObject = baseItem;
	Projectile::source = source;
	texture = tex;
	position = launchPos;
	acceleration = accel;
	velocity = Vector2f::Zero();
	velocity.x = cos( launchAngle * PI / 180.0 ) * launchSpeed;
	velocity.y = sin( launchAngle * PI / 180.0 ) * launchSpeed;
	rotation = rotAngle;

	OutputDebugString( "We've got a projectile!\n" );

	ignoredObjects.insert( (Collidable*)source );
}

void Projectile::Collision()
{
	// TODO: When it collides with somthing, kill the projectile and place a "Weapon Pickup" on the ground
}

void Projectile::Update( float elapsedTime )
{
	velocity += acceleration;
	position += velocity * elapsedTime;
	colRect.x = (int)position.x;
	colRect.y = (int)position.y;

	rotation += rotSpeed * elapsedTime;
}