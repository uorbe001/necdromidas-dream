/*
 *      enemy.hpp
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


#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "../include/physicobject.hpp"
#include "../include/button.hpp"
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

class Switch;
class Character;

class Enemy: public PhysicObject
{
	public:
		//construcor, posX and posY set the position, switch is the engine switch, in case we want to change
		// the scene from here, and flip sets if the default image orientation.
		Enemy(int unsigned startX, unsigned int startY, std::string nam, Switch *sw, bool flip = false);

		//returns live.
		inline unsigned int getLive() {return live;};
		//Sets live to l number if it's in the limits set by stats.
		void setLive(int l);
		//set the stamina depending on s.
		void setStamina(unsigned int s);
    //return mana
		inline unsigned int getMana() {return mana;};
		//returns the stamina.
		inline unsigned int getStamina() {return stamina;};
		//return the max live.
		inline unsigned int getTotalLive() {return totalLive;};
		//return the max mana.
		inline unsigned int getTotalMana() {return totalMana;};
		//return the max stamina.
		inline unsigned int getTotalStamina() {return totalStamina;};
		//return the time left for character turn.
		inline unsigned int getTime(){return timeLeft;};
		//return the max time it has to wait.
		inline unsigned int getTotalTime(){return totalWaitTime;};
		//return strenght atribute.
		inline unsigned int getStrength(){return strength;};
    //return intelligence atribute.
		inline unsigned int getIntelligence(){return intelligence;};
		//return agility atribute.
		inline unsigned int getAgility(){return agility;};
		//return resistance atribute.
		inline unsigned int getResistance(){return resistance;};
		//reset time to the max time.
		void ResetTime();
		//Set live, mana etc depending on atributes.
		void setStats();

    //Deals damage, sets stamina levels and activates attacl animation. en is the target
    // and the activated animation depends on "flip".
    void Attack(Character *en, bool flip = false);
    //Walks setting animation and speed.
		void WalkRight();
    //Walks setting animation and speed.
		void WalkLeft();
    //Stops walking setting animation and speed.
		void StopWalkRight();
    //Stops walking setting animation and speed.
		void StopWalkLeft();
		//Event when character colides with this enemy.
		void ColitionEvent();
    //Draw the enemy to screen nextImage sets if we have to change to the next animation frame.
		virtual void Draw(bool nextImg, SDL_Surface *screen);
    //Draw the text it may have to write.
		virtual void DrawText(SDL_Surface *screen);
		//Draw stats bars.
		virtual void DrawBars(SDL_Surface *screen);
		//Update reaction time depending on t
		virtual void Logic(float t);

	protected:
    //engine swithch alows to change scene from here
		Switch *swtch;
		//react to colitions?
		bool react;
		//a lot of atributes and stats
		unsigned int live, mana, stamina, timeLeft, strength, agility, intelligence, resistance;
		unsigned int totalWaitTime, totalLive, totalMana, totalStamina;


};

#endif /* ENEMY_HPP */
