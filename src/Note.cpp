#include "Note.h"


Note::Note(){
}
void Note::init(){
    myDialogue;
    position;
    read = false;
}
Position Note::getPosition(){
    return position;
}

void Note::setPosition(float x, float y){
    position.x = x;
    position.y = y;
}

void Note::setDialogue(string dialogue){
    myDialogue = dialogue;
}

string Note::getDialogue(){
    return myDialogue;
}

string Note::interact(PlayerActor &player){
    read = true;
    return myDialogue;
}

bool Note::nextToPlayer(PlayerActor &player){
    bool close = false;
    int diffx = abs(player.getPosition().x - this->getPosition().x);
    int diffy = abs(player.getPosition().y - this->getPosition().y);
    if(diffx < 15 && diffy < 15)
        close = true;
    return close;
}
