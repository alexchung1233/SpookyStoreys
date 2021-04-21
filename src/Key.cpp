#include "Key.h"

Key::Key(){
}

void Key::init(){
    string myDialogue;
    int pickup = 0;
}

Position Key::getPosition(){
    return position;
}

void Key::setDialogue(string dialogue){
    this->myDialogue = dialogue;
}

string Key::getDialogue(){
    return this->myDialogue;
}

void Key::use(){
    this->pickup = 0;
}

bool Key::obtained(){
    bool has = false;
    if(this->pickup){
        has = true;
    }
    return has;
}

string Key::interact(PlayerActor &player){
    string input = "A key!";
    if (this->nextToPlayer(player)){
        this->setDialogue(input);
        this->pickup = 1;
    }

    return this->getDialogue();
}

bool Key::nextToPlayer(PlayerActor &player){
   bool close = false;
    int diffx = abs(player.getPosition().x - this->getPosition().x);
    int diffy = abs(player.getPosition().y - this->getPosition().y);
    if(diffx < 15 || diffy < 15)
        close = true;
    return close;
}