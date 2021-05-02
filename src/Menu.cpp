#include "Menu.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <iostream>

Menu::Menu(sf::RenderWindow& app, AudioManager& audioManager){
  this->App = &app;
  itemSelected = 0;
  difficultyLevel = 1;
  this->status = State::UNINIT;
  this->audioManager = &audioManager;
}

Menu::Menu(sf::RenderWindow& app){
  this->App = &app;
  itemSelected = 0;
  difficultyLevel = 1;
  this->status = State::UNINIT;
}


void Menu::init(){
  makeBox(startBox, sf::Vector2f(450, 290), sf::Color::White);
  makeBox(difficultyBox, sf::Vector2f(450, 390), sf::Color::Black);
  makeBox(exitBox, sf::Vector2f(450, 490), sf::Color::Black);

  loadFont(titleFont);
  titleText.setFont(titleFont);
  titleText.setString("Spookey\nStoreys");
  titleText.setCharacterSize(80);
  titleText.setFillColor(sf::Color(200, 0, 0));
  titleText.setPosition(sf::Vector2f(450 - titleText.getGlobalBounds().width/2, 60));

  loadFont(selectableFont);
  startText.setFont(selectableFont);
  difficultyText.setFont(selectableFont);
  exitText.setFont(selectableFont);

  makeText(startText, startBox, sf::Color::Black, "Start");
  makeText(difficultyText, difficultyBox, sf::Color::White, "<\tDifficulty: Normal\t>");
  makeText(exitText, exitBox, sf::Color::White, "Exit");

  this->status = State::RUNNING;

  audioManager->playMenuMusic();

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

int Menu::getDifficulty(){
  return difficultyLevel;
}

void Menu::toggleDifficulty(int i){
  difficultyLevel = difficultyLevel + i;

  if(difficultyLevel < 1){
    difficultyText.setString(" \tDifficulty: Easy\t>");
    difficultyLevel = 0;
  }
  else if(difficultyLevel == 1){
    difficultyText.setString("<\tDifficulty: Normal\t>");
  }
  else if(difficultyLevel > 1){
    difficultyText.setString("<\tDifficulty: EXTREME\t ");
    difficultyLevel = 2;
  }
}

void Menu::boxSelected(int boxInt){

  if(boxInt==0){
    colorSelected(startBox, startText, true);
    colorSelected(difficultyBox, difficultyText, false);
    colorSelected(exitBox, exitText, false);
  }
  else if(boxInt==1){
    colorSelected(startBox, startText, false);
    colorSelected(difficultyBox, difficultyText, true);
    colorSelected(exitBox, exitText, false);
  }
  else if(boxInt==2){
    colorSelected(startBox, startText, false);
    colorSelected(difficultyBox, difficultyText, false);
    colorSelected(exitBox, exitText, true);
  }
}

void Menu::colorSelected(sf::RectangleShape& box, sf::Text& text, bool selected){
  if(selected){
    box.setFillColor(sf::Color::White);
    text.setFillColor(sf::Color::Black);
  }
  else{
    box.setFillColor(sf::Color::Black);
    text.setFillColor(sf::Color::White);
  }
}

void Menu::makeBox(sf::RectangleShape& box, sf::Vector2f position, sf::Color color){
  box.setFillColor(color);
  box.setSize(sf::Vector2f(890, 100));
  box.setOutlineColor(sf::Color::White);
  box.setOutlineThickness(5);

  sf::Vector2f myPos = sf::Vector2f(position.x - box.getSize().x/2, position.y);

  box.setPosition(myPos);

}

void Menu::loadFont(sf::Font& font){
  if(!font.loadFromFile("../data/courier.ttf"))
    std::cout << "Font unable to load\n";
}

void Menu::makeText(sf::Text& text, sf::RectangleShape box, sf::Color color, std::string string){
  text.setString(string);
  text.setCharacterSize(35);
  text.setFillColor(color);

  sf::FloatRect boxBounds = box.getGlobalBounds();
  sf::FloatRect textBounds = text.getLocalBounds();

  sf::Vector2f myPos = sf::Vector2f(boxBounds.left + boxBounds.width/2 - textBounds.width/2,
    boxBounds.top + boxBounds.height/2.7 - textBounds.height/2);

  text.setPosition(myPos);

}

void Menu::update(sf::Event& Event, float dt){
  while(App->pollEvent(Event))
  {
    // Exit
    if(Event.type == sf::Event::Closed) {
      App->close();
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
      App->close();
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
      upPressed();
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
      downPressed();
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
      if(itemSelected == 1){
        toggleDifficulty(-1);
      }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
      if(itemSelected == 1){
        toggleDifficulty(1);
      }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){

      int num = enterPressed();
      if(num == 0){
        audioManager->stopMenuMusic();
        audioManager->playPlayingMusic();
        this->status = State::SUCCESS;
        this->childState = new GameView(*App, *audioManager);
      }
      else if(num == 2){
        App->close();
      }
    }

  }
}

void Menu::render(){
  this->App->clear();

  this->App->draw(titleText);

  this->App->draw(startBox);
  this->App->draw(startText);

  this->App->draw(difficultyBox);
  this->App->draw(difficultyText);

  this->App->draw(exitBox);
  this->App->draw(exitText);

}

void Menu::pause(){}

void Menu::unpause(){}
