#include "Base.h"

int main( int argc, char* args[] )
{
	if ( !MainGame::Initialize() )
	{
		OutputDebugString( "CRASH?\n" );
		return 1;
	}

	// Run the game
	MainGame::GameLoop();

	return 0;
}