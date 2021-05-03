#include "Note.h"


Note::Note(vector<string> inputVector){
    this->position = Position(stoi(inputVector.at(0)), stoi(inputVector.at(1)));
    this->id = stoi(inputVector.at(2));
}
void Note::init(){
    this->itemName = "note";

    mySize.x = 47;
    mySize.y = 50;

    if(this->id == 1){
        this->myDialogue = "A note! How lucky!";
        canBeDestroyed = true;
    }
    else if(this->id == 2){
        this->myDialogue = "A note! I can't reach it though...\nMaybe there's something that could help?";
        canBeDestroyed = false;
    }

}
Position Note::getPosition(){
    return position;
}

void Note::setPosition(float x, float y){
    position.x = x;
    position.y = y;
}

string Note::interact(PlayerActor &player){
    if(this->id == 1){
        player.getInventory()->foundNewNote(1);
    }
    else if(this->id == 2){
        if(player.getInventory()->hasFoundFirepoker()){
            this->myDialogue = "The fire poker gave me extra reach to get the note! Thank goodness...";
            canBeDestroyed = true;
            player.getInventory()->foundNewNote(2);
        }        
    }

    return myDialogue;
}

bool Note::nextToPlayer(PlayerActor &player){
    bool close = false;
    int diffx = abs(player.getPosition().x - (this->getPosition().x + mySize.x/2));
    int diffy = abs(player.getPosition().y - (this->getPosition().y + mySize.y/2));

    int reach = 10;
    if(this->id == 2)
        reach = 170;

    if(diffx < mySize.x/2 + 20 && diffy < mySize.y/2 + reach){
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
