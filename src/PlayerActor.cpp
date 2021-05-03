#include "PlayerActor.h"
#include "MovementStates.h"


PlayerActor::PlayerActor(){
  holyWaterCount = 0;
}

void PlayerActor::init(){
  position = Position(400.f, 300.f);
  characterVelocity = sf::Vector2f(2000.f,2000.f);
  mySize = sf::Vector2f(48.f, 105.6f);
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
  if(direction.x == 1){
    return MovementStates::RIGHT;
  }
  if(direction.y == 1){
    return MovementStates::UP;
  }
  if(direction.y == -1){
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

void PlayerActor::upHolyWaterCount(){
  holyWaterCount++;
}

void PlayerActor::downHolyWaterCount(){
  holyWaterCount--;
}

int PlayerActor::getHolyWaterCount(){
  return holyWaterCount;
}