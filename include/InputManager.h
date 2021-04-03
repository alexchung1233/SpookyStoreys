#ifndef INPUT_MANAGER_H // include guard
#define INPUT_MANAGER_H
#include <SFML/Graphics.hpp>


class InputManager
{
  private:
    sf::RenderWindow* App;

  public:
    InputManager(sf::RenderWindow &app);
    void update(sf::Event Event);
    
};

#endif /* MY_CLASS_H */
