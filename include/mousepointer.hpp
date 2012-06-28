/*
 * mouseMousePointer.hpp
 * Copyright (C) Unai Orbe 2009 <uorbe001@gmail.com>
 *
 * mouseMousePointer.hpp is free software: you can redistribute it and/or modify it
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

#ifndef MOUSEPOINTER_HPP
#define MOUSEPOINTER_HPP

#include "../include/physicobject.hpp"

class MousePointer: public PhysicObject
{
  public:
    MousePointer(unsigned int x, unsigned int y) : PhysicObject(x, y, 1, 0, 1)
    {
      colitionBoxes.resize(1);
      colitionBoxes[0].x = x;
      colitionBoxes[0].y = y;
      colitionBoxes[0].w = 1;
      colitionBoxes[0].h = 1;
    }
};

#endif /* MOUSEPOINTER_HPP */
