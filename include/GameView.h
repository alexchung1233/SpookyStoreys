#ifndef GAME_VIEW_H // include guard
#define GAME_VIEW_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "InputManager.h"
#include "Animation.h"

class GameView
{
  private:
    sf::Event Event;
    InputManager inputManager;
    sf::RenderWindow* App;
    GameLogic logic;
    Animation animation;

    //temporary sprite files until we know what to do with them
    sf::Sprite sprite;
    sf::Sprite sprite_player;
    sf::Texture texture;
    sf::Texture texture_player;

    sf::Sprite sprite_animate_example;
    sf::Texture texture_animated;


    void updatePlayerAnimation();



  public:
    GameView()	{	}
    GameView(sf::RenderWindow& app);
    void update(sf::Event& Event, float dt);
    void setup();
    void setLogic(GameView& logic);
    float myPos();

  };

#endif /* MY_CLASS_H */
