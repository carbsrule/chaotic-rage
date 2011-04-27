// This file is part of Chaotic Rage (c) 2010 Josh Heidenreich
//
// kate: tab-width 4; indent-width 4; space-indent off; word-wrap off;

#pragma once
#include <iostream>
#include <SDL.h>
#include "rage.h"

using namespace std;


class Mod {
	private:
		vector<AnimModel*> * animmodels;
		vector<AreaType*> * areatypes;
		vector<ParticleType*> * particletypes;
		vector<ParticleGenType*> * pgeneratortypes;
		vector<UnitType*> * unitclasses;
		vector<Song*> * songs;
		vector<Sound*> * sounds;
		vector<WallType*> * walltypes;
		vector<WeaponType*> * weapontypes;
		
	public:
		GameState * st;
		string name;
		string directory;
		
	public:
		char * loadText(string filename);
		SDL_RWops * loadRWops(string filename);
		
	public:
		Mod(GameState * st, string directory);
		
	public:
		bool load();
		
		AnimModel * getAnimModel(int id);
		AreaType * getAreaType(int id);
		UnitType * getUnitType(int id);
		ParticleType * getParticleType(int id);
		ParticleGenType * getParticleGenType(int id);
		Song * getSong(int id);
		Sound * getSound(int id);
		WallType * getWallType(int id);
		WeaponType * getWeaponType(int id);
		
		AnimModel * getAnimModel(string name);
		Sound * getSound(string name);
		WallType * getWallType(string name);
};
