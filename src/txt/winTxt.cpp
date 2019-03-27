#include "winTxt.h"
#include <cassert>
#include <stdlib.h>
#include <stdarg.h>
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <unistd.h>


void termClear() //efface le terminal
{
	system("clear");
}
void termInit()      // configure la saisie : ne pas afficher les caracteres tapes
{
    struct termios ttystate;
    bool state = true;
    //get the terminal state
    tcgetattr(STDIN_FILENO, &ttystate);
    if (state) {
        //turn off canonical mode
        ttystate.c_lflag &= ~ICANON;
        //minimum of number input read.
        ttystate.c_cc[VMIN] = 1;
    }
    else {
        //turn on canonical mode
        ttystate.c_lflag |= ICANON;
    }
    //set the terminal attributes.
    tcsetattr(STDIN_FILENO, TCSANOW, &ttystate);
    struct termios t;
    tcgetattr(STDIN_FILENO, &t);
    t.c_lflag |= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &t);
}
winTxt::winTxt(int dx, int dy){
	dimx=dx;
	dimy=dy;
	fenetre=new char [dimx*dimy];
	effacer();
	termInit();
}

void winTxt::effacer(char c){
	for(int i=0;i<dimx;++i){
		for(int j=0;j<dimy;++j){
			ajouteCaractere(i,j,c);
		}
	}
}

void winTxt::ajouteCaractere(int x, int y, char c){
	if (x<0) return;
  if (y<0) return;
  if (x>=dimx) return;
  if (y>=dimy) return;
  fenetre[y*dimx+x] = c;
}
int kbhit() {
    struct timeval tv;
    fd_set fds;
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds); //STDIN_FILENO is 0
    select(STDIN_FILENO+1, &fds, NULL, NULL, &tv);
    return FD_ISSET(STDIN_FILENO, &fds);
}
void winTxt::pause(){
	printf("Appuyer sur une touche\n");
	while(!kbhit());
}

char winTxt::getCh(){ //lire un caractère si une touche a été pressée
	char touche=0;
	if (kbhit()){
		touche=fgetc(stdin);
	}
	return touche;
}
void termMove(int x, int y) // deplace le curseur du terminal
{
    char t[16];
    sprintf(t, "\033[%d;%dH", y, x);
    printf("%s",t);

}
void winTxt::dessine (int x, int y) {
    termMove(0,0);
    for(int j=0;j<dimy;++j) {
        for(int i=0;i<dimx;++i)
            printf("%c",fenetre[j*dimx+i]);
        printf("\n");
    }
    termMove(0,dimy);
}
	
