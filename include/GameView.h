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
    sf::Sprite sprite;
    sf::Sprite sprite_player;
    sf::Sprite sprite_holywater;
    sf::Texture texture;
    sf::Texture texture_player;
    sf::Texture texture_water;



  public:
    GameView()	{	}
    void update(sf::Event& Event, float dt);
    void setup(sf::RenderWindow& app);
    void setLogic(GameView& logic);
    float myPos();
    void isDialogue(DialogueBox& box);

  };

#endif /* MY_CLASS_H */
