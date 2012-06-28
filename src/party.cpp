/*
 * party.cpp
 * Copyright (C) Unai Orbe 2009 <uorbe001@gmail.com>
 *
 * party.cpp is free software: you can redistribute it and/or modify it
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


#include "../include/party.hpp"
#include "../include/character.hpp"


Party::Party(int unsigned startX, unsigned int startY, unsigned int width, float height, float weight)
	: PhysicObject( startX, startY, width, weight, height)
{
  //Entity name party.
  name = "Party";

  //Load the animations.
	animationVector.resize(NUM_ANIM);

	animationVector[STAND].imageList.push_back("resources/images/characters/Ianus/stand.png");
	animationVector[STAND].horizontalFlip = false;
	animationVector[STAND].verticalFlip = false;

	animationVector[WALK_RIGHT].imageList.push_back("resources/images/characters/Ianus/walk1.png");
	animationVector[WALK_RIGHT].imageList.push_back("resources/images/characters/Ianus/walk2.png");
	animationVector[WALK_RIGHT].horizontalFlip = false;
	animationVector[WALK_RIGHT].verticalFlip = false;

	animationVector[WALK_LEFT].imageList.push_back("resources/images/characters/Ianus/walk1.png");
	animationVector[WALK_LEFT].imageList.push_back("resources/images/characters/Ianus/walk2.png");
	animationVector[WALK_LEFT].horizontalFlip = true;
	animationVector[WALK_LEFT].verticalFlip = false;

	animationVector[WALK_UP].imageList.push_back("resources/images/characters/Ianus/walk-up1.png");
	animationVector[WALK_UP].imageList.push_back("resources/images/characters/Ianus/walk-up2.png");
	animationVector[WALK_UP].imageList.push_back("resources/images/characters/Ianus/walk-up3.png");
	animationVector[WALK_UP].horizontalFlip = false;
	animationVector[WALK_UP].verticalFlip = false;

	animationVector[WALK_DOWN].imageList.push_back("resources/images/characters/Ianus/walk-down1.png");
	animationVector[WALK_DOWN].imageList.push_back("resources/images/characters/Ianus/walk-down2.png");
	animationVector[WALK_DOWN].horizontalFlip = false;
	animationVector[WALK_DOWN].verticalFlip = false;

	//Set the colition box.
	colitionBoxes.resize(1);
  colitionBoxes[0].x = 21;
  colitionBoxes[0].y = 16;
  colitionBoxes[0].w = 25;
  colitionBoxes[0].h = 43;
}

void Party::AddCharacter (char* name, unsigned int strength, unsigned int agility, unsigned int intelligence, unsigned int resistance
    , unsigned short int type)
{
	Character *tempCharacter = new Character (name, strength, agility, intelligence, resistance, type);
	tempCharacter->LoadAnimations();
	characterList.push_back(tempCharacter);
}

void Party::AddCharacter (std::string name, unsigned int strength, unsigned int agility, unsigned int intelligence,
                        unsigned int resistance, unsigned short int type, unsigned int live, unsigned int mana,
                        unsigned int stamina, unsigned long int experience, unsigned int lev)
{
	Character *tempCharacter = new Character (name, strength, agility, intelligence, resistance, type, live, mana, stamina, experience, lev);
	tempCharacter->LoadAnimations();
	characterList.push_back(tempCharacter);
}

void Party::WalkUp()
{
	setInactiveAnimation(0);
	setActiveAnimation(WALK_UP);
	speedY += -1;
	moving = true;
}
void Party::WalkDown()
{
	setInactiveAnimation(0);
	setActiveAnimation(WALK_DOWN);
	speedY += 1;
	moving = true;
}
void Party::WalkRight()
{
	setInactiveAnimation(0);
	setActiveAnimation(WALK_RIGHT);
	speedX += 1;
	moving = true;
}
void Party::WalkLeft()
{
	setInactiveAnimation(0);
	setActiveAnimation(WALK_LEFT);
	speedX += -1;
	moving = true;
}


void Party::StopWalkUp()
{
	setInactiveAnimation(WALK_UP);
	setActiveAnimation(STAND);
	speedY -= speedY;
	moving = false;
}
void Party::StopWalkDown()
{
	setInactiveAnimation(WALK_DOWN);
	setActiveAnimation(STAND);
	speedY -= speedY;
	moving = false;
}
void Party::StopWalkRight()
{
	setInactiveAnimation(WALK_RIGHT);
	setActiveAnimation(STAND);
	speedX -= speedX;
	moving = false;
}
void Party::StopWalkLeft()
{
	setInactiveAnimation(WALK_LEFT);
	setActiveAnimation(STAND);
	speedX -= speedX;
	moving = false;
}

void Party::clear()
{
  Character* tempChar;

  for (short int i = characterList.size(); i; i--)
  {
    tempChar = characterList.front();
    characterList.pop_front();
    delete tempChar;
  }
}
