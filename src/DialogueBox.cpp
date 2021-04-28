#include "DialogueBox.h"

DialogueBox::DialogueBox(){
}

void DialogueBox::init(){
    makeBox(sf::Vector2f(400, 490), sf::Color::Black);
    tracker = 0; //counter to determine if the dialogue box should be shown, if the player is interacting with an item
    if (!font.loadFromFile("../data/Lato-Bold.ttf")){
        std::cout << "incorrect font";
    }
}


void DialogueBox::makeBox(sf::Vector2f position, sf::Color color){
    this->dialogueBox.setFillColor(color);
    this->dialogueBox.setSize(sf::Vector2f(790, 40));
    this->dialogueBox.setOutlineColor(sf::Color::White);
    this->dialogueBox.setOutlineThickness(2);

    sf::Vector2f myPos = sf::Vector2f(position.x - this->dialogueBox.getSize().x/2, 550);

    dialogueBox.setPosition(myPos);
}


void DialogueBox::setText(std::string string){
  this->message.setString(string);
  this->message.setCharacterSize(15);
  this->message.setFillColor(sf::Color::Red);
  this->message.setFont(font);

  sf::FloatRect boxBounds = this->dialogueBox.getGlobalBounds();
  sf::FloatRect textBounds = this->message.getLocalBounds();

  sf::Vector2f myPos = sf::Vector2f(boxBounds.left + boxBounds.width/2 - textBounds.width/2,
    boxBounds.top + boxBounds.height/2.7 - textBounds.height/2);

  this->message.setPosition(myPos);

}

int DialogueBox::getDialogueLimit(){
  return dialogueLimit;
}
