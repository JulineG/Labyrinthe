CORE = src/core/Jeu.cpp src/core/Monstre.cpp src/core/Personnage.cpp src/core/Terrain.cpp 
EXEC_NAME = bin/txt
EXEC_NAME_SDL = bin/sdl
OBJ_FILES = obj/Jeu.o obj/Terrain.o obj/Monstre.o obj/Personnage.o obj/mainTxt.o obj/winTxt.o obj/JeuModeTexte.o
OBJ_FILES_SDL = obj/Jeu.o obj/Terrain.o obj/Monstre.o obj/Personnage.o obj/main_sdl.o obj/SDLJeu.o obj/menu.o
CORE_H = src/core/Jeu.h src/core/Terrain.h src/core/Monstre.h src/core/Personnage.h
TXT_H = src/txt/JeuModeTexte.h src/txt/winTxt.h
SDL_H = src/sdl2/SDLJeu.h src/sdl2/menu.h
INCLUDE_DIR_SDL = -I/usr/include/SDL2
LIBS_SDL = -lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_mixer

CC = g++ -g -ggdb
CFFLAGS = g++ -g -Wall -c
CFFLAGS_SDL = g++ -g -Wall $(INCLUDE_DIR_SDL) -c

all: $(EXEC_NAME) $(EXEC_NAME_SDL) doc

$(EXEC_NAME) : $(OBJ_FILES) $(CORE_H) $(TXT_H)
	$(CC) $(OBJ_FILES) -o $(EXEC_NAME)

$(EXEC_NAME_SDL) : $(OBJ_FILES_SDL) $(CORE_H) $(SDL_H)
	$(CC) $(OBJ_FILES_SDL) $(LIBS_SDL) -o $(EXEC_NAME_SDL)

obj/mainTxt.o : src/txt/mainTxt.cpp $(TXT_H)
	$(CFFLAGS) src/txt/mainTxt.cpp -o obj/mainTxt.o

obj/main_sdl.o : src/sdl2/main_sdl.cpp $(SDL_H)
	$(CFFLAGS_SDL) src/sdl2/main_sdl.cpp -o obj/main_sdl.o

obj/menu.o : src/sdl2/menu.cpp $(SDL_H)
	$(CFFLAGS_SDL) src/sdl2/menu.cpp -o obj/menu.o

obj/SDLJeu.o : src/sdl2/SDLJeu.cpp $(SDL_H) src/core/Jeu.h
	$(CFFLAGS_SDL) src/sdl2/SDLJeu.cpp -o obj/SDLJeu.o
	
obj/JeuModeTexte.o : src/txt/JeuModeTexte.cpp $(TXT_H) src/core/Jeu.h 
	$(CFFLAGS) src/txt/JeuModeTexte.cpp -o obj/JeuModeTexte.o
	
obj/Jeu.o : src/core/Jeu.cpp $(CORE_H)
	$(CFFLAGS) src/core/Jeu.cpp -o obj/Jeu.o

obj/Personnage.o : src/core/Personnage.cpp src/core/Personnage.h src/core/Terrain.h
	$(CFFLAGS) src/core/Personnage.cpp -o obj/Personnage.o

obj/Monstre.o : src/core/Monstre.cpp src/core/Monstre.h src/core/Terrain.h
	$(CFFLAGS) src/core/Monstre.cpp -o obj/Monstre.o

obj/Terrain.o : src/core/Terrain.cpp src/core/Terrain.h
	$(CFFLAGS) src/core/Terrain.cpp -o obj/Terrain.o

obj/winTxt.o : src/txt/winTxt.cpp src/txt/winTxt.h
	$(CFFLAGS) src/txt/winTxt.cpp -o obj/winTxt.o

doc:doc/doxyfile

clean : 
	rm obj/*.o
	rm bin/*

veryclean : clean 
	rm obj/* 
	rm bin/*
