#ifndef GAME_VIEW_H // include guard
#define GAME_VIEW_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "InputManager.h"
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
    sf::Texture texture;
    sf::Texture texture_player;

    //temp test rectangles
    sf::RectangleShape transitionRectangle{ sf::Vector2f(800, 600) };
    sf::Uint8 transitionRectangleAlphaChannel;
    sf::Clock clockFilter;


  public:
    GameView();

    GameView(sf::RenderWindow& app);
    void update(sf::Event& Event, float dt);
    void init();

    void setLogic(GameView& logic);
    void render();
    void pause();
    void unpause();
    void fadeIn(float duration, int r, int g, int b);
    void fadeOut(float duration, int r, int g, int b);
  };

#endif /* MY_CLASS_H */
