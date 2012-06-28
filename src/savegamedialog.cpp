/*
 * savegamedialog.cpp
 * Copyright (C) Unai Orbe 2009 <uorbe001@gmail.com>
 *
 * button.cpp is free software: you can redistribute it and/or modify it
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


#include "../include/savegamedialog.hpp"

#include <fstream>

#define BLACK (SDL_Color){0,0,0}

SaveGameDialog::SaveGameDialog(Party *party)
    : Entity(170, 90)
{
  //It's not visible at the beginning.
  visible = false;
  temp_party = party;

  //Create buttons and make them not visible.
  buttonYES = new Button(posX + 96, posY + 80, (char*)"YES");
  buttonNO = new Button(posX + 96, posY + 180, (char*)"NO");
  buttonYES->LoadAnimations();
  buttonNO->LoadAnimations();
  buttonYES->Hide();
  buttonNO->Hide();

	//Load animation image.
  animationVector.resize(1);
	animationVector[0].imageList.push_back("resources/images/others/savegamedialog.png");
	animationVector[0].horizontalFlip = false;
	animationVector[0].verticalFlip = false;
	LoadAnimations();
}

SaveGameDialog::~SaveGameDialog()
{
  //Clean up.
  delete buttonYES;
  delete buttonNO;
}

void SaveGameDialog::Draw(bool nextImg, SDL_Surface *screen)
{
	SDL_Rect *pos = new SDL_Rect;

  //If the dialog is visible, draw it and the text.
	if (visible)
	{
		pos->x = posX;
		pos->y = posY;

    SDL_BlitSurface(getNextImage(false), NULL, screen, pos);

    buttonYES->Draw(nextImg, screen);
    buttonYES->DrawText(screen);
    buttonNO->Draw(nextImg, screen);
    buttonNO->DrawText(screen);
	}

	delete pos;
}

void SaveGameDialog::ListenNextFrame(SDL_Event *event)
{
    if ((event->type == SDL_MOUSEBUTTONUP) && (event->button.button == SDL_BUTTON_LEFT ))
    {
      int x = event->button.x;
			int	y = event->button.y;

      if (( x > buttonNO->box.x ) && ( x < buttonNO->box.x + buttonNO->box.w ) &&
                ( y > buttonNO->box.y ) && ( y < buttonNO->box.y + buttonNO->box.h ))
      {
        Hide();
      }
      if (( x > buttonYES->box.x ) && ( x < buttonYES->box.x + buttonYES->box.w ) &&
                ( y > buttonYES->box.y ) && ( y < buttonYES->box.y + buttonYES->box.h ))
      {
        std::fstream save_file;
        save_file.open("savegames/game.save");

        std::list<Character*> char_list = temp_party->getCharacterList();

        std::list<Character*>::iterator pos;
        pos = char_list.begin();

        int num_chars = char_list.size();

        save_file << num_chars << std::endl;
        save_file << temp_party->getPosX() << std::endl;
        save_file << temp_party->getPosY() << std::endl;

        while (pos != char_list.end()) {
          save_file << (*pos)->getName() << std::endl;
          save_file << (*pos)->getType() << std::endl;
          save_file << (*pos)->getExperience() << std::endl;
          save_file << (*pos)->getLive() << std::endl;
          save_file << (*pos)->getMana() << std::endl;
          save_file << (*pos)->getStamina() << std::endl;
          save_file << (*pos)->getStrength() << std::endl;
          save_file << (*pos)->getAgility() << std::endl;
          save_file << (*pos)->getIntelligence() << std::endl;
          save_file << (*pos)->getResistance() << std::endl;
          save_file << (*pos)->getLevel() << std::endl;
          pos++;
        }

        save_file.close();
        Hide();
      }
    }

    if (event->type == SDL_MOUSEMOTION)
    {
      int x = event->motion.x;
      int y = event->motion.y;

      if (( x > buttonYES->box.x ) && ( x < buttonYES->box.x + buttonYES->box.w ) &&
															( y > buttonYES->box.y ) && ( y < buttonYES->box.y + buttonYES->box.h ))
      {
        buttonYES->setOver(true);
      }
      else if (!(( x > buttonYES->box.x ) && ( x < buttonYES->box.x + buttonYES->box.w ) &&
															( y > buttonYES->box.y ) && ( y < buttonYES->box.y + buttonYES->box.h )))
      {
        buttonYES->setOver(false);
      }
      if (( x > buttonNO->box.x ) && ( x < buttonNO->box.x + buttonNO->box.w ) &&
															( y > buttonNO->box.y ) && ( y < buttonNO->box.y + buttonNO->box.h ))
      {
        buttonNO->setOver(true);
      }
      else if (!(( x > buttonNO->box.x ) && ( x < buttonNO->box.x + buttonNO->box.w ) &&
															( y > buttonNO->box.y ) && ( y < buttonNO->box.y + buttonNO->box.h )))
      {
        buttonNO->setOver(false);
      }
    }
}

void SaveGameDialog::Show()
{
  //Hide the dialog and buttons
	visible = true;
	buttonYES->Show();
	buttonNO->Show();
}

void SaveGameDialog::Hide()
{
  //Hide the dialog and buttons
	visible =false;
	buttonYES->Hide();
	buttonNO->Hide();
}
