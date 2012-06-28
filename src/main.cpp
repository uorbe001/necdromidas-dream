/*
 * main.cc
 * Copyright (C) Unai Orbe 2009 <uorbe001@gmail.com>
 *
 * main.cc is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * main.cc is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include"../include/engine.hpp"
#include"../include/window.hpp"
#include"../include/mainmenu.hpp"
#include"../include/world.hpp"
#include"../include/switch.hpp"

int main(int argc, char **argv)
{
  //Create engine and window with name and size.
	Engine *eng = new Engine((char*)"Necromida's Dream", 640, 480);
	//Creater switcher to change between scenes in the engine.
	Switch *sw = new Switch(eng);

  //Create the game world with that size of the screen and pointer to the switch.
	World *world = new World(sw, 640, 480);
	//Create the game main menu with that size of the screen and pointer to the switch.
	MainMenu *mMenu = new MainMenu(sw, 640, 480);

  //Add menu and world to the engine.
	eng->AddMenu((Menu*)mMenu);
	eng->AddWorld(world);

  //Main render loop, only ended when the engine receives the exit order.
	eng->Render();

  //Clean up.
	delete eng;
	delete world;
	delete mMenu;
	return 0;
}
