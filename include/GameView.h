#ifndef GAME_VIEW_H // include guard
#define GAME_VIEW_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class GameView
{
  private:
    sf::Event Event;
    sf::RenderWindow* App;

  public:
    GameView(sf::RenderWindow &app);
    void setup();

  };

#endif /* MY_CLASS_H */
