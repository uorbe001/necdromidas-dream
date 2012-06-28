/*
 * clock.hpp
 * Copyright (C) Unai Orbe 2009 <uorbe001@gmail.com>
 *
 * clock.hpp is free software: you can redistribute it and/or modify it
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

#ifndef CLOCK_HPP
#define CLOCK_HPP

class Clock
{
  public:
    Clock() : started(false) {}
    ~Clock() {}

    // Return ticks
    long int getTicks();

    // Start the clock
    void Start();
    // Stop the clock.
    void Stop() {started = false;}

  private:
    // Sets if the clock is working.
    bool started;
    // Cliks when started.
    unsigned int startTicks;
};

#endif /* CLOCK_HPP */
