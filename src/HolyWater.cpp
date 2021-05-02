#include "HolyWater.h"


HolyWater::HolyWater(vector<string> inputVector){
    this->position = Position(stoi(inputVector.at(0)), stoi(inputVector.at(1)));
}
void HolyWater::init(){
    this->itemName = "holy_water";
    this->health = 3;
    this->myDialogue = "A bottle of holy water? Maybe I can use this on the monster.";
    //this->position;
    this->pickedup = false;

    this->itemName = "holy_water";

    canBeDestroyed = true;

}
Position HolyWater::getPosition(){
    return this->position;
}

void HolyWater::setHealth(int bar){
    this->health = bar;
}

int HolyWater::getHealth(){
    return this->health;
}

void HolyWater::useWater(){
    this->health = this->getHealth();
    if(this->health > 0){
        this->health--;
        this->setHealth(this->health);
    }
}

void HolyWater::resetUse(){
    this->setHealth(3);
}


string HolyWater::interact(PlayerActor &player){
    this->resetUse();
    this->pickedup = true;

    player.getInventory()->upHolyWaterCount();
    return myDialogue;
}

bool HolyWater::nextToPlayer(PlayerActor &player){
    bool close = false;
    int diffx = abs(player.getPosition().x - this->getPosition().x);
    int diffy = abs(player.getPosition().y - this->getPosition().y);
    if(diffx < 50 && diffy < 50)
        close = true;
    return close;
}
void HolyWater::setSize(sf::Vector2f size){
  mySize.x = size.x;
  mySize.y = size.y;

}

void HolyWater::setSize(float x, float y){
  mySize.x = x;
  mySize.y = y;
}

sf::Vector2f HolyWater::getSize(){
  return mySize;
}

bool HolyWater::obtained(){
    return pickedup;
}
