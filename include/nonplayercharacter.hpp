#ifndef NONPLAYERCHARACTER_HPP
#define NONPLAYERCHARACTER_HPP

#include "../include/character.hpp"
#include "../include/textbubble.hpp"
#include "../include/physicobject.hpp"


class PhysicObject;

class NonPlayerCharacter : public Character
{
  public:
    //Constructor, posX/posY set position, nam is the name, bub is the bubble where he will talk,
    // and flip sets wheter it will talk or not.
    NonPlayerCharacter(unsigned int posX, unsigned int posY, std::string nam, TextBubble *bub, bool flip = false);
    //Destructor
    ~NonPlayerCharacter() {}
    //The event that happens when the player colides with this object.
    virtual void ColitionEvent();

  protected:
    //text bubble pointer, where has to talk.
    TextBubble *bubble;
    //is it talking?
    bool talking;
    //List of things to say.
    std::list<std::string> speakList;

  };

#endif // NONPLAYERCHARACTER_HPP
