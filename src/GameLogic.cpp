#include "GameLogic.h"
#include "PlayerActor.h"
#include "DialogueBox.h"
#include <iostream>


GameLogic::GameLogic(){
	setup();

	//set up the very first room
	myRoom.setUpRoom("../data/room_data.txt");
}

void GameLogic::setup(){
	createPlayer();
	createDialogueBox();
	createWater();
	Etracker = 0; //keeps track of the number of times E is pressed to handle locking the player when they interact with an item
}

void GameLogic::createPlayer(){
	player = PlayerActor();
	player.init();
}


void GameLogic::createDialogueBox(){
	dialogue = DialogueBox();
	dialogue.init();
}

void GameLogic::createWater(){
	water = HolyWater();
	water.init();
	water.setPosition(479.f, 152.f);
}

PlayerActor GameLogic::getPlayer(){
  return player;
}

HolyWater GameLogic::getWater(){
	return water;
}

DialogueBox GameLogic::getDialogueBox(){
	return dialogue;
}

void GameLogic::EPressed(){
	if(water.nextToPlayer(player)){
		Etracker++; //toggle player movement, locks player if they are interacting with an item
		dialogue.tracker++; //toggle the dialogue box, shows the dialogue box if the player is interacting with an item
		water.interact(player, dialogue);
	}else{
		dialogue.message.setString(" ");
	}
}

void GameLogic::upPressed(float dt){
	if (Etracker%4 == 0 || Etracker == 0){ //if the player is interacting with an item, do not let them move
		if(!detectCollisionUp(dt))
		player.moveUp(dt);
	}
}

void GameLogic::downPressed(float dt){
	if (Etracker%4 == 0 || Etracker == 0){
		if(!detectCollisionDown(dt))
		player.moveDown(dt);
	}
}

void GameLogic::leftPressed(float dt){
	if (Etracker%4 == 0 || Etracker == 0){
		if(!detectCollisionLeft(dt))
			player.moveLeft(dt);
	}
}

void GameLogic::rightPressed(float dt){
	if (Etracker%4 == 0 || Etracker == 0){
		if(!detectCollisionRight(dt))
			player.moveRight(dt);
	}
}

bool GameLogic::detectCollisionUp(float dt){
	Position playerPos = player.getPosition();
	float movement = dt * player.getVelocity().y;

	if(!myRoom.getBoundaries().contains(playerPos.x, playerPos.y - movement))
		return true;
	
	sf::IntRect check(playerPos.x, playerPos.y - movement, player.getSize().x, player.getSize().y);

	for(int i = 0; i < myRoom.getObstacles().size(); i++){
		sf::IntRect obj = myRoom.getObstacles().at(i);
		if(obj.intersects(check))
			return true;
	}
	return false;
}

bool GameLogic::detectCollisionDown(float dt){
	Position playerPos = player.getPosition();
	float movement = dt * player.getVelocity().y;

	if(!myRoom.getBoundaries().contains(playerPos.x, playerPos.y + movement + player.getSize().y))
		return true;
	
	sf::IntRect check(playerPos.x, playerPos.y + movement, player.getSize().x, player.getSize().y);

	for(int i = 0; i < myRoom.getObstacles().size(); i++){
		sf::IntRect obj = myRoom.getObstacles().at(i);
		if(obj.intersects(check))
			return true;
	}

	return false;
}

bool GameLogic::detectCollisionLeft(float dt){
	Position playerPos = player.getPosition();
	float movement = dt * player.getVelocity().x;

	if(!myRoom.getBoundaries().contains(playerPos.x - movement, playerPos.y))
		return true;

	sf::IntRect check(playerPos.x - movement, playerPos.y, player.getSize().x, player.getSize().y);

	for(int i = 0; i < myRoom.getObstacles().size(); i++){
		sf::IntRect obj = myRoom.getObstacles().at(i);
		if(obj.intersects(check))
			return true;
	}

	return false;
}

bool GameLogic::detectCollisionRight(float dt){
	Position playerPos = player.getPosition();
	float movement = dt * player.getVelocity().x;

	if(!myRoom.getBoundaries().contains(playerPos.x + movement + player.getSize().x, playerPos.y))
		return true;

	sf::IntRect check(playerPos.x + movement, playerPos.y, player.getSize().x, player.getSize().y);
	
	for(int i = 0; i < myRoom.getObstacles().size(); i++){
		sf::IntRect obj = myRoom.getObstacles().at(i);
		if(obj.intersects(check))
			return true;
	}

	return false;
}

void GameLogic::setRoom(Room room){
	//this->myRoom = room;
	//myRoom.setUpRoom();
}