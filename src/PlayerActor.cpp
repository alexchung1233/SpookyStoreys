#include "PlayerActor.h"


PlayerActor::PlayerActor(){
  this->myInventory = new Inventory();
}

void PlayerActor::init(){
  position = Position(450.f, 330.f);
  characterVelocity = sf::Vector2f(2000.f,2000.f);
  mySize = sf::Vector2f(48.f, 105.6f);
  this->myInventory->init();
}

void PlayerActor::setVelocity(sf::Vector2f vector){
  characterVelocity.x = vector.x;
  characterVelocity.y = vector.y;
}

void PlayerActor::setVelocity(float x, float y){
  characterVelocity.x = x;
  characterVelocity.y = y;
}

sf::Vector2f PlayerActor::getVelocity(){
  return characterVelocity;
}

void PlayerActor::move(){

}
void PlayerActor::setPosition(float x, float y){
  position.x = x;
  position.y = y;
}

Position PlayerActor::getPosition(){
  return position;
}

void PlayerActor::moveUp(float deltaMS){
  position.y -= deltaMS * characterVelocity.y;
  direction.y = 1;
  direction.x = 0;
  this->moveState = MovementStates::movementStates::MOVING_UP;

}

void PlayerActor::moveDown(float deltaMS){
  position.y += deltaMS * characterVelocity.y;
  direction.y = -1;
  direction.x = 0;
  this->moveState = MovementStates::movementStates::MOVING_DOWN;


}

void PlayerActor::moveLeft(float deltaMS){
  position.x -= deltaMS * characterVelocity.x;
  direction.x = -1;
  direction.y = 0;
  this->moveState = MovementStates::movementStates::MOVING_LEFT;



}

void PlayerActor::moveRight(float deltaMS){
  position.x += deltaMS * characterVelocity.x;
  direction.x = 1;
  direction.y = 0;
  this->moveState = MovementStates::movementStates::MOVING_RIGHT;

}

MovementStates::direcStates PlayerActor::getDirectionState(){
  if(direction.x == -1){
    return MovementStates::LEFT;
  }
  else if(direction.x == 1){
    return MovementStates::RIGHT;
  }
  else if(direction.y == 1){
    return MovementStates::UP;
  }
  else if(direction.y == -1){
    return MovementStates::DOWN;
  }
  else {
    return MovementStates::DOWN;
  }
}

MovementStates::movementStates PlayerActor::getMovementState(){
  return this->moveState;
}

void PlayerActor::setSize(sf::Vector2f size){
  mySize.x = size.x;
  mySize.y = size.y;

}

void PlayerActor::setSize(float x, float y){
  mySize.x = x;
  mySize.y = y;
}

sf::Vector2f PlayerActor::getSize(){
  return mySize;
}

Inventory* PlayerActor::getInventory(){
  return myInventory;
}

bool PlayerActor::useHolyWater(){
  if(myInventory->getHolyWaterCount() < 1){
    std::cout << "You don't have any holy water to use!" << std::endl;
    return false;
  }
  else{
    std::cout << "You used the holy water!" << std::endl;
    myInventory->downHolyWaterCount();
    return true;
  }
}
