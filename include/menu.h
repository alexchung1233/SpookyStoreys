#ifndef TITLE_MENU_H // include guard
#define TITLE_MENU_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class menu
{

  public:
    menu();

    menu(sf::RenderWindow &app);

    void update(sf::Event event);

  private:
    sf::Event Event;
    sf::RenderWindow* App;
    int itemSelected;

};



#endif /* MY_CLASS_H */