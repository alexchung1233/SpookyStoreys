#include "PlayerActor.h"
#include "MovementStates.h"


PlayerActor::PlayerActor(){
}

void PlayerActor::init(){
  position = Position(400.f, 300.f);
  characterVelocity = sf::Vector2f(0,0);
  direction = sf::Vector2f(0,0);
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

Position PlayerActor::getPosition(){
  return position;
}

void PlayerActor::moveUp(float deltaMS){
  characterVelocity.y = -velocityConst;
  position.y += deltaMS * characterVelocity.y;
  direction.y = 1;
  direction.x = 0;

}

void PlayerActor::moveDown(float deltaMS){
  characterVelocity.y = velocityConst;
  position.y += deltaMS * characterVelocity.y;
  direction.y = -1;
  direction.x = 0;

}

void PlayerActor::moveLeft(float deltaMS){
  characterVelocity.x = -velocityConst;
  position.x += deltaMS * characterVelocity.x;
  direction.x = -1;
  direction.y = 0;


}

void PlayerActor::moveRight(float deltaMS){
  characterVelocity.x = velocityConst;
  position.x += deltaMS * characterVelocity.x;
  direction.x = 1;
  direction.y = 0;

}

void PlayerActor::resetVelocity(){
  characterVelocity.x = 0;
  characterVelocity.y = 0;
}

MovementStates::movementStates PlayerActor::getMovementState(){
  
    if((int)characterVelocity.x  == 0 && (int)characterVelocity.y == 0){
      return MovementStates::IDLE;
    }

    if(direction.x == -1){
      return MovementStates::MOVING_LEFT;
    }
    if(direction.x == 1){
      return MovementStates::MOVING_RIGHT;
    }
    if(direction.y == 1){
      return MovementStates::MOVING_UP;
    }
    if(direction.y == -1){
      return MovementStates::MOVING_DOWN;
    }
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
