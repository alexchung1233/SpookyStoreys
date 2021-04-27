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
    LevelManager levelManager;

    GameLogic logic;
    Animation player_anim_down;
    Animation player_anim_up;
    Animation player_anim_left;
    Animation player_anim_right;
    sf::Sprite levelSprite;
    sf::Sprite sprite_player;
    sf::Texture texture;
    sf::Clock gameClock;
    sf::Texture player_sprite_sheet;


    void updatePlayerAnimation(float dt);



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
