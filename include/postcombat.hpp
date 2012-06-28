/*
 * postcombat.hpp
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

#ifndef POSTCOMBAT_HPP
#define POSTCOMBAT_HPP

#include "../include/menu.hpp"
#include "../include/engine.hpp"
#include <SDL/SDL_ttf.h>

class Button;
class Party;

class PostCombat: public Menu
{
	public:
		PostCombat(Switch *sw, unsigned int scrWidth, unsigned int scrHeight, unsigned long int experience, Party* p);
		~PostCombat();
		virtual void ListenNextFrame(SDL_Event *event);
    virtual void Draw(bool nextImg, SDL_Surface *screen);

  protected:
    unsigned long int exp;
    Party* party;

    std::vector<SDL_Surface*> textVector;
    char* text;
    TTF_Font *font;

    Mix_Music *victory_music;
};

#endif /* POSTCOMBAT_HPP */
