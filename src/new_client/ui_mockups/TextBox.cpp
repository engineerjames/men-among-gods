#include "TextBox.h"

#include <iostream>

TextBox::TextBox()
    : maxCharacters_( 45 )
    , font_()
    , text_()
    , commandList_()
{
  // Temporarily hardcode the font
  if ( ! font_.loadFromFile( "/usr/share/fonts/truetype/msttcorefonts/Times_New_Roman.ttf" ) )
  {
    std::cerr << "Unable to load font!" << std::endl;
  };

//   this->setFont( font_ );
//   this->setCharacterSize( 12 );
//   this->setFillColor( sf::Color::Yellow );
//   this->setOutlineColor( sf::Color::Black );
//   this->setLetterSpacing( 1.5f );
}