#ifndef TITLE_MENU_H // include guard
#define TITLE_MENU_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Menu
{

  public:
    Menu();

    void upPressed();
    void downPressed();
    int enterPressed();

    sf::RectangleShape getStartBox();
    sf::RectangleShape getDifficultyBox();
    sf::RectangleShape getExitBox();


  private:
  	void init();
  	void boxSelected(int boxInt);

    int itemSelected;

    sf::RectangleShape startBox;
    sf::Text startText;

    sf::RectangleShape difficultyBox;
    sf::RectangleShape exitBox;

};

#endif /* MY_CLASS_H */