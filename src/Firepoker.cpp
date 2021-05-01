#include "Firepoker.h"

Firepoker::Firepoker(vector<string> inputVector){
    this->position = Position(stoi(inputVector.at(0)), stoi(inputVector.at(1)));
}
void Firepoker::init(){
    this->myDialogue = "A fire poker! Maybe I can use this to reach high places?";
    this->itemName = "firepoker";
    canBeDestroyed = true;
    mySize.x = 47;
    mySize.y = 93;

}
Position Firepoker::getPosition(){
    return position;
}

void Firepoker::setPosition(float x, float y){
    position.x = x;
    position.y = y;
}

string Firepoker::interact(PlayerActor &player){
    return myDialogue;
}

bool Firepoker::nextToPlayer(PlayerActor &player){
    bool close = false;
    int diffx = abs(player.getPosition().x - (this->getPosition().x + mySize.x/2));
    int diffy = abs(player.getPosition().y - (this->getPosition().y + mySize.y/2));
    if(diffx < mySize.x/2 + 10 && diffy < mySize.y/2 + 10){
        close = true;
    }
    return close;
}

void Firepoker::setSize(sf::Vector2f size){
  mySize.x = size.x;
  mySize.y = size.y;

}

void Firepoker::setSize(float x, float y){
  mySize.x = x;
  mySize.y = y;
}

sf::Vector2f Firepoker::getSize(){
  return mySize;
}