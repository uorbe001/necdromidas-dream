/*
 * button.hpp
 * Copyright (C) Unai Orbe 2009 <uorbe001@gmail.com>
 *
 * button.hpp is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * main.cc is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received[NUM_STATES] a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "../include/entity.hpp"
#include "../include/enums.hpp"
#include <SDL/SDL_ttf.h>
#include <SDL/SDL.h>

//Message struct setting the surface to draw and color of the text.
struct Message
{
	SDL_Surface *msg;
	SDL_Color color;
};

class Button: public Entity
{
	public:
    //Button, startx/starty set the position and txt text in the button
		Button(unsigned int startX, unsigned int startY, char* txt);
    //Button, startx/starty set the position.
		Button(unsigned int startX, unsigned int startY): Entity(startX, startY){};
		virtual ~Button();

    //Draws the text in the button.
		virtual void DrawText(SDL_Surface *screen);
		//Returns if the button is pressed.
		inline bool getPressed () {return pressed;};
		//returns if the mouse is over the button.
		inline bool getOver () {return over;};
		//Set if the mouse is over.
    void setOver(bool ov = true);
    //Set if the buttons is presed.
		void setPressed();
		//set if the button is released.
		void setReleased();
		//set the button box position.
		virtual void setBoxPosition (unsigned int x, unsigned int y);

    //Button box, setting the size and position of the button.
		SDL_Rect box;
		//Messafge in the different states of the button, with color and message.
		Message message[NUM_STATES];
	protected:
    //Button text.
		char* text;
		//Font to use.
		TTF_Font *font;
		//Over/pressed variables.
		bool pressed, over;
};

#endif /* BUTTON_HPP */
