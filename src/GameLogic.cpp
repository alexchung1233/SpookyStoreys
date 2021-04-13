#include "GameLogic.h"
#include "PlayerActor.h"
#include <iostream>


GameLogic::GameLogic(){
	setup();
	myRoom.setUpRoom();
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
	if(!detectCollisionUp())
		player.moveUp(dt);
}

void GameLogic::downPressed(float dt){
	if(!detectCollisionDown())
		player.moveDown(dt);
}

void GameLogic::leftPressed(float dt){
	if(!detectCollisionLeft())
		player.moveLeft(dt);
}

void GameLogic::rightPressed(float dt){
	if(!detectCollisionRight())
		player.moveRight(dt);
}

bool GameLogic::detectCollisionUp(){
	if((player.getPosition().y - player.getVelocity().y) < myRoom.myBoundaries[3])
		return true;
	return false;
}

bool GameLogic::detectCollisionDown(){
	if((player.getPosition().y + player.getVelocity().y + player.getSize().y) > (myRoom.myBoundaries[1] + myRoom.myBoundaries[3]))
		return true;
	return false;
}

bool GameLogic::detectCollisionLeft(){	
	if((player.getPosition().x - player.getVelocity().x) < myRoom.myBoundaries[2])
		return true;
	return false;
}

bool GameLogic::detectCollisionRight(){
	if((player.getPosition().x + player.getVelocity().x + player.getSize().x) > (myRoom.myBoundaries[0] + myRoom.myBoundaries[2]))
		return true;
	return false;
}

void GameLogic::setRoom(Room room){
	this->myRoom = room;
	myRoom.setUpRoom();
}