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

  if(myFont.loadFromFile("../data/Lato-Bold.ttf"))
    std::cout << "i load!\n";
  startText.setString("Start");
  startText.setFont(myFont);
  startText.setFillColor(sf::Color::Black);
  startText.setPosition(sf::Vector2f(350, 300));

  std::cout << (void*)(&myFont);
  std::cout << "\n";


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

void Menu::boxSelected(int boxInt){

  if(boxInt==0){
    startBox.setFillColor(sf::Color::White);
    difficultyBox.setFillColor(sf::Color::Black);
  }
  else if(boxInt==1){
    startBox.setFillColor(sf::Color::Black);
    difficultyBox.setFillColor(sf::Color::White);
    exitBox.setFillColor(sf::Color::Black);
  }
  else if(boxInt==2){
    difficultyBox.setFillColor(sf::Color::Black);
    exitBox.setFillColor(sf::Color::White);
    
  }
}

sf::RectangleShape Menu::getStartBox(){
  return startBox;
}

sf::RectangleShape Menu::getDifficultyBox(){
  return difficultyBox;
}

sf::RectangleShape Menu::getExitBox(){
  return exitBox;
}

sf::Text& Menu::getStartText(){
  return startText;
}






