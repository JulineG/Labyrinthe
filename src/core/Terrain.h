/**
@brief Module gérant un terrain dans l'application Labyrinthe
Un terrain est un tableau 2D de caractères dont le taille est dimx * dimy.

@file Terrain.h
*/

#ifndef _TERRAIN_H
#define _TERRAIN_H

/**
@brief La classe Terrain contient les dimensions du terrain et un tableau 2D de cases (une case = un caractère)
*/
class Terrain {

private : 	

	int dimx;
	int dimy;
	char ter[100][100];

public :
		/**
	@brief <B>Construit</B> un objet terrain
	@details le constructeur remplit dimx et dimy et les cases du tableau ter avec un terrain par 		défaut.
		*/
	Terrain ();
		/**
	@brief Accesseur
	@details Renvoie la largeur du terrain
		*/
	int getDimx () const;	
		/**
	@brief Accesseur
	@details Renvoie la hauteur du terrain
		*/
	int getDimy () const;
		/**
	@brief Accesseur
	@details Renvoie le type d'objet se trouvant en (x,y)
	@param x : abscisse de la case de l'objet
	@param y : ordonnée de la case de l'objet
		*/
	char getXY (const int x, const int y) const;	
		/**
	@brief Mutateur
	@details Modifie la case (x,y) avec le caractère car
	@param x : abs de la case de l'objet à modifier
	@param y : ordonnée de la case de l'objet à modifier
	@param car : caractère à ajouter
		*/
	void setXY (const int x, const int y, char car);	
		/**
	@brief Booléen
	@brief Vérifie la validité d'une position.
	@details Renvoie vrai si on peut positionner un objet aux coordonnées (x,y), faux sinon
	@param x : abscisse de la case à tester
	@param y : ordonnée de la case à tester
		*/
	bool positionEstValide (const int x, const int y) const;
		/**
	@brief Booléen
	@brief Test de comparaison entre la position du personnage de coordonnées (x,y) avec l'épée se trouvant en (x,y).
	@return Renvoie vrai si l'objet se trouvant en (x,y) est une épée, faux sinon.
	@param x : abscisse de la case du personnage.
	@param y : ordonnée de la case du personnage.
		*/
	bool recupererEpee (const int x, const int y);	
		/**
	@brief Booléen
	@brief Test de comparaison entre la position du personnage de coordonnées (x,y) avec l'étoile se trouvant en (x,y).
	@return Renvoie vrai si l'objet se trouvant en (x,y) est une étoile, faux sinon.
	@param x : abscisse de la case du personnage.
	@param y : ordonnée de la case du personnage.
		*/
	bool recupererEtoile (const int x, const int y);
};

#endif










