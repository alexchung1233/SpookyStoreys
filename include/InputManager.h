#ifndef INPUT_MANAGER_H // include guard
#define INPUT_MANAGER_H
#include <SFML/Graphics.hpp>
#include "GameLogic.h"
#include "Menu.h"

class InputManager
{
  private:
    sf::RenderWindow* App;
    Menu menu;

  public:
    InputManager();
    GameLogic logic;
    bool gameStart;

    InputManager(sf::RenderWindow &app, GameLogic &logic);
    void operator()(sf::RenderWindow &app, GameLogic &logic);
    void update(sf::Event& Event, float dt);
    void updateMenu(sf::Event& Event);
    Menu getMenu();


};

#endif /* MY_CLASS_H */
