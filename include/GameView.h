#ifndef GAME_VIEW_H // include guard
#define GAME_VIEW_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "InputManager.h"
#include "Animation.h"
#include "State.h"
#include "GameOver.h"



class GameView : public State
{
  private:
    InputManager inputManager;
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
    GameView();

    GameView(sf::RenderWindow& app);
    void update(sf::Event& Event, float dt);
    void init();
    void setLogic(GameView& logic);
    void render();
    void pause();
    void unpause();

  };

#endif /* MY_CLASS_H */
