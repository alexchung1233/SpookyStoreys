#ifndef GAME_VIEW_H // include guard
#define GAME_VIEW_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "InputManager.h"

class GameView
{
  private:
    sf::Event Event;
    sf::RenderWindow* App;
    InputManager inputManager(sf::RenderWindow);

  public:
    GameView(sf::RenderWindow &app);
    void update(sf::Event Event);
    void setup();

  };

#endif /* MY_CLASS_H */
