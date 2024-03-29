#ifndef DIALOGUE_BOX_H // include guard
#define DIALOGUE_BOX_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Position.h"

using namespace std;

class DialogueBox
{
    public:
        DialogueBox(){};
        DialogueBox(int dialogueLimit);
        void init();
        Position position;
        Position getPosition();
        int getDialogueLimit();
        void setUsingState(bool state){this->currentUsingState=state;}
        bool getUsingState(){return this->currentUsingState;};
        void setDialogue(string dialogue);
        string getDialogue();
        void incrementTracker(){
          this->tracker++;
        }
        void resetTracker();

        int getTracker(){
          return this->tracker;
        }


    private:
        int dialogueLimit;
        bool currentUsingState;
        string dialogue;
        int tracker; //keep track of times item is interacted with to tell if dialogue should be shown - "press E to close dialogue box"


};

#endif
