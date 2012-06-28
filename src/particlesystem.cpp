
#include"../include/particlesystem.hpp"

ParticleSystem::ParticleSystem()
{
	//initialize the list.
	particles.clear();
	activeParticle = NULL;
	active = false;
}

ParticleSystem::~ParticleSystem()
{
	Entity *tempEnt;

	for (short int i = particles.size(); i; i--)
	{
		tempEnt = particles.front();
		particles.pop_front();
		delete tempEnt;
	}
}
void ParticleSystem::AddParticles(Entity* particle)
{
	//Put new particle in the list.
 	particles.push_back(particle);
}

bool ParticleSystem::StartParticle(std::string part, unsigned int posX, unsigned int posY)
{
	Entity *tempEnt;

	for (short int i = particles.size(); i; i--)
	{
		tempEnt = particles.front();
		particles.pop_front();

		if (tempEnt->getName() == part)
		{
			tempEnt->Show();
			tempEnt->setPosition(posX, posY);
			tempEnt->setActiveAnimation(0);
			activeParticle = tempEnt;
			active = true;
		}

		particles.push_back(tempEnt);
	}

	return true;
}

void ParticleSystem::Draw(bool nextImg, SDL_Surface *screen)
{
	if (active && (activeParticle->getAnimationFinished(0)))
	{
		activeParticle->Hide();
		active = false;
	}
	else if (active)
		activeParticle->Draw(nextImg, screen);
}
