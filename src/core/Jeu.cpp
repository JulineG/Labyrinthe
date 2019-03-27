#include "Jeu.h"
#include "Terrain.h"
#include "Monstre.h"
#include "Personnage.h"
#include <cassert>
#include <iostream>
#include <stdio.h>


using namespace std;

Jeu::Jeu () : mon1(12,17,0), mon2(13,5,0) , mon3(7,16,0) {
	vie = 3;
	nb_etoile = 0;
	nb_jumelle = 2;
	avoir_epee = false;
	avoir_perdu = false;
	jeu_termine = false;
	avoir_gagne=false;
	tuer = false;
}

const Terrain& Jeu::getConstTerrain () const {
	return ter;
}

const Monstre& Jeu::getConstMonstre1 () const {
	return mon1;
}

const Monstre& Jeu::getConstMonstre2 () const {
	return mon2;
}

const Monstre& Jeu::getConstMonstre3 () const {
	return mon3;
}


const Personnage& Jeu::getConstPersonnage () const {
	return per;
}

int Jeu:: getJumelle () const{
	return nb_jumelle;
}
int Jeu:: getVie () const{
	return vie;
}

bool Jeu:: getAvoir_perdu () const{
	return avoir_perdu;
}

void Jeu:: setAvoir_perdu(const bool c){
	avoir_perdu=c;
}

bool Jeu:: getJeu_termine () const{
	return jeu_termine;
}

void Jeu:: setJeu_termine(const bool c){
	jeu_termine=c;
}

bool Jeu:: getAvoir_epee () const{
	return avoir_epee;
}

int Jeu:: getEtoile () const{
	return 3-nb_etoile;
}

bool Jeu:: getTuer () const{
	return tuer;
}


void Jeu::actionsAutomatiques (){	
	mon1.bougeAutoHorizontal(ter);
	mon2.bougeAutoHorizontal(ter);
	mon3.bougeAutoVertical(ter);
}

void Jeu::actionClavier (const char touche) {
	switch (touche) {
		case 'q' : 
			per.gauche(ter);
			break;
		case 'd' :
			per.droite(ter);
			break;
		case 'z' : 
			per.haut(ter);
			break;
		case 's' :
			per.bas(ter);
			break;
	}
	
}



void Jeu::gererPosition (){
	if (ter.recupererEtoile(per.getX(), per.getY())){
		nb_etoile= nb_etoile + 1;
		if (nb_etoile == 3){
			ter.setXY(4,5,'P');
		}
	}
	if (ter.getXY(per.getX(),per.getY()) =='P'){
		jeu_termine = true;
	}
	
	if (ter.recupererEpee(per.getX(), per.getY())){
		avoir_epee = true;
	}
	
	if (avoir_epee && (per.getX()==mon1.getX()) && (per.getY()==mon1.getY())){
		tuer = true;
		mon1.~Monstre();
		avoir_epee = false;
	}
	if ( !avoir_epee && (per.getX()==mon1.getX()) && (per.getY()==mon1.getY())){
		gererNbVie(); 
	}
	if (avoir_epee && (per.getX()==mon2.getX()) && (per.getY()==mon2.getY())){
		tuer = true;
		mon2.~Monstre();
		avoir_epee = false;
	}
	if ( !avoir_epee && (per.getX()==mon2.getX()) && (per.getY()==mon2.getY())){
		gererNbVie();
	}
	if (avoir_epee && (per.getX()==mon3.getX()) && (per.getY()==mon3.getY())){
		tuer = true;
		mon3.~Monstre();
		avoir_epee = false;
	}
	if ( !avoir_epee && (per.getX()==mon3.getX()) && (per.getY()==mon3.getY())){
		gererNbVie();
	}
	if ( ter.getXY(per.getX(),per.getY())=='L') {
		nb_jumelle = nb_jumelle + 1;
		ter.setXY(per.getX(),per.getY(),' ');
	}
	if(ter.getXY(per.getX(),per.getY())=='P') {
		avoir_gagne = true;
	}
}

void Jeu :: gererNbVie (){	
	if (vie != 0) {
		vie--;		
	}
	if (vie==0) {
		avoir_perdu = true;
	}
}




		

	
	 


	
	
