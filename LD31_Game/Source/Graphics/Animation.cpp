#include "Base.h"

Animation::Animation( std::vector< std::string > textureIds, bool loop )
{
	Animation::textureIds = textureIds;
	currentFrame = 0;
	Animation::loop = loop;
	frameCounter = 0.0f;
	playing = false;
	paused = false;
}

void Animation::Update( float elapsedTime )
{
	if ( playing )
	{
		frameCounter += elapsedTime;

		if ( frameCounter >= FRAME_RATE )
		{
			frameCounter++;
		}

		if ( frameCounter >= textureIds.size() )
		{
			if ( loop )
				frameCounter = 0;
			else
				frameCounter = textureIds.size() - 1;
		}
	}
}

void Animation::Play()
{
	playing = true;
	paused = false;
}

void Animation::Pause()
{
	if ( playing )
	{
		paused = true;
		playing = false;
	}
}

void Animation::Stop()
{
	playing = false;
	paused = false;
	frameCounter = 0.0f;
	currentFrame = 0;
}

Texture* Animation::GetCurrentFrame()
{
	return TextureManager::GetTexture( textureIds[ currentFrame ] );
}