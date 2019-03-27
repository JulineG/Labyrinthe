#include <iostream>
#include <cassert>
#include <string>
#include <fstream>
#include <stdlib.h>

#include "SDLJeu.h"


using namespace std;

const int TAILLE_SPRITE = 32;

Image::Image () {
    surface = NULL;
    texture = NULL;
    a_change = false;
}

void Image::chargerImageDepuisFichier(const char* filename, SDL_Renderer * renderer) {
    surface = IMG_Load(filename);
    if (surface == NULL) {
        string nfn = string("../") + filename;
        cout << "Error: cannot load "<< filename <<". Trying "<<nfn<<endl;
        surface = IMG_Load(nfn.c_str());
        if (surface == NULL) {
            nfn = string("../") + nfn;
            surface = IMG_Load(nfn.c_str());
        }
    }
    if (surface == NULL) {
        cout<<"Error: cannot load "<< filename <<endl;
        exit(1);
    }

    SDL_Surface * surfaceCorrectPixelFormat = SDL_ConvertSurfaceFormat(surface,SDL_PIXELFORMAT_ARGB8888,0);
    SDL_FreeSurface(surface);
    surface = surfaceCorrectPixelFormat;

    texture = SDL_CreateTextureFromSurface(renderer,surface);
    if (texture == NULL) {
        cout << "Error: problem to create the texture of "<< filename<< endl;
        exit(1);
    }
}

void Image::creerTextureAPartirDeSurface (SDL_Renderer * renderer) {
    texture = SDL_CreateTextureFromSurface(renderer,surface);
    if (texture == NULL) {
        cout << "Error: problem to create the texture from surface " << endl;
        exit(1);
    }
}

void Image::dessiner (SDL_Renderer * renderer, int x, int y, int w, int h) {
    int ok;
    SDL_Rect r;
    r.x = x;
    r.y = y;
    r.w = (w<0)?surface->w:w;
    r.h = (h<0)?surface->h:h;
	
    if (a_change) {
        ok = SDL_UpdateTexture(texture,NULL,surface->pixels,surface->pitch);
        assert(ok == 0);
        a_change = false;
    }


    ok = SDL_RenderCopy(renderer,texture,NULL,&r);  
    assert(ok == 0);

	if (texture != NULL){
		ok = SDL_RenderCopy(renderer,texture,NULL,&r);
		assert (ok==0);
	}

}

SDL_Texture * Image::getTexture() const {return texture;}

void Image::setSurface(SDL_Surface * surf) {surface = surf;}


sdlJeu::sdlJeu () : jeu() {
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

    if( Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 1, 2048 ) < 0 )
    {
        cout << "SDL_mixer ne peut pas être initialiser! SDL_mixer Erreur: " << Mix_GetError() << endl;
        cout << "Pas de son !!!" << endl;
        withSound = false;
    }
    else withSound = true;

	int dimx, dimy;
	dimx = jeu.getConstTerrain().getDimx();
	dimy = jeu.getConstTerrain().getDimy();
	dimx = dimx * TAILLE_SPRITE;
	dimy = (dimy+3) * TAILLE_SPRITE;

    // Creation de la fenetre
    window = SDL_CreateWindow("Labyrinthe", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, dimx, dimy, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (window == NULL) {
        cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << endl; SDL_Quit(); exit(1);
    }

    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);

    // IMAGES

	
	im_arbre.chargerImageDepuisFichier("./data/arbre.png",renderer);
	im_personnage_gauche_droite.chargerImageDepuisFichier("./data/personnage_gauche_droite.png",renderer);
	im_personnage_droite_gauche.chargerImageDepuisFichier("./data/personnage_droite_gauche.png",renderer);
	im_personnage_epee_gauche_droite.chargerImageDepuisFichier("./data/personnage_epee_gauche_droite.png",renderer);
	im_personnage_epee_droite_gauche.chargerImageDepuisFichier("./data/personnage_epee_droite_gauche.png",renderer);
	im_monstre.chargerImageDepuisFichier("./data/monstre.png",renderer);
	im_etoile.chargerImageDepuisFichier("./data/etoile.png",renderer);
	im_loupe.chargerImageDepuisFichier("./data/loupe.png",renderer);
	im_porte.chargerImageDepuisFichier("./data/porte.png",renderer);
	im_epee.chargerImageDepuisFichier("./data/epee.png",renderer);
	im_coeur.chargerImageDepuisFichier("./data/coeur.png",renderer);
	im_chemin.chargerImageDepuisFichier("./data/chemin.png",renderer);
	

    // FONTS
   font = TTF_OpenFont("data/ObelixPro.ttf",70);
  	  if (font == NULL) {
         	   cout << "Failed to load ObelixPro.ttf! SDL_TTF Error: " << TTF_GetError() << endl; SDL_Quit(); exit(1);
		}

    // SONS
    if (withSound)
    {
        music = Mix_LoadWAV("data/jeu_son.wav");
        if (music == NULL) {
                cout << "Failed to load jeu_son.wav! SDL_mixer Error: " << Mix_GetError() << endl; SDL_Quit(); exit(1);
        }
    }
	//TEMPS
	setTemps(0);

}

