/*
 * thunder.hpp
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

#ifndef THUNDER_HPP
#define THUNDER_HPP

#include "../include/entity.hpp"

class Thunder: public Entity
{
  public:
    Thunder() : Entity(0,0)
    {
      name = "Thunder";

      animationVector.resize(1);
      animationVector[0].imageList.push_back("resources/images/magic/electricity/electric1.png");
      animationVector[0].imageList.push_back("resources/images/magic/electricity/electric2.png");
      animationVector[0].imageList.push_back("resources/images/magic/electricity/electric3.png");
      animationVector[0].verticalFlip = false;
      animationVector[0].horizontalFlip = false;

      LoadAnimations();
    }
};

#endif /* THUNDER_HPP */
