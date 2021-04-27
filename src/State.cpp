#include "State.h"

State::State(sf::RenderWindow& app){
  this->App = &app;
  this->status = UNINIT;
}


State::~State(){


}

void State::init(){
  this->status = RUNNING;
}
