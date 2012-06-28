/*
 *      switch.hpp
 *
 *      Copyright 2009 Unai Orbe <uorbe001@gmail.com>
 *
 *      This program is free software; you can redistribute it and/or modify
 *      it under the terms of the GNU General Public License as published by
 *      the Free Software Foundation; either version 2 of the License, or
 *      (at your option) any later version.
 *
 *      This program is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *      GNU General Public License for more details.
 *
 *      You should have received a copy of the GNU General Public License
 *      along with this program; if not, write to the Free Software
 *      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 *      MA 02110-1301, USA.
 */

#ifndef SWITCH_HPP
#define SWITCH_HPP

#include "../include/engine.hpp"

class Switch
{
  public:
    Switch(Engine *eng) {engine = eng;}

    void SwitchToMenu(char* menuName) {engine->SwitchToMenu(menuName);}
    void SwitchToLevel(Scene *lvl) {engine->SwitchToLevel(lvl);}
    void SwitchToCombatLevel(CombatLevel *lvl) {engine->SwitchToCombatLevel(lvl);}
    void SwitchToWorld() {engine->SwitchToWorld();}
    void setWorlActive(bool a = true) {engine->setWorldActive(a);}
    World* getWorld() {return engine->getWorld();}

  private:
    Engine *engine;
};

#endif /* SWITCH_HPP */
