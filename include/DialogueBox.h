#ifndef DIALOGUE_BOX_H // include guard
#define DIALOGUE_BOX_H
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

class DialogueBox
{
    public:
        DialogueBox();
        void init();
        sf::RectangleShape dialogueBox;
        sf::Text message;
        void setText(sf::Text& text, sf::RectangleShape box, std::string string);
        int tracker; //keep track of times item is interacted with to tell if dialogue should be shown - "press E to close dialogue box"
    
    private:
        sf::Font font;
        void makeBox(sf::RectangleShape& box, sf::Vector2f position, sf::Color color);
        
      

};

#endif