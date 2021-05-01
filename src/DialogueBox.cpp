#include "DialogueBox.h"

DialogueBox::DialogueBox(int dialogueLimit, string dialogue){
  this->dialogueLimit = dialogueLimit;
  this->dialogue = dialogue;
}

void DialogueBox::init(){
    //counter to determine if the dialogue box should be shown
    //if the player is interacting with an item 
    this->tracker = 0;
    this->currentUsingState = false; 
    this->position = Position(600,0);
    this->dialogueLimit = 2;
}



int DialogueBox::getDialogueLimit(){
  return dialogueLimit;
}

Position DialogueBox::getPosition(){
  return position;
}



