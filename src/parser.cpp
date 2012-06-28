/*
 * File:   parser.cpp
 * Author: geru
 *
 * Created on April 25, 2009, 12:25 AM
 */

#include <iostream>

#include "../include/parser.hpp"
#include "../include/nonplayercharacter.hpp"
#include "../include/savepoint.hpp"
#include "../include/savegamedialog.hpp"
#include "../include/scenery.hpp"
#include "../include/chest.hpp"
#include "../include/scene.hpp"
#include "../include/physicobject.hpp"

Parser::Parser(Scene *s, TextBubble  *bub, SaveGameDialog  *sav)
{
  scene = s;
  bubble = bub;
  savegame =  sav;
}


void Parser::LoadTabs()
{
  Tabs.push_back("<savepoint>");
  Tabs.push_back("<scenery>");
  Tabs.push_back("<NPC>");
  Tabs.push_back("<chest>");
}

bool Parser::ManageTab(std::string line, std::string tab)
{
  //Rellenar Struct correspondiente a la etiqueta, crear constructor, añadir a scene y resetear datos struct.

  std::string posX = "<posX>";
  std::string end_posX = "</posX>";
  std::string posY = "<posY>";
  std::string end_posY = "</posY>";
  std::string name = "<name>";
  std::string end_name = "</name>";

  /*posX*/
  int init = line.find(posX) + posX.size();
  int limit = line.find(end_posX);
  posX = line.substr(init,limit-init);
  const char *pX = posX.data();
  /*posY*/
  init = line.find(posY) + posY.size();
  limit = line.find(end_posY);
  posY = line.substr(init,limit-init);
  const char *pY = posY.data();
  /*Name*/
  init = line.find(name) + name.size();
  limit = line.find(end_name);
  char *n = strdup((line.substr(init, limit-init)).c_str());

  if (tab == "<NPC>")
  {
    personStruct p_struct;

    std::string flip = "<flip>";
    std::string end_flip = "</flip>";

    p_struct.x = atoi(pX);
    p_struct.y = atoi(pY);
    p_struct.name = n;

    /*flip*/
    init = line.find(flip) + flip.size();
    limit = line.find(end_flip);
    flip = line.substr(init,limit-init);
    const char *f = flip.data();
    p_struct.flip = atoi(f);

    std::cout<<p_struct.name<<std::endl;

    NonPlayerCharacter *npc = new NonPlayerCharacter(p_struct.x, p_struct.y, p_struct.name,bubble ,p_struct.flip);
    scene->AddPhysicObject(npc);
    scene->AddEntity(npc);
  }
  else if (tab == "<savepoint>" || tab == "<scenery>" || tab == "<chest>")
  {
    BuildingStruct b_struct;

    b_struct.x = atoi(pX);
    b_struct.y = atoi(pY);
    b_struct.name = n;

    if (tab == "<savepoint>")
    {
      SavePoint *sp = new SavePoint(b_struct.x, b_struct.y, b_struct.name, savegame);
      scene->AddPhysicObject(sp);
      scene->AddEntity(sp);
    }
    else if (tab == "<scenery>")
    {
      Scenery *s = new Scenery(b_struct.x, b_struct.y, b_struct.name);
      scene->AddPhysicObject(s);
      scene->AddEntity(s);
    }
    else // tab == "<chest>"
    {
      Chest *c = new Chest(b_struct.x, b_struct.y, b_struct.name, bubble);
      scene->AddPhysicObject(c);
      scene->AddEntity(c);
    }
  }
  else if (tab == "<Others>")
  {
    //Provisional
  }

  free(n);
  return true;
}

void Parser::LoadXml(const char* xml_file)
{
  std::fstream xml;
  xml.open(xml_file);

  std::string line;
  LoadTabs();

  std::string space = " ";
  bool blank;

  while(! xml.eof())
  {
    getline(xml, line);
    if ((line.find(space) == 0) || (line.find(space) == 1)) {
     blank = true;
    }

    for(int i = Tabs.size(); i; i--)
    {
      if (line.find(Tabs[i -1], 0) <= 100)  //= if it exists.
        ManageTab(line, Tabs[i -1]);
    }

  }
  xml.close();
}

Parser::~Parser()
{
}

