/*
 * entity.hpp
 * Copyright (C) Unai Orbe 2009 <uorbe001@gmail.com>
 *
 * entity.hpp is free software: you can redistribute it and/or modify it
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

#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <list>
#include <string>
#include <vector>

struct SDL_Surface;

struct Animation
{
  bool active, finished;
  bool horizontalFlip, verticalFlip; // Do we have to flip the image?
  // Pointers to the images needded for  tha animation.
  std::vector<SDL_Surface*> image;
  // List of images to load to the vector
  std::list<std::string> imageList;
  // Sets the next frame in the list.
  unsigned int nextFrame;
  // Stores the number of frames in the animation.
  unsigned int numFrames;
};

class Entity
{
  public:
    virtual ~Entity();

    // Function to draw text on screen.
    virtual void DrawText(SDL_Surface *screen) {}
    // Function to draw life bars or something else on screen.
    virtual void DrawBars(SDL_Surface *screen) {}
    // Draws the entity on screen and nextImg sets if we have to change to the next frame.
    virtual void Draw(bool nextImg, SDL_Surface *screen);
    // Draws nextImg to screen as the image for this entity.
    virtual void Draw(SDL_Surface* nextImg, SDL_Surface *screen);

    // Returns if the entity is ok.
    bool IsOk() {return entOk;}
    // Returns the last drawn image.
    SDL_Surface* getLastImage() {return lastImage;}
    // Returns the number of animations in the vector.
    unsigned int getNumAnimations() {return animationVector.size();}
    // Returns the entity position X coordinate.
    unsigned int getPosX() {return posX;}
    // Returns the entity position Y coordinate.
    unsigned int getPosY() {return posY;}
    // Returns the entity's name.
    std::string getName() {return name;}
    // returns if the entity is visible (default).
    bool getVisible() {return visible;}
    // Returns if there's "any" animation finished (except the default animation 0).
    bool getAnimationFinished() {return animationFinished;}
    // Returns if the animation in position i of the animation vector is finished.
    bool getAnimationFinished(unsigned int i);
    // Returns the next image to be drawn depending on advanceFrame to change to the next animation frame.
    virtual SDL_Surface* getNextImage(bool advanceFrame);

    // Sets position to x, y.
    virtual void setPosition(unsigned int x, unsigned int y);
    // Activates the animation in the animPos position of the vector.
    void setActiveAnimation(unsigned int animPos);
    // Stops the animation in the animPos position of the vector and starts the default animation 0.
    void setInactiveAnimation(unsigned int animPos);
    // Makes entity visible.
    void Show() {visible = true;}
    // Hides entity.
    void Hide() {visible = false;}

    // Loads the images needed for the animatiosn set in the animationVector for each animation,
    // loading the images set in the imageList
    virtual bool LoadAnimations();
    // Makes the entity's logic.
    virtual void Logic(float t) {}

  protected:
    // Constructor, startx starty set  the position.
    Entity(unsigned int startX, unsigned int startY);
    Entity() {}

    // The vector with all the animations for this entity.
    std::vector<Animation> animationVector;
    // Sets if the entity is fine.
    bool entOk;
    // True if there's any animation finished.
    bool animationFinished;
    // Entity name.
    std::string name;
    // entity position.
    unsigned int posX, posY;
    // Sets if the entity is visible.
    bool visible;
    // Pointer to the last draw image.
    SDL_Surface *lastImage;
};

#endif /* ENTITY_HPP */
