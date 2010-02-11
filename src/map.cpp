#include <iostream>
#include <SDL.h>
#include <math.h>
#include "rage.h"

using namespace std;

/**
* Load a file (simulated)
**/
int Map::load(string name)
{
	Area *a;
	
	this->width = 1000;
	this->height = 1000;
	
	// Default area
	a = new Area();
	a->x = 0;
	a->y = 0;
	a->width = this->width;
	a->height = this->width;
	a->type = getAreaTypeByID(0);
	this->areas.push_back(a);
	
	a = new Area();
	a->x = 10;
	a->y = 10;
	a->width = 50;
	a->height = 100;
	a->type = getAreaTypeByID(2);
	this->areas.push_back(a);
	
	a = new Area();
	a->x = 50;
	a->y = 170;
	a->width = 100;
	a->height = 100;
	a->type = getAreaTypeByID(2);
	this->areas.push_back(a);
	
	return 1;
}


/**
* Render a single frame of the wall animation
**/
SDL_Surface* Map::renderWallFrame(int frame)
{
	SDL_Surface* surf = SDL_CreateRGBSurface(SDL_SWSURFACE, this->width, this->height, 32, 0,0,0,0);
	
	Area *a;
	unsigned int i;
	SDL_Rect src;
	SDL_Rect dest;
	int free_surf = 0;
	
	for (i = 0; i < this->areas.size(); i++) {
		a = this->areas[i];
		
		SDL_Surface *areasurf = a->type->surf;
		
		free_surf = 0;
		if (a->type->stretch)  {
			areasurf = zoomSurface(areasurf, ((double)a->width) / ((double)areasurf->w), ((double)a->height) / ((double)areasurf->h), 0);
			if (areasurf == NULL) continue;
			free_surf = 1;
		}
		
		src.x = 0;
		src.y = 0;
		src.w = a->width;
		src.h = a->height;
		
		dest.x = a->x;
		dest.y = a->y;
		
		SDL_BlitSurface(areasurf, &src, surf, &dest);
		
		if (free_surf) {
			SDL_FreeSurface(areasurf);
		}
	}
	
	return surf;
}

