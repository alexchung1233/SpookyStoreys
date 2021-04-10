#include "GameLogic.h"
#include "PlayerActor.h"

void GameLogic::setup(){
  createPlayer();
}

void GameLogic::createPlayer(){
  player = PlayerActor();
}

PlayerActor GameLogic::getPlayer(){
  return player;
}

void GameLogic::UpPressed(){
  player.moveUp(1);
}
