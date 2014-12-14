#include "Base.h"

Player::Player( Level* level, int playerColor, PlayerInput playerInput, Vector2f spawnPosition )
	: Collidable( true )
{
	Player::level = level;

	Player::playerColor = playerColor;
	Player::playerInput = playerInput;

	position = spawnPosition;
	velocity = Vector2f::Zero();

	moveSpeed = BASE_MOVE_SPEED;
	jumpHeight = BASE_JUMP_HEIGHT;
	
	colRect.x = (int)position.x + (texture->getWidth() / 4);
	colRect.y = (int)position.y;
	colRect.w = texture->getWidth() / 2;
	colRect.h = texture->getHeight();

	playerState = IDLE;

	dodgeTimer = 0.0f;

	throwTimer = 0.0f;

	facingLeft = false;

	initialized = false;

	SetAnimations();
}

void Player::SetAnimations()
{
	std::string colorString;
	if ( playerColor == 1 )
		colorString = "Blue";
	else if ( playerColor == 2 )
		colorString = "Green";		
	else if ( playerColor == 3 )
		colorString = "Red";
	else if ( playerColor == 4 )
		colorString = "Black";
	else if ( playerColor == 5 )
		colorString = "White";
	else
		colorString = "Blue";

	std::vector< std::string > idleIds;
	TextureManager::LoadTexture( "Player_" + colorString + "_Idle", "Resources/Textures/Characters/" + colorString + "/Char_Idle.png" );		
	idleIds.push_back( "Player_" + colorString + "_Idle" );
	Animation* idleAnim = new Animation( idleIds, true );

	std::vector< std::string > walkIds;
	TextureManager::LoadTexture( "Player_" + colorString + "_Walk01", "Resources/Textures/Characters/" + colorString + "/Char_Walk1.png" );
	TextureManager::LoadTexture( "Player_" + colorString + "_Walk02", "Resources/Textures/Characters/" + colorString + "/Char_Walk2.png" );
	walkIds.push_back( "Player_" + colorString + "_Walk01" );
	walkIds.push_back( "Player_" + colorString + "_Idle" );
	walkIds.push_back( "Player_" + colorString + "_Walk02" );
	Animation* moveAnim = new Animation( walkIds, true );

	std::vector< std::string > jumpIds;
	TextureManager::LoadTexture( "Player_" + colorString + "_Jump01", "Resources/Textures/Characters/" + colorString + "/Char_Jump1.png" );
	TextureManager::LoadTexture( "Player_" + colorString + "_Jump02", "Resources/Textures/Characters/" + colorString + "/Char_Jump2.png" );
	jumpIds.push_back( "Player_" + colorString + "_Jump01" );
	jumpIds.push_back( "Player_" + colorString + "_Jump02" );
	Animation* jumpAnim = new Animation( jumpIds, false );

	std::vector< std::string > dodgeIds;
	TextureManager::LoadTexture( "Player_" + colorString + "_Dodge", "Resources/Textures/Characters/" + colorString + "/Char_Dodge.png" );		
	dodgeIds.push_back( "Player_" + colorString + "_Dodge" );
	Animation* dodgeAnim = new Animation( dodgeIds, false );

	std::vector< std::string > throwIds;
	TextureManager::LoadTexture( "Player_" + colorString + "_Throw01", "Resources/Textures/Characters/" + colorString + "/Char_Throw1.png" );
	TextureManager::LoadTexture( "Player_" + colorString + "_Throw02", "Resources/Textures/Characters/" + colorString + "/Char_Throw2.png" );
	throwIds.push_back( "Player_" + colorString + "_Throw01" );
	throwIds.push_back( "Player_" + colorString + "_Throw02" );
	Animation* throwAnim = new Animation( throwIds, false );
		
	std::vector< std::string > hitIds;
	TextureManager::LoadTexture( "Player_" + colorString + "_Hit", "Resources/Textures/Characters/" + colorString + "/Char_Hit.png" );
	hitIds.push_back( "Player_" + colorString + "_Hit" );
	Animation* hitAnim = new Animation( hitIds, false );

	std::vector< std::string > deadIds;
	TextureManager::LoadTexture( "Player_" + colorString + "_Dead", "Resources/Textures/Characters/" + colorString + "/Char_Dead.png" );
	deadIds.push_back( "Player_" + colorString + "_Dead" );
	Animation* deadAnim = new Animation( deadIds, false );

	animations[ IDLE ] = idleAnim;
	animations[ MOVE ] = moveAnim;
	animations[ JUMP ] = jumpAnim;
	animations[ DODGE ] = dodgeAnim;
	animations[ THROW ] = throwAnim;
	animations[ HIT ] = hitAnim;
	animations[ DEAD ] = deadAnim;
}

