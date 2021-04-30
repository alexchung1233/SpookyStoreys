#ifndef GAME_VIEW_H // include guard
#define GAME_VIEW_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "InputManager.h"
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

    sf::Sprite levelSprite;
    sf::Sprite sprite_player;
    sf::Sprite sprite_item;
    std::vector<sf::Sprite> itemSprites;

    sf::Texture texture;
    sf::Texture texture_player;
    sf::Texture texture_item;


  public:
    GameView();

    GameView(sf::RenderWindow& app);
    void update(sf::Event& Event, float dt);
    void init();

    void setLogic(GameView& logic);
    float myPos();
    void isDialogue();
    void render();
    void pause();
    void unpause();
    //DialogueBox getDialogueBox();
    void createDialogueBox();
    //HolyWater water;
    //HolyWater getHolyWater();
    //void createHolyWater();

  };

#endif /* MY_CLASS_H */
