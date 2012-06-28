/*
 * menu.cpp
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


#ifndef MENU_HPP
#define MENU_HPP

#include "../include/scene.hpp"
#include <string>
#include <vector>

class Button;

class Menu: public Scene
{
	public:
		Menu(Switch *sw, unsigned int scnWidth, unsigned int scnHeight, unsigned int scrWidth, unsigned int scrHeight);
		inline char* getName(){return name;};	
		void Draw(bool nextImg, SDL_Surface *screen);
	protected:
		char* name;
		std::vector<Button*> buttonVector;
};

#endif /* MENU_HPP */ 
