#include "TextInput.h"

TextInput::TextInput()
    : sizeInPixels_( 20 )
    , font_()
    , text_()
    , boundingBox_()
{
}

void TextInput::handleInput(sf::Event e)
{

  if ( e.type != sf::Event::TextEntered )
    return;

  if ( e.text.unicode == 8 )
  { // Delete key
    text_ = text_.substr( 0, text_.size() - 1 );
  }
  else if ( text_.size() < sizeInPixels_ )
  {
    text_ += e.text.unicode;
  }
}
