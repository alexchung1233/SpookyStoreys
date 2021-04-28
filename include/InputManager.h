#ifndef INPUT_MANAGER_H // include guard
#define INPUT_MANAGER_H
#include <SFML/Graphics.hpp>
#include "GameLogic.h"

class InputManager
{
  private:
    sf::RenderWindow* App;
    int playState;

  public:
    InputManager();

    GameLogic* logic;

    InputManager(sf::RenderWindow &app, GameLogic &logic);
    void operator()(sf::RenderWindow &app, GameLogic &logic);
    void update(sf::Event& Event, float dt);
    int getPlayState();

};

#endif /* MY_CLASS_H */
