#include <unistd.h>
#include <stdio.h>
#include <ctime>
#include "winTxt.h"
#include "../core/Jeu.h"

#include <iostream>
using namespace std;

void txtAff(winTxt & win, const Jeu & jeu) {
	const Terrain& ter = jeu.getConstTerrain();
	const Personnage& per = jeu.getConstPersonnage();
	const Monstre& mon1 = jeu.getConstMonstre1();
	const Monstre& mon2 = jeu.getConstMonstre2();
	const Monstre& mon3 = jeu.getConstMonstre3();
	win.effacer();

    // Affichage des murs et des objets

    	for(int x=-jeu.getJumelle(); x<=jeu.getJumelle();x++){
		        for(int y=-jeu.getJumelle(); y<=jeu.getJumelle();y++){
		        	win.ajouteCaractere(per.getX()+x, per.getY()+y, ter.getXY(per.getX()+x,per.getY()+y));
				if(!jeu.getTuer() && (mon1.getX()<=per.getX()+x)&&(mon1.getY()<=per.getY()+y)&&(mon1.getY()>=per.getY()-y)&&(mon1.getX()>=per.getX()-x)){
				win.ajouteCaractere(mon1.getX(),mon1.getY(),'M');		
			}
			if((mon2.getX()<=per.getX()+x)&&(mon2.getY()<=per.getY()+y)&&(mon2.getY()>=per.getY()-y)&&(mon2.getX()>=per.getX()-x)){
				win.ajouteCaractere(mon2.getX(),mon2.getY(),'M');	
			}
			if((mon3.getX()<=per.getX()+x)&&(mon3.getY()<=per.getY()+y)&&(mon3.getY()>=per.getY()-y)&&(mon3.getX()>=per.getX()-x)){
				win.ajouteCaractere(mon3.getX(),mon3.getY(),'M');
			}
	}}

    	
    	

    // Affichage du personnage
	win.ajouteCaractere(per.getX(),per.getY(),'I');	
	win.dessine();

}

void txtBoucle (Jeu & jeu){
	// Creation d'une nouvelle fenetre en mode texte
	// => fenetre de dimension et position (WIDTH,HEIGHT,STARTX,STARTY)
    winTxt win (jeu.getConstTerrain().getDimx(),jeu.getConstTerrain().getDimy());
    bool ok = true;
    int c;
    clock_t debut = clock();
    do {
    	txtAff(win,jeu);
    	cout<< "Nombre de vies : "<<jeu.getVie()<<endl;
    	cout<< "Epee en possession :" << jeu.getAvoir_epee()<<endl;
    	cout<< "Nombre d'etoiles restantes : " << jeu.getEtoile()<<endl;
    	usleep(100000);
    	jeu.actionsAutomatiques();
	jeu.gererPosition();
    	c = win.getCh();
    	switch(c){
    		case 'q' :
    			jeu.actionClavier('q');
    			jeu.gererPosition();
    			break;
    		case 'z' :
    			jeu.actionClavier('z');
    			jeu.gererPosition();
    			break;
    		case 's' :
    			jeu.actionClavier('s');
    			jeu.gererPosition();
    			break;

   		case 'd' :

    			jeu.actionClavier('d');
    			jeu.gererPosition();
    			break;
    		case 'o' :
    			ok = false;
				
    			break;
    	}
			if (jeu.getAvoir_perdu()) {
    			clock_t fin = clock();    		
    			cout<< "Vous avez perdu en " << (fin-debut)/3600 << " secondes"<<endl;	
				jeu.setAvoir_perdu(false);
			
			}
    		if (jeu.getJeu_termine()){
    			clock_t fin = clock();    		
    			cout<< "Vous avez gagné en " << (fin-debut)/3600 << " secondes"<<endl;
				jeu.setJeu_termine(false);	
			}  		
    

    	
    }while(ok);
	
}
    			
    		
    	
