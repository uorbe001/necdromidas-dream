/*
 *      enemy.cpp
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


#include "../include/enemy.hpp"
#include "../include/character.hpp"
#include "../include/engine.hpp"
#include "../include/combatlevel.hpp"
#include "../include/switch.hpp"
#include "../include/enums.hpp"
#include <fstream>

Enemy::Enemy(int unsigned startX, unsigned int startY, std::string nam, Switch *sw, bool flip)
	: PhysicObject( startX, startY, 0, 0, 0)
{
	swtch = sw;
	react = true;
	name = nam;

	std::string fileName ("resources/config/enemies/");
	fileName += nam;
	fileName += ".cfg";

  std::fstream loadFile;
  std::string line;
	std::string text;
  loadFile.open(fileName.c_str());

  const char *temp;

  //Set the animations.
  getline(loadFile, line);
  temp = line.data();
  int numAnimations = atoi(temp);

  animationVector.resize(numAnimations);

  for (short int i = 0; i < numAnimations; i++)
  {
    getline(loadFile, line);
    temp = line.data();
    int numImgs = atoi(temp);
    animationVector[i].imageList.clear();

    for (; numImgs; numImgs--)
    {
      getline(loadFile, line);
      temp = line.data();
      animationVector[i].imageList.push_back(temp);
    }
  }

  getline(loadFile, line);
  temp = line.data();
  strength = atoi(temp);

  getline(loadFile, line);
  temp = line.data();
  agility = atoi(temp);

  getline(loadFile, line);
  temp = line.data();
  intelligence = atoi(temp);

  getline(loadFile, line);
  temp = line.data();
  resistance = atoi(temp);

  setStats();

  getline(loadFile, line);
  temp = line.data();
  unsigned int x = atoi(temp);

  getline(loadFile, line);
  temp = line.data();
  unsigned int y = atoi(temp);

  getline(loadFile, line);
  temp = line.data();
  unsigned int w = atoi(temp);
  oWidth = w;

  getline(loadFile, line);
  temp = line.data();
  unsigned int h = atoi(temp);
  oHeight = h;

	animationVector[0].horizontalFlip = flip;
	animationVector[0].verticalFlip = false;
	animationVector[ATTACK_ANIM].horizontalFlip = false;
	animationVector[ATTACK_ANIM].verticalFlip = false;
	animationVector[ATTACK_ANIM_FLIP].horizontalFlip = true;
	animationVector[ATTACK_ANIM_FLIP].verticalFlip = false;

  //create enemy colition box.

	colitionBoxes.resize(1);
  colitionBoxes[0].x = x;
  colitionBoxes[0].y = y;
  colitionBoxes[0].w = w;
  colitionBoxes[0].h = h;

  ResetBoxes();
}

void Enemy::ColitionEvent()
{
}

void Enemy::Attack(Character *en, bool flip)
{
  //Set active animation attack animation and set the enemy life and stamina.
  setActiveAnimation(ATTACK_ANIM);
  int damage = (this->getStrength() - en->getResistance()/2);

  if (damage < 0)
    damage = 0;

  en->setLive(en->getLive() - damage );
  en->setStamina(en->getStamina() + damage);

  //If the enemy is on the opposite side of the animation's front, use the fliped animation instead.
  if (flip)
    setActiveAnimation(ATTACK_ANIM_FLIP);
}

void Enemy::WalkRight()
{
}
void Enemy::WalkLeft()
{
}

void Enemy::StopWalkRight()
{
}
void Enemy::StopWalkLeft()
{
}

void Enemy::Draw(bool nextImg, SDL_Surface *screen)
{
	SDL_Rect *pos = new SDL_Rect;

  //If the enemy is visible, draw it.
	if (visible)
	{
		pos->x = posX;
		pos->y = posY;

    SDL_BlitSurface( getNextImage(nextImg), NULL, screen, pos);
	}
	delete pos;
}

void Enemy::DrawText(SDL_Surface *screen)
{
}

void Enemy::DrawBars(SDL_Surface *screen)
{
	char txt[10];

	short unsigned int x = 0, y = 0;

	x = posX + animationVector[0].image[0]->clip_rect.w/2 - 25;
	y = posY + animationVector[0].image[0]->clip_rect.h/2 - 25;

	//Lock the surface.
	if(SDL_MUSTLOCK(screen))
		SDL_LockSurface(screen);

	Uint32 *pixels = (Uint32 *)screen->pixels;
	Uint32 pixel;

	//Draw box around bar in black
	for (short unsigned int i = 52; i; i--)
	{
		for (short unsigned int h = 7; h; h--)
		{
			if ((h == 1) || (h == 7) || (i == 52) || (i == 1))
			{
				//Set pixel color
				pixel = 0x00000000;
 				//Set the pixel
				pixels[ ( (y + h -1) * screen->w ) + (x + i -1) ] = pixel;
			}
		}
	}

	//Draw live bar.
	for (short unsigned int l = ((live * 50) / totalLive); l ; l--)
	{
		for (short unsigned int h = 5; h; h--)
		{
			//Set pixel color
			pixel = SDL_MapRGB(screen->format,0,255,0);
 			//Set the pixel
			pixels[ ( (y + h ) * screen->w ) + (x + l) ] = pixel;
		}
	}

	//Unlock when we are done.
	if(SDL_MUSTLOCK(screen))
		SDL_UnlockSurface(screen);
}

void Enemy::setStats()
{
  //set live, mana, etc stats depending on atributes.
	live = resistance*5 - intelligence - agility/2;
	totalLive = live;
	mana = intelligence*5 - resistance - agility/2;
	totalMana = mana;
	stamina = 0;
	totalStamina = resistance * 2 - intelligence/2;
	totalWaitTime = 40 - agility;
	timeLeft = totalWaitTime;
}

void Enemy::Logic(float t)
{
  //if the enemy isn't edad, time passes.
  if (!(live == 0))
  {
    timeLeft -= t;

    if ((timeLeft < 0) || (timeLeft > totalWaitTime))
      timeLeft = 0;
  }
  else
    timeLeft = totalWaitTime;

  //Sets whether there's a finished animation or not.
  animationFinished = false;

  //if there's  an aniation finished set the animatonFinished variable true.
  for (unsigned int i = NUM_ANIM; i; i--)
  {
    if (animationVector[i -1].finished)
      animationFinished = true;
  }
}

void Enemy::ResetTime()
{
  //set time to the total time.
	timeLeft = totalWaitTime;
}

void Enemy::setLive(int l)
{
  //Set the live, it has to be between 0 ant totalLive.
  if (l <= 0 )
  {
    live = 0;
    entOk = false;
  }
  else if (l > totalLive)
    live = totalLive;
  else
    live = l;
}

void Enemy::setStamina(unsigned int s)
{
  //Set the samina within limits.
  if (s <= 0)
  {
    stamina = 0;
  }
  else if (s > totalStamina)
    stamina = totalStamina;
  else
    stamina = s;
}
