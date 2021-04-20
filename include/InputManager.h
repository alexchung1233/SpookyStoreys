#ifndef INPUT_MANAGER_H // include guard
#define INPUT_MANAGER_H
#include <SFML/Graphics.hpp>
#include "GameLogic.h"
<<<<<<< HEAD
#include "Menu.h"
#include <unistd.h>
=======


>>>>>>> adding_game_states

class InputManager
{
  private:
    sf::RenderWindow* App;
    Menu mainMenu;

  public:
    InputManager();
<<<<<<< HEAD
    GameLogic logic;
    bool gameStart;
=======
    GameLogic* logic;
>>>>>>> adding_game_states

    InputManager(sf::RenderWindow &app, GameLogic &logic);
    void operator()(sf::RenderWindow &app, GameLogic &logic);
    void update(sf::Event& Event, float dt);
<<<<<<< HEAD
    void updateMenu(sf::Event& Event);
    Menu& getMenu();

=======
>>>>>>> adding_game_states

};

#endif /* MY_CLASS_H */
