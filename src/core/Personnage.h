#ifndef _PERSONNAGE_H
#define _PERSONNAGE_H

#include "Terrain.h"

using namespace std;
/**
@brief Un personnage = sa position 2D initiale
*/
class Personnage {

private : 
	
	unsigned int posX,posY;
	
public :
	
	Personnage ();
	Personnage (unsigned int x,unsigned int y);
		/**
	@brief Déplacement à gauche du personnage
	@details Vérifie si le déplacement est valide ou  non
	@return la nouvelle position du monstre si les coordonnées (x,y) sont valides
		*/
	void gauche (const Terrain & t);
		/**
	@brief Déplacement à droite du personnage
	@details Vérifie si le déplacement est valide ou  non
	@return la nouvelle position du monstre si les coordonnées (x,y) sont valides
		*/
  void droite (const Terrain & t);
  	/**
	@brief Déplacement en haut du personnage
	@details Vérifie si le déplacement est valide ou  non
	@return la nouvelle position du monstre si les coordonnées (x,y) sont valides
		*/
  void haut (const Terrain & t);
  	/**
	@brief Déplacement en bas du personnage
	@details Vérifie si le déplacement est valide ou  non
	@return la nouvelle position du monstre si les coordonnées (x,y) sont valides
		*/
  void bas (const Terrain & t);
  	/**
	@brief Accesseur
	@details Récupère le coordonée x de la position du personnage
		*/
  int getX() const;
  	/**
	@brief Accesseur
	@details Récupère le coordonée y de la position du personnage
		*/
  int getY() const;    
};

#endif
