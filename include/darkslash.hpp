/*
 * darkslash.hpp
 * Copyright (C) Unai Orbe 2009 <uorbe001@gmail.com>
 *
 * fire.hpp is free software: you can redistribute it and/or modify it
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

#ifndef DARKSLASH_HPP
#define DARKSLASH_HPP

#include "../include/entity.hpp"

class DarkSlash: public Entity
{
  public:
    DarkSlash() : Entity(0, 0)
    {
      name = "DarkSlash";

      animationVector.resize(1);
      animationVector[0].imageList.push_back("resources/images/magic/dark-slash/dark-slash1.png");
      animationVector[0].imageList.push_back("resources/images/magic/dark-slash/dark-slash2.png");
      animationVector[0].imageList.push_back("resources/images/magic/dark-slash/dark-slash3.png");
      animationVector[0].imageList.push_back("resources/images/magic/dark-slash/dark-slash4.png");
      animationVector[0].imageList.push_back("resources/images/magic/dark-slash/dark-slash5.png");
      animationVector[0].imageList.push_back("resources/images/magic/dark-slash/dark-slash6.png");
      animationVector[0].verticalFlip = false;
      animationVector[0].horizontalFlip = false;

      LoadAnimations();
    }
};

#endif /* DARKSLASH_HPP */
