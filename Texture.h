#ifndef INC_TEXTURE_H
#define INC_TEXTURE_H

class Texture
{
private:
	// The actual texture
	SDL_Texture* texture;

	// Image dimensions
	int width;
	int height;

public:
	// Initializes variables
	Texture();
	// Deallocates memory
	~Texture();

	// Loads an image at specified path
	bool loadFromFile( std::string path );

	// Deallocates texture
	void free();

	// Renders texture at given point
	void render( int x, int y );

	// Gets image dimensions
	int getWidth() { return width; }
	int getHeight() { return height; }
};

#endif