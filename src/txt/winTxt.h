#ifndef WINTXT_H
#define WINTXT_H

class winTxt {

private:

	int dimx;//largeur
	int dimy;//hauteur
	char* fenetre;//stocke le contenu de la fenêtre dans un tableau 1D mais on y accède en 2D

public:
	winTxt(int dx, int dy);
		/**
	*@brief Efface tout le tableau
		*/
	void effacer(char c=' ');
		/**
	*@brief Ajoute un caractère c sur les coordonnées (x,y)
		*/
	void ajouteCaractere(int x, int y, char c);
		/**
	*@brief Permet de mettre en pause. 
		*/
	void pause();
		/**
	*@brief accesseur 
	*@details Récupère le Ch.
		*/
	char getCh();
		/**
	*@brief dessine sur les coordonnées (x,y)
		*/
	void dessine(int x=0, int y=0);
		
};
	/**
*@brief Déplace le curseur sur la position (x,y)
*@param x : position horizontal 
*@param y : position vertical
	*/
void termMove(int x, int y);
	/**
*@brief Permet d'effacer le terminal. 
	*/
void termClear();
	/**
*@brief Permet de saisir et initialiser le terminal.
	*/
void termInit();

#endif
		
