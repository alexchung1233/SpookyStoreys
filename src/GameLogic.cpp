#include "GameLogic.h"
#include "PlayerActor.h"
#include <iostream>


void GameLogic::setLevelManager(LevelManager &LM){
	this->levelManager = &LM;
	this->myRoom = this->levelManager->getCurrentRoom();
}

void GameLogic::setup(){
	createPlayer();
	createDialogueBox();
	Etracker = 0; //keeps track of the number of times E is pressed to handle locking the player when they interact with an item
}

void GameLogic::createPlayer(){
	player = PlayerActor();
	player.init();
}

PlayerActor GameLogic::getPlayer(){
  return player;
}

void GameLogic::createDialogueBox(){
	dialoguebox = DialogueBox();
	dialoguebox.init();
}

DialogueBox GameLogic::getDialogueBox(){
	return dialoguebox;
}

void GameLogic::EPressed(){
	Etracker++;
	dialoguebox.setUsingState(true);
}

void GameLogic::upPressed(float dt){
	if (Etracker%4 == 0){
		if(!detectCollisionUp(dt))
			player.moveUp(dt);
	}
}

void GameLogic::downPressed(float dt){
	if (Etracker%4 == 0){
		if(!detectCollisionDown(dt))
			player.moveDown(dt);
	}
}

void GameLogic::leftPressed(float dt){
	if (Etracker%4 == 0){
		if(!detectCollisionLeft(dt))
			player.moveLeft(dt);
	}
}

void GameLogic::rightPressed(float dt){
	if (Etracker%4 == 0){
		if(!detectCollisionRight(dt))
			player.moveRight(dt);
	}
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
	std::vector<Door> doors = myRoom.getDoors();
	for(int i = 0; i < doors.size(); i++){
		Door checkDoor = doors.at(i);

		if(checkDoor.getDoorBoundaries().intersects(possiblePlayerPosition)){
			this->levelManager->setRoom(checkDoor.getNextRoom());
			player.setPosition(checkDoor.getNewPosition().x, checkDoor.getNewPosition().y);
			setRoom(this->levelManager->getCurrentRoom());
			return true;
		}
	}

	return false;
}

bool GameLogic::isDialogueBoxUsed(){
	//printf("%s", dialoguebox.getUsingState()? "true":"false"); //
	//printf("%d\n ", dialoguebox.tracker);
	if(dialoguebox.tracker <= dialoguebox.getDialogueLimit()
		&& dialoguebox.getUsingState()){ //toggle the dialogue box, if the  player has some sort of interaction
		//printf("%s", dialoguebox.getUsingState()? "true":"false");
		
		return true;
  	}else if(dialoguebox.tracker == 0 && Etracker != 0){ //for the first interaction with an item of any kind
    	return true;
	}else{
		//printf("%s", dialoguebox.getUsingState()? "true":"false");
		return false;
	}
}

bool GameLogic::isPlayerByItem(){
	for(int i = 0; i < this->myRoom.getWaters().size(); i++){
		if (this->myRoom.getWaters().at(i).nextToPlayer(this->player)){
			dialoguebox.dialogue = this->myRoom.getWaters().at(i).getDialogue();
			this->myRoom.getWaters().at(i).interact(this->player);
			return true;
			continue;
		}else{
			return false;
		}
		
	}
}
