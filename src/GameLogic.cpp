#include "GameLogic.h"
#include "PlayerActor.h"
#include <iostream>


GameLogic::GameLogic(){
	setup();
}

void GameLogic::setLevelManager(LevelManager &LM){
	this->levelManager = &LM;
	this->myRoom = this->levelManager->getCurrentRoom();
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
	if(!detectCollisionUp(dt))
		player.moveUp(dt);
}

void GameLogic::downPressed(float dt){
	if(!detectCollisionDown(dt))
		player.moveDown(dt);
}

void GameLogic::leftPressed(float dt){
	if(!detectCollisionLeft(dt))
		player.moveLeft(dt);
}

void GameLogic::rightPressed(float dt){
	if(!detectCollisionRight(dt))
		player.moveRight(dt);
}

bool GameLogic::detectCollisionUp(float dt){
	Position playerPos = player.getPosition();
	float movement = dt * player.getVelocity().y;
	
	sf::IntRect possiblePlayerPosition(playerPos.x, playerPos.y - movement, player.getSize().x, player.getSize().y);

	if(hitsDoor(possiblePlayerPosition)){
		return true;
	}

	for(int i = 0; i < myRoom.getObstacles().size(); i++){
		sf::IntRect obj = myRoom.getObstacles().at(i);
		if(obj.intersects(possiblePlayerPosition))
			return true;
	}

	if(!myRoom.getBoundaries().contains(playerPos.x, playerPos.y - movement))
		return true;
	
	return false;
}

bool GameLogic::detectCollisionDown(float dt){
	Position playerPos = player.getPosition();
	float movement = dt * player.getVelocity().y;
	
	sf::IntRect possiblePlayerPosition(playerPos.x, playerPos.y + movement, player.getSize().x, player.getSize().y);

	if(hitsDoor(possiblePlayerPosition)){
		return true;
	}

	for(int i = 0; i < myRoom.getObstacles().size(); i++){
		sf::IntRect obj = myRoom.getObstacles().at(i);
		if(obj.intersects(possiblePlayerPosition))
			return true;
	}

	if(!myRoom.getBoundaries().contains(playerPos.x, playerPos.y + movement + player.getSize().y))
		return true;

	return false;
}

bool GameLogic::detectCollisionLeft(float dt){
	Position playerPos = player.getPosition();
	float movement = dt * player.getVelocity().x;

	sf::IntRect possiblePlayerPosition(playerPos.x - movement, playerPos.y, player.getSize().x, player.getSize().y);
	
	if(hitsDoor(possiblePlayerPosition)){
		return true;
	}

	for(int i = 0; i < myRoom.getObstacles().size(); i++){
		sf::IntRect obj = myRoom.getObstacles().at(i);
		if(obj.intersects(possiblePlayerPosition))
			return true;
	}

	if(!myRoom.getBoundaries().contains(playerPos.x - movement, playerPos.y))
		return true;

	return false;
}

bool GameLogic::detectCollisionRight(float dt){
	Position playerPos = player.getPosition();
	float movement = dt * player.getVelocity().x;

	sf::IntRect possiblePlayerPosition(playerPos.x + movement, playerPos.y, player.getSize().x, player.getSize().y);
	
	if(hitsDoor(possiblePlayerPosition)){
		return true;
	}

	for(int i = 0; i < myRoom.getObstacles().size(); i++){
		sf::IntRect obj = myRoom.getObstacles().at(i);
		if(obj.intersects(possiblePlayerPosition))
			return true;
	}

	if(!myRoom.getBoundaries().contains(playerPos.x + movement + player.getSize().x, playerPos.y))
		return true;

	return false;
}

void GameLogic::setRoom(Room room){
	this->myRoom = room;
}

bool GameLogic::hitsDoor(sf::IntRect possiblePlayerPosition){
	for(int i = 0; i < myRoom.myDoor.size(); i++){
		sf::IntRect doorBoundaries;

		doorBoundaries.left = stoi(myRoom.myDoor.at(0));
		doorBoundaries.top = stoi(myRoom.myDoor.at(1));
		doorBoundaries.width = stoi(myRoom.myDoor.at(2));
		doorBoundaries.height = stoi(myRoom.myDoor.at(3));

		if(doorBoundaries.intersects(possiblePlayerPosition)){
			this->levelManager->setRoom(myRoom.myDoor.at(4));
			player.setPosition(stoi(myRoom.myDoor.at(5)), stoi(myRoom.myDoor.at(6)));
			setRoom(this->levelManager->getCurrentRoom());
			return true;
		}
	}
	return false;
}