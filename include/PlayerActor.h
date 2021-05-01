#ifndef PLAYER_ACTOR_H
#define PLAYER_ACTOR_H

#include "CharacterActor.h"
#include "Inventory.h"

class PlayerActor : public CharacterActor {
public:
  PlayerActor();
  void init();
  void setVelocity(sf::Vector2f vector);
  void setVelocity(float x, float y);
  sf::Vector2f getVelocity();
  void setPosition(float x, float y);
  Position getPosition();

  void move();
  void moveUp(float deltaMS);
  void moveDown(float deltaMS);
  void moveLeft(float deltaMS);
  void moveRight(float deltaMS);

  MovementStates::movementStates getMovementState();
  MovementStates::direcStates getDirectionState();
  void setMovementState(MovementStates::movementStates state){
    this->moveState = state;
  }

  sf::Vector2f getSize();
  void setSize(sf::Vector2f size);
  void setSize(float x, float y);

  void upHolyWaterCount();
  void downHolyWaterCount();
  int getHolyWaterCount();

  Inventory* getInventory();


private:
  Inventory* myInventory;
  int holyWaterCount;

};

#endif
