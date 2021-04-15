#ifndef GAME_VIEW_H // include guard
#define GAME_VIEW_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "InputManager.h"



class GameView
{
  private:
    sf::Event Event;
    InputManager inputManager;
    sf::RenderWindow* App;
    GameLogic logic;
    sf::Sprite sprite;
    sf::Sprite sprite_player;
    sf::Texture texture;
    sf::Texture texture_player;



  public:
    GameView()	{	}
    GameView(sf::RenderWindow& app);
    void update(sf::Event& Event, float dt);

    void updateMenu(sf::Event& Event);
    void drawMenu();

    InputManager& getManager();

    void setup();
    float myPos();

  };

#endif /* MY_CLASS_H */
