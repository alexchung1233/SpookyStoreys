#include "HolyWater.h"


HolyWater::HolyWater(){
}
void HolyWater::init(){
    int health = 3;
    string myDialogue;
}
Position HolyWater::getPosition(){
    return position;
}

void HolyWater::setDialogue(string dialogue){
    this->myDialogue = dialogue;
}

string HolyWater::getDialogue(){
    return this->myDialogue;
}

void HolyWater::setHealth(int bar){
    this->health = bar;
}

int HolyWater::getHealth(){
    return this->health;
}

void HolyWater::useWater(){
    this->health = this->getHealth();
    health--;
    this->setHealth(health);
}

void HolyWater::resetUse(){
    this->setHealth(3);
}

string HolyWater::interact(PlayerActor &player){
    string input = "A bottle of holy water. Maybe I can use this on the monster";
    if(this->nextToPlayer(player)){
        this->setDialogue(input);
        this->resetUse();
    }

    return this->getDialogue();
}

bool HolyWater::nextToPlayer(PlayerActor &player){
    bool close = false;
    int diffx = abs(player.getPosition().x - this->getPosition().x);
    int diffy = abs(player.getPosition().y - this->getPosition().y);
    if(diffx < 15 || diffy < 15)
        close = true;
    return close;
}