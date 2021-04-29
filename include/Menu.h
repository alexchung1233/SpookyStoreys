#ifndef TITLE_MENU_H // include guard
#define TITLE_MENU_H
#include <SFML/Graphics.hpp>
#include "State.h"
#include "GameView.h"


class Menu : public State
{

  public:
    //Menu();

    Menu(sf::RenderWindow& app, AudioManager& audioManager);
    Menu(sf::RenderWindow& app);

    void upPressed();
    void downPressed();
    int enterPressed();

    int getDifficulty();

    void init();

    void update(sf::Event& Event, float dt);
    void render();
    void pause();
    void unpause();

  private:
    void makeBox(sf::RectangleShape& box, sf::Vector2f position, sf::Color color);
    void loadFont(sf::Font& font);
    void makeText(sf::Text& text, sf::RectangleShape box, sf::Color color, std::string string);

  	void boxSelected(int boxInt);

    void colorSelected(sf::RectangleShape& box, sf::Text& text, bool selected);

    void toggleDifficulty(int i);

    int itemSelected;

    sf::Text titleText;

    sf::RectangleShape startBox, difficultyBox, exitBox;
    sf::Text startText, difficultyText, exitText;

    sf::Font titleFont, selectableFont;

    int difficultyLevel;



};

#endif /* MY_CLASS_H */
