/**
@brief Module gérant le jeu (Le labyrinthe) en mode texte dans un module de commande.

@file JeuModeTexte.h
@date 2018/03/13
*/
#ifndef _JeuModeTexte_H
#define _JeuModeTexte_H

#include "../core/Jeu.h"

/**
@brief Boucle permmetttant de faire fonctionner le jeu dans un terminal.
@param j : Variable du jeu qui sera retransmis dans un terminal. 
*/

void txtBoucle(Jeu& j);

#endif
