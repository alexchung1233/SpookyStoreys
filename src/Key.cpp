#include "Key.h"

Key::Key(){
}

void Key::init(){
    string myDialogue;
    bool pickedup = false;
    Position position;
}

Position Key::getPosition(){
    return position;
}

void Key::setPosition(float x, float y){
    position.x = x;
    position.y = y;
}


void Key::use(){
    this->pickedup = false;
}

bool Key::obtained(){
    return this->pickedup;
}

string Key::interact(PlayerActor &player, DialogueBox &box){
    string input = "A key!";
    box.setText(box.message, box.dialogueBox, input);
    this->pickedup = true;
    return input;
}

bool Key::nextToPlayer(PlayerActor &player){
   bool close = false;
    int diffx = abs(player.getPosition().x - this->getPosition().x);
    int diffy = abs(player.getPosition().y - this->getPosition().y);
    if(diffx < 15 && diffy < 15)
        close = true;
    return close;
}