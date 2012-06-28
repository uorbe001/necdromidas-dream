/*
 * tile.hpp
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

#ifndef TILE_HPP
#define TILE_HPP

#include <SDL/SDL.h>

class Tile
{
  public:
    Tile(int unsigned startX, unsigned int startY, unsigned int w, unsigned int h, unsigned int type)
    {
      tileRectangle.x = startX;
      tileRectangle.y = startY;
      tileRectangle.w = w;
      tileRectangle.h = h;
      tileType = type;
    }

    unsigned int getType() {return tileType;}
    SDL_Rect getRectangle() {return tileRectangle;}
    void Event();

  private:
    SDL_Rect tileRectangle;
    unsigned int tileType;
};

#endif /* TILE_HPP */
