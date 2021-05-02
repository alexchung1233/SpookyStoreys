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
	Position monsterPos = monster.getPosition();
	float movement = dt * monster.getVelocity().y;

	sf::IntRect possibleMonsterPosition(monsterPos.x, monsterPos.y - movement, monster.getSize().x, monster.getSize().y);

	if(hitsDoor(possibleMonsterPosition)){
		return true;
	}

	for(int i = 0; i < myRoom.getObstacles().size(); i++){
		sf::IntRect obj = myRoom.getObstacles().at(i);
		if(obj.intersects(possibleMonsterPosition))
			return true;
	}

	if(!myRoom.getBoundaries().contains(monsterPos.x, monsterPos.y - movement))
		return true;

	return false;
}

bool MonsterView::detectCollisionDown(float dt){
	Position monsterPos = monster.getPosition();
	float movement = dt * monster.getVelocity().y;

	sf::IntRect possibleMonsterPosition(monsterPos.x, monsterPos.y + movement, monster.getSize().x, monster.getSize().y);

	if(hitsDoor(possibleMonsterPosition)){
		return true;
	}

	for(int i = 0; i < myRoom.getObstacles().size(); i++){
		sf::IntRect obj = myRoom.getObstacles().at(i);
		if(obj.intersects(possibleMonsterPosition))
			return true;
	}

	if(!myRoom.getBoundaries().contains(monsterPos.x, monsterPos.y + movement + monster.getSize().y))
		return true;

	return false;
}

bool MonsterView::detectCollisionLeft(float dt){
	Position monsterPos = monster.getPosition();
	float movement = dt * monster.getVelocity().x;

	sf::IntRect possibleMonsterPosition(monsterPos.x - movement, monsterPos.y, monster.getSize().x, monster.getSize().y);

	if(hitsDoor(possibleMonsterPosition)){
		return true;
	}

	for(int i = 0; i < myRoom.getObstacles().size(); i++){
		sf::IntRect obj = myRoom.getObstacles().at(i);
		if(obj.intersects(possibleMonsterPosition))
			return true;
	}

	if(!myRoom.getBoundaries().contains(monsterPos.x - movement, monsterPos.y))
		return true;

	return false;
}

bool MonsterView::detectCollisionRight(float dt){
	Position monsterPos = monster.getPosition();
	float movement = dt * monster.getVelocity().x;

	sf::IntRect possibleMonsterPosition(monsterPos.x + movement, monsterPos.y, monster.getSize().x, monster.getSize().y);

	if(hitsDoor(possibleMonsterPosition)){
		return true;
	}

	for(int i = 0; i < myRoom.getObstacles().size(); i++){
		sf::IntRect obj = myRoom.getObstacles().at(i);
		if(obj.intersects(possibleMonsterPosition))
			return true;
	}


	if(!myRoom.getBoundaries().contains(monsterPos.x + movement + monster.getSize().x, monsterPos.y))
		return true;

	return false;
}

void MonsterView::setRoom(Room room){
	this->myRoom = room;
}

Room MonsterView::getRoom(){
	return (this->myRoom);
}

bool MonsterView::hitsDoor(sf::IntRect possibleMonsterPosition){
	//Gets list of doors and iterates through them
	std::vector<Door> doors = myRoom.getDoors();
	for(int i = 0; i < doors.size(); i++){
		Door checkDoor = doors.at(i);

		//If the monster intersects with the door
		if(checkDoor.getDoorBoundaries().intersects(possibleMonsterPosition)){
			//Set the current room and monster position to the values dictated by the door
			this->levelManager->setRoom(checkDoor.getNextRoom());
			monster.setPosition(checkDoor.getNewPosition().x, checkDoor.getNewPosition().y);
			setRoom(this->levelManager->getCurrentRoom());

			//Get a new target door
			sf::Vector2f newDoor = getRandomDoor();
			newDoorX = newDoor.x;
			newDoorY = newDoor.y;

			return true;
		}
	}

	return false;
}

sf::Vector2f MonsterView::getRandomDoor(){
	//Gets list of possible doors and chooses one to use as the monsters target
	std::vector<Door> doors;
	for(int i = 0; i < myRoom.getDoors().size(); i++){
		if(!(myRoom.getDoors().at(i).getNextRoom() == "OFFICE")){
			//only push office if conditions met
			doors.push_back(myRoom.getDoors().at(i));
		}
	}

	int randomNum = rand() % doors.size();
	Door newDoor = (doors.at(randomNum));
	float width = newDoor.getDoorBoundaries().left + (newDoor.getDoorBoundaries().width/2);
	float height = newDoor.getDoorBoundaries().top + (newDoor.getDoorBoundaries().height/2);
	sf::Vector2f vec = sf::Vector2f(width, height);
	//Sets a variable that indicats that the room has just been changed
	justChangedRooms = true;

	this->newDoorX = vec.x;
	this->newDoorY = vec.y;
	//Returns the center of the door
	return(vec);
}

void MonsterView::sendToBasement(){
	//Set the room to a new basement room object
	this->levelManager->setRoom("BASEMENT");
	monster.setPosition(400, 300);
	setRoom(this->levelManager->getCurrentRoom());
	//Get a new target door
	sf::Vector2f newDoor = getRandomDoor();
	newDoorX = newDoor.x;
	newDoorY = newDoor.y;
}
