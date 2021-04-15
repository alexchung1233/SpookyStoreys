#include "InputManager.h"

InputManager::InputManager(sf::RenderWindow &app, GameLogic &logic){

  this->App = &app;
  this->logic = logic;
  gameStart = false;

}

InputManager::InputManager(){

}

void InputManager::operator()(sf::RenderWindow &app, GameLogic &logic){

  this->App = &app;
  this->logic = logic;

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

void InputManager::updateMenu(sf::Event& Event){

  while(App->pollEvent(Event))
  {
    // Exit
    if(Event.type == sf::Event::Closed) {
      App->close();
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
      App->close();
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
      mainMenu.upPressed();
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
      mainMenu.downPressed();
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
      int num = mainMenu.enterPressed();
      if(num == 1){
        mainMenu.toggleDifficulty(-1);
      }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
      int num = mainMenu.enterPressed();
      if(num == 1){
        mainMenu.toggleDifficulty(1);
      }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){

      int num = mainMenu.enterPressed();
      if(num == 0){
        logic.setDifficulty(mainMenu.getDifficulty());
        gameStart = true;
      }
      else if(num == 2){
        App->close();
      }
    }

  }

}

Menu& InputManager::getMenu(){
  return mainMenu;
}
