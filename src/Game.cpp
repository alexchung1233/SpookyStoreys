#include "Game.h"
#include "GameView.h"


Game::Game(){
  initWindow();
  initVariables();
  initGameView();
}

void Game::initVariables(){
  srand(time(0));
  this-> dt = 0.f;
}
/**
runGame handles the adaptive gameloop
*/
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
  //updates the delat time
  this->dt = this->clock.restart().asSeconds();
}

void Game::update(){
  //updates the current gamestate
  this->gameView.update(event, dt);
}

void Game::render(){
  //handles rendering the gamestate
  this->window->display();
}

void Game::initGameView(){
  this->gameView = GameView(*window);
  this->gameView.setup();
}

void Game::initWindow(){
  std::string windowTitle = "Spooky Storeys";

  //creates the window object
  this->window = new sf::RenderWindow(
    sf::VideoMode(800,600,32),
    windowTitle,
    sf::Style::Close);

}
