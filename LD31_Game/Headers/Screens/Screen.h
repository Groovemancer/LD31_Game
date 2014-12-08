#ifndef INC_SCREEN_H
#define INC_SCREEN_H

class Screen
{
protected:
	bool finished;
	bool disposable;
	Screen* nextScreen;

public:
	Screen();
	virtual ~Screen();
	virtual void Update( float elapsedTime );
	virtual void Render();
	bool IsFinished();
	bool IsDisposable();
	Screen* GetNextScreen();
};

#endif