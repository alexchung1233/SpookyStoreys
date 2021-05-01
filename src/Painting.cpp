#include "Painting.h"

Painting::Painting(vector<string> inputVector){
    this->position = Position(stoi(inputVector.at(0)), stoi(inputVector.at(1)));
    this->itemName = "painting_" + inputVector.at(2);
    
    if(inputVector.at(2) == "1" || inputVector.at(2) == "2"){
      mySize.x = 52;
      mySize.y = 63;
    }
    else if(inputVector.at(2) == "3"){
      mySize.x = 47;
      mySize.y = 63;
    }
    else{
      mySize.x = 73;
      mySize.y = 47;
    }

}
void Painting::init(){
    this->myDialogue = "A painting!";
    canBeDestroyed = true;
    

}
Position Painting::getPosition(){
    return position;
}

void Painting::setPosition(float x, float y){
    position.x = x;
    position.y = y;
}

string Painting::interact(PlayerActor &player){
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