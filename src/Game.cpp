#include "Game.h"
#include "GameView.h"


Game::Game(){
  initWindow();
  initGameView();
}

void Game::initVariables(){
  
  srand(time(0));
  this-> dt = 0.f;
}

void Game::runGame()
{

	while (this->window->isOpen())
	{
    this->updateDt();
    this->update();
    this->render();
	}
}



void Game::updateDt(){
  this->dt = this->clock.restart().asSeconds();
}

void Game::update(){
  if(this->gameView.getManager().gameStart)
    this->gameView.update(event, dt);
  else
    this->gameView.updateMenu(event);
}

void Game::render(){
  this->window->display();
}

void Game::initGameView(){
  this->gameView = GameView(*window);
  this->gameView.setup();
}

void Game::initWindow(){
  std::string windowTitle = "Spooky Storeys";

  this->window = new sf::RenderWindow(
    sf::VideoMode(800,600,32),
    windowTitle,
    sf::Style::Close);

}
