Projet : Le labyrinthe (LTJGDV98)
bin/txt exécute le jeu en mode texte directement sur le terminal
bin/sdl exécute le jeu en mode graphique sur une nouvelle fenêtre

	Prérequis

Utilisation du jeu "Le labyrinthe" sous Linux
Bibliothèque SDL2 nécessaire : Obtenir la librairie en effectuant la commande suivante :
$> sudo apt-get install libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libsdl2-mixer-dev

	Règles du jeu 
	
Le but du jeu est de parcourir le labyrinthe afin de trouver 3 pièces qui permettront l'apparition d'une porte de sortie dans le labyrinthe. 
Pour cela, le joueur possède 3 vies, il pourra récupérer tout au long du parcours des épées (une seule à la fois) 
lui permettant de tuer les monstres et des loupes pour augmenter sa zone de vue.

	Organisation de l'archive
	
labyrinthe/
	src/
		core/
			Jeu.cpp
			Jeu.h
			Monstre.cpp
			Monstre.h
			Personnage.cpp
			Personnage.h
			Terrain.cpp
			Terrain.h
		sdl2/
			main_sdl.cpp
			menu.cpp
			menu.h
			SDLJeu.cpp
			SDLJeu.h
		txt/
			JeuModeTexte.cpp
			JeuModeTexte.h
			mainTxt.cpp
			winTxt.cpp
			winTxt.h
	data/
		arbre.png
		chemin.png
		coeur.png
		epee.png
		etoile.png
		icone.ico
		jeu_son.wav
		loupe.png
		menu.png
		meunu_aide.png
		monstre.png
		ObelixPro.ttf
		personnage_droite_gauche.png
		personnage_epeee_droite_gauche.png
		personnage_epeee_gauche_droite.png
		personnage_gauche_droite.png
		police.ttf
		porte.png
		son_menu.wav
	doc/
		html/
		21042018_CahierdesCharges.pdf
		22042018_Soutenance_Labyrinthe.pdf
		doxyfile
	obj/
	bin/
	Makefile
	Readme.txt
	Readme.md
	
	Compiler le programme
$> make
$> bin/txt //pour éxécuter le jeu en mode Texte
$> bin/sdl //pour éxécuter le jeu en mode graphique

	Vider les fichiers .o
$> make clean

	Détails pour bin/text:

Touche "Q" pour déplacer le personnage vers la gauche
Touche "S" pour déplacer le personnage vers le bas
Touche "D" pour déplacer le personnage vers la droite
Touche "Z" pour déplacer le personnage vers le haut
Touche "O" pour quitter le jeu
		
	Détails pour bin/sdl :

Utilisation de la souris pour le menu
Touche flèche du haut pour déplacer le personnager vers le haut
Touche flèche du bas pour déplacer le personnager vers le bas
Touche flèche de droite pour déplacer le personnager vers la droite
Touche flèche de gauche pour déplacer le personnager vers la gauche
Touche "1" pour quitter le jeu

	Détails pour doc/ :

Le cahier des charges comporte :
	Le diagramme des classes
	Le diagramme de Gantt
	Les tâches



	Membres du groupe:
	
Tran Laura 11606591 
Gabrovec Juline 11609223
Véricel David 11606297


