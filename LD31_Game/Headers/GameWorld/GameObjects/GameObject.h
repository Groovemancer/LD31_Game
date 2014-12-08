#pragma once

#ifndef INC_GAMEOBJECT_H
#define INC_GAMEOBJECT_H

#include "Graphics\Texture.h"
#include "Helpers\Vector2f.h"

class GameObject
{
protected:
	Vector2f position;
	Vector2f velocity;

	Texture* texture;

	int id;
	bool initialized;
public:
	GameObject();
	GameObject( Vector2f* pos = NULL, Vector2f* vel = NULL, Texture* texture = NULL );
	virtual ~GameObject();
	void Initialize( int id );
	void SetId( int id );

	void Update( int ticks );
	void Render();

	Vector2f GetPosition();
	Vector2f GetVelocity();
};

#endif