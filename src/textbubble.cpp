/*
 * textbubble.cpp
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


#include "../include/textbubble.hpp"

#define BLACK (SDL_Color){0,0,0}

TextBubble::TextBubble()
    : Entity(10, 350)
{
  //It's not visible at the beginning.
  visible = false;
  nextMessage = false;

	//Set font.
	font = TTF_OpenFont( "resources/fonts/DejaVuSans.ttf", 12 );

	//Load animation image.
  animationVector.resize(1);
	animationVector[0].imageList.push_back("resources/images/others/bubble.png");
}

TextBubble::~TextBubble()
{
  //Clean up.
	TTF_CloseFont( font );
}

void TextBubble::ContinueMessage()
{
  if (!messageList.empty())
    nextMessage = true;
  else
    visible = false;
}

void TextBubble::DrawText(SDL_Surface *screen)
{
  //Draws the text in the buttons.
	SDL_Surface *m = new SDL_Surface;

  //If we have to change to the next message, do it.
  if (nextMessage)
  {
    text = (char*)(messageList.front().c_str());
    messageList.pop_front();
    nextMessage = false;
  }

	m = TTF_RenderText_Solid(font, text, BLACK);

	//The message has to go centered.
	pos.y = posY + 60 - m->clip_rect.h/2;
  pos.x = posX + 10;

	SDL_BlitSurface( m, NULL, screen, &pos);

  SDL_FreeSurface(m);
}

void TextBubble::Draw(bool nextImg, SDL_Surface *screen)
{
	SDL_Rect *pos = new SDL_Rect;

  //If the bubble is visible, draw it and the text.
	if (visible)
	{
		pos->x = posX;
		pos->y = posY;

    SDL_BlitSurface(getNextImage(nextImg), NULL, screen, pos);

    this->DrawText(screen);
	}
}

void TextBubble::Logic(float t)
{

}

void TextBubble::Say(std::list<std::string> mList)
{
  //Set the message to say and make the bubble visible.
  messageList = mList;
  nextMessage = true;
  this->Show();
}
