#ifndef BUBBLEBUTTON_HPP
#define BUBBLEBUTTON_HPP

#include "../include/button.hpp"
#include "../include/entity.hpp"

#define BLACK (SDL_Color){0,0,0}
#define GREY (SDL_Color){130, 100, 100}

class BubbleButton : public Button
{
  public:
    //Button for the textbubble, startx/starty set the position and txt text in the button
    BubbleButton(unsigned int startX, unsigned int startY, char* txt) : Button(startX, startY)
    {
      //Start default status variables.
      pressed = false;
      over = false;

      //Set text variables
      text = txt;
      font = TTF_OpenFont( "resources/fonts/DejaVuSans.ttf", 14 );
      TTF_SetFontStyle( font, TTF_STYLE_BOLD );

      //Load animation images and messages.
      animationVector.resize(NUM_STATES);

      animationVector[NORMAL].imageList.push_back("resources/images/others/bubbleButton.png");
      message[NORMAL].color = BLACK;
      message[NORMAL].msg = TTF_RenderText_Solid( font, text, message[NORMAL].color );

      animationVector[OVER].imageList.push_back("resources/images/others/bubbleButtonOver.png");
      message[OVER].color = BLACK;
      message[OVER].msg = TTF_RenderText_Solid( font, text, message[OVER].color );

      animationVector[INNACTIVE].imageList.push_back("resources/images/others/bubbleButton.png");
      message[INNACTIVE].color = GREY;
      message[INNACTIVE].msg = TTF_RenderText_Solid( font, text, message[INNACTIVE].color );

      animationVector[PRESSED].imageList.push_back("resources/images/others/bubbleButtonOver.png");
      message[PRESSED].color = BLACK;
      message[PRESSED].msg = TTF_RenderText_Solid( font, text, message[PRESSED].color );

      //Set box size.
      box.w = 160;
      box.h = 32;
      box.x = startX;
      box.y = startY;
    }
};

#endif // BUBBLEBUTTON_HPP
