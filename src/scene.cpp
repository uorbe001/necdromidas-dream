/*
 * scene.cpp
 * Copyright (C) Unai Orbe 2009 <uorbe001@gmail.com>
 *
 * scene.cpp is free software: you can redistribute it and/or modify it
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

#include "../include/scene.hpp"
#include "../include/entity.hpp"
#include "../include/physicobject.hpp"
#include <iostream>


Scene::Scene(Switch *sw, unsigned int scnWidth, unsigned int scnHeight, unsigned int scrWidth, unsigned int scrHeight)
{
  swtch = sw;
  sceneHeight = scnHeight;
  sceneWidth = scnWidth;
  screenHeight = scrHeight;
  screenWidth = scrWidth;
  active = false;
  background = NULL;

  // Start the gravity to 0 by default.
  gravity = 0;

  // Set the clock and time counter.
  timeSeconds = 0;
  timeMinutes = 0;
}

Scene::~Scene()
{
  if (background) SDL_FreeSurface(background);
  // Cleans up the used resources.
  std::cout<<"Unloading resources..."<<std::endl;
  if (!UnLoadResources())
    std::cout<<"Error:: Unloading resources failed!"<<std::endl;
}

bool Scene::AddEntity(Entity *ent)
{
  // Adds entity to the list.
  Entities.push_back(ent);
  if (!(Entities.back()->IsOk()))
  {
    std::cout<<"ERROR: Failed to add entity "<<ent->getName()<<std::endl;
    isOk = false;
  }
  return isOk;
}

bool Scene::AddPhysicObject(PhysicObject *obj)
{
  // Adds object to the list.
  PhysicObjects.push_back(obj);
  if (!(PhysicObjects.back()->IsOk()))
  {
    std::cout<<"ERROR: Failed to add physic object "<<obj->getName()<<std::endl;
    isOk = false;
  }
  return isOk;
}

void Scene::Logic(float t)
{
  // If the gravity isn't 0.
  if (gravity != 0)
  {
    // Make gravity affect all the physic objects.
    for (unsigned int i = PhysicObjects.size(); i; i--)
    {
      PhysicObject *tempObj = PhysicObjects.front();
      PhysicObjects.pop_front();
      tempObj->Gravitate(gravity, t);
      PhysicObjects.push_back(tempObj);
    }
  }

  // Call the logic entities logic.
  for (unsigned int i = Entities.size(); i; i--)
  {
    Entity *tempEnt = Entities.front();
    Entities.pop_front();
    tempEnt->Logic(t);
    Entities.push_back(tempEnt);
  }

  static float ti = 0;
  ti += t;

  if (ti > 10)
  {
    timeSeconds += t;
    ti -= 10;
  }
  if (timeSeconds >= 60 )
  {
    timeSeconds -= 60;
    timeMinutes += 1;
  }
}

void Scene::ResetAnimations()
{
  for (unsigned int i = Entities.size(); i; i--)
  {
    Entity *tempEnt = Entities.front();
    Entities.pop_front();
    tempEnt->setActiveAnimation(0);
    Entities.push_back(tempEnt);
  }
}

void Scene::Draw(bool nextImg, SDL_Surface *screen)
{
  // Move the objects before drawing.
  for (unsigned int i = PhysicObjects.size(); i; i-- )
  {
      PhysicObject* tempObj = PhysicObjects.front();
      PhysicObjects.pop_front();
      tempObj->Move(PhysicObjects);
      PhysicObjects.push_back(tempObj);
  }

  if (background)
  {
    // Draw the background.
    SDL_Rect *pos = new SDL_Rect;
    pos->x = 0;
    pos->y = 0;

    SDL_BlitSurface(background, NULL, screen, pos);
  }

  // Draw the enities.
  for (unsigned int i = Entities.size(); i; i-- )
  {
    Entity* tempEnt = Entities.front();
    Entities.pop_front();

    tempEnt->Draw(nextImg, screen);

    Entities.push_back(tempEnt);
  }
}

bool Scene::LoadResources()
{
  for (unsigned int i = Entities.size(); i; i--)
  {
    Entity *tempEnt = Entities.front();
    Entities.pop_front();

    if (!(tempEnt->LoadAnimations()))
      return false;

    Entities.push_back(tempEnt);
  }
  return true;
}

bool Scene::UnLoadResources()
{
  for (unsigned int i = Entities.size(); i; i--)
  {
    Entity *tempEnt = Entities.front();
    delete tempEnt;
    Entities.pop_front();
  }
  return true;
}
