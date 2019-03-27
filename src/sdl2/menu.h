


	/**
@brief Module qui gère l'affichage du menu en SDL2
@file menu.h
@date 12/04/2018
	*/

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include "SDLJeu.h"
#include "../core/Jeu.h"

#define SCREEN_WIDTH 512
#define SCREEN_HEIGHT 512

using namespace std;
 /** Pour gérer un menu avec SDL2 */
class Menu {
	
private :	

	char format [50];
	SDL_Window * fenetre;
	SDL_Renderer * renderer;

	TTF_Font * police;

	Image im_menu;
	Image police_im;
	SDL_Color police_couleur;

	bool avecSon;
	Mix_Chunk * music_menu;
		
public :
		/**
	@brief Initialisation du menu
	@details Initialisation de la console
	@details Création de la fenêtre
	@details Ajout du son
		*/
	Menu();
		/**
	@brief Détructeur
	@details Supression de tous les paramètres (Sons, Fenêtres, Textes...)
		*/
	~Menu();
		/**
	@brief Traitement des événements en boucle tant que l'utilisateur n'a pas quitté la fenêtre
		*/
	void MenuBoucle();
		/**
	@brief Affichage du texte "Tentez votre chance"
	@details Lorsque la souris passe sur la touche jouer, un texte s'affiche
		*/
	void sdlAff_jouer();
	void sdlAffichage();
		/**
	@brief Affichage du texte "Vous nous quittez... ?"
	@details Lorsque la souris passe sur la touche quitter, un texte s'affiche
		*/
	void sdlAff_quitter();
		/**
	@brief Affichage du texte "Prochainement..."
	@details Lorsque la souris passe sur la touche à suivre, un texte s'affiche
		*/
	void sdlAff_a_suivre();
		/**
	@brief Affichage du texte "Besoin d'aide ?"
	@details Lorsque la souris passe sur la touche Aide, un texte s'affiche
		*/
	void sdlAff_aide();
};
