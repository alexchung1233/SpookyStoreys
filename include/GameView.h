#ifndef GAME_VIEW_H // include guard
#define GAME_VIEW_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "InputManager.h"
#include "Animation.h"
#include "MonsterAI.h"
#include "State.h"
#include "GameOver.h"


class GameView : public State
{
  private:
    InputManager inputManager;
    LevelManager levelManager;
    MonsterAI monsterAI;
    LevelManager monsterLevelManager;

    GameLogic logic;
    MonsterView monsterView;

    Animation player_anim_down;
    Animation player_anim_up;
    Animation player_anim_left;
    Animation player_anim_right;
    sf::Sprite levelSprite;
    sf::Sprite sprite_player;
    sf::Sprite sprite_monster;
    sf::Texture texture;
    sf::Clock gameClock;
    sf::Texture player_sprite_sheet;
    sf::Texture texture_player;
    sf::Texture texture_monster;

    AudioManager* sound;


    void updatePlayerAnimation(float dt);

    bool inRoomLastTime = false;
    bool nextRoomLastTime = false;


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
