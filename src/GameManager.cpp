#include "GameManager.h"
#include "GameView.h"


GameManager::GameManager(){
  initWindow();
  initVariables();
  initGameView();
}

void GameManager::initVariables(){
  srand(time(0));
  this-> dt = 0.f;
}
/**
runGame handles the adaptive gameloop
*/
void GameManager::runGame()
{
	while (this->window->isOpen())
	{
    this->updateDt();
    this->update();
    this->render();

	}
}



void GameManager::updateDt(){
  //updates the delat time
  this->dt = this->clock.restart().asSeconds();
}

void GameManager::update(){
  //updates the current gamestate
  this->gameView.update(event, dt);
}

void GameManager::render(){
  //handles rendering the gamestate
  this->window->display();
}

void GameManager::initGameView(){
  this->gameView = GameView(*window);
  this->gameView.setup();
}

void GameManager::initWindow(){
  std::string windowTitle = "Spooky Storeys";

  //creates the window object
  this->window = new sf::RenderWindow(
    sf::VideoMode(800,600,32),
    windowTitle,
    sf::Style::Close);

}
