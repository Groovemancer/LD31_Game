#pragma once

#ifndef INC_PLAYER_H
#define INC_PLAYER_H

#include "GameObject.h"
#include "Collidable.h"
#include "Graphics\Animation.h"
#include <map>

enum PlayerInput
{
	KEYBOARD1, KEYBOARD2, CONTROLLER1,
	CONTROLLER2, CONTROLLER3, CONTROLLER4
};

enum PlayerState
{
	IDLE, MOVE, JUMP, DODGE, THROW, HIT, DEAD
};

class Player : public GameObject, Collidable
{
private:
	Level* level;

	// Color: 1 - Blue, 2 - Green, 3 - Red, 4 - Black, 5 - White
	int playerColor;

	PlayerInput playerInput;

	float moveSpeed;
	float jumpHeight;
	bool facingLeft;

	Vector2f moveDir;

	PlayerState playerState;

	float dodgeTimer;
	float dodgeCooldown;
	
	float throwTimer;

	std::map< PlayerState, Animation* > animations;
	
	void SetAnimations();

	void Move( bool moveLeft );
	void Jump();
	void Throw();
	void Dodge();
	void Catch();

public:
	static const float BASE_MOVE_SPEED; // 5.0
	static const float BASE_JUMP_HEIGHT; // 128.0
	static const float GRAVITY; // 5.0
	static const float DODGE_DURATION; // 0.5 second duration
	static const float DODGE_COOLDOWN; // 5 second cooldown
	static const float THROW_DURATION; // 0.1

	Player( Level* level, int playerColor, PlayerInput playerInput, Vector2f spawnPosition );
	~Player();

	void Update( float elapsedTime );
	void UpdateInput( float elapsedTime );
	void UpdateRect();
	void Collision();

	bool IsGrounded();

	void ChangeState( PlayerState state );

	void Render();
};

#endif