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

#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "listener.hpp"

struct SDL_Surface;
union SDL_Event;

class Window : public Listener
{
  public:
    Window(char* name, bool &q, unsigned int Width, unsigned int Height, unsigned  int bpp);
    virtual ~Window();

    SDL_Surface* getScreen() {return screen;}
    virtual void ListenNextFrame(SDL_Event *event);

  private:
    bool *quit;
    SDL_Surface *screen;

    bool StartListener();
};

#endif /* WINDOW_HPP */
