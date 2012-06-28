/*
 * physicobject.hpp
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


#ifndef PHYSICOBJECT_HPP
#define PHYSICOBJECT_HPP

#include <SDL/SDL.h>

#include "../include/entity.hpp"

class PhysicObject: public Entity
{
	public:
    //Contructor, startX startY set the position, widht weight and height those stats for the object.
    PhysicObject(int unsigned startX, unsigned int startY, unsigned int width, float weight, float height);
    //Contructor, startX startY set the position.
    PhysicObject(int unsigned startX, unsigned int startY);
    PhysicObject(){};

    //Acelerates the speed depending on the aceleration parameters and t time.
    void Acelerate(float t);
    //Returns true if there's a colition between this and obj object,
    // and makes this object react to the colition if it should.
    bool CheckColitions(PhysicObject *obj);
    //Checks if the object is inside the rec rectangle.
    bool CheckPos(SDL_Rect rec);
    //The event when there's a colition.
    virtual void ColitionEvent(){};
    //returns aceleration on x coord.
    inline float getAcelerationx(){return acelerationX;};
    //returns aceleration on y coord.
    inline float getAcelerationy(){return acelerationY;};
    //returns object height.
    inline unsigned int getHeight() {return oHeight;};
    //returns object widht.
    inline unsigned int getWidth() {return oWidth;};
    //returns the colition boxes list for this object.
    inline std::vector<SDL_Rect>& getRectangles(){return colitionBoxes;};
    //returns the speed on x coord.
    inline int getSpeedx(){return speedX;};
    //returns the speed on y coord.
    inline int getSpeedy(){return speedY;};
    //Stores the posX (only one position can be stored).
    void storePosX();
    //Stores the posY (only one position can be stored).
    void storePosY();
    //restores the position to the previously stored one.
    void restorePosX();
    //restores the position to the previously stored one.
    void restorePosY();
    //returns if the onject has been selected (by click, etc.)
    inline bool getSelected(){return selected;};
    //Returns object weight.
    inline float getWeight(){ return oWeight;};
    //Makes object be affected by gravity and time .
    virtual void Gravitate(float gravity, float t);
    //Move the object checking colitions with every object in the colideList.
    virtual void Move(std::list<PhysicObject*> colideList);
    //resets the colition boxes to their place depending on position.
    void ResetBoxes();
    //Sets the speed.
    void setSpeed(int x, int y);
    //sets if the object is selected.
    void setSelected(bool sel = true);
    //sets the position.
    virtual void setPosition(unsigned int x, unsigned int y);

    protected:
    //The object's speed and aceleration.
    int speedX, speedY;
    float acelerationX, acelerationY, lastGravityAceleration;
    //Object's weight and width.
    unsigned int oWidth;
    float oWeight, oHeight;
    //Sets whether the object reacts to colitions with event or not.
    bool reactToColition;
    //Sets if the object is selected by the mouse.
    bool selected;
    //The colition boxes.
    std::vector<SDL_Rect> colitionBoxes;
    //Stored positions
    unsigned int storedPosX, storedPosY;
    //name of the object that activated the colition event.
    std::string coliderName;
    //sets if the object is moving
    bool moving;
};

#endif /* PHYSICOBJECT_HPP */
