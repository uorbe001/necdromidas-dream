/*
 * world.cpp
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

#include "../include/world.hpp"
#include "../include/engine.hpp"
#include "../include/switch.hpp"
#include "../include/textbubble.hpp"
#include "../include/bubblebutton.hpp"
#include "../include/savegamedialog.hpp"
#include "../include/party.hpp"
#include "../include/enemy.hpp"
#include "../include/tile.hpp"
#include "../include/combatlevel.hpp"
#include "../include/parser.hpp"
#include <fstream>
#include <time.h>

World::World(Switch *sw, unsigned int scrWidth, unsigned int scrHeight)
	: Scene(sw, scrWidth, scrHeight)
{
  //Set scene dimentions
	screenHeight = scrHeight;
	screenWidth = screenWidth;

  //Initialize variables
	zone = 0;
	danger = 0;

  //Load Images that may be used on the map
	if (!LoadTileImages())
		std::cout<<"ERROR: Could not load tile image!"<<std::endl;

	//Create speech dialog bubble.
	textBubble = new TextBubble();
	textBubble->LoadAnimations();
	textBubbleButton = new BubbleButton(450,420,(char*)"Continue");
	textBubbleButton->LoadAnimations();

  //Create party
	party = new Party( 73, 142, 25, 40, 0);

 //Create the savegame dialog.
  savegame = new SaveGameDialog(party);

  //Parse entities file.
  Parser *parser = new Parser(this, textBubble, savegame);
  parser->LoadXml((char*)"resources/map/secure_forest.xml");
  parser->LoadXml((char*)"resources/map/city.xml");
  parser->LoadXml((char*)"resources/map/forest.xml");
  parser->LoadXml((char*)"resources/map/plains.xml");
  parser->LoadXml((char*)"resources/map/cave.xml");
  delete parser;

  //Add party and characters
	AddEntity(party);
	AddPhysicObject(party);
	party->LoadAnimations();

  //Load map.
	if (!LoadMap((char*)"resources/map/world.map"))
		std::cout<<"ERROR: Could not load map!"<<std::endl;

  //load resources.
	if (!LoadResources())
		std::cout<<"ERROR: Could not load resources!"<<std::endl;
}

World::~World()
{
	for (short int i = NUM_TILES; i; i--)
	{
		SDL_FreeSurface(tileImages[i -1]);
	}
}

void World::GenerateRandomCombat(float time)
{
	static short int timeSinceLastCombat = 0;
	timeSinceLastCombat += time;

	if (((rand() % 2000 + 1) <= danger) && (timeSinceLastCombat >= 300))
	{
		timeSinceLastCombat = 0;

		unsigned int numEnemies = rand() % danger + danger;

		lastPartyPosition.x = party->getPosX();
		lastPartyPosition.y = party->getPosY();

		CombatLevel *clevel = new CombatLevel(swtch, screenWidth, screenHeight, party, zone);
		clevel->AddEnemy(numEnemies);
		swtch->SwitchToCombatLevel(clevel);
	}
}

void World::ListenNextFrame(SDL_Event *event)
{
	ResetAnimations();

  if (savegame->getVisible())
  {
    savegame->ListenNextFrame(event);
  }
  else if (textBubble->getVisible())
  {
    if ((event->type == SDL_MOUSEBUTTONUP) && (event->button.button == SDL_BUTTON_LEFT ))
    {
      int x = event->button.x;
			int	y = event->button.y;

      if (( x > textBubbleButton->box.x ) && ( x < textBubbleButton->box.x + textBubbleButton->box.w ) &&
                ( y > textBubbleButton->box.y ) && ( y < textBubbleButton->box.y + textBubbleButton->box.h ))
      {
        textBubble->ContinueMessage();
      }
    }

    if (event->type == SDL_MOUSEMOTION)
    {
      int x = event->motion.x;
      int y = event->motion.y;

      if (( x > textBubbleButton->box.x ) && ( x < textBubbleButton->box.x + textBubbleButton->box.w ) &&
															( y > textBubbleButton->box.y ) && ( y < textBubbleButton->box.y + textBubbleButton->box.h ))
      {
        textBubbleButton->setOver(true);
      }
      else
      {
        textBubbleButton->setOver(false);
      }
    }
  }
	else
	{
	  if( event->type == SDL_KEYDOWN )
    {
      switch( event->key.keysym.sym )
      {
        case SDLK_UP: party->WalkUp(); break;
        case SDLK_DOWN: party->WalkDown(); break;
        case SDLK_LEFT: party->WalkLeft(); break;
        case SDLK_RIGHT: party->WalkRight(); break;
        case SDLK_ESCAPE:{
                          break;}
        default:    break;
      }
    }

    if( event->type == SDL_KEYUP )
    {
      switch( event->key.keysym.sym )
      {
        case SDLK_UP: party->StopWalkUp(); break;
        case SDLK_DOWN: party->StopWalkDown(); break;
        case SDLK_LEFT: party->StopWalkLeft(); break;
        case SDLK_RIGHT: party->StopWalkRight(); break;

        default:    break;
      }
    }
	}
}

bool World::LoadMap(const char* mp)
{
	unsigned int x = 0, y = 0;

	//Open map.
	std::ifstream map(mp);

	if (map == NULL)
		return false;

	//Read the Tile's size from the file.
	unsigned int xSize = 0, ySize = 0;
	map >> xSize;
	map >> ySize;

	//Read the number of tiles in the file.
	unsigned int numTilesX = 0, numTilesY = 0, numTiles = 0;
	map >> numTilesX;
	map >> numTilesY;
	numTiles = numTilesX * numTilesY;

	//Set scene width and height according to the map.
	sceneWidth = xSize * numTilesX;
	sceneHeight = ySize * numTilesY;

	//Resize the tile vector to the number of tiles set in the map.
	tilesVector.resize(numTiles);

	int tileType;

	//Load tile types from file.
	for(unsigned int i = 0; i < numTiles ; i++)
	{
		tileType = -1;

		//Reading tiles..
		map >> tileType;

		//If load failed, return error.
		if (map.fail())
		{
			map.close();
			return false;
		}

		//If the tile type exists add it to the vector.
		if ((tileType >= 0) && (tileType < NUM_TILES))
		{
			tilesVector[i] = new Tile(x, y, xSize, ySize, tileType);
		}

		else
		{
			map.close();
			return false;
		}

		//Add the tiles width to the position of the next tile.
		x += xSize;

		if (((i % numTilesX == 0) && (i != 0)))
		{
			y += ySize;
			x = 0;
		}

	}

	map.close();
  return true;
}

bool World::LoadTileImages()
{
  //Load the images needed for every tile type.
	for (short int i = NUM_TILES; i; i--)
	{
		tileImages[i -1] = NULL;
	}

	tileImages[TCASTLE] = Engine::LoadImage("resources/images/tiles/castle.png");
	tileImages[TCASTLE_HF] = Engine::HorizontalFlipImage(Engine::LoadImage("resources/images/tiles/castle.png"));
	tileImages[TCASTLE_VF] = Engine::VerticalFlipImage (Engine::LoadImage("resources/images/tiles/castle.png"));
	tileImages[TCASTLE_FORESTA] = Engine::LoadImage("resources/images/tiles/castle-forest.png");
	tileImages[TCASTLE_FORESTB] = Engine::VerticalFlipImage (Engine::LoadImage("resources/images/tiles/castle-forest.png"));
	tileImages[TCASTLE_FORESTC] = Engine::HorizontalFlipImage(Engine::LoadImage("resources/images/tiles/castle-forest.png"));
	tileImages[TCASTLE_FORESTD] = Engine::VerticalFlipImage (tileImages[TCASTLE_FORESTC]);
	tileImages[TCASTLE_GRASSA] = Engine::LoadImage("resources/images/tiles/castle-grass.png");
	tileImages[TCASTLE_GRASSB] = Engine::VerticalFlipImage (Engine::LoadImage("resources/images/tiles/castle-grass.png"));
	tileImages[TCASTLE_GRASSC] = Engine::HorizontalFlipImage( Engine::LoadImage("resources/images/tiles/castle-grass.png"));
	tileImages[TCASTLE_GRASSD] = Engine::VerticalFlipImage (tileImages[TCASTLE_GRASSC]);
	tileImages[TCAVE] = Engine::LoadImage("resources/images/tiles/cave.png");
	tileImages[TCAVE_HF] = Engine::HorizontalFlipImage(Engine::LoadImage("resources/images/tiles/cave.png"));
	tileImages[TCAVE_VF] = Engine::VerticalFlipImage (Engine::LoadImage("resources/images/tiles/cave.png"));
	tileImages[TCAVE_FORESTA] = Engine::LoadImage("resources/images/tiles/cave-forest.png");
	tileImages[TCAVE_FORESTB] = Engine::VerticalFlipImage (Engine::LoadImage("resources/images/tiles/cave-forest.png"));
	tileImages[TCAVE_FORESTC] = Engine::HorizontalFlipImage( Engine::LoadImage("resources/images/tiles/cave-forest.png"));
	tileImages[TCAVE_FORESTD] = Engine::VerticalFlipImage (tileImages[TCAVE_FORESTC]);
	tileImages[TFOREST] = Engine::LoadImage("resources/images/tiles/forest.png");
	tileImages[TFOREST_HF] = Engine::HorizontalFlipImage(Engine::LoadImage("resources/images/tiles/forest.png"));
	tileImages[TFOREST_VF] = Engine::VerticalFlipImage (Engine::LoadImage("resources/images/tiles/forest.png"));
	tileImages[TFOREST_GRASSA] = Engine::LoadImage("resources/images/tiles/forest-grass.png");
	tileImages[TFOREST_GRASSB] = Engine::VerticalFlipImage (Engine::LoadImage("resources/images/tiles/forest-grass.png"));
	tileImages[TFOREST_GRASSC] = Engine::HorizontalFlipImage ( Engine::LoadImage("resources/images/tiles/forest-grass.png") );
	tileImages[TFOREST_GRASSD] = Engine::VerticalFlipImage (tileImages[TFOREST_GRASSC]);
	tileImages[TSECURE_FOREST] = Engine::LoadImage("resources/images/tiles/forest.png");
	tileImages[TSECURE_FOREST_HF] = Engine::HorizontalFlipImage(Engine::LoadImage("resources/images/tiles/forest.png"));
	tileImages[TSECURE_FOREST_VF] = Engine::VerticalFlipImage (Engine::LoadImage("resources/images/tiles/forest.png"));
	tileImages[TGRASS] = Engine::LoadImage("resources/images/tiles/grass.png");
	tileImages[TGRASS_HF] = Engine::HorizontalFlipImage(Engine::LoadImage("resources/images/tiles/grass.png"));
	tileImages[TGRASS_VF] = Engine::VerticalFlipImage (Engine::LoadImage("resources/images/tiles/grass.png"));


  //If a tile couldn't be laoded, report error.
	for (short int i = NUM_TILES; i; i--)
	{
		if (tileImages[i -1] == NULL)
			return false;
	}

	return true;
}

void World::Logic(float t)
{
	setZone();
	setDanger();

	if (!textBubble->getVisible())
    GenerateRandomCombat(t);

	//Call the logic entities logic.
  for (unsigned int i = Entities.size(); i; i--)
  {
    Entity *tempEnt = Entities.front();
    Entities.pop_front();
    tempEnt->Logic(t);
    Entities.push_back(tempEnt);
	}
}

void World::Draw(bool nextImg, SDL_Surface *screen)
{
	//Move the party before drawing.
  party->Move(PhysicObjects);

	SDL_Rect *camera = new SDL_Rect;

  //Center the camera over the party
  camera->x = (party->getPosX() + party->getWidth()) - screenWidth/2;
  camera->y = (party->getPosY()  + party->getHeight()) - screenHeight/2;
	camera->h = screenHeight;
	camera->w = screenWidth;

  //Keep the camera in bounds.
  if( camera->x < 0 )
    camera->x = 0;

  if( camera->y < 0 )
    camera->y = 0;

  if( camera->x  > sceneWidth - camera->w )
    camera->x = sceneWidth - camera->w;

  if( camera->y > sceneHeight - camera->h )
    camera->y = sceneHeight - camera->h;

	SDL_Rect pos;

	//Draw the tiles.
	for (unsigned int i = 0; i < tilesVector.size(); i++)
	{
		pos = tilesVector[i]->getRectangle();
		pos.x -= camera->x;
		pos.y -= camera->y;
      if ((pos.x < (camera->x + camera->w)) && (pos.y < (camera->y + camera->h))
                  && (pos.y > -100) && (pos.x > -100))
        SDL_BlitSurface(tileImages[tilesVector[i]->getType()], NULL, screen, &pos);
	}

	//Draw the enities.
  for (unsigned int i = Entities.size(); i; i-- )
  {
    Entity* tempEnt = Entities.front();
    Entities.pop_front();

		if (tempEnt->getVisible())
		{
			pos.x = tempEnt->getPosX() - camera->x;
			pos.y = tempEnt->getPosY() - camera->y;
			pos.w = 0;
			pos.h = 0;

      if ((pos.x < (camera->x + camera->w)) && (pos.y < (camera->y + camera->h))
                  && (pos.y > -100) && (pos.x > -100))
        SDL_BlitSurface( tempEnt->getNextImage(nextImg), NULL, screen, &pos);
		}
		Entities.push_back(tempEnt);
  }



	//If the bubble is visible show control message.
	if (textBubble->getVisible())
  {
    //Update the bubble position.
    textBubbleButton->Show();
    party->setSpeed(0,0);
    party->setActiveAnimation(0);
    textBubble->Draw(false,screen);
    textBubbleButton->Draw(true, screen);
    textBubbleButton->DrawText(screen);
  }
  else
    textBubbleButton->Hide();

  if (savegame->getVisible())
  {
    party->setSpeed(0,0);
    party->setActiveAnimation(0);
    savegame->Draw(true, screen);
  }

  delete camera;
}

void World::setActive(bool a)
{
	party->StopWalkUp();
	party->StopWalkDown();
	party->StopWalkRight();
	party->StopWalkLeft();
	active = a;
}

void World::setZone()
{
  std::vector<SDL_Rect> recs = party->getRectangles();

	for (short int i = tilesVector.size(); i; i--)
	{
		for (short int j = recs.size(); j; j-- )
		{
			if (party->CheckPos(tilesVector[i-1]->getRectangle()) )
			{
				if (tilesVector[i-1]->getType() == TCASTLE)
          zone = CITY;
				else if (tilesVector[i-1]->getType() == TFOREST)
					zone = FOREST;
				else if (tilesVector[i-1]->getType() == TSECURE_FOREST)
					zone = CITY;
				else if (tilesVector[i-1]->getType() == TGRASS)
					zone = PLAIN;
				else if (tilesVector[i-1]->getType() == TCAVE)
					zone = CAVE;
			}
		}
	}
}

void World::setDanger()
{
	danger = zone;
	if (night)
		danger++;
}

/*

Party* World::modifyParty(int posX, int posY){
    party->setPosition(posX, posY);
    return party;
}
*/
