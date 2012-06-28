/*
 * mainmenu.hpp
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

#ifndef MAINMENU_HPP
#define MAINMENU_HPP

#include "../include/menu.hpp"
#include "SDL/SDL_mixer.h"

class Button;

class MainMenu: public Menu
{
	public:
		MainMenu(Switch *sw, unsigned int scrWidth, unsigned int scrHeight);
		virtual void ListenNextFrame(SDL_Event *event);
private:
    Mix_Music *menu_music;
};

#endif /* MAINMENU_HPP */ 
