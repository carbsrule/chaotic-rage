#include <iostream>
#include <SDL.h>
#include "rage.h"


using namespace std;



int main (int argc, char ** argv) {
	SDL_Surface *screen = SDL_SetVideoMode(800, 600, 32, SDL_SWSURFACE);
	
	if (screen == NULL) {
		fprintf(stderr, "Unable to set %ix%i video: %s\n", 800, 600, SDL_GetError());
		exit(1);
	}
	
	Player *p = new Player();
	
	GameState *st = new GameState();
	st->addUnit(p);
	
	st->curr_player = p;
	
	gameLoop(st, screen);
	
	exit(0);
}




