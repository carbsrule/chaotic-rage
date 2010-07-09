// This file is part of Chaotic Rage (c) 2010 Josh Heidenreich
//
// kate: tab-width 4; indent-width 4; space-indent off; word-wrap off;

#pragma once
#include <iostream>
#include <SDL.h>
#include <confuse.h>
#include "rage.h"

using namespace std;


#define UNIT_NUM_MODIFIERS 3
#define UNIT_MOD_CLOAK (1 << 0)
#define UNIT_MOD_SHIELD (1 << 1)
#define UNIT_MOD_SPEED (1 << 2)

#define UNIT_STATE_STATIC 1
#define UNIT_STATE_RUNNING 2
#define UNIT_STATE_FIRING 3


class UnitClassSettings;
class UnitClassStates;
class UnitClass;


bool loadAllUnitClasses(Render * render);
UnitClass* loadUnitClass(cfg_t *cfg, Render * render);
UnitClass* getUnitClassByID(int id);


class UnitClassSettings
{
	public:
		int lin_speed;		// max pps unit can move
		int lin_accel;		// pps/second
		int turn_move;		// degrees/second
		int turn_aim;		// degrees/second
};

class UnitClassState
{
	public:
		int id;
		string image;
		int type;
		unsigned int num_frames;
		unsigned int sprite_offset;
};

class UnitClass : public EntityType
{
	friend UnitClass* loadUnitClass(cfg_t *cfg, Render * render);
	
	public:
		string name;
		int id;
		int width, height;
		
	private:
		UnitClassSettings initial;
		UnitClassSettings mod[UNIT_NUM_MODIFIERS];
		vector<UnitClassState*> states;
		unsigned int max_frames;
		Render * render;
		
	public:
		UnitClass();
		~UnitClass();
		
	public:
		UnitClassSettings* getSettings(Uint8 modifier_flags);
		UnitClassState* getState(int type);
		vector<SpritePtr>* loadAllSprites();
		unsigned int getMaxFrames();
};


