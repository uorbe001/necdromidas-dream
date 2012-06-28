/*
 * portrait.cpp
 * Copyright (C) Unai Orbe 2009 <uorbe001@gmail.com>
 *
 * protrait.cpp is free software: you can redistribute it and/or modify it
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


#include "../include/portrait.hpp"
#include <iostream>


#define WHITE (SDL_Color){255, 255, 255}

Portrait::Portrait(char* name)
	: Entity(0,0)
{
	font = TTF_OpenFont( "resources/fonts/DejaVuSans.ttf", 16 );
	TTF_SetFontStyle( font, TTF_STYLE_BOLD );

  animationVector.resize(1);

	std::string na("resources/images/portraits/");
	animationVector[0].horizontalFlip = false;
	animationVector[0].verticalFlip = false;
	na += name;
	na += ".png";
	animationVector[0].imageList.push_back(na);

	message.color = WHITE;
	message.msg = TTF_RenderText_Solid( font, name, message.color );

	box.w = 50;
	box.h = 50;
	box.x = 0;
	box.y = 0;
}

void Portrait::DrawText(SDL_Surface *screen)
{
	SDL_Rect *pos = new SDL_Rect;
	pos->x = posX + 50 /2 - message.msg->clip_rect.w/2;
	pos->y = 10 - message.msg->clip_rect.h/2;

	SDL_BlitSurface( message.msg, NULL, screen, pos);
}
