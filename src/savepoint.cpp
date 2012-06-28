/*
 * File:   savepoint.cpp
 * Author: geru
 *
 * Created on April 25, 2009, 12:29 AM
 */

#include "../include/savepoint.hpp"
#include "../include/savegamedialog.hpp"

SavePoint::SavePoint(unsigned int startX, unsigned int startY, char* n, SaveGameDialog *sav)
    : PhysicObject(startX, startY, 24, 0, 24)
{
  name = n;
  //Set the dialog it will use to save games.
  savegame = sav;

 //Reacts to colitions.
  reactToColition = true;

  //Load the animations.
	animationVector.resize(1);
	animationVector[0].imageList.push_back("resources/images/scenery/ball-blue.png");
	animationVector[0].horizontalFlip = false;
	animationVector[0].verticalFlip = false;

  //create character colition box.
	colitionBoxes.resize(1);
  colitionBoxes[0].x = 24;
  colitionBoxes[0].y = 24;
  colitionBoxes[0].w = 24;
  colitionBoxes[0].h = 24;

  ResetBoxes();
}

void SavePoint::ColitionEvent()
{
  //only want to talk to the party
  savegame->Show();
}