sdlJeu::~sdlJeu () {
    if (withSound) Mix_Quit();
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int sdlJeu::getTemps()const{
	return temps;
}

void sdlJeu::setTemps(const int t){
	temps=t;
}

void sdlJeu::sdlAff (const char action_clavier) {
	//Remplir l'cran de blanc
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

	int x,y;
	const Terrain& ter = jeu.getConstTerrain();
	const Personnage& per = jeu.getConstPersonnage();
	const Monstre& mon1=jeu.getConstMonstre1();
	const Monstre& mon2=jeu.getConstMonstre2();
	const Monstre& mon3=jeu.getConstMonstre3();
	
    // Afficher les sprites 
  
  for (int i=0;i<jeu.getVie();i++) {
  	im_coeur.dessiner(renderer,i*TAILLE_SPRITE,27*TAILLE_SPRITE,TAILLE_SPRITE,TAILLE_SPRITE);
  }
  for (int j=18;j>18-jeu.getEtoile();j--){
  	im_etoile.dessiner(renderer,j*TAILLE_SPRITE,27*TAILLE_SPRITE,TAILLE_SPRITE,TAILLE_SPRITE);
	}
	if(jeu.getEtoile()==0){
		im_porte.dessiner(renderer,18*TAILLE_SPRITE,27*TAILLE_SPRITE,TAILLE_SPRITE,TAILLE_SPRITE);
	}
	if (jeu.getAvoir_epee()){
		im_epee.dessiner(renderer,9*TAILLE_SPRITE,27*TAILLE_SPRITE,TAILLE_SPRITE,TAILLE_SPRITE);
	}			
	for (x=-jeu.getJumelle();x<=jeu.getJumelle();x++){
		for (y=-jeu.getJumelle();y<=jeu.getJumelle();y++){
			im_chemin.dessiner(renderer,(per.getX()+x)*TAILLE_SPRITE,(per.getY()+y)*TAILLE_SPRITE,TAILLE_SPRITE,TAILLE_SPRITE);	
			if(!jeu.getTuer() && (mon1.getX()<=per.getX()+x)&&(mon1.getY()<=per.getY()+y)&&(mon1.getY()>=per.getY()-y)&&(mon1.getX()>=per.getX()-x)){
				im_monstre.dessiner(renderer,mon1.getX()*TAILLE_SPRITE,mon1.getY()*TAILLE_SPRITE,TAILLE_SPRITE,TAILLE_SPRITE);	
			}
			if((mon2.getX()<=per.getX()+x)&&(mon2.getY()<=per.getY()+y)&&(mon2.getY()>=per.getY()-y)&&(mon2.getX()>=per.getX()-x)){
				im_monstre.dessiner(renderer,mon2.getX()*TAILLE_SPRITE,mon2.getY()*TAILLE_SPRITE,TAILLE_SPRITE,TAILLE_SPRITE);	
			}
			if((mon3.getX()<=per.getX()+x)&&(mon3.getY()<=per.getY()+y)&&(mon3.getY()>=per.getY()-y)&&(mon3.getX()>=per.getX()-x)){
				im_monstre.dessiner(renderer,mon3.getX()*TAILLE_SPRITE,mon3.getY()*TAILLE_SPRITE,TAILLE_SPRITE,TAILLE_SPRITE);	
			}	
			switch(ter.getXY(per.getX()+x,per.getY()+y)){				
				case 'P' : 
					im_porte.dessiner(renderer,(per.getX()+x)*TAILLE_SPRITE,(per.getY()+y)*TAILLE_SPRITE,TAILLE_SPRITE,TAILLE_SPRITE);
					break;
				case '#' :
					// Afficher le sprite arbre
					im_arbre.dessiner(renderer,(per.getX()+x)*TAILLE_SPRITE,(per.getY()+y)*TAILLE_SPRITE,TAILLE_SPRITE,TAILLE_SPRITE);
					break;										
				case 'E' :
					// Afficher le sprite de l'etoile
					im_etoile.dessiner(renderer,(per.getX()+x)*TAILLE_SPRITE,(per.getY()+y)*TAILLE_SPRITE,TAILLE_SPRITE,TAILLE_SPRITE);
					break;					
				case 'e' : 
					// Afficher le sprite du epee
					im_epee.dessiner(renderer,(per.getX()+x)*TAILLE_SPRITE,(per.getY()+y)*TAILLE_SPRITE,TAILLE_SPRITE,TAILLE_SPRITE);					
					break;					
				case 'L' : 
					// Afficher le sprite des loupes
					im_loupe.dessiner(renderer,(per.getX()+x)*TAILLE_SPRITE,(per.getY()+y)*TAILLE_SPRITE,TAILLE_SPRITE,TAILLE_SPRITE);					
					break;
			}	
		 
		} 					 
	}
	char format [50];
	int t = getTemps();
	
 
	if (jeu.getAvoir_perdu()) {
			sprintf(format, "Vous avez perdu en %d secondes", t);
			font_color.r = 195;font_color.g = 0;font_color.b = 0;
			font_im.setSurface(TTF_RenderText_Solid(font,format,font_color));
			font_im.creerTextureAPartirDeSurface(renderer);
			SDL_Rect positionTitre;
			positionTitre.x = 4*TAILLE_SPRITE;positionTitre.y = 13*TAILLE_SPRITE;positionTitre.w = 12*TAILLE_SPRITE;positionTitre.h = 2*TAILLE_SPRITE;
			SDL_RenderCopy(renderer,font_im.getTexture(),NULL,&positionTitre);

	}		
	if (jeu.getJeu_termine()){
			sprintf(format, "Vous avez gagne en %d secondes", t);
			font_color.r = 195;font_color.g = 0;font_color.b = 0;
			font_im.setSurface(TTF_RenderText_Solid(font,format,font_color));
			font_im.creerTextureAPartirDeSurface(renderer);
			SDL_Rect positionTitre;
			positionTitre.x = 4*TAILLE_SPRITE;positionTitre.y = 13*TAILLE_SPRITE;positionTitre.w = 12*TAILLE_SPRITE;positionTitre.h = 2*TAILLE_SPRITE;
			SDL_RenderCopy(renderer,font_im.getTexture(),NULL,&positionTitre);

	}	
	if (jeu.getAvoir_epee())
	{	
		switch (action_clavier){
			case 'd' :
				im_personnage_epee_gauche_droite.dessiner(renderer,per.getX()*TAILLE_SPRITE,per.getY()*TAILLE_SPRITE,TAILLE_SPRITE,TAILLE_SPRITE);
				break;
			case 'q' :
				im_personnage_epee_droite_gauche.dessiner(renderer,per.getX()*TAILLE_SPRITE,per.getY()*TAILLE_SPRITE,TAILLE_SPRITE,TAILLE_SPRITE);
				break;
		}
	}
	else
	{
		switch (action_clavier){
			case 'd' :
				im_personnage_gauche_droite.dessiner(renderer,per.getX()*TAILLE_SPRITE,per.getY()*TAILLE_SPRITE,TAILLE_SPRITE,TAILLE_SPRITE);
				break;
			case 'q' :
				im_personnage_droite_gauche.dessiner(renderer,per.getX()*TAILLE_SPRITE,per.getY()*TAILLE_SPRITE,TAILLE_SPRITE,TAILLE_SPRITE);
				break;
			case NULL :
				im_personnage_droite_gauche.dessiner(renderer,per.getX()*TAILLE_SPRITE,per.getY()*TAILLE_SPRITE,TAILLE_SPRITE,TAILLE_SPRITE);
				break;
		}
	}
}

void sdlJeu::sdlBoucle() {
	
    SDL_Event events;
	bool quit = false;
	bool termine = false;
	char action;

    Uint32 t = SDL_GetTicks(), nt;
	
	// tant que ce n'est pas la fin ...
	while (!quit) {
        nt = SDL_GetTicks();
        if (nt-t>300) {
        	jeu.actionsAutomatiques();
			jeu.gererPosition();
			t = nt;
        }
		// tant qu'il y a des evenements  traiter (cette boucle n'est pas bloquante)
		while (SDL_PollEvent(&events)) {
			if (events.type == SDL_QUIT) quit = true;           // Si l'utilisateur a clique sur la croix de fermeture
			else if (events.type == SDL_KEYDOWN) {              // Si une touche est enfoncee
				switch (events.key.keysym.scancode) {
				case SDL_SCANCODE_UP:
					jeu.actionClavier('z');    // car Y inverse
					jeu.gererPosition();		

					break;
				case SDL_SCANCODE_DOWN:
					jeu.actionClavier('s');     // car Y inverse
					jeu.gererPosition();

					break;
				case SDL_SCANCODE_LEFT:
					jeu.actionClavier('q');
					jeu.gererPosition();
					action = 'q';
					
					break;
				case SDL_SCANCODE_RIGHT:
					jeu.actionClavier('d');
					jeu.gererPosition();
					action = 'd';
					break;
				case SDL_SCANCODE_KP_1:
					quit = true;
					break;
				case SDL_SCANCODE_1:
					quit = true;
					break;
									
 				default: break;
				}
			}
			Mix_PlayChannel(-1,music,-1);
		}
		if (((jeu.getAvoir_perdu()) || (jeu.getJeu_termine())) && !termine)
		{
			termine = true;
			nt=SDL_GetTicks();
			setTemps(nt*0.001);
		}

		// on affiche le jeu sur le buffer cach
		sdlAff(action);

		// on permute les deux buffers (cette fonction ne doit se faire qu'une seule fois dans la boucle)
        SDL_RenderPresent(renderer);
	}
}
