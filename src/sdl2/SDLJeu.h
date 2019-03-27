#ifndef _JEU_H_INCLUDED
#define _IMAGE_H_INCLUDED

/**
@brief Module qui gère l'affichage du Jeu en SDL2
@file SDLJeu.h
@date 20/03/2018
*/

#include "../core/Jeu.h"
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

using namespace std;

//! \brief Pour gérer une image avec SDL2
class Image {

private : 
 
	SDL_Surface * surface;
	SDL_Texture * texture; 
	bool a_change;
		
public :
		
		/**
	@brief <B>Construire</B> un objet image.
	@details Constructeur par défaut de la classe: initialise dimx et dimy à 0
	ce constructeur n'alloue pas de pixel.
		*/
	Image ();
	void chargerImageDepuisFichier(const char* filename, SDL_Renderer * renderer);
 	void creerTextureAPartirDeSurface (SDL_Renderer * renderer);
 	void dessiner (SDL_Renderer * renderer, int x, int y, int w=-1, int h=-1);
 	SDL_Texture * getTexture() const;
 	void setSurface(SDL_Surface * surf);
	
};

class sdlJeu {

private :

	Jeu jeu;
	SDL_Window * window;
	SDL_Renderer * renderer;
	
	int temps;
	
	TTF_Font * font;
	Image font_im;
	SDL_Color font_color;
		
	Mix_Chunk * music;
	bool withSound;

	Image im_arbre;
	Image im_personnage_gauche_droite;
	Image im_personnage_droite_gauche;
	Image im_personnage_epee_gauche_droite;
	Image im_personnage_epee_droite_gauche;
	Image im_monstre;
	Image im_etoile;
	Image im_loupe;
	Image im_porte;
	Image im_epee;
	Image im_coeur;
	Image im_chemin;

public :
	
		/**
	@brief Iniatialisateur du Jeu en SDL
	@details Création de la fenêtre, Ajout du son, Initialisation de la console, Ajout du texte
		*/
  sdlJeu ();
  	/**
  @brief Destructeur 
  @details Initialise tout le jeu à NULL (Suppression de la fenêtre, du son, des textes...)
  	*/
  ~sdlJeu ();
  	/**
  @brief Accesseur
  @details Retourne le temps parcouru dans le jeu
  	*/
  int getTemps()const;
  	/**
  @brief Mutateur
  @details Récupère le temps parcouru dans le jeu
  	*/
	void setTemps (const int t);
		/**
	@brief Traitement des événements en boucle tant que l'utilisateur n'a pas quitté la fenêtre
		*/
  void sdlBoucle ();
  	/**
  @brief Affichage de tous les éléments du jeu (sprites)
  	*/
  void sdlAff (const char action_clavier);
};
	
#endif	
