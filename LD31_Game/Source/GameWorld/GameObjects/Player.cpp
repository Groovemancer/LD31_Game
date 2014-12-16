#include "Base.h"

const float Player::BASE_MOVE_SPEED = 128.0f;
const float Player::BASE_JUMP_HEIGHT = 256.0f;
const float Player::GRAVITY = 5.0f;
const float Player::DODGE_DURATION = 0.5f;
const float Player::DODGE_COOLDOWN = 5.0f;
const float Player::THROW_DURATION = 0.1f;

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
	
	playerState = IDLE;

	dodgeTimer = 0.0f;

	throwTimer = 0.0f;

	facingLeft = false;

	initialized = false;

	SetAnimations();

	UpdateRect();

	animations[ playerState ]->Play();
}

Player::~Player()
{
	for ( std::map< PlayerState, Animation* >::iterator itr = animations.begin(); itr != animations.end(); itr++ )
	{
		delete itr->second;
	}
	animations.clear();
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
	// Get user input
	UpdateInput( elapsedTime );

	// Update position based on velocity
	velocity.x = moveDir.x * moveSpeed;
	if ( !IsGrounded() )
		velocity.y += GRAVITY;
	position += velocity * elapsedTime;

	// Update collision rectangle
	UpdateRect();

	if ( IsGrounded() && playerState == JUMP )
	{
		ChangeState( IDLE );
		velocity.y = 0;
		velocity.x = 0;
	}

	if ( playerState == DODGE )
	{
		dodgeTimer -= elapsedTime;

		if ( dodgeTimer <= 0 )
			ChangeState( IDLE );
	}

	animations[ playerState ]->Update( elapsedTime );
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
		if ( InputManager::IsKeyHeld( KEY_a ) )
			moveLeft = true;
		// Right
		else if ( InputManager::IsKeyHeld( KEY_d ) )
			moveRight = true;

		// Up
		if ( InputManager::IsKeyHeld( KEY_w ) )
			moveUp = true;
		// Down
		else if ( InputManager::IsKeyHeld( KEY_s ) )
			moveDown = true;
		
		// Jump
		if ( InputManager::IsKeyHeld( KEY_SPACE ) )
			jump = true;
		// Throw
		else if ( InputManager::IsKeyDown( KEY_f ) )
			throwing = true;
		// Dodge
		else if ( InputManager::IsKeyDown( KEY_q ) )
			dodge = true;
		// Catch
		else if ( InputManager::IsKeyDown( KEY_e ) )
			catching = true;
	}

	if ( moveLeft )
	{
		// True for moving left
		Move( true );
	}
	else if ( moveRight )
	{
		// False for moving right
		Move( false );
	}
	else
	{
		moveDir.x = 0;
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

void Player::UpdateRect()
{
	std::stringstream str;
	Texture* tex = animations[ playerState ]->GetCurrentFrame();
	colRect.x = 6;
	colRect.y = 0;
	colRect.w = 24;
	colRect.h = 48;

	//str << "X: " << colRect.x << ", Y: " << colRect.y << ", W: " << colRect.w << ", H: " << colRect.h << "\n";
	OutputDebugString( str.str().c_str() );
}

void Player::Move( bool moveLeft )
{
	if ( playerState != THROW && playerState != DODGE && playerState != DEAD && playerState != HIT )
	{
		if ( moveLeft )
		{
			moveDir.x = -1.0f;
			facingLeft = true;
			if ( playerState != JUMP )
			{
				ChangeState( MOVE );
			}
		}
		else if ( !moveLeft )
		{
			moveDir.x = 1.0f;
			facingLeft = false;
			if ( playerState != JUMP )
			{
				ChangeState( MOVE );
			}
		}
	}
}

void Player::Jump()
{
	if ( IsGrounded() && (playerState == IDLE || playerState == MOVE) )
	{
		// Adding a negative value to the y axis moves the player towards
		// the top of the screen.
		velocity.y = -BASE_JUMP_HEIGHT;
		ChangeState( JUMP );
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
			dodgeTimer = DODGE_DURATION;
			ChangeState( DODGE );
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

	std::stringstream str;
	str << "TileX: " << tileX << ", TileY: " << tileY << "\n";
	OutputDebugString( str.str().c_str() );

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

void Player::Render()
{
	Texture* currentFrame = animations[ playerState ]->GetCurrentFrame();

	SDL_RendererFlip flip = SDL_FLIP_NONE;
	if ( facingLeft )
		flip = SDL_FLIP_HORIZONTAL;
	currentFrame->render( (int)position.x, (int)position.y, NULL, 0, NULL, flip );
}

void Player::ChangeState( PlayerState state )
{
	playerState = state;

	for ( std::map< PlayerState, Animation* >::iterator itr = animations.begin(); itr != animations.end(); itr++ )
	{
		if ( itr->first != state )
		{
			animations[ itr->first ]->Stop();
		}
		else
		{
			animations[ itr->first ]->Play();
		}
	}
}

void Player::Collision()
{
	// TODO: Anything specific to a player colliding with something?
}