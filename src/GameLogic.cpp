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

void GameLogic::setDifficulty(int diff){
	if(diff == 0){
		//set monster speed slow
	}
	if(diff == 1){
		//set monster speed normal
	}
	if(diff == 2){
		//set monster speed FAST
	}
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