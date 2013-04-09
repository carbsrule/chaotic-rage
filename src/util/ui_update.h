// This file is part of Chaotic Rage (c) 2010 Josh Heidenreich
//
// kate: tab-width 4; indent-width 4; space-indent off; word-wrap off;

#pragma once
#include <iostream>
#include <SDL.h>
#include <list>
#include "../rage.h"

using namespace std;


/**
* Interface for a class which should be updated reguarlly about something which is happening, for loading bars etc.
**/
class UIUpdate
{
	public:
		/**
		* The UI should update.
		**/
		virtual void update() = 0;
};

