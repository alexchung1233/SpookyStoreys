#ifndef GAME_VIEW_H // include guard
#define GAME_VIEW_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "InputManager.h"
#include "Logic.h"

class GameView
{
  private:
    sf::Event Event;
    InputManager inputManager;
    Logic logic;
    sf::RenderWindow* App;


  public:
    GameView(){
    }
    GameView(sf::RenderWindow& app);
    void update(sf::Event Event);
    void setup();

  };

#endif /* MY_CLASS_H */
