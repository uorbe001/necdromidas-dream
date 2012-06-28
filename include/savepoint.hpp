/*
 * File:   savepoint.h
 * Author: geru
 *
 * Created on April 25, 2009, 12:29 AM
 */

#include "../include/physicobject.hpp"

#ifndef _SAVEPOINT_HPP
#define	_SAVEPOINT_HPP

class SaveGameDialog;

class SavePoint: public PhysicObject{
public:
    SavePoint(unsigned int startX, unsigned int startY, char* n, SaveGameDialog *sav);

    virtual void ColitionEvent();
private:
    SaveGameDialog *savegame;
};

#endif	/* _SAVEPOINT_HPP */
