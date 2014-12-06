#include "Base.h"

int main( int argc, char* args[] )
{
	if ( !MainGame::Initialize() )
	{
		system( "PAUSE" );
		return 1;
	}


	// Run the game
	MainGame::GameLoop();

	system( "PAUSE" );

	return 0;
}