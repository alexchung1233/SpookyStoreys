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
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
    {
      playState = 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
    {
      playState = 2;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)){
      if(!logic->isDialogueBoxUsed()){
        logic->dialoguebox.tracker++;
        if(logic->isPlayerByItem()){
          logic->EPressed();
        }
      }
    }
  }

}

int InputManager::getPlayState(){
  return playState;
}
