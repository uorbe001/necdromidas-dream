/*
 * combatlevel.cpp
 * Copyright (C) Unai Orbe 2009 <uorbe001@gmail.com>
 *
 * combatlevel.cpp is free software: you can redistribute it and/or modify it
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

#include "../include/combatlevel.hpp"
#include "../include/gameover.hpp"
#include "../include/postcombat.hpp"
#include "../include/engine.hpp"
#include "../include/particlesystem.hpp"
#include "../include/pointer.hpp"
#include "../include/activehalo.hpp"
#include "../include/mousepointer.hpp"
#include "../include/switch.hpp"
#include "../include/party.hpp"
#include "../include/enemy.hpp"
#include "../include/button.hpp"
#include "../include/character.hpp"
#include "../include/portrait.hpp"
#include "../include/enums.hpp"
#include <list>

CombatLevel::CombatLevel(Switch *sw, unsigned int scrWidth, unsigned int scrHeight, Party *p, unsigned int z)
	: Menu(sw, scrWidth, scrHeight, scrWidth, scrHeight)
{
  //Init varables.
	zone = z;
	party = p;

  gainedExp = 0;

  //Set the precombat phase active, the rest innactive.
	preCombat = true;
	selectingTarget = false;
	playerTurn = false;
  enemTurn = false;
	waitTime = true;
	characterChosen = false;

  //Create but don't show the pointer arrow.
  pointer = new Pointer(0,0);
  pointer->Hide();
  AddEntity(pointer);

  //Create but don't show the halo arround active charaacters.
  halo = new ActiveHalo(0,0);
  halo->Hide();
  AddEntity(halo);

  //Set backgrounds.
	background = Engine::LoadImage("resources/images/backgrounds/combat-background.png");
	combatLoadImage = Engine::LoadImage("resources/images/backgrounds/combat-load.png");

  //Create buttons.
	buttonVector.resize(NUM_COMBATBUTTONS);
	buttonVector[PHYSIC] = new Button(30, 385, (char*)"Physic");
	AddEntity(buttonVector[PHYSIC]);

	buttonVector[MAGIC] = new Button(30, 415, (char*)"Magic");
	AddEntity(buttonVector[MAGIC]);

	buttonVector[RUN] = new Button(30, 445, (char*)"Run");
	AddEntity(buttonVector[RUN]);

	buttonVector[ATTACK] = new Button(240, 385, (char*)"Attack");
	buttonVector[ATTACK]->Hide();
	AddEntity(buttonVector[ATTACK]);

	buttonVector[CURE] = new Button(240, 385, (char*)"Cure [M:20]");
	buttonVector[CURE]->Hide();
	AddEntity(buttonVector[CURE]);

	buttonVector[FIRE] = new Button(240, 415, (char*)"Fire [M:30]");
	buttonVector[FIRE]->Hide();
	AddEntity(buttonVector[FIRE]);

	buttonVector[THUNDER] = new Button(240, 445, (char*)"Thunder [M:50]");
	buttonVector[THUNDER]->Hide();
	AddEntity(buttonVector[THUNDER]);

	buttonVector[SLASH] = new Button(240, 415, (char*)"Slash [S:10]");
	buttonVector[SLASH]->Hide();
	AddEntity(buttonVector[SLASH]);

	buttonVector[DARKSLASH] = new Button(240, 445, (char*)"Dark S. [S:20]");
	buttonVector[DARKSLASH]->Hide();
	AddEntity(buttonVector[DARKSLASH]);

	buttonVector[DEFENDB] = new Button(450, 385, (char*)"Defend");
	buttonVector[DEFENDB]->Hide();
	AddEntity(buttonVector[DEFENDB]);


  //Load resources.
	if (!LoadResources())
		std::cout<<"ERROR: Could not load resources!"<<std::endl;

  //Set the characters in the party for the combat.
	charList = party->getCharacterList();
	portraits.resize(charList.size());
	Character* tempChar;

	if (charList.size() == 1)
	{
		tempChar = charList.front();
		tempChar->setPosition(320,170);
		tempChar->ResetTime();
    tempChar->storePosX();
    tempChar->storePosY();
		AddEntity(tempChar);
		AddPhysicObject(tempChar);

		portraits[0] = tempChar->getPortrait();
		portraits[0]->setPosition(10, 15);
		AddEntity(portraits[0]);
	}
	else if (charList.size() == 2)
	{
		tempChar = charList.front();
		tempChar->setPosition(320,240);
    tempChar->storePosX();
    tempChar->storePosY();
		tempChar->ResetTime();
		AddEntity(tempChar);
		AddPhysicObject(tempChar);

		portraits[0] = tempChar->getPortrait();
		portraits[0]->setPosition(10, 15);
		AddEntity(portraits[0]);

		charList.pop_front();
		charList.push_back(tempChar);

		tempChar = charList.front();
		tempChar->setPosition(320,100);
    tempChar->storePosX();
    tempChar->storePosY();
		tempChar->ResetTime();
		AddEntity(tempChar);
		AddPhysicObject(tempChar);

		portraits[1] = tempChar->getPortrait();
		portraits[1]->setPosition(200, 15);
		AddEntity(portraits[1]);

		charList.pop_front();
		charList.push_back(tempChar);
	}
}

CombatLevel::~CombatLevel()
{
  for (short int i = charList.size(); i; i--)
  {
    Character* tempChar;
    tempChar =  charList.front();
    charList.pop_front();

    for (short int j = Entities.size(); j; j--)
    {
      Entity* tempEnt;
      tempEnt = Entities.front();
      Entities.pop_front();

      //If it's not one of the characters or the portraits, let the scene delete the entity.
      if ((tempEnt != tempChar) && (tempEnt != portraits[i -1]))
        Entities.push_back (tempEnt);
    }
  }

  enemList.clear();
  SDL_FreeSurface(combatLoadImage);
}

void CombatLevel::AddEnemy(unsigned int numEnem)
{
	int posx = 0;
	int posy = 0;
  bool flip = false;
  if (numEnem > 6)
    numEnem = 6;

	for (short int i = numEnem; i; i--)
	{
		switch (numEnem)
		{
		 case 2:
			switch (i)
			{
				case 2:
							posx = 480;
							posy = 100;
              flip = true;
							break;
				default:
							posx = 480;
							posy = 240;
              flip = true;
							break;
			}
			break;

		case 3:
			switch (i)
			{
				case 3:
							posx = 480;
							posy = 100;
               flip = true;
							break;
				case 2:
							posx = 480;
							posy = 240;
              flip = true;
							break;
				default:
							posx = 530;
              flip = true;
							posy = 170;
							break;
			}
			break;

		case 4:
			switch (i)
			{
				case 4:
							posx = 480;
							posy = 100;
              flip = true;
							break;
				case 3:
							posx = 480;
							posy = 240;
              flip = true;
							break;
				case 2:
							posx = 100;
							posy = 240;
              flip = false;
							break;
				default:
							posx = 100;
							posy = 100;
              flip = false;
							break;
			}
			break;

		case 5:
			switch (i)
			{
				case 5:
							posx = 480;
							posy = 100;
              flip = true;
							break;
				case 4:
							posx = 530;
							posy = 170;
              flip = true;
							break;
				case 3:
							posx = 480;
							posy = 240;
              flip = true;
							break;
				case 2:
							posx = 100;
							posy = 240;
              flip = false;
							break;
				default:
							posx = 100;
							posy = 100;
              flip = false;
							break;
			}
			break;

		default:
			switch (i)
			{
				case 6:
							posx = 480;
							posy = 100;
              flip = true;
							break;
				case 5:
							posx = 50;
							posy = 170;
              flip = false;
							break;
				case 4:
							posx = 530;
							posy = 170;
              flip = true;
							break;
				case 3:
							posx = 480;
							posy = 240;
              flip = true;
							break;
				case 2:
							posx = 100;
							posy = 240;
              flip = false;
							break;
				default:
							posx = 100;
							posy = 100;
              flip = false;
							break;
			}
			break;

		}

		Enemy *tempEnem;

    if (zone == FOREST)
      tempEnem = new Enemy (posx, posy, "deathblade",swtch, flip);
    else if (zone == CAVE)
      tempEnem = new Enemy (posx, posy, "wraith",swtch, flip);
    else
      tempEnem = new Enemy (posx, posy, "orc",swtch, flip);

		tempEnem->LoadAnimations();
    tempEnem->storePosX();
    tempEnem->storePosY();
    enemList.push_back(tempEnem);
		this->AddEntity(tempEnem);
		this->AddPhysicObject(tempEnem);
	}
}

void CombatLevel::AddEnemy(Enemy *enem)
{
	int posx = 0;
	int posy = 0;
  bool flip = false;

  switch (enemList.size() + 1)
  {
    case 2:
      posx = 480;
      posy = 100;
      flip = true;
			break;

		case 3:
      posx = 480;
      posy = 100;
      flip = true;
      break;

		case 4:
      posx = 480;
      posy = 100;
      flip = true;
      break;

		case 5:
      posx = 480;
      posy = 100;
      flip = true;
      break;

		default:
      posx = 480;
      posy = 100;
      flip = true;
      break;
		}

		enem->LoadAnimations();
		enem->setPosition(posx, posy);
    enem->storePosX();
    enem->storePosY();
    enemList.push_back(enem);
		this->AddEntity(enem);
		this->AddPhysicObject(enem);
}

void CombatLevel::ListenNextFrame(SDL_Event *event)
{
  //Listen events depending on the phase
  if (preCombat)
    this->PreCombat_ListenNextFrame(event);
  else if (waitTime)
    this->WaitTime_ListenNextFrame(event);
  else if (playerTurn)
    this->PlayerTurn_ListenNextFrame(event);
  else if (enemTurn)
    this->EnemyTurn_ListenNextFrame(event);
  else if (selectingTarget)
    this->SelectingTarget_ListenNextFrame(event);
}

void CombatLevel::Draw(bool nextImg, SDL_Surface *screen)
{
  //Draw depending on the phase
  if (preCombat)
    this->PreCombat_Draw(nextImg, screen);
  else if (waitTime)
    this->WaitTime_Draw(nextImg, screen);
  else if (playerTurn)
    this->PlayerTurn_Draw(nextImg, screen);
  else if (enemTurn)
    this->EnemyTurn_Draw(nextImg, screen);
  else if (selectingTarget)
    this->SelectingTarget_Draw(nextImg, screen);
}

void CombatLevel::DrawBars(SDL_Surface *screen)
{
  //Draw the bars for each entity on the scene.
  Entity* tempEnt;

  for (short int i = Entities.size(); i; i--)
  {
    tempEnt = Entities.front();
    Entities.pop_front();

    tempEnt->DrawBars(screen);

    Entities.push_back(tempEnt);
  }
}

void CombatLevel::Logic(float t)
{
  //Call logic depending on the phase.
  if (preCombat)
    this->PreCombat_Logic(t);
  else if (waitTime)
    this->WaitTime_Logic(t);
  else if (playerTurn)
    this->PlayerTurn_Logic(t);
  else if (enemTurn)
    this->EnemyTurn_Logic(t);
  else if (selectingTarget)
    this->SelectingTarget_Logic(t);
}

void CombatLevel::PreCombat_Draw(bool nextImg, SDL_Surface *screen)
{
	//Draw the background.
	SDL_Rect *pos = new SDL_Rect;
	pos->x = 0;
	pos->y = 0;

	SDL_BlitSurface( combatLoadImage, NULL, screen, pos);

	delete pos;
}

void CombatLevel::PreCombat_Logic (float t)
{
  //PreCombat phase logic, wait time and finish the phase.
	static float ti = 0;
	ti += t;

  if (ti > 10)
  {
    timeSeconds += 1;
    ti -= 10;
  }

	//When ~3 seconds have passed, change to combat.
	if (timeSeconds >= 3)
	{
	  timeSeconds = 0;
	  preCombat = false;
	  waitTime = true;
	}
}

void CombatLevel::PreCombat_ListenNextFrame(SDL_Event *event)
{
  //Nothing to do in precombat phase.
}

void CombatLevel::WaitTime_Draw(bool nextImg, SDL_Surface *screen)
{
	//Move the objects before drawing.
  for (unsigned int i = PhysicObjects.size(); i; i-- )
  {
    PhysicObject* tempObj = PhysicObjects.front();
    PhysicObjects.pop_front();
    tempObj->Move(PhysicObjects);
    PhysicObjects.push_back(tempObj);
  }

	//Draw the background.
	SDL_Rect *pos = new SDL_Rect;
	pos->x = 0;
	pos->y = 0;

	SDL_BlitSurface( background, NULL, screen, pos);

	delete pos;

	//Set buttons innactive in this phase.
	for (unsigned int i = 0; i < buttonVector.size(); i++)
	{
		buttonVector[i]->setActiveAnimation(INNACTIVE);
	}

	//Draw the enities.
  for (unsigned int i = Entities.size(); i; i-- )
  {
    Entity* tempEnt = Entities.front();
    Entities.pop_front();

		if (tempEnt->getVisible())
    {
      if (tempEnt->getAnimationFinished(DIE))
        tempEnt->Draw(tempEnt->getLastImage(), screen);
      else
        tempEnt->Draw(nextImg, screen);
      tempEnt->DrawText(screen);
    }

    Entities.push_back(tempEnt);
  }

  //Draw bars..
  DrawBars(screen);
}

void CombatLevel::WaitTime_Logic (float t)
{
  //PreCombat phase logic, wait time and finish the phase.
  Entity *tempEnt;
	static float ti = 0;
	ti += t;

  if (ti > 10)
  {
    timeSeconds += 1;

    //Go through all the entities and make the logic work
    for (short int i = Entities.size(); i; i--)
    {
      tempEnt = Entities.front();
      Entities.pop_front();

      tempEnt->Logic(t/10);

      Entities.push_back(tempEnt);
    }
    ti -= 10;
  }
	if (timeSeconds >= 60 )
	{
		timeSeconds -= 60;
		timeMinutes += 1;
	}

  unsigned int activeAgil = 0;
  bool allDead = true;

	//if a character is waiting his turn, give it.
	for (short int i = charList.size(); i; i--)
	{
    tempEnt = charList.front();
    charList.pop_front();

    //if the character is alive, unset the "allDead" var and add a bit of mana.
    if (dynamic_cast<Character*>(tempEnt)->getLive() > 0)
      {
        allDead = false;

        if (!(timeSeconds % 5))
          {
            dynamic_cast<Character*>(tempEnt)->setMana(dynamic_cast<Character*>(tempEnt)->getMana() + 1);
          }
      }

    //Give turn  to the waiting character with the hightest agility.
    if ((dynamic_cast<Character*>(tempEnt)->getTime() == 0) && (dynamic_cast<Character*>(tempEnt)->getAgility() >= activeAgil)
              && !(dynamic_cast<Character*>(tempEnt)->getLive() == 0))
    {
      activeAgil = dynamic_cast<Character*>(tempEnt)->getAgility();
      activeCharacter = dynamic_cast<Character*>(tempEnt);
      playerTurn = true;
      waitTime = false;
    }
    //if the character's live is 0, the character dies.
    else if (!(dynamic_cast<Character*>(tempEnt)->getDead()) && (dynamic_cast<Character*>(tempEnt)->getLive() == 0))
      dynamic_cast<Character*>(tempEnt)->Die();

    charList.push_back(dynamic_cast<Character*>(tempEnt));
	}

  //if all the characters are dead and animations finished, gameover.
  if (allDead)
  {

    bool animationFinished = true;

    for (short int i = charList.size(); i; i--)
    {
      tempEnt = charList.front();
      charList.pop_front();

      animationFinished = dynamic_cast<Character*>(tempEnt)->getAnimationFinished(DIE);

      charList.push_back(dynamic_cast<Character*>(tempEnt));
    }

    //if all the deadth animations are finished, gameover.
    if (animationFinished)
    {
      active = false;
      //Set it to not ok, do the engine can destroy the scene.
      isOk = false;
      GameOver* gOver = new GameOver(swtch, screenWidth, screenHeight);
      swtch->SwitchToLevel(gOver);
    }
  }

  //if there's no enemies alive, combat cleared.
  if (enemList.empty())
  {
    //Set it to not ok, do the engine can destroy the scene.
    isOk = false;
    active = false;
    PostCombat* psCombat = new PostCombat(swtch, screenWidth, screenHeight, gainedExp, party);
    swtch->SwitchToLevel(psCombat);
  }

	//If there isn't a player already set to act, give turn to the waiting enemies.
	if (!playerTurn)
	{
    activeAgil = 0;

    for (short int i = enemList.size(); i; i--)
    {
      tempEnt = enemList.front();
      enemList.pop_front();

      //Give turn  to the waiting enemy with the hightest agility.
      if ((dynamic_cast<Enemy*>(tempEnt)->getTime() == 0) && (dynamic_cast<Enemy*>(tempEnt)->getAgility() >= activeAgil)
                                                                              && !(dynamic_cast<Enemy*>(tempEnt)->getLive() == 0))
      {
        activeAgil = dynamic_cast<Enemy*>(tempEnt)->getAgility();
        activeEnemy = dynamic_cast<Enemy*>(tempEnt);
        enemTurn = true;
        waitTime = false;
      }

      //If the character is dead, don't return it to the lit and remove it from entities.
      if (dynamic_cast<Enemy*>(tempEnt)->getLive() == 0)
      {
        for (unsigned short int i = Entities.size(); i; i--)
        {
          Entity *tempEnt = Entities.front();
          Entities.pop_front();

          if (tempEnt->IsOk())
          {
            Entities.push_back(tempEnt);
          }
        }
        for (unsigned short int i = PhysicObjects.size(); i; i--)
        {
          PhysicObject *tempObj = PhysicObjects.front();
          PhysicObjects.pop_front();

          if (tempObj->IsOk())
            PhysicObjects.push_back(tempObj);
          else
            delete tempObj;
        }
      }
      else
        enemList.push_back(dynamic_cast<Enemy*>(tempEnt));
    }
	}
}

void CombatLevel::WaitTime_ListenNextFrame(SDL_Event *event)
{
}

void CombatLevel::PlayerTurn_Draw(bool nextImg, SDL_Surface *screen)
{
	//Move the objects before drawing.
  for (unsigned int i = PhysicObjects.size(); i; i-- )
  {
    PhysicObject* tempObj = PhysicObjects.front();
    PhysicObjects.pop_front();
    tempObj->Move(PhysicObjects);
    PhysicObjects.push_back(tempObj);
  }

	//Draw the background.
	SDL_Rect *pos = new SDL_Rect;
	pos->x = 0;
	pos->y = 0;

	SDL_BlitSurface( background, NULL, screen, pos);

	delete pos;

	//Set buttons active in this phase.
	for (unsigned int i = 0; i < buttonVector.size(); i++)
	{
		if (!buttonVector[i]->getOver() && !buttonVector[i]->getPressed())
      buttonVector[i]->setActiveAnimation(NORMAL);
	}

	//If there's no enough mana/stamina for a magic, it's innactive.
  if (buttonVector[CURE]->getVisible() && (activeCharacter->getMana() <= 20))
    buttonVector[CURE]->setActiveAnimation(INNACTIVE);
  if (buttonVector[FIRE]->getVisible() && (activeCharacter->getMana() <= 30))
    buttonVector[FIRE]->setActiveAnimation(INNACTIVE);
  if (buttonVector[THUNDER]->getVisible() && (activeCharacter->getMana() <= 50))
    buttonVector[THUNDER]->setActiveAnimation(INNACTIVE);
  if (buttonVector[SLASH]->getVisible() && (activeCharacter->getStamina() <= 10))
    buttonVector[SLASH]->setActiveAnimation(INNACTIVE);
  if (buttonVector[DARKSLASH]->getVisible() && (activeCharacter->getStamina() <= 20))
    buttonVector[DARKSLASH]->setActiveAnimation(INNACTIVE);

	//Draw the enities.
  for (unsigned int i = Entities.size(); i; i-- )
  {
    Entity* tempEnt = Entities.front();
    Entities.pop_front();

		if (tempEnt->getVisible())
    {
      if (tempEnt->getAnimationFinished(DIE))
        tempEnt->Draw(tempEnt->getLastImage(), screen);
      else
        tempEnt->Draw(nextImg, screen);
      tempEnt->DrawText(screen);
    }

    Entities.push_back(tempEnt);
  }

  //Draw bars..
  DrawBars(screen);
}
void CombatLevel::PlayerTurn_Logic (float t)
{
  //If a character is defending since last turn, stop the defense.
  if (activeCharacter->getDefending())
    activeCharacter->StopDefend();

  halo->setPosition(activeCharacter->getPosX() + activeCharacter->getWidth()/2 - halo->getWidth()/2,
                    activeCharacter->getPosY() + activeCharacter->getHeight()/2 - halo->getHeight()/2);
  halo->Show();
}

void CombatLevel::PlayerTurn_ListenNextFrame(SDL_Event *event)
{
  int x, y;

  for (unsigned int i = 0; i < buttonVector.size(); i++)
  {
    if (event->type == SDL_MOUSEMOTION)
    {
      x = event->motion.x;
      y = event->motion.y;

      //if the mouse moves over a button set the over animation, else unset it.
      if (( x > buttonVector[i]->box.x ) && ( x < buttonVector[i]->box.x + buttonVector[i]->box.w ) &&
															( y > buttonVector[i]->box.y ) && ( y < buttonVector[i]->box.y + buttonVector[i]->box.h ))
      {
        buttonVector[i]->setOver(true);

        if (buttonVector[i]->getVisible())
        {
          pointer->Show();
          pointer->setPosition((buttonVector[i]->getPosX() - 30), buttonVector[i]->getPosY());
        }
      }
      else
      {
        buttonVector[i]->setOver(false);
      }
    }


    if( event->type == SDL_MOUSEBUTTONUP )
    {
      if( event->button.button == SDL_BUTTON_LEFT )
      {
        x = event->button.x;
        y = event->button.y;

        //if there's a left mouse click, do whatever we have to do in each case.
        if (( x > buttonVector[PHYSIC]->box.x ) && ( x < buttonVector[PHYSIC]->box.x + buttonVector[PHYSIC]->box.w ) &&
                          ( y > buttonVector[PHYSIC]->box.y ) && ( y < buttonVector[PHYSIC]->box.y + buttonVector[PHYSIC]->box.h ))
        {

          //Set all the buttons released, before seting another one pressed.
          for (unsigned int i = 0; i < buttonVector.size(); i++)
          {
            buttonVector[i]->setReleased();
          }

          if (activeCharacter->getType() == WARRIOR)
            buttonVector[DEFENDB]->Show();
          if ((activeCharacter->getType() == WARRIOR) && (activeCharacter->getLevel() >= 2))
            buttonVector[SLASH]->Show();
          if ((activeCharacter->getType() == WARRIOR) && (activeCharacter->getLevel() >= 3))
            buttonVector[DARKSLASH]->Show();

          buttonVector[PHYSIC]->setPressed();
          buttonVector[ATTACK]->Show();
          buttonVector[FIRE]->Hide();
          buttonVector[CURE]->Hide();
          buttonVector[THUNDER]->Hide();
        }
        else if (( x > buttonVector[MAGIC]->box.x ) && ( x < buttonVector[MAGIC]->box.x + buttonVector[MAGIC]->box.w ) &&
														( y > buttonVector[MAGIC]->box.y ) && ( y < buttonVector[MAGIC]->box.y + buttonVector[MAGIC]->box.h ))
        {
          //Set all the buttons released, before seting another one pressed.
          for (unsigned int i = 0; i < buttonVector.size(); i++)
          {
            buttonVector[i]->setReleased();
          }

          buttonVector[MAGIC]->setPressed();
          buttonVector[ATTACK]->Hide();
          buttonVector[SLASH]->Hide();
          buttonVector[DARKSLASH]->Hide();
          buttonVector[DEFENDB]->Hide();

          if ((activeCharacter->getType() == WIZARD) && (activeCharacter->getLevel() >= 1))
            buttonVector[CURE]->Show();
          if ((activeCharacter->getType() == WIZARD) && (activeCharacter->getLevel() >= 2))
            buttonVector[FIRE]->Show();
          if ((activeCharacter->getType() == WIZARD) && (activeCharacter->getLevel() >= 3))
            buttonVector[THUNDER]->Show();
        }
        else if (( x > buttonVector[RUN]->box.x ) && ( x < buttonVector[RUN]->box.x + buttonVector[RUN]->box.w ) &&
														( y > buttonVector[RUN]->box.y ) && ( y < buttonVector[RUN]->box.y + buttonVector[RUN]->box.h ))
        {
          //Set all the buttons released, before seting another one pressed.
          for (unsigned int i = 0; i < buttonVector.size(); i++)
          {
            buttonVector[i]->setReleased();
          }

          buttonVector[RUN]->setPressed();
          buttonVector[ATTACK]->Hide();
          buttonVector[SLASH]->Hide();
          buttonVector[DARKSLASH]->Hide();
          buttonVector[DEFENDB]->Hide();
          buttonVector[FIRE]->Hide();
          buttonVector[CURE]->Hide();
          buttonVector[THUNDER]->Hide();

          if ((activeCharacter->getIntelligence() - activeCharacter->getResistance()) > (rand() % 100))
          {
            active = false;
            isOk = false;
            swtch->SwitchToWorld();
          }
          else
          {
            playerTurn = false;
            waitTime = true;
          }
        }
        else if (( x > buttonVector[ATTACK]->box.x ) && ( x < buttonVector[ATTACK]->box.x + buttonVector[ATTACK]->box.w ) &&
														( y > buttonVector[ATTACK]->box.y ) && ( y < buttonVector[ATTACK]->box.y + buttonVector[ATTACK]->box.h )
                                && buttonVector[ATTACK]->getVisible())
        {
          //Set all the buttons released, before seting another one pressed.
          for (unsigned int i = 0; i < buttonVector.size(); i++)
          {
            buttonVector[i]->setReleased();
          }

          buttonVector[ATTACK]->setPressed();
          lastPressedButton = ATTACK;
          //Change to the select target phase.
          selectingTarget = true;
          playerTurn = false;
        }
        else if (( x > buttonVector[FIRE]->box.x ) && ( x < buttonVector[FIRE]->box.x + buttonVector[FIRE]->box.w ) &&
														( y > buttonVector[FIRE]->box.y ) && ( y < buttonVector[FIRE]->box.y + buttonVector[FIRE]->box.h )
                              && buttonVector[FIRE]->getVisible() && (activeCharacter->getMana() >= 30))
        {
          //Set all the buttons released, before seting another one pressed.
          for (unsigned int i = 0; i < buttonVector.size(); i++)
          {
            buttonVector[i]->setReleased();
          }

          buttonVector[FIRE]->setPressed();
          lastPressedButton = FIRE;
          //Change to the select target phase.
          selectingTarget = true;
          playerTurn = false;
        }
        else if (( x > buttonVector[THUNDER]->box.x ) && ( x < buttonVector[THUNDER]->box.x + buttonVector[THUNDER]->box.w ) &&
														( y > buttonVector[THUNDER]->box.y ) && ( y < buttonVector[THUNDER]->box.y + buttonVector[THUNDER]->box.h )
                              && buttonVector[THUNDER]->getVisible() && (activeCharacter->getMana() >= 50))
        {
          //Set all the buttons released, before seting another one pressed.
          for (unsigned int i = 0; i < buttonVector.size(); i++)
          {
            buttonVector[i]->setReleased();
          }

          buttonVector[THUNDER]->setPressed();
          lastPressedButton = THUNDER;
          //Change to the select target phase.
          selectingTarget = true;
          playerTurn = false;
        }
        else if (( x > buttonVector[CURE]->box.x ) && ( x < buttonVector[CURE]->box.x + buttonVector[CURE]->box.w ) &&
														( y > buttonVector[CURE]->box.y ) && ( y < buttonVector[CURE]->box.y + buttonVector[CURE]->box.h )
                              && buttonVector[CURE]->getVisible() && (activeCharacter->getMana() >= 20))
        {
          //Set all the buttons released, before seting another one pressed.
          for (unsigned int i = 0; i < buttonVector.size(); i++)
          {
            buttonVector[i]->setReleased();
          }

          buttonVector[CURE]->setPressed();
          lastPressedButton = CURE;
          //Change to the select target phase.
          selectingTarget = true;
          playerTurn = false;
        }
        else if (( x > buttonVector[SLASH]->box.x ) && ( x < buttonVector[SLASH]->box.x + buttonVector[SLASH]->box.w ) &&
														( y > buttonVector[SLASH]->box.y ) && ( y < buttonVector[SLASH]->box.y + buttonVector[SLASH]->box.h )
                              && buttonVector[SLASH]->getVisible()  && (activeCharacter->getStamina() >= 10))
        {
          //Set all the buttons released, before seting another one pressed.
          for (unsigned int i = 0; i < buttonVector.size(); i++)
          {
            buttonVector[i]->setReleased();
          }

          buttonVector[SLASH]->setPressed();
          lastPressedButton = SLASH;
          //Change to the select target phase.
          selectingTarget = true;
          playerTurn = false;
        }
        else if (( x > buttonVector[DARKSLASH]->box.x ) && ( x < buttonVector[DARKSLASH]->box.x + buttonVector[DARKSLASH]->box.w ) &&
														( y > buttonVector[DARKSLASH]->box.y ) && ( y < buttonVector[DARKSLASH]->box.y + buttonVector[DARKSLASH]->box.h )
                              && buttonVector[DARKSLASH]->getVisible()  && (activeCharacter->getStamina() >= 20))
        {
          //Set all the buttons released, before seting another one pressed.
          for (unsigned int i = 0; i < buttonVector.size(); i++)
          {
            buttonVector[i]->setReleased();
          }

          buttonVector[DARKSLASH]->setPressed();
          lastPressedButton = DARKSLASH;
          //Change to the select target phase.
          selectingTarget = true;
          playerTurn = false;
        }
        else if (( x > buttonVector[DEFENDB]->box.x ) && ( x < buttonVector[DEFENDB]->box.x + buttonVector[DEFENDB]->box.w ) &&
														( y > buttonVector[DEFENDB]->box.y ) && ( y < buttonVector[DEFENDB]->box.y + buttonVector[DEFENDB]->box.h )
                              && buttonVector[DEFENDB]->getVisible())
        {
          //Set all the buttons released, before seting another one pressed.
          for (unsigned int i = 0; i < buttonVector.size(); i++)
          {
            buttonVector[i]->setReleased();
          }

          buttonVector[DEFENDB]->setPressed();
          lastPressedButton = DEFENDB;

          activeCharacter->Defend();
          playerTurn = false;
          selectingTarget = true;
          //waitTime = true;
        }
      }
    }
  }
}

void CombatLevel::EnemyTurn_Draw(bool nextImg, SDL_Surface *screen)
{
	//Move the objects before drawing.
  for (unsigned int i = PhysicObjects.size(); i; i-- )
  {
    PhysicObject* tempObj = PhysicObjects.front();
    PhysicObjects.pop_front();
    tempObj->Move(PhysicObjects);
    PhysicObjects.push_back(tempObj);
  }

	//Draw the background.
	SDL_Rect *pos = new SDL_Rect;
	pos->x = 0;
	pos->y = 0;

	SDL_BlitSurface( background, NULL, screen, pos);

	delete pos;

	//Set buttons innactive in this phase.
	for (unsigned int i = 0; i < buttonVector.size(); i++)
	{
		if (!buttonVector[i]->getOver() && !buttonVector[i]->getPressed())
      buttonVector[i]->setActiveAnimation(INNACTIVE);
	}

	//Draw the enities.
  for (unsigned int i = Entities.size(); i; i-- )
  {
    Entity* tempEnt = Entities.front();
    Entities.pop_front();

		if (tempEnt->getVisible())
    {
      if (tempEnt->getAnimationFinished(DIE))
        tempEnt->Draw(tempEnt->getLastImage(), screen);
      else
        tempEnt->Draw(nextImg, screen);
      tempEnt->DrawText(screen);
    }

    Entities.push_back(tempEnt);
  }

  //Draw bars..
  DrawBars(screen);
}
void CombatLevel::EnemyTurn_Logic (float t)
{
  //If there isn't a target character chosen, choose it
  if (!characterChosen)
  {
    Character *tempChar;
    attacked = false;
    characterChosen = false;

    //Search until we find a calid target.
    while (!characterChosen)
    {
      //Select a random character to attack.
      short int randomChoice = rand() % charList.size() + 1;
      short int movesToResetList = charList.size() - randomChoice;

      //Store the selected target
      for (; randomChoice; randomChoice--)
      {
        tempChar = charList.front();
        charList.pop_front();

        if (randomChoice == 1)
        {
          chosenCharacter = tempChar;

          //if the character is dead, don't choose it.
          if (tempChar->getLive() != 0)
            characterChosen = true;
        }

        charList.push_back(tempChar);
      }

      //reset list to the original order.
      for (;movesToResetList;movesToResetList--)
      {
        tempChar = charList.front();
        charList.pop_front();
        charList.push_back(tempChar);
      }
    }
  }
  else if (characterChosen && !attacked)
  {
    //Attack the selected target depending on the position.
    if (chosenCharacter->getPosX() < activeEnemy->getPosX())
    {
      activeEnemy->Attack(chosenCharacter, true);
      activeEnemy->setPosition(chosenCharacter->getPosX() + activeEnemy->getWidth(), chosenCharacter->getPosY());
      attacked =  true;
    }
    else
    {
      activeEnemy->Attack(chosenCharacter);
      activeEnemy->setPosition(chosenCharacter->getPosX() - activeEnemy->getWidth(), chosenCharacter->getPosY());
      attacked =  true;
    }
  }
  //If the enemy's attack animation is over, return to the position, set the default animation and change phase.
  else if (activeEnemy->getAnimationFinished(ATTACK_ANIM) || activeEnemy->getAnimationFinished(ATTACK_ANIM_FLIP))
  {
    activeEnemy->restorePosX();
    activeEnemy->restorePosY();
    activeEnemy->setActiveAnimation(0);

    if (attacked)
    {
      activeEnemy->ResetTime();
      characterChosen = false;
      enemTurn = false;
      waitTime = true;
      attacked = false;
    }
  }
}
void CombatLevel::EnemyTurn_ListenNextFrame(SDL_Event *event)
{
  //Nothing to do in enemy turn.
}
void CombatLevel::SelectingTarget_Draw(bool nextImg, SDL_Surface *screen)
{
	//Move the objects before drawing.
  for (unsigned int i = PhysicObjects.size(); i; i-- )
  {
    PhysicObject* tempObj = PhysicObjects.front();
    PhysicObjects.pop_front();
    tempObj->Move(PhysicObjects);
    PhysicObjects.push_back(tempObj);
  }

	//Draw the background.
	SDL_Rect *pos = new SDL_Rect;
	pos->x = 0;
	pos->y = 0;

	SDL_BlitSurface( background, NULL, screen, pos);

	delete pos;

	//Set buttons normal in this phase unless the mouse is over them or pressed.
	for (unsigned int i = 0; i < buttonVector.size(); i++)
	{
		if (!buttonVector[i]->getOver() && !buttonVector[i]->getPressed())
      buttonVector[i]->setActiveAnimation(NORMAL);
	}
	//If there's no enough mana/stamina for a magic, it's innactive.
  if (buttonVector[CURE]->getVisible() && (activeCharacter->getMana() <= 20))
    buttonVector[CURE]->setActiveAnimation(INNACTIVE);
  if (buttonVector[FIRE]->getVisible() && (activeCharacter->getMana() <= 30))
    buttonVector[FIRE]->setActiveAnimation(INNACTIVE);
  if (buttonVector[THUNDER]->getVisible() && (activeCharacter->getMana() <= 50))
    buttonVector[THUNDER]->setActiveAnimation(INNACTIVE);
  if (buttonVector[SLASH]->getVisible() && (activeCharacter->getStamina() <= 10))
    buttonVector[SLASH]->setActiveAnimation(INNACTIVE);
  if (buttonVector[DARKSLASH]->getVisible() && (activeCharacter->getStamina() <= 20))
    buttonVector[DARKSLASH]->setActiveAnimation(INNACTIVE);

	//Draw the enities.
  for (unsigned int i = Entities.size(); i; i-- )
  {
    Entity* tempEnt = Entities.front();
    Entities.pop_front();

		if (tempEnt->getVisible())
    {
      if (tempEnt->getAnimationFinished(DIE))
        tempEnt->Draw(tempEnt->getLastImage(), screen);
      else
        tempEnt->Draw(nextImg, screen);
      tempEnt->DrawText(screen);
    }

    Entities.push_back(tempEnt);
  }

  //Draw bars..
  DrawBars(screen);

  //Draw particles.
  activeCharacter->getParticleSystem()->Draw(nextImg, screen);
}

void CombatLevel::SelectingTarget_Logic (float t)
{
  //hide halo
  halo->Hide();

  //if there's an animation finished, go to the wait phase.
  if (activeCharacter->getAnimationFinished(ATTACK_ANIM) || activeCharacter->getAnimationFinished(ATTACK_ANIM_FLIP)
          || activeCharacter->getAnimationFinished(DEFEND))
  {
    buttonVector[ATTACK]->Hide();
    buttonVector[CURE]->Hide();
    buttonVector[FIRE]->Hide();
    buttonVector[THUNDER]->Hide();
    buttonVector[SLASH]->Hide();
    buttonVector[DARKSLASH]->Hide();
    buttonVector[DEFENDB]->Hide();
    pointer->Hide();
    activeCharacter->restorePosX();
    activeCharacter->restorePosY();
    activeCharacter->setActiveAnimation(0);
    activeCharacter->ResetTime();
    selectingTarget = false;
    waitTime = true;
  }
}

void CombatLevel::SelectingTarget_ListenNextFrame(SDL_Event *event)
{
  if (activeCharacter->getDefending())
  {
    buttonVector[ATTACK]->Hide();
    buttonVector[CURE]->Hide();
    buttonVector[FIRE]->Hide();
    buttonVector[THUNDER]->Hide();
    buttonVector[SLASH]->Hide();
    buttonVector[DARKSLASH]->Hide();
    buttonVector[DEFENDB]->Hide();
  }
  else if( event->type == SDL_MOUSEBUTTONUP )
  {
    //if the left mouse click is detected...
    MousePointer *mousePointer = new MousePointer (event->button.x, event->button.y);

    if( event->button.button == SDL_BUTTON_LEFT )
    {
      PhysicObject *tempObj;

      for (unsigned int i = enemList.size(); i; i-- )
      {
        //Check if the mouse has clicked an enemy.
        tempObj = enemList.front();

        if (tempObj->CheckColitions(mousePointer))
        {
          if (!(tempObj->getSelected()))
          {
            pointer->setPosition(tempObj->getPosX() - 30, tempObj->getPosY() +30);
            tempObj->setSelected(true);
          }
          else if (tempObj->getSelected())
          {
            pointer->Hide();
            tempObj->setSelected(false);

            if (tempObj->getPosX() < activeCharacter->getPosX())
            {
              if (lastPressedButton == ATTACK)
              {
                activeCharacter->Attack(dynamic_cast<Enemy*>(tempObj), true);
                gainedExp += activeCharacter->getDealtDamage();
                activeCharacter->setPosition(tempObj->getPosX() + activeCharacter->getWidth() ,
                                                                              tempObj->getPosY());
                tempObj->setSelected(false);
              }
             else if (lastPressedButton == FIRE)
              {
                activeCharacter->Attack_Fire(dynamic_cast<Enemy*>(tempObj), true);
                gainedExp += activeCharacter->getDealtDamage();
                tempObj->setSelected(false);
              }
               else if (lastPressedButton == THUNDER)
              {
                activeCharacter->Attack_Thunder(dynamic_cast<Enemy*>(tempObj), true);
                gainedExp += activeCharacter->getDealtDamage();
                tempObj->setSelected(false);
              }
              else if (lastPressedButton == SLASH)
              {
                activeCharacter->Attack_SpecialSlash(dynamic_cast<Enemy*>(tempObj), true);
                gainedExp += activeCharacter->getDealtDamage();
                activeCharacter->setPosition(tempObj->getPosX() + activeCharacter->getWidth() ,
                                                                              tempObj->getPosY());
                tempObj->setSelected(false);
              }
              else if (lastPressedButton == DARKSLASH)
              {
                activeCharacter->Attack_DarkSlash(dynamic_cast<Enemy*>(tempObj), true);
                gainedExp += activeCharacter->getDealtDamage();
                activeCharacter->setPosition(tempObj->getPosX() + activeCharacter->getWidth() ,
                                                                              tempObj->getPosY());
                tempObj->setSelected(false);
              }
              else
              {
                selectingTarget = false;
                playerTurn = true;
              }
            }
            else
            {
              if (lastPressedButton == ATTACK)
              {
                activeCharacter->Attack(dynamic_cast<Enemy*>(tempObj));
                gainedExp += activeCharacter->getDealtDamage();
                activeCharacter->setPosition(tempObj->getPosX() - activeCharacter->getWidth() ,
                                                                              tempObj->getPosY());
                tempObj->setSelected(false);
              }
              else if (lastPressedButton == FIRE)
              {
                activeCharacter->Attack_Fire(dynamic_cast<Enemy*>(tempObj), false);
                gainedExp += activeCharacter->getDealtDamage();
                tempObj->setSelected(false);
              }
               else if (lastPressedButton == THUNDER)
              {
                activeCharacter->Attack_Thunder(dynamic_cast<Enemy*>(tempObj), false);
                gainedExp += activeCharacter->getDealtDamage();
                tempObj->setSelected(false);
              }
              else if (lastPressedButton == SLASH)
              {
                activeCharacter->Attack_SpecialSlash(dynamic_cast<Enemy*>(tempObj));
                gainedExp += activeCharacter->getDealtDamage();
                activeCharacter->setPosition(tempObj->getPosX() - activeCharacter->getWidth() ,
                                                                              tempObj->getPosY());
                tempObj->setSelected(false);
              }
              else if (lastPressedButton == DARKSLASH)
              {
                activeCharacter->Attack_DarkSlash(dynamic_cast<Enemy*>(tempObj));
                gainedExp += activeCharacter->getDealtDamage();
                activeCharacter->setPosition(tempObj->getPosX() - activeCharacter->getWidth() ,
                                                                              tempObj->getPosY());
                tempObj->setSelected(false);
              }
              else
              {
                selectingTarget = false;
                playerTurn = true;
                tempObj->setSelected(false);
              }
            }

            //Set all the buttons released.
            for (unsigned int i = 0; i < buttonVector.size(); i++)
            {
              buttonVector[i]->setReleased();
            }

            buttonVector[ATTACK]->Hide();
            buttonVector[CURE]->Hide();
            buttonVector[FIRE]->Hide();
            buttonVector[THUNDER]->Hide();
            buttonVector[SLASH]->Hide();
            buttonVector[DARKSLASH]->Hide();
            buttonVector[DEFENDB]->Hide();
          }
        }

        enemList.pop_front();
        enemList.push_back(dynamic_cast<Enemy*>(tempObj));
      }

      for (unsigned int i = charList.size(); i; i-- )
      {
        //If the mouse clicks an ally...
        tempObj = charList.front();

        if (tempObj->CheckColitions(mousePointer))
        {
          if (!(tempObj->getSelected()))
          {
            pointer->setPosition(tempObj->getPosX() - 30, tempObj->getPosY() +30);
            tempObj->setSelected(true);
          }
          else if (tempObj->getSelected())
          {
            pointer->Hide();
            tempObj->setSelected(false);

            if (tempObj->getPosX() < activeCharacter->getPosX())
            {
              if (lastPressedButton == CURE)
              {
                activeCharacter->Attack_Cure(dynamic_cast<Character*>(tempObj), true);
                tempObj->setSelected(false);
              }
              else
              {
                selectingTarget = false;
                playerTurn = true;
                tempObj->setSelected(false);
              }
            }
            else
            {
              if (lastPressedButton == CURE)
              {
                activeCharacter->Attack_Cure(dynamic_cast<Character*>(tempObj), false);
                tempObj->setSelected(false);
              }
              else
              {
                selectingTarget = false;
                playerTurn = true;
                tempObj->setSelected(false);
              }
            }

            for (unsigned int i = 0; i < buttonVector.size(); i++)
            {
              buttonVector[i]->setReleased();
            }

            buttonVector[ATTACK]->Hide();
            buttonVector[CURE]->Hide();
            buttonVector[FIRE]->Hide();
            buttonVector[THUNDER]->Hide();
            buttonVector[SLASH]->Hide();
            buttonVector[DARKSLASH]->Hide();
            buttonVector[DEFENDB]->Hide();
          }
        }

        charList.pop_front();
        charList.push_back(dynamic_cast<Character*>(tempObj));
      }
    }
    //Else if the click is from the right button, go back to player turn phase.
    else if( event->button.button == SDL_BUTTON_RIGHT )
      {
        selectingTarget = false;
        playerTurn = true;
      }

    delete mousePointer;
  }
}
