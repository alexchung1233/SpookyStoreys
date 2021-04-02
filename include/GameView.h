#ifndef GAME_VIEW_H // include guard
#define GAME_VIEW_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "menu.h"


class GameView
{
  private:
    sf::Event Event;
    sf::RenderWindow* App;
    menu myMenu;

  public:
    GameView(sf::RenderWindow &app);
    void setup();
    void update(sf::Event event);

  };

#endif /* MY_CLASS_H */
