# Global variables
OBJECTS = button.o \
          character.o \
          chest.o \
          clock.o \
          combatlevel.o \
          enemy.o \
          engine.o \
          entity.o \
          gameover.o \
          main.o \
          mainmenu.o \
          menu.o \
          nonplayercharacter.o \
          parser.o \
          particlesystem.o \
          party.o \
          physicobject.o \
          portrait.o \
          postcombat.o \
          savegamedialog.o \
          savepoint.o \
          scene.o \
          scenery.o \
          textbubble.o \
          window.o \
          world.o
SDL_LIBS = -L/usr/lib/x86_64-linux-gnu -lSDL -lSDL_gfx -lSDL_image -lSDL_mixer -lSDL_ttf -lfreetype
CFLAGS = -c -g -Wall -I/usr/include/SDL -D_GNU_SOURCE=1 -D_REENTRANT
CC = g++
EXE = necromidas

# Headers dependencies
ACTIVEHALO = include/activehalo.hpp \
             $(PHYSICOBJECT)

BUBBLEBUTTON = include/bubblebutton.hpp \
               $(BUTTON) \
               $(ENTITY)

BUTTON = include/button.hpp \
         $(ENTITY) \
         $(ENUMS)

CHARACTER = include/character.hpp \
            $(PHYSICOBJEC) \
            $(BUTTON)

CHEST = include/chest.hpp \
        $(TEXTBUBBLE) \
        $(PHYSICOBJECT)

CLOCK = include/clock.hpp

COMBATLEVEL = include/combatlevel.hpp \
              $(SCENE) \
              $(MENU)

CURE = include/cure.hpp \
       $(ENTITY)

DARKSLASH = include/darkslash.hpp \
            $(ENTITY)

ENEMY = include/enemy.hpp \
        $(PHYSICOBJECT) \
        $(BUTTON)

ENGINE = include/engine.hpp

ENTITY = include/entity.hpp

ENUMS = include/enums.hpp

FIRE = include/fire.hpp \
       $(ENTITY)

GAMEOVER = include/gameover.hpp \
           $(MENU) \
           $(ENGINE)

LIGHTSLASH = include/lightslash.hpp \
             $(ENTITY)

LISTENER = include/listener.hpp

MAINMENU = include/mainmenu.hpp \
           $(MENU)

MENU = include/menu.hpp \
       $(SCENE)

MOUSEPOINTER = include/mousepointer.hpp \
               $(PHYSICOBJECT)

NONPLAYERCHARACTER = include/nonplayercharacter.hpp \
                     $(CHARACTER) \
                     $(TEXTBUBBLE) \
                     $(PHYSICOBJECT)

PARSER = include/parser.hpp \
         $(SCENE)

PARTICLESYSTEM = include/particlesystem.hpp \
                 $(ENTITY) \
                 $(ENUMS)

PARTY = include/party.hpp \
        $(PHYSICOBJECT)

PHYSICOBJECT = include/physicobject.hpp \
               $(ENTITY)

POINTER = include/pointer.hpp \
          $(ENTITY)

PORTRAIT = include/portrait.hpp \
           $(ENTITY) \
           $(BUTTON)

POSTCOMBAT = include/postcombat.hpp \
             $(MENU) \
             $(ENGINE)

SAVEGAMEDIALOG = include/savegamedialog.hpp \
                 $(ENTITY) \
                 $(BUTTON) \
                 $(PARTY) \
                 $(CHARACTER)

SAVEPOINT = include/savepoint.hpp \
            $(PHYSICOBJECT)

SCENE = include/scene.hpp \
        $(LISTENER)

SCENERY = include/scenery.hpp \
          $(PHYSICOBJECT)

SWITCH = include/switch.hpp \
         $(ENGINE)

TEXTBUBBLE = include/textbubble.hpp \
             $(ENTITY)

THUNDER = include/thunder.hpp \
          $(ENTITY)

TILE = include/tile.hpp

WINDOW = include/window.hpp \
         $(LISTENER)

WORLD = include/world.hpp \
        $(SCENE) \
        $(ENUMS)

# Build dependencies
$(EXE) : $(OBJECTS)
	$(CC) $(OBJECTS) $(SDL_LIBS) -o $(EXE)

button.o : src/button.cpp $(BUTTON)
	$(CC) $(CFLAGS) src/button.cpp

character.o : src/character.cpp $(CHARACTER) \
              $(ENEMY) \
              $(PORTRAIT) \
              $(ENGINE) \
              $(PARTICLESYSTEM) \
              $(FIRE) \
              $(CURE) \
              $(THUNDER) \
              $(LIGHTSLASH) \
              $(DARKSLASH)
	$(CC) $(CFLAGS) src/character.cpp

chest.o : src/chest.cpp $(CHEST) \
          $(PHYSICOBJECT)
	$(CC) $(CFLAGS) src/chest.cpp

clock.o : src/clock.cpp $(CLOCK)
	$(CC) $(CFLAGS) src/clock.cpp

