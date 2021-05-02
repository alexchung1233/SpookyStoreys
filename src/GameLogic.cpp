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
}

void GameLogic::createPlayer(){
	player = PlayerActor();
	player.init();
}

PlayerActor GameLogic::getPlayer(){
  return player;
}

void GameLogic::createDialogueBox(){
	int sampleLimit = 1;
	dialogueBox = DialogueBox(sampleLimit);
	dialogueBox.init();
}


void GameLogic::upPressed(float dt){
	if (!isDialogueBoxUsed()){
		if(!detectCollisionUp(dt))
			player.moveUp(dt);
	}
}

void GameLogic::downPressed(float dt){
	if (!isDialogueBoxUsed()){
		if(!detectCollisionDown(dt))
			player.moveDown(dt);
	}
}

void GameLogic::leftPressed(float dt){
	if (!isDialogueBoxUsed()){
		if(!detectCollisionLeft(dt))
			player.moveLeft(dt);
	}
}

void GameLogic::rightPressed(float dt){
	if (!isDialogueBoxUsed()){
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
	//as long as dialogue box current tracker is below diaglost limit and it's being used
	if(dialogueBox.getUsingState()){

		//reset the values of the dialoguebox after it finishes
		if(dialogueBoxFinished()){
			postDialogueBoxUse();
		}
		return true;
		}
	return false;

}

//inidicates if the dialogue box is finished
bool GameLogic::dialogueBoxFinished(){
	if(dialogueBox.getTracker() > dialogueBox.getDialogueLimit())
		return true;
	return false;
}


//logic for when the player is next to the items
//here we set dialoguebox and the current state of the item
bool GameLogic::isPlayerByItem(){
	//goes through list of current room items
	for(int i = 0; i < this->myRoom.getItems().size(); i++){
		if (this->myRoom.getItems().at(i)->nextToPlayer(this->player) &&
			this->myRoom.getItems().at(i)->getActiveStatus()){

			//set the properties for item next to player
			this->currentNextToItem = this->myRoom.getItems().at(i);

			this->currentNextToItem->interact(player);


			return true;
			}
		}
		return false;

}

//handle dialogue box properties when item next to it
void GameLogic::setDialogueBoxStatus(bool state){
	//if there is a item next to player, set the dialogue to that
	dialogueBox.setDialogue(this->currentNextToItem->getDialogue());

	dialogueBox.setUsingState(state);
}


void GameLogic::postDialogueBoxUse(){
	dialogueBox.resetTracker();
	dialogueBox.setUsingState(false);
	if(this->currentNextToItem->destroyable())
		this->currentNextToItem->setActiveStatus(false);
	}


void GameLogic::update(float dt){
}

void GameLogic::setMovementState(MovementStates::movementStates state){
	player.setMovementState(state);
}


//handles together the item and dialoguebox iteraction whenever inputed
void GameLogic::itemAndDialogueBoxHandler(){
	if(!this->isDialogueBoxUsed() && this->isPlayerByItem()){
		this->setDialogueBoxStatus(true);
		dialogueBox.incrementTracker();
	}
	//if the dialogue box is currently opened
	else if(this->isDialogueBoxUsed())
		dialogueBox.incrementTracker();

}
