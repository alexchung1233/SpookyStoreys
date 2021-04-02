#include "menu.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <iostream>


menu::menu(){
  itemSelected = 0;
}

menu::menu(sf::RenderWindow &app){
  this->App = &app;
  itemSelected = 0;
}


void menu::update(sf::Event event){

switch (event.key.code){
  
  case sf::Keyboard::W:
    if (itemSelected > 0) itemSelected--;
    std::cout << itemSelected;
    break;

  case sf::Keyboard::S:
    if (itemSelected < 2) itemSelected++;
    std::cout << itemSelected;
    break;

  case sf::Keyboard::Escape:
    std::cout << itemSelected;
    break;

  case sf::Keyboard::Enter:
    std::cout << itemSelected;
    break;
  
  }

  
}

