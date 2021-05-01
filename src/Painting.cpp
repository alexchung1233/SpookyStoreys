#include "Painting.h"

Painting::Painting(vector<string> inputVector){
  this->position = Position(stoi(inputVector.at(0)), stoi(inputVector.at(1)));
  this->id = stoi(inputVector.at(2));
  this->myDialogue = "A painting...";
}
void Painting::init(){
  canBeDestroyed = true;
  this->itemName = "painting_" + to_string(this->id);

  switch (this->id) {
  case 1:
    mySize.x = 52;
    mySize.y = 63;
    this->myDialogue = "It's a portrait of someone I've never seen before...";
    break;
  case 2:
    mySize.x = 52;
    mySize.y = 63;
    this->myDialogue = "Something feels wrong with this one... I don't want to look at it.";
    break;
  case 3:
    mySize.x = 47;
    mySize.y = 63;
    this->myDialogue = "It's a landscape painting that got turned sideways... Huh? It looks like...\nOh! There's a piece of paper behind it! It's a note!";
    break;
  case 4:
    mySize.x = 73;
    mySize.y = 47;
    this->myDialogue = "A strange mountain. I wish I was there instead of here...";
    break;
  }
}

Position Painting::getPosition(){
  return position;
}

void Painting::setPosition(float x, float y){
  position.x = x;
  position.y = y;
}

string Painting::interact(PlayerActor &player){
  if(this->id == 3){
    player.getInventory()->foundNewNote(3);
  }
  return myDialogue;
}

bool Painting::nextToPlayer(PlayerActor &player){
  bool close = false;
  int diffx = abs(player.getPosition().x - (this->getPosition().x + mySize.x/2));
  int diffy = abs(player.getPosition().y - (this->getPosition().y + mySize.y/2));
  if(diffx < mySize.x/2 + 10 && diffy < mySize.y/2 + 40){
      close = true;
  }
  return close;
}

void Painting::setSize(sf::Vector2f size){
  mySize.x = size.x;
  mySize.y = size.y;

}

void Painting::setSize(float x, float y){
  mySize.x = x;
  mySize.y = y;
}

sf::Vector2f Painting::getSize(){
  return mySize;
}