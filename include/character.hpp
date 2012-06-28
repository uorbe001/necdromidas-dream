/*
 * character.hpp		inline unsigned int getAgility(){return agility;};
 * Copyright (C) Unai Orbe 2009 <uorbe001@gmail.com>
 *
 * character.hpp is free software: you can redistribute it and/or modify it
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


#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "../include/physicobject.hpp"
#include "../include/button.hpp"

class Portrait;
class Enemy;
class ParticleSystem;

class Character: public PhysicObject
{
	public:
    //character contructor, n is the name, s strenght, a agility, i intelligence,
    //r resistance, used to set the rest of the stats, type is the type of character, set with enums.
		Character(char* n, unsigned int s, unsigned int a, unsigned int i, unsigned int r, short int t = 0);
		//character construcor2, posX and posY set the position, height /weight/widht the other physic object atributes.
		Character(unsigned int posX, unsigned int posY, unsigned short int height, unsigned short int weight, unsigned short int width)
        :PhysicObject(posX, posY, height, weight, width),font(NULL),portrait(NULL),particleSys(NULL){};

    //character contructor, n is the name, s strenght, a agility, i intelligence,
    //r resistance, used to set the rest of the stats, type is the type of character, set with enums.
		Character(std::string name, unsigned int s, unsigned int a, unsigned int i,
                        unsigned int r, unsigned short int t, unsigned int l, unsigned int m,
                        unsigned int stam, unsigned long int exp, unsigned int lev);
		~Character();

    //Adds exp earned experience to the character and levels up if it has to.
    bool AddExperience(unsigned long int exp);
		//Returns the character portrait.
		inline Portrait* getPortrait() {return portrait;};
		//returns live if it's more than 0.
		inline unsigned int getLive() {return (live>0)?live:0;};
		//returns character level.
		inline unsigned int getLevel() {return level;};
		//Sets live to l number if it's in the limits set by stats.
		void setLive( int l);
		//set the stamina depending on s.
		void setStamina(int s);
		//Set the mana to m.
    void setMana(int m);
		//Returns the character actual experience.
    inline unsigned long int getExperience() {return experience;};
    //Returns if the character is dead (and animation started)
    inline bool getDead() {return dead;};
    //return mana
		inline unsigned int getMana() {return mana;};
		//returns the stamina.
		inline unsigned int getStamina() {return stamina;};
		//returns the damage dealt the last time the character attacked.
		inline unsigned int getDealtDamage() {return damage;};
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
		//returns character type.
		inline unsigned short int getType(){return type;};
		//returns defending.
    inline bool getDefending(){return defending;};

		//reset time to the max time.
		void ResetTime();
		//reset the stats for the next combat.
		void ResetForCombat();
		//Set live, mana etc depending on atributes.
		void setStats();
		//returns pointer to particle system.
		inline ParticleSystem* getParticleSystem(){return particleSys;};

    //Deals damage, sets stamina levels and activates attacl animation. en is the target
    // and the activated animation depends on "flip".
    void Attack(Enemy *en, bool flip = false);
    //Deals damage, sets stamina levels and activates attacl animation. en is the target
    // and the activated animation depends on "flip".
    void Attack_Fire(Enemy *en, bool flip = false);
    //Deals damage, sets stamina levels and activates attacl animation. en is the target
    // and the activated animation depends on "flip".
    void Attack_Thunder(Enemy *en, bool flip = false);
    //Deals damage, sets stamina levels and activates attacl animation. en is the target
    // and the activated animation depends on "flip".
    void Attack_DarkSlash(Enemy *en, bool flip = false);
    //Deals damage, sets stamina levels and activates attacl animation. en is the target
    // and the activated animation depends on "flip".
    void Attack_SpecialSlash(Enemy *en, bool flip = false);
    //Deals damage, sets stamina levels and activates attacl animation. en is the target
    // and the activated animation depends on "flip".
    void Attack_Cure(Character *ch, bool flip = false);
    //Walks setting animation and speed.
		void WalkRight();
    //Walks setting animation and speed.
		void WalkLeft();
    //Stops walking setting animation and speed.
		void StopWalkRight();
    //Stops walking setting animation and speed.
		void StopWalkLeft();
		//Sets character dead and activates death animation.
    void Die();
		//Sets character defend animation and imroves resistance.
    void Defend();
		//Unsets character defend animation and restores resistance.
    void StopDefend();
    //Character lgoic, changes timeLeft depending on t.
		virtual void Logic(float t);
    //Draw the text it may have to write.
		virtual void DrawText(SDL_Surface *screen);
		//Draw stats bars.
		virtual void DrawBars(SDL_Surface *screen);

	protected:
    //Sets the image to load.
		virtual void setImages();

    //Font type to use if there's something to write.
		TTF_Font *font;
		//Different stats for the character.
		unsigned int level,live, mana, stamina, timeLeft, strength, agility, intelligence, resistance;
		unsigned int totalWaitTime, totalLive, totalMana, totalStamina;
    unsigned long int experience;
    unsigned int damage;
    bool dead;
    short unsigned int type;
    //Portrait that has to be drawn in combat representing character.
    Portrait *portrait;
    //Particle System with the particles to use.
    ParticleSystem *particleSys;
    //Sets if the character is defending.
    bool defending;
};

#endif /* CHARACTER_HPP */
