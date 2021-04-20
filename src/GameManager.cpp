#include "GameManager.h"
#include "GameView.h"
#include "Menu.h"

GameManager::GameManager(){
  initWindow();
  initVariables();
  initStates();
}

void GameManager::initVariables(){
  srand(time(0));
  this-> dt = 0.f;

  //initial starting state
  this->stateStack.push(new GameView(*window));
  this->stateStack.push(new Menu(*window));

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
  //updates the delta time
  this->dt = this->clock.restart().asSeconds();
}

void GameManager::update(){
  //updates the current gamestate by getting the top of the stack
  initStates();

  State* currentState = this->stateStack.top();

  //this handles the transitioning of states from one state to another
  if(!this->stateStack.empty()){
    //as long as the stack is not empty and the current state is running
    //then update
    if(currentState->getStatus() == State::RUNNING){
      currentState->update(event, dt);
    }
    //if the current state is has finished then pop it off the stack
    else if(currentState->isDead()){
      if(currentState->getStatus() == State::SUCCESS){
        //get the next gamestate after the current state finishes
        if(currentState->hasChildState()){
          stateStack.push(currentState->getChildState());
        }
      }
      this->stateStack.pop();
    }
  }
}

void GameManager::render(){
  //handles rendering the gamestate
  this->window->display();
  if(!this->stateStack.empty()){
    this->stateStack.top()->render();
  }
}

void GameManager::initStates(){
  if(stateStack.top()->getStatus() == State::UNINIT)
    this->stateStack.top()->init();
}

void GameManager::initWindow(){
  std::string windowTitle = "Spooky Storeys";

  //creates the window object
  this->window = new sf::RenderWindow(
    sf::VideoMode(800,600,32),
    windowTitle,
    sf::Style::Close);

}
