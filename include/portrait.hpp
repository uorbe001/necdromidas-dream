/*
 * portrait.hpp
 * Copyright (C) Unai Orbe 2009 <uorbe001@gmail.com>
 * 
 * portrait.hpp is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * main.cc is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received[NUM_STATES] a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#ifndef PORTRAIT_HPP
#define PORTRAIT_HPP

#include "../include/entity.hpp"
#include "../include/button.hpp"
#include <SDL/SDL.h>

class Portrait: public Entity
{
	public:
		Portrait(char* name);

		SDL_Rect box;
		virtual void DrawText(SDL_Surface *screen);
		int getWidth() {return box.w;};
		Message message;

	protected:
		TTF_Font *font;
};

#endif /* PORTRAIT_HPP */ 
