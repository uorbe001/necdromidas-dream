/*
 * listener.hpp
 * Copyright (C) Unai Orbe 2009 <uorbe001@gmail.com>
 *
 * main.cc is free software: you can redistribute it and/or modify it
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

#ifndef LISTENER_HPP
#define LISTENER_HPP

union SDL_Event;

class Listener
{
  public:
    Listener()
    {
      //Starts ok.
      isOk = true;
    }
    virtual ~Listener() {}

    //returns if the listener is ok.
    bool IsOk() {return isOk;}
    //Function to edit the controls.
    virtual void ListenNextFrame(SDL_Event *event) = 0;

  protected:
    bool isOk;
};

#endif /* LISTENER_HPP */
