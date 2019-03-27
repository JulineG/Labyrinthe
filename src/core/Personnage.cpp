#include "Personnage.h"

Personnage::Personnage () {
	posX =14;
	posY =21;
}

Personnage::Personnage (unsigned int x, unsigned int y){
	posX = x;
	posY = y;
}

void Personnage::gauche (const Terrain & t){
	if (t.positionEstValide(posX-1,posY)) posX--;	
}

void Personnage::droite (const Terrain & t){
	if (t.positionEstValide(posX+1,posY)) posX++;	
}

void Personnage::haut (const Terrain & t){
	if (t.positionEstValide(posX,posY-1)) posY--;	
}

void Personnage::bas (const Terrain & t){
	if (t.positionEstValide(posX,posY+1)) posY++;	
}

int Personnage::getX() const{
	return posX;
}

int Personnage::getY() const{
	return posY;
}



