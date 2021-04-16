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
  this->gameView.update(event, dt);
}

void Game::render(){
  this->window->display();
}

void Game::initGameView(){
  this->gameView.setup(*window);
}

void Game::initWindow(){
  std::string windowTitle = "Spooky Storeys";

  this->window = new sf::RenderWindow(
    sf::VideoMode(800,600,32),
    windowTitle,
    sf::Style::Close);

}
