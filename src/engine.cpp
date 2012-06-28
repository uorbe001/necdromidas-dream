/*
 * engine.cpp
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

#include "../include/engine.hpp"

#include <SDL/SDL_image.h>
#include <SDL/SDL_rotozoom.h>
#include <SDL/SDL_ttf.h>

#include "../include/clock.hpp"
#include "../include/combatlevel.hpp"
#include "../include/mainmenu.hpp"
#include "../include/window.hpp"
#include "../include/world.hpp"

Engine::Engine(char* name, unsigned int width , unsigned int height, unsigned int bpp)
{
  // Initialize SDL.
  if (!Init())
    std::cout<<"ERROR: Could not start SDL system!"<<std::endl;

  // Start the window.
  if (!CreateWindow(name, width, height, bpp))
    std::cout<<"ERROR: Failed to start window!"<< std::endl;

  // Start the event.
  event = new SDL_Event;

  // Start clock.
  timer = new Clock();

  // Set MaxFPS.
  MAXFPS = 60;

  // Set the level and combat level pointer to null.
  level = NULL;
  clevel = NULL;
}

Engine::~Engine()
{
  // Clean.
  std::cout<<"Cleaning up..."<<std::endl;
  delete event;
  delete timer;
  delete window;

  // Close SDL.
  std::cout<<"Closing SDL system..."<<std::endl;
  SDL_Quit();
}

void Engine::setWorldActive(bool a)
{
  world->setActive(a);
}

bool Engine::AddMenu(Menu *menu)
{
  std::cout<<"Adding menu..."<<std::endl;
  listMenu.push_back(menu);
  if (!listMenu.back()->IsOk())
  {
    return false;
    std::cout<<"Error: Could not add menu!";
  }
  return true;
}

bool Engine::AddWorld(World *w)
{
  std::cout<<"Adding world..."<<std::endl;
  world = w;
  if (!world->IsOk())
  {
    std::cout<<"Error: Could not add World!";
    return false;
  }
  return true;
}

void Engine::SwitchToMenu(char* menuName)
{
  for (unsigned int i = listMenu.size(); i; i--)
  {
    Menu *tempMenu = listMenu.front();
    listMenu.pop_front();
    listMenu.push_back(tempMenu);
    if (!(strcmp(tempMenu->getName(), menuName)))
    {
      tempMenu->setActive();
      LoadMusic("resources/music/main_menu.ogg");
      return;
    }
  }
}

void Engine::SwitchToLevel(Scene *lvl)
{
  level = lvl;
  level->setActive();
}

void Engine::SwitchToCombatLevel(CombatLevel *lvl)
{
  clevel = lvl;
  clevel->setActive();
  StopMusic();
  LoadMusic("resources/music/combates.ogg");
}

void Engine::SwitchToWorld()
{
  world->setActive();
  StopMusic();
  LoadMusic("resources/music/mapa.ogg");
}

void Engine::Render()
{
  // Frame counter.
  unsigned int frames = 0;

  // If we don't have to exit...
  while (!exit)
  {
    // Start clock time
    timer->Start();

    // Clean the screen on black.
    SDL_FillRect( window->getScreen(), &(window->getScreen()->clip_rect), SDL_MapRGB( window->getScreen()->format, 0x00, 0x00, 0x00 ) );

    // Handle input events.
    HandleEvents();

    // Logic.
    CalculateLogic((timer->getTicks()));

    // Every 10 frames change the animations to the next img.
    if (frames == 10)
    {
      Draw(true);
      frames = 0;
    }
    else
      Draw(false);

    // If there are more than the MaxFPS, wait.
    if (timer->getTicks() < (1000/MAXFPS))
      SDL_Delay((1000/MAXFPS) - timer->getTicks());

    // Flip the screen.
    SDL_Flip(window->getScreen());

    // Stop clock time
    timer->Stop();
    frames++;
  }
}

SDL_Surface* Engine::LoadImage(std::string name)
{
  // Initializes the surfaces we need.
  SDL_Surface *loadedImage = NULL;
  SDL_Surface *goodImage = NULL;

  // Load image file.
  loadedImage = IMG_Load(name.c_str());

  if (loadedImage != NULL)
  {
    // Optimize image.
    goodImage = SDL_DisplayFormatAlpha(loadedImage);

    // Clean the loaded image's surface.
    SDL_FreeSurface(loadedImage);
  }
  else
    std::cout<<"Could not load image!"<<std::endl;

  return goodImage;
}

SDL_Surface* Engine::HorizontalFlipImage(SDL_Surface *s)
{
  return zoomSurface(s, -1, 1, 0);
}

SDL_Surface* Engine::VerticalFlipImage(SDL_Surface *s)
{
  return zoomSurface(s, 1, -1, 0);
}

void Engine::OpenMixer()
{
  if(Mix_OpenAudio(22050, AUDIO_S16, 2, 4096))
  {
    std::cout << "Could not open Audio system" << std::endl;
    SDL_GetError();
  }
}

void Engine::LoadMusic(const char *song) 
{
  music = Mix_LoadMUS(song);
  channel = Mix_PlayMusic(music, -1);
}

Mix_Music* Engine::LoadStaticMusic(const char *song)
{
  Mix_Music *menu_music = Mix_LoadMUS(song);
  /*int m_channel = */Mix_PlayMusic(menu_music, -1);
  return menu_music;
}