void Player::Update( float elapsedTime )
{
	UpdateInput( elapsedTime );

	velocity.x = moveDir.x * moveSpeed;
	
	velocity.y += GRAVITY;

	position += velocity * elapsedTime;
}

void Player::UpdateInput( float elapsedTime )
{
	bool moveLeft = false;
	bool moveRight = false;
	bool moveUp = false;
	bool moveDown = false;
	bool jump = false;
	bool dodge = false;
	bool throwing = false;
	bool catching = false;
	
	if ( playerInput == KEYBOARD1 )
	{
		// Left
		if ( InputManager::IsKeyHeld( Key::KEY_a ) )
			moveLeft = true;
		// Right
		else if ( InputManager::IsKeyHeld( Key::KEY_d ) )
			moveRight = true;

		// Up
		if ( InputManager::IsKeyHeld( Key::KEY_w ) )
			moveUp = true;
		// Down
		else if ( InputManager::IsKeyHeld( Key::KEY_s ) )
			moveDown = true;
		
		// Jump
		if ( InputManager::IsKeyHeld( Key::KEY_SPACE ) )
			jump = true;
		// Throw
		else if ( InputManager::IsKeyDown( Key::KEY_f ) )
			throwing = true;
		// Dodge
		else if ( InputManager::IsKeyDown( Key::KEY_q ) )
			dodge = true;
		// Catch
		else if ( InputManager::IsKeyDown( Key::KEY_e ) )
			catching = true;
	}

	if ( moveLeft )
	{
		moveDir.x = -1.0f;
		facingLeft = true;
	}
	else if ( moveRight )
	{
		moveDir.x = 1.0f;
		facingLeft = false;
	}

	if ( moveUp )
	{
		moveDir.y = -1.0f;
	}
	else if ( moveDown )
	{
		moveDir.y = 1.0f;
	}

	if ( jump )
	{
		Jump();
	}
	else if ( throwing )
	{
		Throw();
	}
	else if ( dodge )
	{
		Dodge();
	}
	else if ( catching )
	{
		Catch();
	}
}

void Player::Jump()
{
	if ( IsGrounded() && (playerState == IDLE || playerState == MOVE) )
	{
		velocity.y = -BASE_JUMP_HEIGHT;
	}
}

void Player::Throw()
{
}

void Player::Dodge()
{
	if ( playerState != DODGE && playerState != DEAD && playerState != HIT && playerState != THROW )
	{
		if ( dodgeCooldown <= 0 && dodgeTimer <= 0 )
		{

		}
	}
}

void Player::Catch()
{
}

bool Player::IsGrounded()
{
	// Convert player's position to tile position, shifted down to the bottom of their feet
	int tileX = (int)( position.x / Tile::WIDTH );
	int tileY = (int)( ( position.y + colRect.h ) / Tile::HEIGHT );

	bool grounded = false;

	// If the player is standing on the bottom edge of the map
	if ( tileY >= level->GetHeight() )
	{
		grounded = true;
	}
	// Get the tile below the player
	Tile* tile = level->GetTile( tileX, tileY );
	if ( tile != NULL && ( tile->GetType() == SOLID || tile->GetType() == PLATFORM ) )
	{
		grounded = true;
	}

	Tile* fTile = level->GetFTile( tileX, tileY );
	if ( fTile != NULL && ( fTile->GetType() == SOLID || fTile->GetType() == PLATFORM ) )
	{
		grounded = true;
	}

	return grounded;
}