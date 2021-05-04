#include "DialogueBox.h"

DialogueBox::DialogueBox(int dialogueLimit){
  this->dialogueLimit = dialogueLimit;
}

void DialogueBox::init(){
    //counter to determine if the dialogue box should be shown
    //if the player is interacting with an item
    this->tracker = 0;
    this->currentUsingState = false;
    this->position = Position(450,0);
    this->dialogueLimit = 2;
}



int DialogueBox::getDialogueLimit(){
  return dialogueLimit;
}

void DialogueBox::setDialogue(string dialogue){
  this->dialogue = dialogue;
}

string DialogueBox::getDialogue(){
  return this->dialogue;
}

Position DialogueBox::getPosition(){
  return position;
}

void DialogueBox::resetTracker(){
  this->tracker = 0;
}
