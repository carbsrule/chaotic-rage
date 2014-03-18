// This file is part of Chaotic Rage (c) 2010 Josh Heidenreich
//
// kate: tab-width 4; indent-width 4; space-indent off; word-wrap off;

#include <iostream>
#include <math.h>
#include <guichan.hpp>

#include "../rage.h"
#include "../render_opengl/menu.h"
#include "../game_manager.h"
#include "../game_settings.h"
#include "../http/serverlist.h"
#include "../mod/mod_manager.h"
#include "dialog.h"
#include "list_models.h"
#include "newgame_weapons.h"

using namespace std;


/**
* Sub-dialog from the new game dialog for mucking about with weapons
**/
DialogNewGameWeapons::DialogNewGameWeapons(DialogNewGame *parent, GameSettings *gs) : Dialog()
{
	this->parent = parent;
	this->gs = gs;
}

DialogNewGameWeapons::~DialogNewGameWeapons()
{
}


/**
* Sub-dialog from the new game dialog for mucking about with weapons
**/
gcn::Container * DialogNewGameWeapons::setup()
{
	gcn::Button* button;
	
	c = new gcn::Window("Weapon Settings");
	c->setDimension(gcn::Rectangle(0, 0, 360, 300));
	
	button = new gcn::Button("Save Weapon Settings");
	button->setPosition((360 - button->getWidth()) / 2, 250);
	button->addActionListener(this);
	c->add(button);
	
	return c;
}


/**
* Button click to close and go back to new game dialog
**/
void DialogNewGameWeapons::action(const gcn::ActionEvent& actionEvent)
{
	this->m->remDialog(this);
}
