/*
 * File:   parser.hpp
 * Author: geru
 *
 * Created on April 25, 2009, 12:25 AM
 */

#include "../include/scene.hpp"

#include <vector>
#include <string>
#include <fstream>

#ifndef _PARSER_H
#define	_PARSER_H

//Structs that will be content the constructors parameters.
struct BuildingStruct
{
    int x,y;
    char* name;
};

//Structs that will be content the constructors parameters.
struct personStruct
{
    int x,y;
    std::string name;
    bool flip;
};

class Scene;
class TextBubble;
class PhysicObject;
class SaveGameDialog;

class Parser {
public:
    Parser(Scene *s, TextBubble  *bub, SaveGameDialog  *sav);
    void LoadTabs(void);
    bool ManageTab(std::string line, std::string tab);
    void LoadXml(const char* xml_file);
    virtual ~Parser();
private:
    std::vector<std::string> Tabs;
    Scene *scene;
    TextBubble *bubble;
    PhysicObject *object;
    SaveGameDialog *savegame;
};

#endif	/* _PARSER_H */