void Engine::StopMusic()
{
  Mix_HaltMusic();
  Mix_FreeMusic(music);
}

void Engine::StopStaticMusic(Mix_Music *song)
{
  Mix_HaltMusic();
  Mix_FreeMusic(song);
}

bool Engine::Init()
{
  // Initialize SDL
  std::cout<<"Initializing SDL system..."<< std::endl;
  if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    return false;

  // Initialize SDL_ttf
  if( TTF_Init() == -1 )
    return false;

  OpenMixer();

  return true;
}

bool Engine::CreateWindow(char* name,unsigned int width, unsigned int height, unsigned int bpp)
{
  // Allocates memory for window and creates it.
  std::cout<<"Creating window..."<< std::endl;
  window = new Window( name, exit, width, height, bpp);
  return window->IsOk();
}

int Engine::HandleEvents()
{
  while (SDL_PollEvent(event))
  {
    window->ListenNextFrame(event);
    if ((clevel != NULL) && (clevel->IsActive()))
      clevel->ListenNextFrame(event);
    else if ((level != NULL) && (level->IsActive()))
      level->ListenNextFrame(event);
    else if (world->IsActive())
      world->ListenNextFrame(event);
    else
    {
      for (unsigned int i = listMenu.size(); i; i--)
      {
        world->ListenNextFrame(event);
        Menu *tempMenu = listMenu.front();
        listMenu.pop_front();

        if (tempMenu->IsActive())
          tempMenu->ListenNextFrame(event);

        listMenu.push_back(tempMenu);
      }
    }
  }
  return 0;
}

void Engine::CalculateLogic(float t)
{
  // If the secondary level or combat level aren't ok, delete them.
  if ((clevel != NULL) && (!clevel->IsOk()))
  {
    delete clevel;
    clevel = NULL;
  }
  else if ((level != NULL) && (!level->IsOk()))
  {
    delete level;
    level = NULL;
  }

  if ((clevel != NULL) && (clevel->IsActive()))
    clevel->Logic(t);
  else if ((level != NULL) && (level->IsActive()))
    level->Logic(t);
  else if (world->IsActive())
    world->Logic(t);
  else
  {
    for (unsigned int i = listMenu.size(); i; i--)
    {
      Menu *tempMenu = listMenu.front();
      listMenu.pop_front();

      if (tempMenu->IsActive())
        tempMenu->Logic(t);

      listMenu.push_back(tempMenu);
    }
  }
}

void Engine::Draw(bool nextImg)
{
  if ((clevel != NULL) && (clevel->IsActive()))
    clevel->Draw(nextImg, window->getScreen());
  else if ((level != NULL) && (level->IsActive()))
    level->Draw(nextImg, window->getScreen());
  else if (world->IsActive())
  {
    world->Draw(nextImg, window->getScreen());
  }
  else
  {
    for (unsigned int i = listMenu.size(); i; i--)
    {
      Menu *tempMenu = listMenu.front();
      listMenu.pop_front();

      if (tempMenu->IsActive())
        tempMenu->Draw(nextImg, window->getScreen());

      listMenu.push_back(tempMenu);
    }
  }
}
