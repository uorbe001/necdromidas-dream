/*
 * cure.hpp
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

#ifndef CURE_HPP
#define CURE_HPP

#include "../include/entity.hpp"

class Cure: public Entity
{
  public:
    Cure() : Entity(0, 0)
    {
      name = "Cure";

      animationVector.resize(1);
      animationVector[0].imageList.push_back("resources/images/magic/cure/cure1.png");
      animationVector[0].imageList.push_back("resources/images/magic/cure/cure2.png");
      animationVector[0].imageList.push_back("resources/images/magic/cure/cure3.png");
      animationVector[0].imageList.push_back("resources/images/magic/cure/cure4.png");
      animationVector[0].imageList.push_back("resources/images/magic/cure/cure5.png");
      animationVector[0].imageList.push_back("resources/images/magic/cure/cure6.png");
      animationVector[0].imageList.push_back("resources/images/magic/cure/cure7.png");
      animationVector[0].verticalFlip = false;
      animationVector[0].horizontalFlip = false;

      LoadAnimations();
    }
};

#endif /* CURE_HPP */
