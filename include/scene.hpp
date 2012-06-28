/*
 * scene.hpp
 * Copyright (C) Unai Orbe 2009 <uorbe001@gmail.com>
 *
 * scene.hpp is free software: you can redistribute it and/or modify it
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

#ifndef SCENE_HPP
#define SCENE_HPP

#include <list>

#include "../include/listener.hpp"

struct SDL_Surface;
union SDL_Event;

class Entity;
class PhysicObject;
class Switch;

class Scene: public Listener
{
  public:
    Scene(Switch *sw, unsigned int scnWidth = 640, unsigned int scnHeight = 480, unsigned int scrWidth = 640, unsigned int scrHeight = 480);
    virtual ~Scene();

    bool AddEntity(Entity *ent);
    bool AddPhysicObject(PhysicObject *obj);

    bool IsActive() {return active;}
    virtual void setActive(bool a = true) {active = a;}

    virtual void Logic(float t);

    virtual void ResetAnimations();
    virtual void Draw(bool nextImg, SDL_Surface *screen);

    virtual void ListenNextFrame(SDL_Event *event) {}

  protected:
    virtual bool LoadResources();
    virtual bool UnLoadResources();

    // Says wether the scene is active or not.
    bool active;
    // The Scene Background.
    SDL_Surface *background;
    // Entity List on scene.
    std::list<Entity*> Entities;
    // Gravity affecting the level.
    float gravity;
    // Physic object list.
    std::list<PhysicObject*> PhysicObjects;
    // The width and height in the scene or level.
    unsigned int sceneWidth;
    unsigned int sceneHeight;
    // The screen's width and height.
    unsigned int screenWidth;
    unsigned int screenHeight;
    // Swith to change screen.
    Switch *swtch;

    unsigned short int timeSeconds, timeMinutes;
};

#endif /* SCENE_HPP */
