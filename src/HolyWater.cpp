#include "HolyWater.h"


HolyWater::HolyWater(){
}
void HolyWater::init(){
    int health = 3;
    string myDialogue = "Nothing\0";
    Position position;
    int pickedup = 0;
}
Position HolyWater::getPosition(){
    return position;
}

void HolyWater::setPosition(float x, float y){
    position.x = x;
    position.y = y;
}

void HolyWater::setHealth(int bar){
    this->health = bar;
}

int HolyWater::getHealth(){
    return this->health;
}

void HolyWater::useWater(){
    this->health = this->getHealth();
    if(health > 0){
        health--;
        this->setHealth(health);
    }
        
}

void HolyWater::resetUse(){
    this->setHealth(3);
}


string HolyWater::interact(PlayerActor &player, DialogueBox &box){
    string input = "A bottle of holy water. Maybe I can use this on the monster\0";
    this->resetUse();
    box.setText(box.message, box.dialogueBox, input);
    pickedup = true;
    return input;
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