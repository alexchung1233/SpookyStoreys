#include "PlayerActor.h"
#include "MovementStates.h"


PlayerActor::PlayerActor(){
}

void PlayerActor::init(){
  position = Position(400.f, 300.f);
  characterVelocity = sf::Vector2f(0,0);
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
}

void PlayerActor::moveDown(float deltaMS){
  characterVelocity.y = velocityConst;
  position.y += deltaMS * characterVelocity.y;
}

void PlayerActor::moveLeft(float deltaMS){
  characterVelocity.x = -velocityConst;
  position.x += deltaMS * characterVelocity.x;
}

void PlayerActor::moveRight(float deltaMS){
  characterVelocity.x = velocityConst;
  position.x += deltaMS * characterVelocity.x;
}

void PlayerActor::resetVelocity(){
  characterVelocity.x = 0;
  characterVelocity.y = 0;
}

MovementStates::movementStates PlayerActor::getMovementState(){
    if((int)characterVelocity.x  == 0 && (int)characterVelocity.y == 0){
      return MovementStates::IDLE;
    }
    else if(characterVelocity.x  < 0.f && characterVelocity.y == 0.f){
      return MovementStates::MOVING_LEFT;
    }
    else if(characterVelocity.x  > 0.f && characterVelocity.y == 0.f){
      return MovementStates::MOVING_RIGHT;
    }
    else if(characterVelocity.x  == 0.f && characterVelocity.y < 0.f){
      return MovementStates::MOVING_UP;
    }
    else if(characterVelocity.x  == 0.f && characterVelocity.y > 0.f){
      return MovementStates::MOVING_DOWN;
    }

}
