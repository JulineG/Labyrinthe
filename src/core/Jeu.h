/**
@brief Module gérant un Jeu (de labyrinthe)

@file Jeu.h
@date 2018/03/13
*/

#ifndef _JEU_H
#define _JEU_H

#include <stdio.h>
#include <time.h>
#include "Personnage.h"
#include "Terrain.h"
#include "Monstre.h"

/**
@brief Un jeu (de labyrinthe) = un terrain, un personnage et des monstres
*/
class Jeu {

private :

	Terrain ter;
	Personnage per;
	Monstre mon1;
	Monstre mon2;
	Monstre mon3;
	int vie;
	int nb_etoile;
	int nb_jumelle;
	bool avoir_epee;
	bool avoir_perdu;
	bool avoir_gagne;
	bool jeu_termine;
	bool tuer;
	
public :

  Jeu ();

		/**
	@brief Accesseur
	@details récupère le terrain original
		*/
  const Terrain& getConstTerrain () const;
    /**
	@brief Accesseur
	@details récupère les coordonnées (x,y) du personnage
		*/
  const Personnage& getConstPersonnage() const;
    /**
	@brief Accesseur
	@details récupère les coordonnées (x,y) du monstre 1
		*/
  const Monstre& getConstMonstre1 () const;
  	/**
	@brief Accesseur
	@details récupère les coordonnées (x,y) du monstre 2
		*/
	const Monstre& getConstMonstre2 () const;
		/**
	@brief Accesseur
	@details récupère les coordonnées (x,y) du monstre 3
		*/
	const Monstre& getConstMonstre3 () const;
    /**
	@brief Accesseur
	@details retourne le nombre de vie
		*/
	int getVie () const;
		/**
	@brief Accesseur
	@details retourne le nombre de jumelles récupéré
		*/
	int getJumelle ()const;
		/**
	@brief Accesseur
	@details retourne le nombre d'étoiles récupéré
		*/
	int getEtoile () const;
		/**
	@brief Booléen
	@details retourne vrai si le joueur a perd, faux sinon
		*/
	bool getAvoir_perdu () const;
		/**
	@brief Mutateur
	@details récupère le booléen vrai ou faux
		*/
	void setAvoir_perdu(const bool c);
		/**
	@brief Accesseur
	@details retourne vrai si le personnage a une épée
		*/
	bool getAvoir_epee () const;
		/**
	@brief Booléen
	@details retourne vrai si le jeu est terminé, faux sinon
		*/
	bool getJeu_termine () const;
		/**
	@brief Mutateur
	@details récupère le booléen vrai ou faux
		*/
	void setJeu_termine(const bool c);
		/**
	@brief Booléen
	@details retourne vrai si le personnage a tué le monstre, faux sinon
		*/
	bool getTuer () const;	
		/**
	@brief Actions automatiques du jeu 
	@details Déplacement des monstres
		*/
  void actionsAutomatiques ();    
   	/**
	@brief Action du jeu par rapport au clavier
	@details récupère les touches pour faire des actions dans le jeu (haut, bas, gauche, droite)
		*/
  void actionClavier(const char touche); 
    /**
	@brief Comparaison de deux coordonnées (x,y)
	@details Compare la position du personnage avec les objets
	@details Récupère une épée si le personnage se trouve sur les mêmes coordonnées
	@details Récupère une étoile si le personnage se trouve sur les mêmes coordonnées
		*/
	void gererPosition();
		/**
	@brief Gère toutes les actions liées aux vies
	@details Perd une vie si on rencontre un monstre et que le personnage n'est pas en possession d'épée
	@details Garde sa vie si on rencontre un monstre et que le personnage est en possesssion d'une épée
		*/
	void gererNbVie();
};

#endif
