/*
 * File:   Scenery.cpp
 * Author: geru
 *
 * Created on April 25, 2009, 12:29 AM
 */

#include "../include/scenery.hpp"
#include <fstream>

Scenery::Scenery(unsigned int startX, unsigned int startY, std::string n)
    : PhysicObject(startX, startY, 0, 0, 0)
{
  name = n;

	std::string fileName ("resources/config/scenery/");
	fileName += n;
	fileName += ".cfg";

  std::fstream loadFile;
  std::string line;
	std::string imgName;
  loadFile.open(fileName.c_str());

  const char *temp;

  getline(loadFile, line);
  temp = line.data();
  int numImgs = atoi(temp);

	animationVector.resize(1);

	for (;numImgs; numImgs--)
	{
    getline(loadFile, line);
    imgName = line.data();
	  animationVector[0].imageList.push_back(imgName);
	}

  getline(loadFile, line);
  temp = line.data();
  unsigned int x = atoi(temp);

  getline(loadFile, line);
  temp = line.data();
  unsigned int y = atoi(temp);

  getline(loadFile, line);
  temp = line.data();
  unsigned int w = atoi(temp);
  oWidth = w;

  getline(loadFile, line);
  temp = line.data();
  unsigned int h = atoi(temp);
  oHeight = h;

	animationVector[0].horizontalFlip = false;
	animationVector[0].verticalFlip = false;

  //create character colition box.

	colitionBoxes.resize(1);
  colitionBoxes[0].x = x;
  colitionBoxes[0].y = y;
  colitionBoxes[0].w = w;
  colitionBoxes[0].h = h;

  LoadAnimations();

  ResetBoxes();
}

