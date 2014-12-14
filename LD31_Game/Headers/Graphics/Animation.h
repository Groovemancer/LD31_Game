#pragma once

#ifndef INC_ANIMATION_H
#define INC_ANIMATION_H

#include "Texture.h"
#include <string>
#include <vector>

class Animation
{
private:
	std::vector< std::string > textureIds;

	int currentFrame;

	bool loop;
	bool playing;
	bool paused;

	float frameCounter;

	const float FRAMES_PER_SECOND = 24.0f;
	const float FRAME_RATE = FRAMES_PER_SECOND / 1000.0f;

public:
	Animation( std::vector< std::string > textureIds, bool loop = false );

	void Update( float elapsedTime );
	void Play();
	void Pause();
	void Stop();

	Texture* GetCurrentFrame();

};

#endif