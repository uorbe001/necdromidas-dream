/*
 * window.cpp
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

#include "../include/window.hpp"

#include <SDL/SDL.h>

Window::Window(char* name, bool &q, unsigned int Width, unsigned int Height, unsigned int bpp)
{
  // Initialize quit as false, when it's true, we will end.
  quit = &q;
  *quit = false;

  // Set video mode to the screen.
  screen = NULL;
  screen = SDL_SetVideoMode(Width , Height, bpp, SDL_HWSURFACE | SDL_DOUBLEBUF );

  // If screen is null, there's something wrong.
  isOk = !(screen == NULL);

  // Set the window caption.
  SDL_WM_SetCaption(name, NULL);
}

Window::~Window()
{
  SDL_FreeSurface(screen);
}

void Window::ListenNextFrame(SDL_Event *event)
{
    // If quit signal received set quit to true.
    if (event->type == SDL_QUIT)
      *quit = true;
}
