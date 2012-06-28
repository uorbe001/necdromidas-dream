/*
 *      party.hpp
 *
 *      Copyright 2009 Unai Orbe <uorbe001@gmail.com>
 *
 *      This program is free software; you can redistribute it and/or modify
 *      it under the terms of the GNU General Public License as published by
 *      the Free Software Foundation; either version 2 of the License, or
 *      (at your option) any later version.
 *
 *      This program is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *      GNU General Public License for more details.
 *
 *      You should have received a copy of the GNU General Public License
 *      along with this program; if not, write to the Free Software
 *      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 *      MA 02110-1301, USA.
 */


#ifndef PARTY_HPP
#define PARTY_HPP

#include "../include/physicobject.hpp"

class Character;

class Party: public PhysicObject
{
	public:
		Party(int unsigned startX, unsigned int startY, unsigned int width, float weight, float height);

		void AddCharacter (char* name, unsigned int strength, unsigned int agility, unsigned int intelligence
                                                            , unsigned int resistance, unsigned short int type);

		void AddCharacter (std::string name, unsigned int strength, unsigned int agility, unsigned int intelligence,
                        unsigned int resistance, unsigned short int type, unsigned int live, unsigned int mana,
                        unsigned int stamina, unsigned long int experience, unsigned int lev);
		void WalkUp();
		void WalkDown();
		void WalkRight();
		void WalkLeft();
		void StopWalkUp();
		void StopWalkDown();
		void StopWalkRight();
		void StopWalkLeft();

		void clear();

		std::list<Character*> getCharacterList() {return characterList;};

	private:

		std::list<Character*> characterList;

};

#endif /* PARTY_HPP */
