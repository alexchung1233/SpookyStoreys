#ifndef INPUT_MANAGER_H // include guard
#define INPUT_MANAGER_H
#include <SFML/Graphics.hpp>
#include "Logic.h"


class InputManager
{
  private:
    sf::RenderWindow* App;
    Logic logic;

  public:
    InputManager();
    InputManager(sf::RenderWindow &app, Logic logic);
    void operator()(sf::RenderWindow &app);
    void update(sf::Event Event);

};

#endif /* MY_CLASS_H */
