#include "Note.h"


Note::Note(vector<string> inputVector){
    this->position = Position(stoi(inputVector.at(0)), stoi(inputVector.at(1)));
}
void Note::init(){
    this->myDialogue = "A note! How lucky!";
    read = false;

    this->filepath = "../data/note.png";
    canBeDestroyed = true;

    mySize.x = 47;
    mySize.y = 50;

}
Position Note::getPosition(){
    return position;
}

void Note::setPosition(float x, float y){
    position.x = x;
    position.y = y;
}

string Note::interact(PlayerActor &player){
    read = true;
    return myDialogue;
}

bool Note::nextToPlayer(PlayerActor &player){
    bool close = false;
    int diffx = abs(player.getPosition().x - (this->getPosition().x + mySize.x/2));
    int diffy = abs(player.getPosition().y - (this->getPosition().y + mySize.y/2));
    if(diffx < mySize.x/2 + 10 && diffy < mySize.y/2 + 10){
        close = true;
    }
    return close;
}

void Note::setSize(sf::Vector2f size){
  mySize.x = size.x;
  mySize.y = size.y;

}

void Note::setSize(float x, float y){
  mySize.x = x;
  mySize.y = y;
}

sf::Vector2f Note::getSize(){
  return mySize;
}