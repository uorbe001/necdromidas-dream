/*
 *      character.cpp
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


#include "../include/character.hpp"
#include "../include/enemy.hpp"
#include "../include/portrait.hpp"
#include "../include/engine.hpp"
#include "../include/particlesystem.hpp"
#include "../include/fire.hpp"
#include "../include/cure.hpp"
#include "../include/thunder.hpp"
#include "../include/lightslash.hpp"
#include "../include/darkslash.hpp"


Character::Character(char* n, unsigned int s, unsigned int a, unsigned int i, unsigned int r, short int t)
	: PhysicObject( 0, 0, 75, 0, 75)
{
  //Set font type
	font = TTF_OpenFont( "resources/fonts/DejaVuSans.ttf", 10 );

  //Sets character stats.
  type = t;
  stamina = 0;
	name = n;
	strength = s;
	agility = a;
	intelligence = i;
	resistance = r;
  dead = false;
  defending = false;
  level = 1;
	setStats();

  //init variables
  damage = 0;
  experience = 0;

  //create the character portrait.
	portrait = new Portrait((char*)name.c_str());
	portrait->LoadAnimations();

  //set characte images
  setImages();

  //set particle system to use for each kind of characteer.
  particleSys = new ParticleSystem();

  if (type == WIZARD)
  {
    Fire *fire = new Fire();
    Cure *cure = new Cure();
    Thunder *thun = new Thunder();
    particleSys->AddParticles(fire);
    particleSys->AddParticles(cure);
    particleSys->AddParticles(thun);
  }
  else if (type == WARRIOR)
  {
    LightSlash *slash = new LightSlash();
    DarkSlash *dark = new DarkSlash();
    particleSys->AddParticles(dark);
    particleSys->AddParticles(slash);
  }


  //create character colition box.
	colitionBoxes.resize(1);
  colitionBoxes[0].x = 21;
  colitionBoxes[0].y = 16;
  colitionBoxes[0].w = oWidth;
  colitionBoxes[0].h = oHeight;
}

Character::Character(std::string n, unsigned int s, unsigned int a, unsigned int i,
                        unsigned int r, unsigned short int t, unsigned int l, unsigned int m,
                        unsigned int stam, unsigned long int exp, unsigned int lev)
      : PhysicObject( 0, 0, 75, 0, 75)
{
  //Set font type
	font = TTF_OpenFont( "resources/fonts/DejaVuSans.ttf", 10 );

  //Sets character stats.
  type = t;
	name = n;
	strength = s;
	agility = a;
	intelligence = i;
	resistance = r;
  dead = false;
  defending = false;
	setStats();

  //init variables
  damage = 0;
  experience = exp;
  level = lev;
	live = l;
	mana = m;
	stamina = stam;

  //create the character portrait.
	portrait = new Portrait((char*)name.c_str());
	portrait->LoadAnimations();

  //set characte images
  setImages();

  //set particle system to use for each kind of characteer.
  particleSys = new ParticleSystem();

  if (type == WIZARD)
  {
    Fire *fire = new Fire();
    Cure *cure = new Cure();
    Thunder *thun = new Thunder();
    particleSys->AddParticles(fire);
    particleSys->AddParticles(cure);
    particleSys->AddParticles(thun);
  }
  else if (type == WARRIOR)
  {
    LightSlash *slash = new LightSlash();
    DarkSlash *dark = new DarkSlash();
    particleSys->AddParticles(dark);
    particleSys->AddParticles(slash);
  }

  //create character colition box.
	colitionBoxes.resize(1);
  colitionBoxes[0].x = 21;
  colitionBoxes[0].y = 16;
  colitionBoxes[0].w = oWidth;
  colitionBoxes[0].h = oHeight;
}

Character::~Character()
{
  TTF_CloseFont(font);
  delete portrait;
  delete particleSys;
}

bool Character::AddExperience(unsigned long int exp)
{
    //Add the experience
    experience += exp;

    //If the character levels up, make the changes and report it.
    if ((experience / (400 * level) >= 1))
    {
        experience -= 400 * level;
        level++;

        if (type == WARRIOR)
          strength += 5;
        else
          strength += 2;
        if (type == WIZARD)
          intelligence += 5;
        else
          intelligence += 2;

        agility += 2;
        resistance += 3;

        setStats();

        return true;
    }

    return false;
}

void Character::Attack(Enemy *en, bool flip)
{
  //Set active animation attack animation and set the enemy life.
  setActiveAnimation(ATTACK_ANIM);
  damage = this->getStrength() - en->getResistance()/2;
  if (damage > en->getLive())
    damage = en->getLive();

  en->setLive(en->getLive() - damage);
  en->setStamina(en->getStamina() + damage);

  //If the enemy is on the opposite side of the animation's front, use the fliped animation instead.
  if (flip)
    setActiveAnimation(ATTACK_ANIM_FLIP);
}

void Character::Attack_Fire(Enemy *en, bool flip)
{
  //Set active animation attack animation and set the enemy life.
  setActiveAnimation(ATTACK_ANIM);
  damage = this->getIntelligence() - en->getResistance()/4;
  if (damage > en->getLive())
    damage = en->getLive();

  en->setLive(en->getLive() - damage);
  mana -= 30;

  //Activate particle  fire
  particleSys->StartParticle("Fire", en->getPosX(), en->getPosY());

  //If the enemy is on the opposite side of the animation's front, use the fliped animation instead.
  if (flip)
    setActiveAnimation(ATTACK_ANIM_FLIP);
}

void Character::Attack_SpecialSlash(Enemy *en, bool flip)
{
  //Set active animation attack animation and set the enemy life.
  setActiveAnimation(ATTACK_ANIM);
  damage = this->getStrength() + intelligence - en->getResistance()/3;
  if (damage > en->getLive())
    damage = en->getLive();

  en->setLive(en->getLive() - damage);
  stamina -= 10;

  //Activate particle  fire
  particleSys->StartParticle("LightSlash", en->getPosX(), en->getPosY());

  //If the enemy is on the opposite side of the animation's front, use the fliped animation instead.
  if (flip)
    setActiveAnimation(ATTACK_ANIM_FLIP);
}

void Character::Attack_DarkSlash(Enemy *en, bool flip)
{
  //Set active animation attack animation and set the enemy life.
  setActiveAnimation(ATTACK_ANIM);
  damage = this->getStrength() + intelligence;
  if (damage > en->getLive())
    damage = en->getLive();

  en->setLive(en->getLive() - damage);
  stamina -= 20;

  //Activate particle  fire
  particleSys->StartParticle("DarkSlash", en->getPosX(), en->getPosY());

  //If the enemy is on the opposite side of the animation's front, use the fliped animation instead.
  if (flip)
    setActiveAnimation(ATTACK_ANIM_FLIP);
}


void Character::Attack_Thunder(Enemy *en, bool flip)
{
  //Set active animation attack animation and set the enemy life.
  setActiveAnimation(ATTACK_ANIM);
  damage = this->getIntelligence();
  if (damage > en->getLive())
    damage = en->getLive();

  en->setLive(en->getLive() - damage);
  mana -= 50;


  //Activate particle  thunder
  particleSys->StartParticle("Thunder", en->getPosX(), en->getPosY());

  //If the enemy is on the opposite side of the animation's front, use the fliped animation instead.
  if (flip)
    setActiveAnimation(ATTACK_ANIM_FLIP);
}

void Character::Attack_Cure(Character *ch, bool flip)
{
  //Set active animation attack animation and set the enemy life.
  setActiveAnimation(ATTACK_ANIM);

  ch->setLive(ch->getLive() + intelligence);
  mana -= 20;

  //Activate particle  cure
  particleSys->StartParticle("Cure", ch->getPosX(), ch->getPosY());

  //If the enemy is on the opposite side of the animation's front, use the fliped animation instead.
  if (flip)
    setActiveAnimation(ATTACK_ANIM_FLIP);
}

void Character::WalkRight()
{
	setInactiveAnimation(0);
	setActiveAnimation(WALK_RIGHT);
	speedX += 1;
}
void Character::WalkLeft()
{
	setInactiveAnimation(0);
	setActiveAnimation(WALK_LEFT);
	speedX += -1;
}

void Character::StopWalkRight()
{
	setInactiveAnimation(WALK_RIGHT);
	setActiveAnimation(STAND);
	speedX -= speedX;
}
void Character::StopWalkLeft()
{
	setInactiveAnimation(WALK_LEFT);
	setActiveAnimation(STAND);
	speedX -= speedX;
}

void Character::DrawText(SDL_Surface *screen)
{
}

void Character::setStats()
{
	live = resistance*5 - intelligence/2;
	totalLive = live;
	mana = intelligence*5 - resistance - agility/2;
	totalMana = mana;
	totalStamina = resistance * 2 - intelligence/2;
	totalWaitTime = 40 - agility;
	timeLeft = totalWaitTime;
}

void Character::Logic(float t)
{
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

  for (unsigned int i = NUM_ANIM ; i; i--)
  {
    if (animationVector[i - 1].finished)
      animationFinished = true;
  }
}

void Character::ResetTime()
{
	timeLeft = totalWaitTime;
}

void Character::DrawBars(SDL_Surface *screen)
{
	SDL_Color color =  {0, 0, 0};
	SDL_Surface *barName;
	SDL_Rect *pos = new SDL_Rect;

	char txt[10];

	short unsigned int x = 0, y = 0;

	x = portrait->getPosX() + portrait->getWidth() +4;
	y = portrait->getPosY();

		//Lock the surface.
	if(SDL_MUSTLOCK(screen))
		SDL_LockSurface(screen);

	Uint32 pixel;
	Uint32 *pixels = (Uint32 *)screen->pixels;

		//Draw box around bar in black
		for (short unsigned int i = 102; i; i--)
		{
			for (short unsigned int h = 12; h; h--)
			{
				if ((h == 1) || (h == 12) || (i == 102) || (i == 1))
				{
					//Set pixel color
					pixel = 0x00000000;

          //Set the pixel
					pixels[ ( (y + h -1) * screen->w ) + (x + i -1) ] = pixel;
				}
			}
		}


		//Draw live bar.
		for (short unsigned int l = (live * 100)/ totalLive; l ; l--)
		{
			for (short unsigned int h = 10; h; h--)
			{
				//Set pixel color
				pixel = SDL_MapRGB(screen->format,0,255,0);

				//Set the pixel
				pixels[ ( (y + h ) * screen->w ) + (x + l) ] = pixel;
			}
		}

		//Draw bar text.
		sprintf(txt, "Live %i/ %i", live, totalLive );
		barName = TTF_RenderText_Solid( font, txt, color );
		pos->x = x + 100 / 2 - barName->clip_rect.w/2;
		pos->y = y + 10 / 2 - barName->clip_rect.h/2 ;
		SDL_BlitSurface( barName, NULL, screen, pos);

		SDL_FreeSurface(barName);

		y += 13;

		//Draw box around bar in black
		for (short unsigned int i = 102; i; i--)
		{
			for (short unsigned int h = 12; h; h--)
			{
				if ((h == 1) || (h == 12) || (i == 102) || (i == 1))
				{
					//Set pixel color
					pixel = 0x00000000;

				  //Set the pixel
					pixels[ ( (y + h -1) * screen->w ) + (x + i -1) ] = pixel;
				}
			}
		}

		//Draw mana bar.
		for (short unsigned int m = ((mana * 100) / totalMana); m ; m--)
		{
			for (short unsigned int h = 10; h; h--)
			{
				//Set pixel color
				pixel = SDL_MapRGB(screen->format,0,0,255);

				//Set the pixel
				pixels[ ( (y + h ) * screen->w ) + (x + m) ] = pixel;
			}
		}

		//Draw bar text.
		sprintf(txt, "Mana %i/ %i",mana, totalMana );
		barName = TTF_RenderText_Solid( font, txt, color );
		pos->x = x + 100 / 2 - barName->clip_rect.w/2;
		pos->y = y + 10 / 2 - barName->clip_rect.h/2 ;
		SDL_BlitSurface( barName, NULL, screen, pos);

		SDL_FreeSurface(barName);

		y += 13;

		//Draw box around bar in black
		for (short unsigned int i = 102; i; i--)
		{
			for (short unsigned int h = 12; h; h--)
			{
				if ((h == 1) || (h == 12) || (i == 102) || (i == 1))
				{
					//Set pixel color
					pixel = 0x00000000;

				  //Set the pixel
					pixels[ ( (y + h -1) * screen->w ) + (x + i -1) ] = pixel;
				}
			}
		}

		//Draw stamina bar.
		for (short unsigned int s = ((stamina * 100) / totalStamina); s ; s--)
		{
			for (short unsigned int h = 10; h; h--)
			{
				//Set pixel color
				pixel = SDL_MapRGB(screen->format,255,0,0);

				//Set the pixel
				pixels[ ( (y + h ) * screen->w ) + (x + s) ] = pixel;
			}
		}

		//Draw bar text.
		sprintf(txt, "Stamina %i/ %i",stamina, totalStamina);
		barName = TTF_RenderText_Solid( font, txt, color );
		pos->x = x + 100 / 2 - barName->clip_rect.w/2;
		pos->y = y + 10 / 2 - barName->clip_rect.h/2 ;
		SDL_BlitSurface( barName, NULL, screen, pos);

		SDL_FreeSurface(barName);

		y += 13;

		//Draw box around bar in black
		for (short unsigned int i = 102; i; i--)
		{
			for (short unsigned int h = 12; h; h--)
			{
				if ((h == 1) || (h == 12) || (i == 102) || (i == 1))
				{
					//Set pixel color
					pixel = 0x00000000;

				  //Set the pixel
					pixels[ ( (y + h -1) * screen->w ) + (x + i -1) ] = pixel;
				}
			}
		}

		//Draw time bar.
		for (short unsigned int t = ((timeLeft * 100) / totalWaitTime); t ; t--)
		{
			for (short unsigned int h = 10; h; h--)
			{
				//Set pixel color
				pixel = 0xF9F9F900;

				//Set the pixel
				pixels[ ( (y + h ) * screen->w ) + (x + t) ] = pixel;
			}
		}

		//Draw bar text.
		sprintf(txt, "Time %i/ %i",timeLeft, totalWaitTime);
		barName = TTF_RenderText_Solid( font, txt, color );
		pos->x = x + 100 / 2 - barName->clip_rect.w/2;
		pos->y = y + 10 / 2 - barName->clip_rect.h/2 ;
		SDL_BlitSurface( barName, NULL, screen, pos);

	//Unlock when we are done.
	if(SDL_MUSTLOCK(screen))
		SDL_UnlockSurface(screen);

		SDL_FreeSurface(barName);
    delete pos;
}

void Character::setLive( int l)
{
  if (l <= 0 )
  {
    live = 0;
  }
  else if (l > totalLive)
    live = totalLive;
  else
    live = l;
}

void Character::setStamina(int s)
{
  if (s <= 0)
  {
    stamina = 0;
  }
  else if (s > totalStamina)
    stamina = totalStamina;
  else
    stamina = s;
}

void Character::setMana(int m)
{
  if (m <= 0)
  {
    mana = 0;
  }
  else if (m > totalMana)
    mana = totalMana;
  else
    mana = m;
}

void Character::Die()
{
  setActiveAnimation(DIE);
  dead = true;
}

void Character::Defend()
{
  setActiveAnimation(DEFEND);
  if (!defending)
  {
    defending = true;
    resistance << 1;
  }
}

void Character::StopDefend()
{
  setActiveAnimation(NORMAL);
  if (defending)
  {
    defending = false;
    resistance >>= 1;
  }
}

void Character::ResetForCombat()
{
  //After the combat the characters are back alive if they die, but with 1 life.
  damage = 0;
  if (dead)
    live = 1;
  dead = false;
  //Set time again.
  timeLeft = totalWaitTime;
  //set the default animation and stop the rest.
  this->setActiveAnimation(0);

  //If the chracter is defending, stop it.
  if (defending)
    StopDefend();
}

void Character::setImages()
{
  //Set the animation iamges.
	std::string na("resources/images/characters/");
	na += name;

	animationVector.resize(NUM_ANIM);
	animationVector[STAND].imageList.push_back(na + "/stand.png");
	animationVector[STAND].horizontalFlip = false;
	animationVector[STAND].verticalFlip = false;

	animationVector[ATTACK_ANIM].imageList.push_back(na + "/attack1.png");
	animationVector[ATTACK_ANIM].imageList.push_back(na + "/attack2.png");
	animationVector[ATTACK_ANIM].imageList.push_back(na + "/attack3.png");
	animationVector[ATTACK_ANIM].imageList.push_back(na + "/attack4.png");

	animationVector[ATTACK_ANIM].horizontalFlip = false;
	animationVector[ATTACK_ANIM].verticalFlip = false;

	animationVector[ATTACK_ANIM_FLIP].imageList.push_back(na + "/attack1.png");
	animationVector[ATTACK_ANIM_FLIP].imageList.push_back(na + "/attack2.png");
	animationVector[ATTACK_ANIM_FLIP].imageList.push_back(na + "/attack3.png");
	animationVector[ATTACK_ANIM_FLIP].imageList.push_back(na + "/attack4.png");
	animationVector[ATTACK_ANIM_FLIP].horizontalFlip = true;
	animationVector[ATTACK_ANIM_FLIP].verticalFlip = false;

	if (type == WARRIOR)
	{
    animationVector[DEFEND].imageList.push_back(na + "/defend1.png");
    animationVector[DEFEND].imageList.push_back(na + "/defend2.png");
    animationVector[DEFEND].imageList.push_back(na + "/defend3.png");
    animationVector[DEFEND].horizontalFlip = true;
    animationVector[DEFEND].verticalFlip = false;
	}

	animationVector[DIE].imageList.push_back(na + "/die1.png");
	animationVector[DIE].imageList.push_back(na + "/die2.png");
	animationVector[DIE].imageList.push_back(na + "/die3.png");
	animationVector[DIE].imageList.push_back(na + "/die4.png");
	animationVector[DIE].imageList.push_back(na + "/die5.png");
	animationVector[DIE].imageList.push_back(na + "/die6.png");
	animationVector[DIE].imageList.push_back(na + "/die7.png");
	animationVector[DIE].horizontalFlip = false;
	animationVector[DIE].verticalFlip = false;
}
