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

	officeUnlocked = false;
	Etracker = 0; //keeps track of the number of times E is pressed to handle locking the player when they interact with an item
	WTracker = 0;
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
	dialoguebox = DialogueBox(sampleLimit);
	dialoguebox.init();
}

DialogueBox GameLogic::getDialogueBox(){
	return dialoguebox;
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

void GameLogic::WPressed(){
	WTracker++;
	if (WTracker%2 == 0){
		holyWaterUsed = player.useHolyWater();
		WTracker = 0;
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
					player.getInventory()->useKey();
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

bool GameLogic::isDialogueBoxUsed(){
	//as long as dialogue box current tracker is below diaglost limit and it's being used
	if(dialoguebox.getUsingState()){

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
	if(dialoguebox.tracker <= dialoguebox.getDialogueLimit())
		return false;
	return true;
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
	dialoguebox.setDialogue(this->currentNextToItem->getDialogue());

	dialoguebox.setUsingState(state);
}


void GameLogic::postDialogueBoxUse(){
	dialoguebox.tracker = 0;
	dialoguebox.setUsingState(false);
	if(this->currentNextToItem->destroyable())
		this->currentNextToItem->setActiveStatus(false);
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