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
	Position playerPos = player.getPosition();
	if(!myRoom.myBoundaries.contains(playerPos.x, playerPos.y - player.getVelocity().y))
		return true;

	for(int i = 0; i < myRoom.myObjects.size(); i++){
		sf::IntRect obj = myRoom.myObjects.at(i);
		sf::IntRect check(playerPos.x, playerPos.y - player.getVelocity().y, player.getSize().x, player.getSize().y);
		if(obj.intersects(check))
			return true;
	}
	return false;
}

bool GameLogic::detectCollisionDown(){
	Position playerPos = player.getPosition();
	if(!myRoom.myBoundaries.contains(playerPos.x, playerPos.y + player.getVelocity().y + player.getSize().y))
		return true;

	for(int i = 0; i < myRoom.myObjects.size(); i++){
		sf::IntRect obj = myRoom.myObjects.at(i);
		sf::IntRect check(playerPos.x, playerPos.y + player.getVelocity().y, player.getSize().x, player.getSize().y);
		if(obj.intersects(check))
			return true;
	}

	return false;
}

bool GameLogic::detectCollisionLeft(){
	Position playerPos = player.getPosition();
	if(!myRoom.myBoundaries.contains(playerPos.x - player.getVelocity().x, playerPos.y))
		return true;

	for(int i = 0; i < myRoom.myObjects.size(); i++){
		sf::IntRect obj = myRoom.myObjects.at(i);
		sf::IntRect check(playerPos.x - player.getVelocity().x, playerPos.y, player.getSize().x, player.getSize().y);
		if(obj.intersects(check))
			return true;
	}

	return false;
}

bool GameLogic::detectCollisionRight(){
	Position playerPos = player.getPosition();
	if(!myRoom.myBoundaries.contains(playerPos.x + player.getVelocity().x + player.getSize().x, playerPos.y))
		return true;

	for(int i = 0; i < myRoom.myObjects.size(); i++){
		sf::IntRect obj = myRoom.myObjects.at(i);
		sf::IntRect check(playerPos.x + player.getVelocity().x, playerPos.y, player.getSize().x, player.getSize().y);
		if(obj.intersects(check))
			return true;
	}

	return false;
}

void GameLogic::setRoom(Room room){
	this->myRoom = room;
	myRoom.setUpRoom();
}