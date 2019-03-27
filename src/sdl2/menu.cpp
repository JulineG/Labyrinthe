#include <iostream>
#include <cassert>
#include <string>
#include <fstream>
#include <stdlib.h>
#include "menu.h"


Menu::Menu (){
	// Initialisation de la console
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << endl;SDL_Quit();exit(1);
    }

    if (TTF_Init() != 0) {
        cout << "Erreur lors de l'initialisation de la SDL_ttf : " << TTF_GetError() << endl;SDL_Quit();exit(1);
    }

    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
    if( !(IMG_Init(imgFlags) & imgFlags)) {
        cout << "SDL_image ne peut pas être initialiser! SDL_image Erreur: " << IMG_GetError() << endl;SDL_Quit();exit(1);
    }

    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        cout << "SDL_mixer ne peut pas être initialiser! SDL_mixer Erreur: " << Mix_GetError() << endl;
        cout << "Pas de son !!!" << endl;
        avecSon = false;
    }
    else avecSon = true;

    // Creation de la fenetre
    fenetre = SDL_CreateWindow("Labyrinthe", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 512, 512, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (fenetre == NULL) {
        cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << endl; SDL_Quit(); exit(1);
    }

    renderer = SDL_CreateRenderer(fenetre,-1,SDL_RENDERER_ACCELERATED);
	
	im_menu.chargerImageDepuisFichier("data/menu.png",renderer);
	
	police = TTF_OpenFont("data/ObelixPro.ttf",50);
  	if (police == NULL) {
		cout << "Failed to load police.ttf! SDL_TTF Error: " << TTF_GetError() << endl; SDL_Quit(); exit(1);
	}

    // SONS
    if (avecSon)
    {
        music_menu = Mix_LoadWAV("data/son_menu.wav");
        if (music_menu == NULL) {
                cout << "Failed to load son.wav! SDL_mixer Error: " << Mix_GetError() << endl; SDL_Quit(); exit(1);
        }
    }
}

Menu::~Menu(){
	if (avecSon) Mix_Quit();
    	TTF_CloseFont(police);
    	TTF_Quit();
    	SDL_DestroyRenderer(renderer);
    	SDL_DestroyWindow(fenetre);
    	SDL_Quit();
}

void Menu::sdlAffichage(){
	//Remplir l'ecran de blanc
    	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    	SDL_RenderClear(renderer);
	im_menu.dessiner(renderer,0,0,512,512);
}

void Menu::sdlAff_jouer(){
	sprintf(format, "Tentez votre chance..");
	police_couleur.r = 210; police_couleur.g = 30; police_couleur.b = 30;
	police_im.setSurface(TTF_RenderText_Solid(police,format,police_couleur));
	police_im.creerTextureAPartirDeSurface(renderer);
	SDL_Rect positionTitre;
	positionTitre.x = 40;positionTitre.y = 380 ;positionTitre.w = 420;positionTitre.h = 100;
	SDL_RenderCopy(renderer,police_im.getTexture(),NULL,&positionTitre);
	SDL_Delay(100);
}


void Menu::sdlAff_quitter(){
	sprintf(format, "Vous nous quittez... ?");
	police_couleur.r = 210; police_couleur.g = 30; police_couleur.b = 30;
	police_im.setSurface(TTF_RenderText_Solid(police,format,police_couleur));
	police_im.creerTextureAPartirDeSurface(renderer);
	SDL_Rect positionTitre;
	positionTitre.x = 40;positionTitre.y = 380 ;positionTitre.w = 420;positionTitre.h = 100;
	SDL_RenderCopy(renderer,police_im.getTexture(),NULL,&positionTitre);
	SDL_Delay(100);
}

void Menu::sdlAff_a_suivre(){
	sprintf(format, "Prochainement...");
	police_couleur.r = 210; police_couleur.g = 30; police_couleur.b = 30;
	police_im.setSurface(TTF_RenderText_Solid(police,format,police_couleur));
	police_im.creerTextureAPartirDeSurface(renderer);
	SDL_Rect positionTitre;
	positionTitre.x = 40;positionTitre.y = 380 ;positionTitre.w = 420;positionTitre.h = 100;
	SDL_RenderCopy(renderer,police_im.getTexture(),NULL,&positionTitre);
	SDL_Delay(100);
}

void Menu::sdlAff_aide(){
	sprintf(format, "Besoin d'aide ?");
	police_couleur.r = 210; police_couleur.g = 30; police_couleur.b = 30;
	police_im.setSurface(TTF_RenderText_Solid(police,format,police_couleur));
	police_im.creerTextureAPartirDeSurface(renderer);
	SDL_Rect positionTitre;
	positionTitre.x = 40;positionTitre.y = 380 ;positionTitre.w = 420;positionTitre.h = 100;
	SDL_RenderCopy(renderer,police_im.getTexture(),NULL,&positionTitre);
	SDL_Delay(100);
}

void Menu::MenuBoucle(){
	SDL_Event events;
	bool quit = false;
	
	// tant que ce n'est pas la fin ...
	while (!quit) {
		// tant qu'il y a des evenements  traiter (cette boucle n'est pas bloquante)
		while (SDL_PollEvent(&events)) {
			switch (events.type)
			{	
				case SDL_QUIT:           // Si l'utilisateur a clique sur la croix de fermeture
					quit = true;
					break;
				
				case SDL_MOUSEMOTION: //position souris

						
					if (events.motion.x > 30 && events.motion.x < 157 && events.motion.y > 32 && events.motion.y < 62 ) //test si on clique sur le bouton jouer
					{
						sdlAff_jouer();
						SDL_RenderPresent(renderer);
					}
					else if (events.button.x > 35 && events.button.x < 157  && events.button.y > 98 && events.button.y <122 ) //bouton pour à suivre
					{
						sdlAff_a_suivre();
						SDL_RenderPresent(renderer);
					}
					else if (events.button.x > 35 && events.button.x <157 && events.button.y > 163 && events.button.y <187 ) //bouton pour aide/règle
					{
						sdlAff_aide();
						SDL_RenderPresent(renderer);
					}
					else if (events.button.x > 35 && events.button.x < 157 && events.button.y > 224 && events.button.y < 260 ) //bouton quitter
					{
						sdlAff_quitter();
						SDL_RenderPresent(renderer);
					}break;
					
				case SDL_MOUSEBUTTONUP: //clique souris
					if (events.button.button == SDL_BUTTON_LEFT)
					{
						if (events.button.x > 35 && events.button.x < 157 && events.button.y > 32 && events.button.y < 62 ) //test si on clique sur le bouton jouer
						{	
							SDL_Delay(2000);
							quit= true;
							SDL_Quit();
							sdlJeu sj;
							sj.sdlBoucle();
						}
						else if (events.button.x > 35 && events.button.x < 157  && events.button.y > 98 && events.button.y <122 ) //bouton pour suite ?
						{
							im_menu.chargerImageDepuisFichier("data/menu_teaser.png",renderer);
						}
						else if (events.button.x > 35 && events.button.x <157 && events.button.y > 163 && events.button.y <187 ) //bouton pour aide/règle
						{
							im_menu.chargerImageDepuisFichier("data/menu_aide.png",renderer);
						}
						else if (events.button.x > 35 && events.button.x < 157 && events.button.y > 224 && events.button.y < 260 ) //bouton quitter
						{
							quit=true;
							
						}
					}
					break;
			}
			Mix_PlayChannel(-1,music_menu,-1);
		}
		sdlAffichage();
		SDL_RenderPresent(renderer);
	}
}		
