#include "Base.h"

void ScreenManager::CleanUp()
{
	// As long as the stack isn't empty, empty it one at a time
	while ( !screenStack.empty() )
	{
		RemoveScreen();
	}
}

void ScreenManager::AddScreen( Screen* screen )
{
	screenStack.push( screen );
}

void ScreenManager::RemoveScreen()
{
	Screen* screen = screenStack.top();
	delete screen;
	screenStack.pop();
}

void ScreenManager::Update( int ticks )
{
	if ( !screenStack.empty() )
	{
		// Get the top screen
		Screen* screen = screenStack.top();

		// Update the top screen
		screen->Update( ticks );

		// If and when the top screen is done, move to its next screen
		if ( screen->IsFinished() )
		{
			if ( screen->GetNextScreen() != NULL )
			{
				AddScreen( screen->GetNextScreen() );
			}
			else
			{
				do
				{
					RemoveScreen();
				} while ( screenStack.top()->IsDisposable() );
			}
		}
	}
}

void ScreenManager::Render()
{
	if ( !screenStack.empty() )
	{
		Screen* screen = screenStack.top();
		if ( screen != NULL && !screen->IsFinished() )
		{
			screen->Render();
		}
	}
}