#include "InputManager.h"

InputManager::InputManager(sf::RenderWindow &app, GameLogic &logic){
  this->App = &app;
  this->logic = &logic;

  playState = 0;
}

InputManager::InputManager(){
  playState = 0;
}

void InputManager::operator()(sf::RenderWindow &app, GameLogic &logic){

  this->App = &app;
  this->logic = &logic;

}

void InputManager::update(sf::Event& Event, float dt){

  while(App->pollEvent(Event))
  {
    // Exit
    if(Event.type == sf::Event::Closed) {
      App->close();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
      App->close();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
      logic->upPressed(dt);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
      logic->downPressed(dt);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
      logic->leftPressed(dt);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
      logic->rightPressed(dt);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
    {
      playState = 1;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)){
      logic->itemAndDialogueBoxHandler();

    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
      logic->WPressed();
    }
  }

}

int InputManager::getPlayState(){
  return playState;
}
