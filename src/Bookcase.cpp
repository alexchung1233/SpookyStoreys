#include "Bookcase.h"

Bookcase::Bookcase(vector<string> inputVector){
    this->position = Position(stoi(inputVector.at(0)), stoi(inputVector.at(1)));
}
void Bookcase::init(){
    this->myDialogue = "So many books...";
    this->itemName = "bookcase";
    canBeDestroyed = false;
    mySize.x = 204;
    mySize.y = 215;

}
Position Bookcase::getPosition(){
    return position;
}

void Bookcase::setPosition(float x, float y){
    position.x = x;
    position.y = y;
}

string Bookcase::interact(PlayerActor &player){
    return myDialogue;
}

bool Bookcase::nextToPlayer(PlayerActor &player){
    bool close = false;
    int diffx = abs(player.getPosition().x - (this->getPosition().x + mySize.x/2));
    int diffy = abs(player.getPosition().y - (this->getPosition().y + mySize.y/2));
    if(diffx < mySize.x/2 + 10 && diffy < mySize.y/2 + 10){
        close = true;
    }
    return close;
}

void Bookcase::setSize(sf::Vector2f size){
  mySize.x = size.x;
  mySize.y = size.y;

}

void Bookcase::setSize(float x, float y){
  mySize.x = x;
  mySize.y = y;
}

sf::Vector2f Bookcase::getSize(){
  return mySize;
}