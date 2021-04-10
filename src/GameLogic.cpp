#include "GameLogic.h"
#include "PlayerActor.h"

GameLogic::setup(){
  createPlayer();
}

void GameLogic::createPlayer(){

}


PlayerActor GameLogic::getPlayer(){
  return player;
}
