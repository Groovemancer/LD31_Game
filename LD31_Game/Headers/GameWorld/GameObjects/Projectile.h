#pragma once

#ifndef INC_PROJECTILE_H
#define INC_PROJECTILE_H

#include "GameObject.h"
#include "Collidable.h"
#include "Player.h"

class Projectile : public GameObject, Collidable
{
private:
	float launchSpeed;
	double rotSpeed;
	Vector2f acceleration;
	int damage;
	
	// TODO: Change to Player instead of GameObject
	GameObject* source;

	// Used for when a Weapon object needs to be placed on the map after it dies
	GameObject* baseObject;

public:
	Projectile( GameObject* baseItem, Player* source, Texture* tex, Vector2f launchPos, float launchSpeed, Vector2f accel, double launchAngle = 0.0, double rotSpeed = 0.0, double rotAngle = 0.0 );

	void Update( float elapsedTime );
	void Collision();
};

#endif