#include "../include/chest.hpp"
#include "../include/physicobject.hpp"
#include <list>
#include <fstream>

Chest::Chest(unsigned int posX, unsigned int posY, std::string nam, TextBubble *bub)
	:PhysicObject(posX, posY, 0,0,0)
{
  //Initialize  NPC
  bubble = bub;
  name = nam;
  talking = false;
  //Reacts to colitions.
  reactToColition = true;

	std::string fileName ("resources/config/scenery/");
	fileName += nam;
	fileName += ".cfg";

  std::fstream loadFile;
  std::string line;
	std::string text;
  loadFile.open(fileName.c_str());

  const char *temp;

  //Set the animations.
  getline(loadFile, line);
  temp = line.data();
  int numImgs = atoi(temp);

	animationVector.resize(2);

	for (;numImgs; numImgs--)
	{
    getline(loadFile, line);
    temp = line.data();
	  animationVector[0].imageList.push_back(temp);
	}

  //Set the animations.
  getline(loadFile, line);
  temp = line.data();
  numImgs = atoi(temp);

	for (;numImgs; numImgs--)
	{
    getline(loadFile, line);
    temp = line.data();
	  animationVector[1].imageList.push_back(temp);
	}

  //Set the text it says.
  getline(loadFile, line);
  temp = line.data();
  int numMsg = atoi(temp);

	for (;numMsg; numMsg--)
	{
    getline(loadFile, line);
    text = line.data();
	  speakList.push_back(text);
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
	animationVector[1].verticalFlip = false;
	animationVector[1].horizontalFlip = false;

  //create character colition box.

	colitionBoxes.resize(1);
  colitionBoxes[0].x = x;
  colitionBoxes[0].y = y;
  colitionBoxes[0].w = w;
  colitionBoxes[0].h = h;

  LoadAnimations();

  ResetBoxes();
}

Chest::~Chest()
{
}

void Chest::ColitionEvent()
{
  //only want to talk to the party
  if (!talking)
  {
    animationVector[0].image[0] = animationVector[1].image[0];
    bubble->Say(speakList);
  }
}
