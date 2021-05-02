#include "Safe.h"

Safe::Safe(vector<string> inputVector){
  this->position = Position(stoi(inputVector.at(0)), stoi(inputVector.at(1)));
}
void Safe::init(){
  this->myDialogue = "It's locked... I know that my parents kept the numbers for the code on pieces of note paper...\nI have to find them.";
  this->itemName = "safe";
  canBeDestroyed = false;
  mySize.x = 48;
  mySize.y = 31;
}

Position Safe::getPosition(){
  return position;
}

void Safe::setPosition(float x, float y){
  position.x = x;
  position.y = y;
}

string Safe::interact(PlayerActor &player){
  int numFound = player.getInventory()->numNotesFound();
  switch (numFound){
    case 0:
      this->myDialogue = "It's a locked safe where my parents keep a powerful weapon...\nThey kept the numbers for the code on pieces of note paper. I think that there are 4. I have to find them.";
      break;
    case 4:
      canBeDestroyed = true;
      player.getInventory()->foundWeapon();
      this->myDialogue = "I have all the pages with the code on it...\nThere! It unlocked. Now I have the weapon. It looks like a gun... I hope it works.";
      break;
    default:
      this->myDialogue = "It's my parents' safe. They keep a powerful weapon in here...\nThey keep the numbers for the code on pieces of note paper. I have to find them. I think that there are " + to_string(4 - numFound) + " more...";
  }
  return myDialogue;
}

bool Safe::nextToPlayer(PlayerActor &player){
  bool close = false;
  int diffx = abs(player.getPosition().x - (this->getPosition().x + mySize.x/2));
  int diffy = abs(player.getPosition().y - (this->getPosition().y + mySize.y/2));
  if(diffx < mySize.x/2 + 10 && diffy < mySize.y/2 + 10){
      close = true;
  }
  return close;
}

void Safe::setSize(sf::Vector2f size){
  mySize.x = size.x;
  mySize.y = size.y;

}

void Safe::setSize(float x, float y){
  mySize.x = x;
  mySize.y = y;
}

sf::Vector2f Safe::getSize(){
  return mySize;
}
