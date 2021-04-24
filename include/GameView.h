#ifndef GAME_VIEW_H // include guard
#define GAME_VIEW_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "InputManager.h"
//<<<<<<< HEAD
#include "MonsterAI.h"
//=======
#include "State.h"
#include "GameOver.h"
#include "Sound.h"

//>>>>>>> main



class GameView : public State
{
  private:
    InputManager inputManager;
    GameLogic logic;
    sf::Sprite sprite;
    sf::Sprite sprite_player;
    sf::Sprite sprite_monster;
    sf::Texture texture;
    sf::Texture texture_player;
    sf::Texture texture_monster;
    MonsterAI monsterAI;
    Sound* sound;

  public:
    GameView();

    GameView(sf::RenderWindow& app, Sound* sound);
    void update(sf::Event& Event, float dt);
    void init();
    void setLogic(GameView& logic);
    void render();
    void pause();
    void unpause();

  };

#endif /* MY_CLASS_H */
