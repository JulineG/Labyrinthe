#include "Monstre.h"
#include <stdlib.h>

Monstre::Monstre(){
	x=12;
	y=8;
	direction=0;
}

Monstre::Monstre(unsigned int dimx, unsigned int dimy, int dir){
	x=dimx;
	y=dimy;
	direction=dir;
}

int Monstre::getX() const{
	return x;
}
int Monstre::getY() const{
	return y;
}
void Monstre::setX(const int dimx){
	x=dimx;
}
void Monstre::setY(const int dimy){
	y=dimy;
}

Monstre::~Monstre (){
	x=0;
	y=0;
	direction=0;
}
	

void Monstre::bougeAutoHorizontal(const Terrain & t){	
	int dx [2] = { 1, -1};
  int xtmp;
  xtmp = x + dx[direction];   
  if (t.positionEstValide(xtmp,y)) {
    x = xtmp;
  }
  else direction = rand()%2;	
}

void Monstre::bougeAutoVertical(const Terrain & t){	
	int dy [2] = { 1, -1};
  int ytmp;
  ytmp = y + dy[direction];   
  if (t.positionEstValide(x,ytmp)) {
    y = ytmp;
  }
  else direction = rand()%2;	
}
