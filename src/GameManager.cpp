#include "GameManager.h"
#include "GameView.h"
#include "Menu.h"
#include "GameOver.h"
#include "ScriptManager.h"


GameManager::GameManager(){
  initWindow();
  initVariables();
  initStates();
}

void GameManager::initVariables(){
  srand(time(0));
  this-> dt = 0.f;
  audioManager.init();

  //initial starting state
  this->stateQueue.push(new Menu(*window, *audioManagerPTR));
  initStates();

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
  //updates the current gamestate by getting the top of the queue


  State* currentState = this->stateQueue.front();

  //this handles the transitioning of states from one state to another
  if(!this->stateQueue.empty()){
    //as long as the queue is not empty and the current state is running
    //then update
    if(currentState->getStatus() == State::RUNNING){
      currentState->update(event, dt);
    }
    //if the current state is has finished then pop it off the queue
    else if(currentState->isDead()){
      if(currentState->getStatus() == State::SUCCESS){
        //get the next gamestate after the current state finishes
        if(currentState->hasChildState()){

          stateQueue.push(currentState->getChildState());

        }
      }
      this->stateQueue.pop();
      initStates();

    }
  }
}

void GameManager::render(){
  //handles rendering the gamestate
  this->window->display();

  if(!this->stateQueue.empty()){
    this->stateQueue.front()->render();
  }


}

void GameManager::initStates(){
  if(stateQueue.front()->getStatus() == State::UNINIT)
    this->stateQueue.front()->init();
}

void GameManager::initWindow(){
  std::string windowTitle = "Spooky Storeys";

  //creates the window object
  this->window = new sf::RenderWindow(
    sf::VideoMode(900,600,32),
    windowTitle,
    sf::Style::Close);

}
