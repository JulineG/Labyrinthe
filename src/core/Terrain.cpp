#include "Terrain.h"
#include <cassert>
#include <iostream>
#include <stdlib.h>

using namespace std;

const char terrain1[26][20] ={
	"###################",
	"###################",
	"###################",
	"###################",
	"#######E##e    ####",
	"####### ##### #####",
	"####    ##### #####",
	"####### ##### #####",
	"#######        ####",
	"####E   ## ## #####",
	"####### ## ## #####",
	"#####     L## #####",
	"##### #### ## #####",
	"##### #### ## #####",
	"#### e      e #####",
	"#### ######## #####",
	"#### ######## #####",
	"#### ###L     #####",
	"#### ### #### #####",
	"#### ### #### #####",
	"####          #####",
	"#############E#####",
	"###################",
	"###################",
	"###################",
	"###################"
};

/*const char terrain2[27][20] = {
	"###################",
	"###################",
	"###################",
	"###################",
	"####   E##     ####",
	"#### ######### ####",
	"####  ####     ####",
	"##### ###e  #######",
	"#####          ####",
	"####  ##L   #######",
	"#### ### #  #######",
	"#### ### #  #######",
	"#### ##e # #E######",
	"#### ##### #   ####",
	"####e          ####",
	"#### ######### ####",
	"####           ####",
	"#### #### #### ####",
	"####    # #  # ####",
	"#### ###### ## ####",
	"#### #L#     # ####",
	"####   #  ## # ####",
	"#### ###  #### ####",
	"#####E		####",
	"###################",
	"###################",
	"###################",
	"###################"
};*/

int Terrain::getDimx () const {
	return dimx;
}

int Terrain::getDimy () const {
	return dimy;
}

char Terrain::getXY (const int x, const int y) const {
	assert(x>=0);
	assert(y>=0);
	assert(x<dimx);
	assert(y<dimy);
	return ter[x][y];
}

void Terrain::setXY (const int x, const int y, char car) {
	assert(x>=0);
	assert(y>=0);
	assert(x<dimx);
	assert(y<dimy);
	ter[x][y]= car;
}

Terrain::Terrain (){
	dimx = 19;
	dimy = 26;
	for (int x=0; x<dimx ; x++){
		for (int y =0; y<dimy; y++){
			ter[x][y] = terrain1[dimy-1-y][x];
		}
	}
}

bool Terrain::positionEstValide (const int x, const int y) const {
	return ((x>=0) && (x<dimx) && (y>=0) && (y<dimy) && (ter[x][y] != '#'));
}

bool Terrain:: recupererEpee (const int x, const int y) {
	assert(x>=0);
	assert(y>=0);
	assert(x<dimx);
	assert(y<dimy);
	if (ter[x][y] == 'e'){
		ter[x][y] = ' ';
		return true;
	} else return false;
}

bool Terrain:: recupererEtoile (const int x, const int y) {
	assert(x>=0);
	assert(y>=0);
	assert(x<dimx);
	assert(y<dimy);
	if (ter[x][y] == 'E'){
		ter[x][y] = ' ';
		return true;
	} else return false;
}


	
	
