#ifndef GAME_VIEW_H // include guard
#define GAME_VIEW_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "InputManager.h"
#include "State.h"



class GameView : public State
{
  private:
    InputManager inputManager;
    GameLogic logic;
    sf::Sprite sprite;
    sf::Sprite sprite_player;
    sf::Texture texture;
    sf::Texture texture_player;


  public:
    GameView()	{	}
// <<<<<<< HEAD
//     void update(sf::Event& Event, float dt);

//     void updateMenu(sf::Event& Event);
//     void drawMenu();

//     InputManager& getManager();

//     void setup(sf::RenderWindow& app);
//     float myPos();
// =======
    GameView(sf::RenderWindow& app);
    void update(sf::Event& Event, float dt);
    void init();
    void setLogic(GameView& logic);
    void render();
    void pause();
    void unpause();
//>>>>>>> adding_game_states

  };

#endif /* MY_CLASS_H */
