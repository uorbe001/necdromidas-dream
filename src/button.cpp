/*
 * button.cpp
 * Copyright (C) Unai Orbe 2009 <uorbe001@gmail.com>
 *
 * button.cpp is free software: you can redistribute it and/or modify it
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


#include "../include/button.hpp"

#define GREY (SDL_Color){130, 100, 100}
#define BLACK (SDL_Color){0,0,0}

Button::Button(unsigned int startX, unsigned int startY, char* txt)
	: Entity(startX, startY)
{
  //Start default status variables.
	pressed = false;
  over = false;

	//Set text variables
	text = txt;
	font = TTF_OpenFont( "resources/fonts/DejaVuSans.ttf", 11 );
	TTF_SetFontStyle( font, TTF_STYLE_BOLD );

	//Load animation images and messages.
  animationVector.resize(NUM_STATES);

	animationVector[NORMAL].imageList.push_back("resources/images/buttons/button.png");
	message[NORMAL].color = BLACK;
	message[NORMAL].msg = TTF_RenderText_Solid( font, text, message[NORMAL].color );

	animationVector[OVER].imageList.push_back("resources/images/buttons/button-over.png");
	message[OVER].color = BLACK;
	message[OVER].msg = TTF_RenderText_Solid( font, text, message[OVER].color );

	animationVector[INNACTIVE].imageList.push_back("resources/images/buttons/button-innactive.png");
	message[INNACTIVE].color = GREY;
	message[INNACTIVE].msg = TTF_RenderText_Solid( font, text, message[INNACTIVE].color );

	animationVector[PRESSED].imageList.push_back("resources/images/buttons/button-pressed.png");
	message[PRESSED].color = BLACK;
	message[PRESSED].msg = TTF_RenderText_Solid( font, text, message[PRESSED].color );

	//Set box size.
	box.w = 108;
	box.h = 22;
	box.x = startX;
	box.y = startY;
}

Button::~Button()
{
	TTF_CloseFont( font );

	for (short int i = NUM_STATES; i; i--)
	{
	  SDL_FreeSurface(message[i-1].msg);
	}
}

void Button::DrawText(SDL_Surface *screen)
{
  //Draws the text in the buttons.
	SDL_Surface *m;
	SDL_Rect *pos = new SDL_Rect;

	for (short int i = NUM_STATES; i; i--)
	{
	  //Set m to the message in the active animation.
		if (animationVector[i -1].active)
      m = message[i -1].msg;
	}

	//The message has to go centered.
	pos->x = box.x + box.w/2 - m->clip_rect.w/2;
	pos->y = box.y + box.h/2 - m->clip_rect.h/2;

	SDL_BlitSurface( m, NULL, screen, pos);

	delete pos;
}

void Button::setPressed()
{
  //set the button has been pressed and activate animation.
	this->setActiveAnimation(PRESSED);
	pressed = true;
	over = false;
}

void Button::setOver(bool ov)
{
  //Set the over parameter and the animation depending on it.
	over = ov;
	pressed = false;

  if (over)
    this->setActiveAnimation(OVER);
  else
    this->setActiveAnimation(NORMAL);
}


void Button::setReleased()
{
  //Set the button has been released and stop the animation.
  this->setInactiveAnimation(PRESSED);
	pressed = false;
}

void Button::setBoxPosition (unsigned int x, unsigned int y)
{
  //Set the button box position
  box.x = x;
  box.y = y;
}
