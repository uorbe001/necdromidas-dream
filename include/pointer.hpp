/*
 * pointer.hpp
 * Copyright (C) Unai Orbe 2009 <uorbe001@gmail.com>
 * 
 * pointer.hpp is free software: you can redistribute it and/or modify it
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

#ifndef POINTER_HPP
#define POINTER_HPP

#include "../include/entity.hpp"

class Pointer: public Entity
{
  public:
    Pointer(int unsigned startX, unsigned int startY) : Entity(startX, startY)
    {
      animationVector.resize(1);
      animationVector[0].imageList.push_back("resources/images/others/pointer.png");
      animationVector[0].horizontalFlip = false;
      animationVector[0].horizontalFlip = false;
    }
};

#endif /* POINTER_HPP */
