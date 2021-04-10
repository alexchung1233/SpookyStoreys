#include "GameLogic.h"
#include "PlayerActor.h"

void GameLogic::setup(){
  createPlayer();
}

GameLogic::GameLogic(){

}

void GameLogic::createPlayer(){
  player = PlayerActor();
  player.init();
}

PlayerActor GameLogic::getPlayer(){
  return player;
}

void GameLogic::upPressed(){
  player.moveUp(1);
}
