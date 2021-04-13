#include "GameLogic.h"
#include "PlayerActor.h"

GameLogic::GameLogic(){
	setup();
}

void GameLogic::setup(){
	createPlayer();
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

void GameLogic::downPressed(){
	player.moveDown(1);
}

void GameLogic::leftPressed(){
	player.moveLeft(1);
}

void GameLogic::rightPressed(){
	player.moveRight(1);
}