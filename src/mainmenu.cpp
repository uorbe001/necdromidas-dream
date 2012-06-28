/*
 * mainmenu.cpp
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


#include "../include/mainmenu.hpp"
#include "../include/button.hpp"
#include "../include/switch.hpp"
#include "../include/world.hpp"
#include "../include/party.hpp"

#include <fstream>

MainMenu::MainMenu(Switch *sw, unsigned int scrWidth, unsigned int scrHeight)
	: Menu(sw, scrWidth, scrHeight, scrWidth, scrHeight)
{
	name = (char*)"MainMenu";
	active = true;
	buttonVector.resize(2);


	buttonVector[0] = new Button(250, 370, (char*)"New game");
	buttonVector[1] = new Button(250, 400, (char*)"Load game");
	AddEntity(buttonVector[0]);
	AddEntity(buttonVector[1]);

	background = Engine::LoadImage("resources/images/backgrounds/main-manu.jpg");
        menu_music = Engine::LoadStaticMusic("resources/music/main_menu.ogg");
	if (!LoadResources())
		std::cout<<"ERROR: Could not load resources!"<<std::endl;

	for (unsigned int i =Entities.size(); i; i--)
	{
		Entity *tempEnt = Entities.front();
		Entities.pop_front();
		tempEnt->setActiveAnimation(0);
		Entities.push_back(tempEnt);
	}
}

void MainMenu::ListenNextFrame(SDL_Event *event)
{
	int x, y;

	ResetAnimations();

  if (event->type == SDL_MOUSEMOTION)
  {
    x = event->motion.x;
    y = event->motion.y;

    for (short int i = buttonVector.size(); i; i--)
    {
      if (( x > buttonVector[i -1]->box.x ) && ( x < buttonVector[i -1]->box.x + buttonVector[i -1]->box.w )
                    && ( y > buttonVector[i -1]->box.y ) && ( y < buttonVector[i -1]->box.y + buttonVector[i -1]->box.h ))
      {
        buttonVector[i -1]->setOver(true);
      }
      else
      {
        buttonVector[i -1]->setOver(false);
      }
    }
  }

	if( event->type == SDL_MOUSEBUTTONDOWN )
	{
		if( event->button.button == SDL_BUTTON_LEFT )
		{
			x = event->button.x;
			y = event->button.y;

			if (( x > buttonVector[0]->box.x ) && ( x < buttonVector[0]->box.x + buttonVector[0]->box.w ) &&
														( y > buttonVector[0]->box.y ) && ( y < buttonVector[0]->box.y + buttonVector[0]->box.h ))
			{
			  swtch->getWorld()->getParty()->clear();
        swtch->getWorld()->getParty()->AddCharacter("Ureg", 30, 15, 15, 25, WARRIOR);
        swtch->getWorld()->getParty()->AddCharacter("Ianus", 15, 20, 30, 15, WIZARD);
        swtch->getWorld()->getParty()->setPosition(73, 142);

				active = false;
        Engine::StopStaticMusic(menu_music);
				swtch->SwitchToWorld();
			}
			if (( x > buttonVector[1]->box.x ) && ( x < buttonVector[1]->box.x + buttonVector[1]->box.w ) &&
														( y > buttonVector[1]->box.y ) && ( y < buttonVector[1]->box.y + buttonVector[1]->box.h ))
			{
        std::fstream load_file;
        std::string line;
        load_file.open("savegames/game.save");

        int num_chars;
        const char *temp;

        getline(load_file, line);
        const char *chars = line.data();
        num_chars = atoi(chars);

        getline(load_file, line);
        temp = line.data();
        int posx = atoi(temp);

        getline(load_file, line);
        temp = line.data();
        int posy = atoi(temp);

        swtch->getWorld()->getParty()->setPosition(posx, posy);
        swtch->getWorld()->getParty()->clear();

        std::string name;
        unsigned int strength, agility, intelligence, resistance, type, live, mana, stamina, level;
        unsigned long int experience;

        for(int i = num_chars; i;i--) {
          getline(load_file, line);
          name = line.data();

          getline(load_file, line);
          temp = line.data();
          type = atoi(temp);

          getline(load_file, line);
          temp = line.data();
          experience = atoi(temp);

          getline(load_file, line);
          temp = line.data();
          live = atoi(temp);

          getline(load_file, line);
          temp = line.data();
          mana = atoi(temp);

          getline(load_file, line);
          temp = line.data();
          stamina = atoi(temp);

          getline(load_file, line);
          temp = line.data();
          strength = atoi(temp);

          getline(load_file, line);
          temp = line.data();
          agility = atoi(temp);

          getline(load_file, line);
          temp = line.data();
          intelligence = atoi(temp);

          getline(load_file, line);
          temp = line.data();
          resistance = atoi(temp);

          getline(load_file, line);
          temp = line.data();
          level = atoi(temp);

          swtch->getWorld()->getParty()->AddCharacter(name, strength, agility, intelligence,
                                    resistance, type, live, mana, stamina, experience, level);
			}

        active = false;
        Engine::StopStaticMusic(menu_music);
				swtch->SwitchToWorld();
		}
			}
		}
	}
