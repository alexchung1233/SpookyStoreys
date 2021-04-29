#ifndef GAME_VIEW_H // include guard
#define GAME_VIEW_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "InputManager.h"
#include "MonsterAI.h"
#include "State.h"
#include "GameOver.h"


class GameView : public State
{
  private:
    InputManager inputManager;
    LevelManager levelManager;

    GameLogic logic;
    sf::Sprite levelSprite;
    sf::Sprite sprite_player;
    sf::Sprite sprite_monster;
    sf::Texture texture;
    sf::Texture texture_player;
    sf::Texture texture_monster;
    MonsterAI monsterAI;

  public:
    GameView();

    GameView(sf::RenderWindow& app, AudioManager& audioManager);
    GameView(sf::RenderWindow& app);

    void update(sf::Event& Event, float dt);
    void init();

    void setLogic(GameView& logic);
    void render();
    void pause();
    void unpause();

  };

#endif /* MY_CLASS_H */
