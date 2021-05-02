#ifndef GAME_VIEW_H // include guard
#define GAME_VIEW_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "InputManager.h"
#include "Animation.h"
#include "MonsterAI.h"
#include "State.h"
#include "GameOver.h"
#include "Room.h"


class GameView : public State
{
  private:
    InputManager inputManager;
    LevelManager levelManager;
    GameLogic logic;
    Room room;
    DialogueBox dialoguebox;

    Animation player_anim_down;
    Animation player_anim_up;
    Animation player_anim_left;
    Animation player_anim_right;

    sf::Sprite levelSprite;
    sf::Sprite sprite_player;
    sf::Sprite sprite_monster;

    sf::Sprite sprite_counter;

    sf::Font font;
    sf::Text counterText;

    sf::Sprite sprite_item;
    std::vector<sf::Sprite*> itemSprites;

    sf::Texture texture;
    sf::Texture texture_counter;

    sf::Clock gameClock;
    sf::Texture player_sprite_sheet;
    sf::Texture texture_player;
    sf::Texture texture_water;
    sf::RectangleShape dialogueBox;
    sf::Text message;





    sf::Texture* texture_item;
    std::map<const std::string, sf::Texture*> itemTextures;


    sf::Texture texture_monster;
    MonsterAI monsterAI;


    void updatePlayerAnimation(float dt);
    void loadItemSprites();


  public:
    GameView();

    GameView(sf::RenderWindow& app, AudioManager& audioManager);
    GameView(sf::RenderWindow& app);

    void update(sf::Event& Event, float dt);
    void init();

    void setCounterText();

    void setLogic(GameView& logic);
    float myPos();
    void isDialogue();
    void render();
    void pause();
    void unpause();
    void makeBox(sf::Vector2f position, sf::Color color);
    void setText(std::string words);


  };

#endif /* MY_CLASS_H */
