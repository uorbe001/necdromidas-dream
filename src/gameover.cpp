/*
 * postcombat.cpp
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


#include "../include/gameover.hpp"
#include "../include/switch.hpp"

#include <iostream>

GameOver::GameOver(Switch *sw, unsigned int scrWidth, unsigned int scrHeight)
	: Menu(sw, scrWidth, scrHeight, scrWidth, scrHeight)
{
  name = (char*)"GameOver";
  active = true;

	background = Engine::LoadImage("resources/images/backgrounds/gameover.png");

	if (!LoadResources())
		std::cout<<"ERROR: Could not load resources!"<<std::endl;

        gameover_music = Engine::LoadStaticMusic("resources/music/defeat.ogg");
}

void GameOver::Logic(float t)
{
  static float ti = 0;
	ti += t;

	if (ti > 60)
	{
		timeSeconds += t;
		ti -=60;
	}
	if (timeSeconds >= 5 )
	{
    active = false;
    swtch->setWorlActive(false);
    Engine::StopStaticMusic(gameover_music);
    swtch->SwitchToMenu((char*)"MainMenu");
	}
}
