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

void GameLogic::upPressed(float dt){
	player.moveUp(dt);
}

void GameLogic::downPressed(float dt){
	player.moveDown(dt);
}

void GameLogic::leftPressed(float dt){
	player.moveLeft(dt);
}

void GameLogic::rightPressed(float dt){
	player.moveRight(dt);
}