combatlevel.o : src/combatlevel.cpp $(COMBATLEVEL) \
                $(GAMEOVER) \
                $(POSTCOMBAT) \
                $(ENGINE) \
                $(PARTICLESYSTEM) \
                $(POINTER) \
                $(ACTIVEHALO) \
                $(MOUSEPOINTER) \
                $(SWITCH) \
                $(PARTY) \
                $(ENEMY) \
                $(BUTTON) \
                $(CHARACTER) \
                $(PORTRAIT) \
                $(ENUMS)
	$(CC) $(CFLAGS) src/combatlevel.cpp

enemy.o : src/enemy.cpp $(ENEMY) \
          $(CHARACTER) \
          $(ENGINE) \
          $(COMBATLEVEL) \
          $(SWITCH) \
          $(ENUMS)
	$(CC) $(CFLAGS) src/enemy.cpp

engine.o : src/engine.cpp $(ENGINE) \
           $(CLOCK) \
           $(WINDOW) \
           $(WORLD) \
           $(MAINMENU) \
           $(COMBATLEVEL)
	$(CC) $(CFLAGS) src/engine.cpp

entity.o : src/entity.cpp $(ENTITY) \
           $(ENGINE)
	$(CC) $(CFLAGS) src/entity.cpp

gameover.o : src/gameover.cpp $(GAMEOVER) \
             $(SWITCH)
	$(CC) $(CFLAGS) src/gameover.cpp

main.o : src/main.cpp \
         $(ENGINE) \
         $(WINDOW) \
         $(MAINMENU) \
         $(WORLD) \
         $(SWITCH)
	$(CC) $(CFLAGS) src/main.cpp

mainmenu.o : src/mainmenu.cpp $(MAINMENU) \
             $(BUTTON) \
             $(SWITCH) \
             $(WORLD) \
             $(PARTY)
	$(CC) $(CFLAGS) src/mainmenu.cpp

menu.o : src/menu.cpp $(MENU) \
         $(ENTITY) \
         $(PHYSICOBJECT) \
         $(BUTTON)
	$(CC) $(CFLAGS) src/menu.cpp

nonplayercharacter.o : src/nonplayercharacter.cpp $(NONPLAYERCHARACTER) \
                       $(PHYSICOBJECT)
	$(CC) $(CFLAGS) src/nonplayercharacter.cpp

parser.o : src/parser.cpp $(PARSER) \
           $(NONPLAYERCHARACTER) \
           $(SAVEPOINT) \
           $(SAVEGAMEDIALOG) \
           $(SCENERY) \
           $(CHEST) \
           $(SCENE) \
           $(PHYSICOBEJCT)
	$(CC) $(CFLAGS) src/parser.cpp

particlesystem.o : src/particlesystem.cpp $(PARTICLESYSTEM)
	$(CC) $(CFLAGS) src/particlesystem.cpp

party.o : src/party.cpp $(PARTY) \
          $(CHARACTER)
	$(CC) $(CFLAGS) src/party.cpp

physicobject.o : src/physicobject.cpp $(PHYSICOBEJCT)
	$(CC) $(CFLAGS) src/physicobject.cpp

portrait.o : src/portrait.cpp $(PORTRAIT)
	$(CC) $(CFLAGS) src/portrait.cpp

postcombat.o : src/postcombat.cpp $(POSTCOMBAT) \
               $(BUTTON) \
               $(SWITCH) \
               $(PARTY) \
               $(CHARACTER)
	$(CC) $(CFLAGS) src/postcombat.cpp

savegamedialog.o : src/savegamedialog.cpp $(SAVEGAMEDIALOG)
	$(CC) $(CFLAGS) src/savegamedialog.cpp

savepoint.o : src/savepoint.cpp $(SAVEPOINT) \
              $(SAVEGAMEDIALOG)
	$(CC) $(CFLAGS) src/savepoint.cpp

scene.o : src/scene.cpp $(SCENE) \
          $(ENTITY) \
          $(PHYSICOBJECT)
	$(CC) $(CFLAGS) src/scene.cpp

scenery.o : src/scenery.cpp $(SCENERY)
	$(CC) $(CFLAGS) src/scenery.cpp

textbubble.o : src/textbubble.cpp $(TEXTBUBBLE)
	$(CC) $(CFLAGS) src/textbubble.cpp

window.o : src/window.cpp $(WINDOW)
	$(CC) $(CFLAGS) src/window.cpp

world.o : src/world.cpp $(WORLD) \
          $(ENGINE) \
          $(SWITCH) \
          $(TEXTBUBBLE) \
          $(BUBBLEBUTTON) \
          $(SAVEGAMEDIALOG) \
          $(PARTY) \
          $(ENEMY) \
          $(TILE) \
          $(COMBATLEVEL) \
          $(PARSER)
	$(CC) $(CFLAGS) src/world.cpp

# Make options
.PHONY : all clean

all: clean
	make

clean :
	rm -f  src/*~ include/*~ $(EXE) $(OBJECTS)
