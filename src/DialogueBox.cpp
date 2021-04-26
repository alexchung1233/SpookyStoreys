#include "DialogueBox.h"

DialogueBox::DialogueBox(){
}

void DialogueBox::init(){
    makeBox(dialogueBox, sf::Vector2f(400, 490), sf::Color::Black);
    tracker = 0; //counter to determine if the dialogue box should be shown, if the player is interacting with an item
    if (!font.loadFromFile("../data/Lato-Bold.ttf")){
        std::cout << "incorrect font";
    }
}


void DialogueBox::makeBox(sf::RectangleShape& box, sf::Vector2f position, sf::Color color){
    box.setFillColor(color);
    box.setSize(sf::Vector2f(790, 40));
    box.setOutlineColor(sf::Color::White);
    box.setOutlineThickness(5);

    sf::Vector2f myPos = sf::Vector2f(position.x - box.getSize().x/2, 550);

    dialogueBox.setPosition(myPos);
}


void DialogueBox::setText(sf::Text& text, sf::RectangleShape box, std::string string){
  text.setString(string);
  text.setCharacterSize(15);
  text.setFillColor(sf::Color::Red);
  text.setFont(font);

  sf::FloatRect boxBounds = box.getGlobalBounds();
  sf::FloatRect textBounds = text.getLocalBounds();

  sf::Vector2f myPos = sf::Vector2f(boxBounds.left + boxBounds.width/2 - textBounds.width/2,
    boxBounds.top + boxBounds.height/2.7 - textBounds.height/2);

  text.setPosition(myPos);

} 