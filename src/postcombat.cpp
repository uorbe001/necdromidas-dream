/*
 * postcombat.cpp
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


#include "../include/postcombat.hpp"
#include "../include/button.hpp"
#include "../include/switch.hpp"
#include "../include/party.hpp"
#include "../include/character.hpp"
#include <list>
#include <iostream>
#include <sstream>

#define WHITE (SDL_Color){255, 255, 255}


PostCombat::PostCombat(Switch *sw, unsigned int scrWidth, unsigned int scrHeight, unsigned long int experience, Party* p)
	: Menu(sw, scrWidth, scrHeight, scrWidth, scrHeight)
{
  font = TTF_OpenFont( "resources/fonts/DejaVuSans.ttf", 13 );

  //Set scene name and data.
	name = (char*)"PostCombat";
	active = true;
  party = p;
  exp = 0;
  exp = experience;

  //load character list
  std::list<Character*> charList = party->getCharacterList();
  textVector.resize(charList.size());

  Character* tempChar;

  std::string text;
  std::ostringstream tempText;

  //Write the text concerning to earned experience.
  for (unsigned short int i = charList.size(); i; i--)
  {
    tempChar = charList.front();
    charList.pop_front();
    text.clear();

    tempText.str("");

    text =  tempChar->getName();
    text += ": Previous exp: ";
    tempText << tempChar->getExperience();
    text += tempText.str();
    text += " + ";
    tempText.str("");
    tempText << exp;
    text += tempText.str();
    text += " exp." ;

    if (tempChar->AddExperience(exp))
    {
      text += " = LEVEL UP!";
    }

    tempChar->ResetForCombat();

    textVector[i -1] =  TTF_RenderText_Solid( font, text.c_str(), WHITE);

    charList.push_back(tempChar);
  }

	buttonVector.resize(1);

	buttonVector[0] = new Button(250, 400, (char*)"Continue");
	AddEntity(buttonVector[0]);

	background = Engine::LoadImage("resources/images/backgrounds/postcombat.png");

  //Load resources
	if (!LoadResources())
		std::cout<<"ERROR: Could not load resources!"<<std::endl;

        victory_music = Engine::LoadStaticMusic("resources/music/victory2.ogg");

  //Set all the animations to the default animation.
	for (unsigned int i = Entities.size(); i; i--)
	{
		Entity *tempEnt = Entities.front();
		Entities.pop_front();
		tempEnt->setActiveAnimation(0);
		Entities.push_back(tempEnt);
	}
}

PostCombat::~PostCombat()
{
  TTF_CloseFont(font);
  Engine::StopStaticMusic(victory_music);
  Engine::LoadStaticMusic("resources/music/mapa.ogg");
}

void PostCombat::ListenNextFrame(SDL_Event *event)
{
	int x, y;

	ResetAnimations();

  //Read events
	for (unsigned int i = 0; i < buttonVector.size(); i++)
	{
		Button *b1 = buttonVector[i];

		if (event->type == SDL_MOUSEMOTION)
		{
			x = event->motion.x;
			y = event->motion.y;

			if (( x > b1->box.x ) && ( x < b1->box.x + b1->box.w ) && ( y > b1->box.y ) && ( y < b1->box.y + b1->box.h ))
			{
				b1->setInactiveAnimation(0);
				b1->setActiveAnimation(1);
			}
			else
			{
				b1->setInactiveAnimation (1);
				b1->setActiveAnimation(0);
			}
		}
	}

	if( event->type == SDL_MOUSEBUTTONDOWN )
	{
		if( event->button.button == SDL_BUTTON_LEFT )
		{
			x = event->button.x;
			y = event->button.y;

			if (( x > buttonVector[0]->box.x ) && ( x < buttonVector[0]->box.x + buttonVector[0]->box.w ) &&
                                ( y > buttonVector[0]->box.y ) && ( y < buttonVector[0]->box.y + buttonVector[0]->box.h ))
			{
				buttonVector[0]->setInactiveAnimation(1);
				active = false;
				isOk = false;
				swtch->SwitchToWorld();
			}
		}
	}
}

void PostCombat::Draw(bool nextImg, SDL_Surface *screen)
{
	//Draw the background.
	SDL_Rect *pos = new SDL_Rect;
	pos->x = 0;
	pos->y = 0;

	SDL_BlitSurface( background, NULL, screen, pos);

	//Draw the enities.
  for (unsigned int i = Entities.size(); i; i-- )
  {
    Entity* tempEnt = Entities.front();
    Entities.pop_front();

		tempEnt->Draw(nextImg, screen);
		if (tempEnt->getVisible())
			tempEnt->DrawText(screen);

    Entities.push_back(tempEnt);
  }

  //Draw the text...
  for (unsigned int i = 0; i < textVector.size(); i++ )
  {
    if (i == 0)
    {
      pos->x = 135;
      pos->y = 145;
    }
    else
    pos->y += textVector[i]->clip_rect.h + 5;

    SDL_BlitSurface( textVector[i], NULL, screen, pos);
  }

  delete pos;
}
