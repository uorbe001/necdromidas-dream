
/*
 * fire.hpp
 * Copyright (C) Unai Orbe 2009 <uorbe001@gmail.com>
 *
 * fire.hpp is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * main.cc is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received[NUM_STATES] a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#ifndef PARTICLESYSTEM_HPP
#define PARTICLESYSTEM_HPP

#include "../include/entity.hpp"
#include "../include/enums.hpp"
#include <SDL/SDL.h>
#include <list>

class ParticleSystem
{
	public:
		ParticleSystem();
		~ParticleSystem();

		//Adds particles to the system.
		virtual void AddParticles(Entity* particle);
		//Shows the selected particle in that place until the animation is over.
		//returns succeed, posX,posY are the position to draw it and part the particle's name.
		virtual bool StartParticle(std::string part, unsigned int posX, unsigned int posY);
    //Draw the active entity to screen nextImage sets if we have to change to the next animation frame.
		virtual void Draw(bool nextImg, SDL_Surface *screen);
		//returns if there's an active particle.
		inline bool getActive() { return active;};
	protected:
		//Pointer to the active particle.
		Entity* activeParticle;
		//Particles list.
		std::list<Entity*> particles;
		//Sets if there's an active particle.
		bool active;
};

#endif /* PARTICLESYSTEM_HPP */
