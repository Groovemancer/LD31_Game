#ifndef INC_SCREENMANAGER_H
#define INC_SCREENMANAGER_H

#include "Screen.h"
#include <stack>

class ScreenManager
{
private:
	std::stack< Screen* > screenStack;

public:
	void CleanUp();
	void AddScreen( Screen* screen );
	void RemoveScreen();
	void Update( float elapsedTime );
	void Render();
};

#endif