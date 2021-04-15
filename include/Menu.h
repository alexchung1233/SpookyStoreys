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

    sf::RectangleShape getBox(int i);

    sf::Text& getStartText();


  private:
  	void init();

    void loadFont();

  	void boxSelected(int boxInt);

    int itemSelected;

    sf::RectangleShape startBox;
    sf::Text startText;
    sf::Font myFont;

    sf::RectangleShape difficultyBox;
    sf::RectangleShape exitBox;

};

#endif /* MY_CLASS_H */