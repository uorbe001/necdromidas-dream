/*
 * combatlevel.hpp
 * Copyright (C) Unai Orbe 2009 <uorbe001@gmail.com>
 *
 * combatlevel.hpp is free software: you can redistribute it and/or modify it
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


#ifndef COMBATLEVEL_HPP
#define COMBATLEVEL_HPP

#include "../include/scene.hpp"
#include "../include/menu.hpp"
#include <iostream>
#include <vector>

class Party;
class Button;
class Pointer;
class Character;
class Enemy;
class Portrait;
class ActiveHalo;

class CombatLevel: public Menu
{
	public:
    //Constructor, scrWidth/scrHeight  set the screen size, party is the aprty that will fight
    //and z is the number of the zone where they fight.
		CombatLevel(Switch *sw, unsigned int scrWidth, unsigned int scrHeight, Party *p, unsigned int z);
		~CombatLevel();

    //Listener function, event is the event to listen.
		virtual void ListenNextFrame(SDL_Event *event);
		//Logic function calls the scene logic.
    virtual void Logic(float t);
    //Draw the scene, nextImg sets wheter we have to advance a frame in animations, and screen is the screen to blit.
		virtual void Draw(bool nextImg, SDL_Surface *screen);
		//Draw status bars to screen.
		void DrawBars(SDL_Surface *screen);
		//Adds numEnem enemies to the scene.
    void AddEnemy(unsigned int numEnem);
    //Adds pre created enem enemy to the scene.
    void AddEnemy(Enemy *enem);

	protected:

    //gained experience in this combat.
    unsigned long int gainedExp;
    //Phase variables, and other control vars.
		bool playerTurn, enemTurn, selectingTarget, preCombat, waitTime, characterChosen, attacked;
		//Combat zone var.
		unsigned short int zone;
		//Comabt loading background
		SDL_Surface *combatLoadImage;
		//party fighting
		Party *party;
		//Arrow selecting targets during combat.
    Pointer *pointer;
    //the halo arround the active character.
    ActiveHalo *halo;
    //Character list.
		std::list<Character*> charList;
		//enemy List
    std::list<Enemy*> enemList;
    //The character active during the player turn.
    Character* activeCharacter;
    //Character chosen as target by enemies.
    Character* chosenCharacter;
    //Active enemy in enemy turn.
    Enemy* activeEnemy;

  private:
    //Draw function for precombat phase.
    void PreCombat_Draw(bool nextImg, SDL_Surface *screen);
    //Logic function for precombat phase.
    void PreCombat_Logic (float t);
    //Draw function for precombar phase
    void PreCombat_ListenNextFrame(SDL_Event *event);
    //...same with the WaitTime, PlayerTurn, EnemyTurn and SelectingTarget phases.
    void WaitTime_Draw(bool nextImg, SDL_Surface *screen);
    void WaitTime_Logic (float t);
    void WaitTime_ListenNextFrame(SDL_Event *event);
    void PlayerTurn_Draw(bool nextImg, SDL_Surface *screen);
    void PlayerTurn_Logic (float t);
    void PlayerTurn_ListenNextFrame(SDL_Event *event);
    void EnemyTurn_Draw(bool nextImg, SDL_Surface *screen);
    void EnemyTurn_Logic (float t);
    void EnemyTurn_ListenNextFrame(SDL_Event *event);
    void SelectingTarget_Draw(bool nextImg, SDL_Surface *screen);
    void SelectingTarget_Logic (float t);
    void SelectingTarget_ListenNextFrame(SDL_Event *event);
    //Portrait vector, to remember when deleting.
    std::vector<Portrait*> portraits;
    //Integer telling what button has been pressed last.
    short int lastPressedButton;
};

#endif /* COMBATLEVEL_HPP */
