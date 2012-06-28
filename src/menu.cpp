/*
 * menu.cpp
 * Copyright (C) Unai Orbe 2009 <uorbe001@gmail.com>
 * 
 * menu.cpp is free software: you can redistribute it and/or modify it
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


#include "../include/menu.hpp"
#include "../include/entity.hpp"
#include "../include/physicobject.hpp"
#include "../include/button.hpp"

Menu::Menu(Switch *sw, unsigned int scnWidth, unsigned int scnHeight, unsigned int scrWidth, unsigned int scrHeight)
	: Scene(sw, scnWidth, scnHeight, scrWidth, scrHeight)
{
	
}

void Menu::Draw(bool nextImg, SDL_Surface *screen)
{
	//Move the objects before drawing.
  for (unsigned int i = PhysicObjects.size(); i; i-- )
  {
      PhysicObject* tempObj = PhysicObjects.front();
      PhysicObjects.pop_front();
      tempObj->Move(PhysicObjects);
      PhysicObjects.push_back(tempObj);
  }
	
	//Draw the background.
	SDL_Rect *pos = new SDL_Rect;
	pos->x = 0;
	pos->y = 0;

	SDL_BlitSurface( background, NULL, screen, pos);
	

	//Draw the enities.
  for (unsigned int i = Entities.size(); i; i-- )
  {
    Entity* tempEnt = Entities.front();
    Entities.pop_front();
		
		tempEnt->Draw(nextImg, screen); 
		if (tempEnt->getVisible())
			tempEnt->DrawText(screen);
		
    Entities.push_back(tempEnt);
  }
}
