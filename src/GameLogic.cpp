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

	this->monsterView.setup();

	this->monsterAI(monsterView);
	monsterAI.setDoorLoc(monsterView.getRandomDoor());

	officeUnlocked = false;
	WTracker = 0;
}

MonsterView& GameLogic::getMonsterView(){
	return this->monsterView;
}

MonsterActor GameLogic::getMonsterActor(){
	return this->monsterView.getMonster();
}

void GameLogic::setMonsterLevelManager(LevelManager &MLM){
	this->monsterView.setLevelManager(MLM);
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
		if(!detectCollisionUp(dt) && !isPlayerLocked())
			player.moveUp(dt);
	}
}

void GameLogic::downPressed(float dt){
	if (!isDialogueBoxUsed()){
		if(!detectCollisionDown(dt) && !isPlayerLocked())
			player.moveDown(dt);
	}
}

void GameLogic::leftPressed(float dt){
	if (!isDialogueBoxUsed()){
		if(!detectCollisionLeft(dt) && !isPlayerLocked())
			player.moveLeft(dt);
	}
}

void GameLogic::rightPressed(float dt){
	if (!isDialogueBoxUsed()){
		if(!detectCollisionRight(dt) && !isPlayerLocked())
			player.moveRight(dt);
		}
}

void GameLogic::WPressed(){
	float distance = 300;
	if(playerAndMonsterInSameRoom()){
		float distX = pow(getMonsterActor().getPosition().x - player.getPosition().x, 2);
  		float distY = pow(getMonsterActor().getPosition().y - player.getPosition().y, 2);
  		distance = sqrt(distX + distY);
	}

	if(distance < 250 && !isDialogueBoxUsed()){
		holyWaterUsed = false;
		WTracker++;
		if (WTracker%2 == 0){
			holyWaterUsed = player.useHolyWater();
			WTracker = 0;
		}
	}
}

bool GameLogic::getHolyWaterUsed(){
	if(holyWaterUsed){
		holyWaterUsed = false;
		return true;
	}
	return false;
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

					if(!this->isDialogueBoxUsed()){
						this->setDialogueBoxStatus(true);
						dialogueBox.setDialogue("The door was locked, but I have the key!");
					}
				}
				else{

					if(!this->isDialogueBoxUsed()){
						this->setDialogueBoxStatus(true);
						dialogueBox.setDialogue("The door is locked... maybe there's a key somewhere?");
					}
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
	if(dialogueBox.getTracker() >= dialogueBox.getDialogueLimit())
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
			dialogueBox.setDialogue(this->currentNextToItem->getDialogue());

			//TODO fix the currentNextToItem implementation
			//for now it destroys right when it interacts with the item
			if(this->currentNextToItem->destroyable())
				this->currentNextToItem->setActiveStatus(false);

			return true;
			}
		}
		return false;

}

//handle dialogue box properties when item next to it
void GameLogic::setDialogueBoxStatus(bool state){
	//if there is a item next to player, set the dialogue to that

	dialogueBox.setUsingState(state);
}


void GameLogic::postDialogueBoxUse(){
	dialogueBox.resetTracker();
	dialogueBox.setUsingState(false);





	}


void GameLogic::updateAI(float dt){
	if(!isDialogueBoxUsed()){
		monsterAI.calculateMove(player, dt, playerAndMonsterInSameRoom(), getHolyWaterUsed());
		monsterAI.setOffice(officeUnlocked);
	}

}

bool GameLogic::playerAndMonsterInSameRoom(){
	std::string playerLevel = myRoom.getRoomTitle();
	std::string monsterLevel = getMonsterView().getRoom().getRoomTitle();

	return playerLevel == monsterLevel;
}

void GameLogic::setPlayerMovementState(MovementStates::movementStates state){
	player.setMovementState(state);
}

void GameLogic::setMonsterMovementState(MovementStates::movementStates state){
	//monsterActor.setMovementState(state);
}


int GameLogic::getPlayState(){
	if(player.getInventory()->hasFoundWeapon()){
		return 1;
	}
	else if(playerAndMonsterInSameRoom()){
		float distX = pow(getMonsterActor().getPosition().x - player.getPosition().x, 2);
    	float distY = pow(getMonsterActor().getPosition().y - player.getPosition().y, 2);

    	if (sqrt(distX + distY) < 70)
			return 2;
	}
	return 0;
}

//handles together the item and dialoguebox iteraction whenever inputed
void GameLogic::itemAndDialogueBoxHandler(){
	if(!this->isDialogueBoxUsed() && this->isPlayerByItem()){
		this->setDialogueBoxStatus(true);
	}
	//if the dialogue box is currently opened
	else if(this->isDialogueBoxUsed()){
		dialogueBox.incrementTracker();
	}



}

//pauses the monster
void GameLogic::pauseMonster(){
	this->monsterAI.pause();
}


//starts up the monster
void GameLogic::startMonster(){
	this->monsterAI.start();
}

void GameLogic::postLogic(){
	this->currentNextToItem = NULL;
}
