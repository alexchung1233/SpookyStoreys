#include "GameView.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <iostream>


using namespace std;


GameView::GameView(){
  //TODO make this extend off a Process class.
  this->status = State::UNINIT;
}

//constructor takes in App
GameView::GameView(sf::RenderWindow& app){
  //TODO make this extend off a Process class.
  this->App = &app;
  this->status = State::UNINIT;

}

void GameView::init(){
  this->levelManager.init();
  this->logic.setup();
  this->logic.setLevelManager(levelManager);
  this->scriptManager.readInScript("test_script");

  transitionRectangleAlphaChannel = 255;

  inputManager(*App, logic);

  texture = this->levelManager.getLevelTexture();

  string player_file = "../data/protag_V1.png";

  if(!texture_player.loadFromFile(player_file)){
    printf("incorrect file format");
  }

  levelSprite.setTexture(texture);
  sprite_player.setTexture(texture_player);
  sprite_player.setScale(sf::Vector2f(0.80f, 0.80f));

  PlayerActor player = this->logic.getPlayer();
  sprite_player.setPosition(player.getPosition().x, player.getPosition().y);

  this->status = State::RUNNING;

}

//update the running game state depending on logic and input
void GameView::update(sf::Event& Event, float dt){
  this->dt = dt;
  inputManager.update(Event, dt);

  texture = this->levelManager.getLevelTexture();
  levelSprite.setTexture(texture);

  PlayerActor player = this->logic.getPlayer();
  sprite_player.setPosition(player.getPosition().x, player.getPosition().y);

  if(inputManager.getPlayState() == 1){
    this->status = State::SUCCESS;
    childState = new GameOver(*App, "You Win!");
  }
  else if(inputManager.getPlayState() == 2){
    this->status = State::SUCCESS;
    childState = new GameOver(*App, "You Lose...");
  }



  //run test script

  ScriptCommand* currentCommand = this->scriptManager.scriptQueue.front();

  if(!this->scriptManager.scriptQueue.empty()){
    if(this->scriptCommandOnFinish(*currentCommand)){
      this->scriptManager.scriptQueue.pop();
    }
    else{
      this->executeScriptCommand(*currentCommand);
    }
  }
  //test script
  //fadeIn(16.f, 0, 0, 0);

  //THIS CODE IS TO SEARCH FOR HITBOXES, DON'T DELETE UNTIL WE TURN IN
  // sf::RectangleShape rectangle(sf::Vector2f(540,385));
  // rectangle.setPosition(sf::Vector2f(170,175));
  // rectangle.setOutlineThickness(-3);
  // rectangle.setOutlineColor(sf::Color(250, 150, 100));
  // rectangle.setFillColor(sf::Color::Transparent);
  // this->App->draw(rectangle);


}

void GameView::setLogic(GameView& logic){}

//renders the running game
void GameView::render(){
    this->App->clear();
    this->App->draw(levelSprite);
    this->App->draw(sprite_player);
    this->App->draw(transitionRectangle);
}

void GameView::pause(){}

void GameView::unpause(){}



void GameView::executeScriptCommand(ScriptCommand command){
  vector<string> data = command.getData();
  switch(command.getCommandType()){
    //matches the command to the type
    case ScriptCommand::FADE_IN:
      fadeIn(
        stof(data.at(1)),stof(data.at(2)), stof(data.at(3)), stof(data.at(4)));
      break;
    case ScriptCommand::MOVE_PLAYER_UP:
      this->logic.upPressed(this->dt);
      break;
  }
}

bool GameView::scriptCommandOnFinish(ScriptCommand command){
  switch(command.getCommandType()){
    case ScriptCommand::FADE_IN:
      if(transitionRectangleAlphaChannel <= 0){
        transitionRectangleAlphaChannel = 255;
        return true;
      }
      return false;
      break;

  }
  return false;

}


//Game Effects

//fades in
void GameView::fadeIn(float duration, int r, int g, int b){
  transitionRectangle.setFillColor(sf::Color(r, g, b, transitionRectangleAlphaChannel));

  float timer = clockFilter.getElapsedTime().asSeconds() * 100;

  if (timer > duration && transitionRectangleAlphaChannel > 0.f)
  {
          clockFilter.restart();
          transitionRectangleAlphaChannel -= 5;

  }

}

//fades out
void GameView::fadeOut(float duration, int r, int g, int b){
  transitionRectangle.setFillColor(sf::Color(r, g, b, transitionRectangleAlphaChannel));

  float timer = clockFilter.getElapsedTime().asSeconds() * 100;

  if (timer > duration && transitionRectangleAlphaChannel < 255.f)
  {
          clockFilter.restart();
          transitionRectangleAlphaChannel += 5;

  }

}
