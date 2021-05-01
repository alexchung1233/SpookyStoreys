#include "Bathtub.h"

Bathtub::Bathtub(vector<string> inputVector){
    this->position = Position(stoi(inputVector.at(0)), stoi(inputVector.at(1)));
}
void Bathtub::init(){
    this->myDialogue = "A tub!";
    this->itemName = "bathtub";
    canBeDestroyed = true;
    mySize.x = 199;
    mySize.y = 374;

}
Position Bathtub::getPosition(){
    return position;
}

void Bathtub::setPosition(float x, float y){
    position.x = x;
    position.y = y;
}

string Bathtub::interact(PlayerActor &player){
    return myDialogue;
}

bool Bathtub::nextToPlayer(PlayerActor &player){
    bool close = false;
    int diffx = abs(player.getPosition().x - (this->getPosition().x + mySize.x/2));
    int diffy = abs(player.getPosition().y - (this->getPosition().y + mySize.y/2));
    if(diffx < mySize.x/2 + 60 && diffy < mySize.y/2 + 10){
        close = true;
    }
    return close;
}

void Bathtub::setSize(sf::Vector2f size){
  mySize.x = size.x;
  mySize.y = size.y;

}

void Bathtub::setSize(float x, float y){
  mySize.x = x;
  mySize.y = y;
}

sf::Vector2f Bathtub::getSize(){
  return mySize;
}