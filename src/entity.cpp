/*
 * entity.cpp
 * Copyright (C) Unai Orbe 2009 <uorbe001@gmail.com>
 *
 * entity.cpp is free software: you can redistribute it and/or modify it
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

#include "../include/entity.hpp"

#include <SDL/SDL.h>

#include "../include/engine.hpp"

Entity::~Entity()
{
  //Free all the loaded images.
  for (unsigned int i = animationVector.size(); i; i--)
    for (unsigned int j = animationVector[i-1].image.size(); j; j--)
      if (animationVector[i-1].image[j-1] != NULL)
        SDL_FreeSurface(animationVector[i-1].image[j-1]);
}

void Entity::Draw(bool nextImg, SDL_Surface *screen)
{
  if (visible)
  {
    SDL_Rect pos;

    pos.x = posX;
    pos.y = posY;

    SDL_BlitSurface(getNextImage(nextImg), NULL, screen, &pos);
  }
}

void Entity::Draw(SDL_Surface* nextImg, SDL_Surface *screen)
{
  if (visible)
  {
    SDL_Rect pos;

    pos.x = posX;
    pos.y = posY;

    SDL_BlitSurface(nextImg, NULL, screen, &pos);
  }
}

bool Entity::getAnimationFinished(unsigned int i)
{
    if (i >= animationVector.size())
      return false;
    else
      return animationVector[i].finished;
}

SDL_Surface* Entity::getNextImage(bool advanceFrame)
{
  // Go through all the animation vector.
  for (unsigned int i = animationVector.size(); i; i--)
  {
    // If animation is active ...
    if (animationVector[i-1].active)
    {
      // If we have to advance to the next image..
      if (advanceFrame)
      animationVector[i-1].nextFrame++;

      // If there's no next image to load in the animation, load the last one.
      if (animationVector[i-1].numFrames == animationVector[i-1].nextFrame)
      {
        animationVector[i-1].nextFrame = 0;
        animationVector[i-1].finished = true;

        lastImage = animationVector[i-1].image[animationVector[i-1].numFrames -1];
        return animationVector[i-1].image[animationVector[i-1].numFrames -1];
      }
      // Return the image.
      lastImage = animationVector[i-1].image[animationVector[i-1].nextFrame];
      return animationVector[i-1].image[animationVector[i-1].nextFrame];
    }
  }
  return NULL;
}

void Entity::setPosition(unsigned int x, unsigned int y)
{
  // Set position.
  posX = x;
  posY = y;
}

void Entity::setActiveAnimation(unsigned int animPos)
{
  // Set all the animations inactive
  for (short int i = animationVector.size(); i; i--)
  {
    animationVector[i-1].active = false;
    animationVector[i-1].finished = false;
  }
  // Set the animation as active.
  animationVector[animPos].active = true;
}

void Entity::setInactiveAnimation (unsigned int animPos)
{
  // Set the animation as inactive and not finished.
  animationVector[animPos].active = false;
  animationVector[animPos].finished = false;
}

bool Entity::LoadAnimations()
{
  if ((animationVector[0].image.empty()))
  {
    for (unsigned int animPos = 0; animPos < animationVector.size(); animPos++)
    {
      std::list<std::string> *imageList = &(animationVector[animPos].imageList);

      // Set innactive animation and non finished.
      animationVector[animPos].active = false;
      animationVector[animPos].finished = false;

      // Set last and next frames.
      animationVector[animPos].numFrames = imageList->size();
      animationVector[animPos].nextFrame = 0;

      // Initialize the animation vector's size
      animationVector[animPos].image.resize(animationVector[animPos].numFrames);

      // Load all the images in the images list.
      for (unsigned int i = 0; i < animationVector[animPos].numFrames; i++)
      {
        animationVector[animPos].image[i] = Engine::LoadImage(imageList->front());

        if (animationVector[animPos].horizontalFlip)
          animationVector[animPos].image[i] = Engine::HorizontalFlipImage(animationVector[animPos].image[i]);
        else if (animationVector[animPos].verticalFlip)
          animationVector[animPos].image[i] = Engine::VerticalFlipImage(animationVector[animPos].image[i]);

        // If the image isn't loaded report problem.
        if (animationVector[animPos].image[i] == NULL)
        return false;

        // Take the loaded image out of the list.
        imageList->pop_front();
      }
    }
  }
  // Set the default animation active.
  animationVector[0].active = true;
  return true;
}

Entity::Entity(int unsigned startX, unsigned int startY)
{
  // Entity starts ok and is visible
  entOk = true;
  visible = true;
  // No active animation is finished.
  animationFinished = false;
  // Set start position
  posX = startX;
  posY = startY;
  // Set default name
  name = "Unnamed";
}
