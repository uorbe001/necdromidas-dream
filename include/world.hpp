/*
 * world.hpp
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


#ifndef WORLD_HPP
#define WORLD_HPP

#include "../include/scene.hpp"
#include "../include/enums.hpp"
#include "SDL/SDL_mixer.h"
#include <iostream>
#include <vector>

#include <SDL/SDL.h>

class Tile;
class Party;
class Enemy;
class CombatLevel;
class TextBubble;
class NonPlayerCharacter;
class BubbleButton;
class SaveGameDialog;

class World: public Scene
{
	public:
		World(Switch *sw, unsigned int scrWidth, unsigned int scrHeight);
		~World();

		virtual void ListenNextFrame(SDL_Event *event);
		virtual void Logic(float t);
		void Draw(bool nextImg, SDL_Surface *screen);
		void setActive(bool a = true);
		void setZone();
		void setDanger();
		inline Party* getParty(){return party;};

	protected:
		void GenerateRandomCombat(float time);
		bool LoadMap(const char* mp);
		bool LoadTileImages();

    std::vector<Tile*> tilesVector;
		unsigned int tileWidth, tileHeight;
		SDL_Surface *tileImages[NUM_TILES];

		Party *party;

		SDL_Rect lastPartyPosition;
		unsigned short int danger;
		bool night;
		unsigned short int zone;
		TextBubble *textBubble;
		SaveGameDialog *savegame;
		BubbleButton *textBubbleButton;

                Mix_Music *world_music;
};

#endif /* WORLD_HPP */
