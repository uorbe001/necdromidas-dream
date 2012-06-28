/*
 * physicobject.cpp
 * Copyright (C) Unai Orbe 2009 <uorbe001@gmail.com>
 *
 * physicobject.cpp is free software: you can redistribute it and/or modify it
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


#include "../include/physicobject.hpp"

PhysicObject::PhysicObject(int unsigned startX, unsigned int startY, unsigned int width, float weight, float height)
	: Entity(startX, startY)
{
	oWidth = width;
	oWeight = weight;
	oHeight = height;
	speedX = speedY = 0;
	acelerationX = acelerationY = 0;
	reactToColition = false;
  selected = false;
  moving = false;
}

PhysicObject::PhysicObject(int unsigned startX, unsigned int startY)
{
	oWidth = 0;
	oWeight = 0;
	oHeight = 0;
	speedX = speedY = 0;
	acelerationX = acelerationY = 0;
	reactToColition = false;
  selected = false;
  moving = false;
}

void PhysicObject::Acelerate(float t)
{
  speedX += 2*t*acelerationX;
  speedY += 2*t*acelerationY;
}

bool PhysicObject::CheckColitions(PhysicObject *obj)
{
  //The sides of the rectangles
  int leftBoxA, leftBoxB;
  int rightBoxA, rightBoxB;
  int topBoxA, topBoxB;
  int bottomBoxA, bottomBoxB;

  std::vector<SDL_Rect> colitionBoxesB = obj->getRectangles();

  //Go through this object's collition boxes
  for( unsigned int i = 0; i < colitionBoxes.size(); i++)
  {
    //Calculate the sides of the boxes.
    leftBoxA = colitionBoxes[i].x;
    rightBoxA = colitionBoxes[i].x + colitionBoxes[i].w;
    topBoxA = colitionBoxes[i].y;
    bottomBoxA = colitionBoxes[i].y + colitionBoxes[i].h;

    //Go through the second object's boxes
    for( unsigned int j = 0 ; j < colitionBoxesB.size() ; j++)
    {
      //Calculate the sides of second collider object's boxes
      leftBoxB = colitionBoxesB[j].x;
      rightBoxB = colitionBoxesB[j].x + colitionBoxesB[j].w;
      topBoxB = colitionBoxesB[j].y;
      bottomBoxB = colitionBoxesB[j].y + colitionBoxesB[j].h;

			if((bottomBoxA < topBoxB) || (topBoxA > bottomBoxB) || (rightBoxA < leftBoxB) || (leftBoxA > rightBoxB))
			{
				//If the character is further than the box+10 pixels of margin, it can react again.
				if (((bottomBoxA+10) < (topBoxB-10)) || ((topBoxA-10) > (bottomBoxB+10)) || ((rightBoxA+10)< (leftBoxB-10))
                                                              || ((leftBoxA-10) > (rightBoxB+10)))
					reactToColition = true;
				return false;
			}
			else if (reactToColition)
			{
        obj->ColitionEvent();
				reactToColition = false;
				coliderName = obj->getName();
			}
    }
	}
	return true;
}

bool PhysicObject::CheckPos(SDL_Rect rec)
{
  //The sides of the rectangles
  int leftBoxA, leftBoxB;
  int rightBoxA, rightBoxB;
  int topBoxA, topBoxB;
  int bottomBoxA, bottomBoxB;

    //Calculate the sides of second collider object's boxes
  leftBoxB = rec.x;
  rightBoxB = rec.x + rec.w;
  topBoxB = rec.y;
  bottomBoxB = rec.y + rec.h;

  //Go through this object's collition boxes
  for( unsigned int i = 0; i < colitionBoxes.size(); i++)
  {
	//Calculate the sides of the boxes.
    leftBoxA = colitionBoxes[i].x;
    rightBoxA = colitionBoxes[i].x + colitionBoxes[i].w;
    topBoxA = colitionBoxes[i].y;
	  bottomBoxA = colitionBoxes[i].y + colitionBoxes[i].h;

		if((bottomBoxA < topBoxB) || (topBoxA > bottomBoxB) || (rightBoxA < leftBoxB) || (leftBoxA > rightBoxB))
			return false;
   }
	return true;
}

void PhysicObject::Gravitate(float gravity, float t)
{
    acelerationY = (2*oWeight*gravity/10000);
		lastGravityAceleration =  2*t*acelerationY;
    Acelerate(t);
}

void PhysicObject::Move(std::list<PhysicObject*> colideList)
{
  if (moving)
  {
    posX += speedX;
    ResetBoxes();

    for (unsigned int i = colideList.size(); i; i--)
    {
      PhysicObject *tempObj = colideList.front();
      colideList.pop_front();
      if (CheckColitions(tempObj) && (tempObj != this))
      {
        posX -= speedX;
        ResetBoxes();
      }
      colideList.push_back(tempObj);
    }

    posY += speedY;
    ResetBoxes();

    for (unsigned int i = colideList.size(); i; i--)
    {
      PhysicObject *tempObj = colideList.front();
      colideList.pop_front();
      if (CheckColitions(tempObj) && (tempObj != this))
      {
        posY -= speedY;
        speedY -= lastGravityAceleration;
        ResetBoxes();
      }
      colideList.push_back(tempObj);
    }

    ResetBoxes();
  }
}

void PhysicObject::ResetBoxes()
{
  //The previous row's height.
  int previousHeight= 0;

	int size = colitionBoxes.size();
  //Set all the collition boxses.
  for( unsigned int i = colitionBoxes.size(); i; i--)
  {
    //Center the collison boxes
    colitionBoxes[size - i].x = posX + (oWidth - colitionBoxes[size - i].w)/2;

    //Set box'es the position.
    colitionBoxes[size - i].y = posY - previousHeight;

    //Move the row offset down the height of the collision box
    previousHeight += colitionBoxes[size -i].h;
  }
}

void PhysicObject::setSpeed(int x, int y)
{
	speedX = x;
	speedY = y;
	moving = true;
}

 void PhysicObject::setPosition(unsigned int x, unsigned int y)
 {
  //Set position.
	posX = x;
	posY = y;
  this->ResetBoxes();
 }

void PhysicObject::setSelected(bool sel)
{
    selected = sel;
}

void PhysicObject::storePosX()
{
  storedPosX = posX;
}

void PhysicObject::storePosY()
{
  storedPosY = posY;
}

 void PhysicObject::restorePosX()
  {
      posX = storedPosX;
      ResetBoxes();
  }

 void PhysicObject::restorePosY()
 {
       posY = storedPosY;
       ResetBoxes();
 }
