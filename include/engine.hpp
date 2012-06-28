/*
 * engine.hpp
 * Copyright (C) Unai Orbe 2009 <uorbe001@gmail.com>
 *
 * engine.hpp is free software: you can redistribute it and/or modify it
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

#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <list>
#include <string>

#include <SDL/SDL_mixer.h>

struct SDL_Surface;
union SDL_Event;

class Clock;
class CombatLevel;
class Menu;
class Scene;
class Window;
class World;

class Engine
{
  public:
    // Creates window with $name name, widht, height dimensions, and bpp bits per pixel, starts the engine.
    Engine(char* name,unsigned int width = 640, unsigned int height = 480, unsigned int bpp = 32);
    ~Engine();

    // Returs pointer to the window.
    Window* getWindow() {return window;}
    // Returns pointer to the world.
    World* getWorld() {return world;}

    // Sets world active or innactive.
    void setWorldActive(bool a = true);

    // Add a menu to the menu list.
    bool AddMenu(Menu *menu);
    // Add world to the engine.
    bool AddWorld(World *w);

    // Changes the rendering to he menu with $menuName name.
    void SwitchToMenu(char* menuName);
    // Changes the rendering to the lvl scene.
    void SwitchToLevel(Scene *lvl);
    // Changes the rendering to the lvl scene.
    void SwitchToCombatLevel(CombatLevel *lvl);
    // Changes the rendering to world.
    void SwitchToWorld();

    // Function with the main loop calling events, logic, draw, etc.
    void Render();

    // Function used to load an image in the route $name.
    static SDL_Surface* LoadImage(std::string name);
    // Returns a horizontally flipped copy of the image s.
    static SDL_Surface* HorizontalFlipImage(SDL_Surface *s);
    // Returns a vertically flipped copy of the image s.
    static SDL_Surface* VerticalFlipImage(SDL_Surface *s);

    // Opens a mixer for the sound.
    void OpenMixer();
    // Loads a song in the route $song.
    void LoadMusic(const char *song);
    // Loads a song in the route $song.
    static Mix_Music* LoadStaticMusic(const char *song);
    // Stops the playing music.
    void StopMusic();
    // Stops playing $song.
    static void StopStaticMusic(Mix_Music *song);

  private:
    // Initializes sdl.
    bool Init();
    // Creates a window with the $name name, width, height and bpp bits per pixel.
    bool CreateWindow(char* name,unsigned int width, unsigned int height, unsigned int bpp);

    // Handles events in teh active listeners.
    int HandleEvents();

    // Calls the logic of the active scenes.
    void CalculateLogic(float t);

    // Draws the active scene, nextImg sets ifwe need to go to the next frame in animations.
    void Draw(bool nextImg);

    // Pointer to event.
    SDL_Event *event;
    // Sets if we have to exit the game.
    bool exit;
    // Menu list with all teh menu scenes we want preloaded.
    std::list<Menu*> listMenu;
    // Max number of frames per second.
    short int MAXFPS;
    // Pointer to the active level.
    Scene *level;
    // Pointer to the active combat level.
    CombatLevel *clevel;
    // Pointer to the engine clock.
    Clock *timer;
    // Pointer to the window where we draw.
    Window *window;
    // Pointer to the world.
    World *world;
    // Pointer to mixer.
    Mix_Music *music;
    // integer setting the audio channel.
    int channel;
};

#endif // ENGINE_HPP
