#include "InputManager.h"

InputManager::InputManager(sf::RenderWindow &app, Logic logic){

  this->App = &app;
  this->logic = logic

}

InputManager::InputManager(){

}

void InputManager::operator()(sf::RenderWindow &app){

  this->App = &app;

}

void InputManager::update(sf::Event Event){

  while(App->pollEvent(Event))
  {
    // Exit
    if(Event.type == sf::Event::Closed) {
      App->close();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
    {
      App->close();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
      logic.MovePlayerUp();
    }
  }
}
