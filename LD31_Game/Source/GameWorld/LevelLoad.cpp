#include <fstream>
#include <string>

using namespace std;

string string1;
const int widthOfLevel = 32;
const int heightOfLevel = 24;
char lvl_Char[heightOfLevel][widthOfLevel];
 

void LoadFile( string path ){
	ifstream infile( path );
	int x = 0;
	int y = 0;
	while (getline(infile, string1)){
		for (x = 0; x < widthOfLevel; x++){
			lvl_Char[y][x] = string1[x];
		}
		y++;
	}
	infile.close();
}