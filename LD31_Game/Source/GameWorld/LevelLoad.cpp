#include <fstream>
#include <string>

const int width = 32;
const int height = 24;

void LoadFile( std::string path )
{
	std::string line;
	char lvlChars[ height ][ width ];

	std::ifstream infile( path );

	int y = 0;
	while ( std::getline( infile, line ) )
	{
		for ( int x = 0; x < width; x++ )
		{
			lvlChars[y][x] = line[x];
		}
		y++;
	}
	infile.close();
}