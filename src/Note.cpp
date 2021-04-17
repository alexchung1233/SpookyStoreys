#include "Note.h"


Note::Note(){
}
void Note::init(){
    string myDialogue;
}
Position Note::getPosition(){
    return position;
}
void Note::setDialogue(string dialogue){
    this->myDialogue = dialogue;
}
string Note::getDialogue(){
    return this->myDialogue;
}
string Note::interact(PlayerActor &player, string message){
    string input = message;
    if(this->nextToPlayer(player)){
        this->setDialogue(input);
    }

    return this->getDialogue();
}

bool Note::nextToPlayer(PlayerActor &player){
    bool close = false;
    int diffx = abs(player.getPosition().x - this->getPosition().x);
    int diffy = abs(player.getPosition().y - this->getPosition().y);
    if(diffx < 15 || diffy < 15)
        close = true;
    return close;
}

