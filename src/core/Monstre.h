/**
@brief Module gérant un monstre
@file Monstre.h
@date 2018/03/06
*/

#ifndef _Monstre_H
#define _Monstre_H

#include "Terrain.h"

/**
@brief Un monstre = sa position 2D et sa direction
*/
class Monstre {

private:

	unsigned int x,y;
	int direction;

public:
		
	Monstre();		
	Monstre(unsigned int dimx, unsigned int dimy, int dir);		
	~Monstre();
	/**
	@brief Accesseur
	@details récupère la coordonnée x
	@param x : la position du monstre sélectionné à la i-1ième colonne.
	*/
	int getX() const;
	/**
	@brief Accesseur
	@details récupère la coordonnée y
	@param y : la position du monstre sélectionné à la i-1ième ligne.
	*/
	int getY() const;
	/**	
	@brief Mutateur
	@details modifie la coordonnée x
	*/	
	void setX(const int dimx);
	/**	
	@brief Mutateur
	@details modifie la coordonnée y
	*/	
	void setY(const int dimy);
	/**
	@brief Action automatique horizontal du monstre 
	@details Vérifie si le déplacement est valide ou non
	@param dx : un tableau de 4 valeurs pour la coordonnée x
	@param xtmp : nouvelle coordonnée x
	@return la nouvelle position du monstre si les coordonnées (x,y) sont valides
	*/
	void bougeAutoHorizontal(const Terrain & t);
	/**
	@brief Action automatique vertical du monstre 
	@details Vérifie si le déplacement est valide ou non
	@param dy : un tableau de 4 valeurs pour la coordonnée y
	@param ytmp : nouvelle coordonnée y
	@return la nouvelle position du monstre si les coordonnées (x,y) sont valides
	*/
	void bougeAutoVertical(const Terrain & t);
};
		
#endif
		
	
		
