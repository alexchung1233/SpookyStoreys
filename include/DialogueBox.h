#ifndef DIALOGUE_BOX_H // include guard
#define DIALOGUE_BOX_H
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

class DialogueBox
{
    public:
        DialogueBox(){};
        DialogueBox(int dialogueLimit);
        void init();
        sf::RectangleShape dialogueBox;
        sf::Text message;
        void setText(std::string string);
        int getDialogueLimit();
        int tracker; //keep track of times item is interacted with to tell if dialogue should be shown - "press E to close dialogue box"
        void setUsingState(bool state){this->currentUsingState=state;}
        bool getUsingState(){return this->currentUsingState;};
    private:
        sf::Font font;
        int dialogueLimit;
        void makeBox(sf::Vector2f position, sf::Color color);
        bool currentUsingState;



};

#endif
