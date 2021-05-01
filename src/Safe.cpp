#include "Safe.h"

Safe::Safe(vector<string> inputVector){
    this->position = Position(stoi(inputVector.at(0)), stoi(inputVector.at(1)));
}
void Safe::init(){
    this->myDialogue = "It's locked. Maybe I need a key?";
    this->filepath = "../data/safe.png";
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