#include "MonsterActor.h"


MonsterActor::MonsterActor(){
}

void MonsterActor::init(){
  position = Position(400.f, 300.f);
  characterVelocity = sf::Vector2f(100.f,100.f);
  mySize = sf::Vector2f(48.f, 48.f);
}

void MonsterActor::setVelocity(sf::Vector2f vector){
  characterVelocity.x = vector.x;
  characterVelocity.y = vector.y;
}

void MonsterActor::setVelocity(float x, float y){
  characterVelocity.x = x;
  characterVelocity.y = y;
}

sf::Vector2f MonsterActor::getVelocity(){
  return characterVelocity;
}

void MonsterActor::move(){

}

void MonsterActor::setPosition(float x, float y){
  position.x = x;
  position.y = y;
}

Position MonsterActor::getPosition(){
  return position;
}

void MonsterActor::moveUp(float deltaMS){
  position.y -= deltaMS * characterVelocity.y;
  direction.y = 1;
  direction.x = 0;
  this->moveState = MovementStates::movementStates::MOVING_UP;

}

void MonsterActor::moveDown(float deltaMS){
  position.y += deltaMS * characterVelocity.y;
  direction.y = -1;
  direction.x = 0;
  this->moveState = MovementStates::movementStates::MOVING_DOWN;

}

void MonsterActor::moveLeft(float deltaMS){
  position.x -= deltaMS * characterVelocity.x;
  direction.x = -1;
  direction.y = 0;
  this->moveState = MovementStates::movementStates::MOVING_LEFT;

}

void MonsterActor::moveRight(float deltaMS){
  position.x += deltaMS * characterVelocity.x;
  direction.x = 1;
  direction.y = 0;
  this->moveState = MovementStates::movementStates::MOVING_RIGHT;

}

void MonsterActor::setSize(sf::Vector2f size){
  mySize.x = size.x;
  mySize.y = size.y;

}

void MonsterActor::setSize(float x, float y){
  mySize.x = x;
  mySize.y = y;
}

sf::Vector2f MonsterActor::getSize(){
  return mySize;
}

MovementStates::direcStates MonsterActor::getDirectionState(){
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

MovementStates::movementStates MonsterActor::getMovementState(){
  return this->moveState;
}
