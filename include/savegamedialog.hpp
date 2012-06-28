/*
 * savegamedialog.hpp
 * Copyright (C) Unai Orbe 2009 <uorbe001@gmail.com>
 *
 * savegamedialog.hpp is free software: you can redistribute it and/or modify it
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


#ifndef SAVEGAMEDIALOG_HPP
#define SAVEGAMEDIALOG_HPP

#include "../include/entity.hpp"
#include "../include/button.hpp"
#include "../include/party.hpp"
#include "../include/character.hpp"
#include <SDL/SDL.h>

class SaveGameDialog: public Entity
{
	public:
		SaveGameDialog(Party *party);
		~SaveGameDialog();

    void ContinueMessage();
		virtual void Draw(bool nextImg, SDL_Surface *screen);
		virtual void ListenNextFrame(SDL_Event *event);
		virtual void Show();
		virtual void Hide();
		inline Button* getButtonYES(){return buttonYES;};
		inline Button* getButtonNO(){return buttonNO;};

  private:
    Button *buttonYES, *buttonNO;
    Party *temp_party;
};

#endif /* SAVEGAMEDIALOG_HPP */
