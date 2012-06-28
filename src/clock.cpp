/*
 * clock.cpp
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

#include "../include/clock.hpp"

#include <SDL/SDL.h>

long int Clock::getTicks()
{
  // If Clock is started...
  if (started)
  {
    // Returns elapsed ticks
    return (SDL_GetTicks() - startTicks);
  }
  // If the clock isn't started, return 0
  return 0;
}

void Clock::Start()
{
  started = true;
  // Sets start time.
  startTicks = SDL_GetTicks();
}
