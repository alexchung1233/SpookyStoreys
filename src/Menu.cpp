#include "Menu.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <iostream>


Menu::Menu(){
  itemSelected = 0;
  init();
}

void Menu::init(){
  startBox.setSize(sf::Vector2f(100, 50));
  startBox.setOutlineColor(sf::Color::White);
  startBox.setOutlineThickness(5);
  startBox.setFillColor(sf::Color::White);
  startBox.setPosition(sf::Vector2f(350, 300));

  loadFont();

  startText.setString("Start");
  startText.setFont(myFont);
  startText.setFillColor(sf::Color::Black);

  sf::FloatRect owo = startBox.getGlobalBounds();
  sf::FloatRect please = startText.getGlobalBounds();

  startText.setPosition(sf::Vector2f(owo.left + owo.width/2 - please.width/2, owo.top + please.height/2));


  difficultyBox.setSize(sf::Vector2f(100, 50));
  difficultyBox.setOutlineThickness(5);
  difficultyBox.setOutlineColor(sf::Color::White);
  difficultyBox.setFillColor(sf::Color::Black);
  difficultyBox.setPosition(sf::Vector2f(350, 400));

  exitBox.setSize(sf::Vector2f(100, 50));
  exitBox.setOutlineColor(sf::Color::White);
  exitBox.setOutlineThickness(5);
  exitBox.setFillColor(sf::Color::Black);
  exitBox.setPosition(sf::Vector2f(350, 500));
}


void Menu::upPressed(){
  if (itemSelected > 0){
    itemSelected--;
    boxSelected(itemSelected);
  }
}

void Menu::downPressed(){
  if (itemSelected < 2){
    itemSelected++;
    boxSelected(itemSelected);
  }
}

int Menu::enterPressed(){
  return itemSelected;
}

sf::RectangleShape Menu::getBox(int i){
  if(i == 0)
    return startBox;
  if(i == 1)
    return difficultyBox;
  if(i == 2)
    return exitBox;
}

sf::Text& Menu::getStartText(){
  return startText;
}

void Menu::boxSelected(int boxInt){

  if(boxInt==0){
    startBox.setFillColor(sf::Color::White);
    difficultyBox.setFillColor(sf::Color::Black);
    startText.setFillColor(sf::Color::Black);

  }
  else if(boxInt==1){
    startBox.setFillColor(sf::Color::Black);
    difficultyBox.setFillColor(sf::Color::White);
    exitBox.setFillColor(sf::Color::Black);
    startText.setFillColor(sf::Color::White);

  }
  else if(boxInt==2){
    difficultyBox.setFillColor(sf::Color::Black);
    exitBox.setFillColor(sf::Color::White);
  }
}

void Menu::loadFont(){
  if(!myFont.loadFromFile("../data/Lato-Bold.ttf"))
    std::cout << "Font unable to load\n";
}