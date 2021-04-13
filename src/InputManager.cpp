#include "InputManager.h"

InputManager::InputManager(sf::RenderWindow &app, GameLogic &logic){

  this->App = &app;
  this->logic = logic;

}

InputManager::InputManager(){

}

void InputManager::operator()(sf::RenderWindow &app, GameLogic &logic){

  this->App = &app;
  this->logic = logic;

  std::cout << this->logic.getPlayer().getPosition().x;
  std::cout << "\n";

}

void InputManager::update(sf::Event& Event, float dt){

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
      logic.upPressed(dt);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
      logic.downPressed(dt);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
      logic.leftPressed(dt);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
      logic.rightPressed(dt);
    }
  }

}
