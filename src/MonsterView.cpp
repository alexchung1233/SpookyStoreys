#include "MonsterView.h"
#include "MonsterActor.h"
#include <iostream>


void MonsterView::setLevelManager(LevelManager &LM){
	this->levelManager = &LM;
	this->myRoom = this->levelManager->getCurrentRoom();
}

void MonsterView::setup(){
	createMonster();
}

void MonsterView::createMonster(){
	monster = MonsterActor();
	monster.init();
}

MonsterActor MonsterView::getMonster(){
  return monster;
}

void MonsterView::upPressed(float dt){
	if(!detectCollisionUp(dt))
		monster.moveUp(dt);
}

void MonsterView::downPressed(float dt){
	if(!detectCollisionDown(dt))
		monster.moveDown(dt);
}

void MonsterView::leftPressed(float dt){
	if(!detectCollisionLeft(dt))
		monster.moveLeft(dt);
}

void MonsterView::rightPressed(float dt){
	if(!detectCollisionRight(dt))
		monster.moveRight(dt);
}

bool MonsterView::detectCollisionUp(float dt){
	Position playerPos = monster.getPosition();
	float movement = dt * monster.getVelocity().y;

	sf::IntRect possiblePlayerPosition(playerPos.x, playerPos.y - movement, monster.getSize().x, monster.getSize().y);

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

bool MonsterView::detectCollisionDown(float dt){
	Position playerPos = monster.getPosition();
	float movement = dt * monster.getVelocity().y;

	sf::IntRect possiblePlayerPosition(playerPos.x, playerPos.y + movement, monster.getSize().x, monster.getSize().y);

	if(hitsDoor(possiblePlayerPosition)){
		return true;
	}

	for(int i = 0; i < myRoom.getObstacles().size(); i++){
		sf::IntRect obj = myRoom.getObstacles().at(i);
		if(obj.intersects(possiblePlayerPosition))
			return true;
	}

	if(!myRoom.getBoundaries().contains(playerPos.x, playerPos.y + movement + monster.getSize().y))
		return true;

	return false;
}

bool MonsterView::detectCollisionLeft(float dt){
	Position playerPos = monster.getPosition();
	float movement = dt * monster.getVelocity().x;

	sf::IntRect possiblePlayerPosition(playerPos.x - movement, playerPos.y, monster.getSize().x, monster.getSize().y);

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

bool MonsterView::detectCollisionRight(float dt){
	Position playerPos = monster.getPosition();
	float movement = dt * monster.getVelocity().x;

	sf::IntRect possiblePlayerPosition(playerPos.x + movement, playerPos.y, monster.getSize().x, monster.getSize().y);

	if(hitsDoor(possiblePlayerPosition)){
		return true;
	}

	for(int i = 0; i < myRoom.getObstacles().size(); i++){
		sf::IntRect obj = myRoom.getObstacles().at(i);
		if(obj.intersects(possiblePlayerPosition))
			return true;
	}

	if(!myRoom.getBoundaries().contains(playerPos.x + movement + monster.getSize().x, playerPos.y))
		return true;

	return false;
}

void MonsterView::setRoom(Room room){
	this->myRoom = room;
}

bool MonsterView::hitsDoor(sf::IntRect possiblePlayerPosition){
	std::vector<Door> doors = myRoom.getDoors();
	for(int i = 0; i < doors.size(); i++){
		Door checkDoor = doors.at(i);

		if(checkDoor.getDoorBoundaries().intersects(possiblePlayerPosition)){
			this->levelManager->setRoom(checkDoor.getNextRoom());
			monster.setPosition(checkDoor.getNewPosition().x, checkDoor.getNewPosition().y);
			setRoom(this->levelManager->getCurrentRoom());
			return true;
		}
	}

	return false;
}
