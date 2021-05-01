#include "GameLogic.h"
#include "PlayerActor.h"
#include <iostream>


void GameLogic::setLevelManager(LevelManager &LM){
	this->levelManager = &LM;
	this->myRoom = this->levelManager->getCurrentRoom();
}

void GameLogic::setup(){
	createPlayer();
	officeUnlocked = false;
	Etracker = 0; //keeps track of the number of times E is pressed to handle locking the player when they interact with an item
}

void GameLogic::createPlayer(){
	player = PlayerActor();
	player.init();
}

PlayerActor GameLogic::getPlayer(){
  return player;
}

void GameLogic::EPressed(){
	Etracker++;
	//std::cout << Etracker;
}

void GameLogic::setUpDialogueBox(ItemActor* myItem, DialogueBox& myBox, float i){
	if(Etracker == 2 
    && myItem->nextToPlayer(player)
    && !myBox.getUsingState()){
      int sampleLimit = 2;
	  myBox = DialogueBox(sampleLimit);
	  myBox.init();

      myItem->interact(player);
      myBox.setText(myItem->getDialogue());
      myBox.tracker++;
      myBox.setUsingState(true);
      if(myItem->destroyable())
      	levelManager->itemToDestroy(i);
    }
    //checks to see if the dialogue box is currently in use and, if it is, 
    //then it destroys the item that was interacted with, closes the box,
    //and unlocks the player
    else if (Etracker == 4 
      && myBox.getUsingState())
    {
      //dialoguebox.tracker++;
      myBox.setUsingState(false);
      levelManager->destroyItem();
    } 
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
			
			//checks to see if the Office is unlocked and, if it is not,
			//then checks to see if the player has the key.
			//if the player does, then the office unlocks
			if(checkDoor.getNextRoom() == "OFFICE" && !officeUnlocked){

				//if the player has the key, then they unlock the office
				if(player.getInventory()->hasFoundKey()){
					officeUnlocked = true;
					//TODO: prompt dialogue box saying the player has used the key
					//to unlock the door
					std::cout << "It is locked, but teehee I have the key!" << endl;
				}
				else{
					//TODO: prompt dialogue box saying the door is locked
					//and that the player should look for it
					std::cout << "Oh no, it is Locked!!" << endl;
					return false;
				}

			}

			this->levelManager->setRoom(checkDoor.getNextRoom());
			player.setPosition(checkDoor.getNewPosition().x, checkDoor.getNewPosition().y);
			setRoom(this->levelManager->getCurrentRoom());
			return true;
		}
	}

	return false;
}


void GameLogic::update(float dt){
}

void GameLogic::setMovementState(MovementStates::movementStates state){
	player.setMovementState(state);
}

int GameLogic::getPlayState(){
	if(player.getInventory()->hasFoundWeapon()){
		return 1;
	}
	return 0;
}