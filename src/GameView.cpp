#include "GameView.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <iostream>
#include "InputManager.h"


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

  inputManager(*App, logic);

  //get current level texture
  texture = this->levelManager.getLevelTexture();

  string player_file = "../data/protag_V1.png";

  if(!texture_player.loadFromFile(player_file)){
    printf("incorrect file format");
  }

  string holywater_file = "../data/holy_water.png";

  if(!texture_water.loadFromFile(holywater_file)){
    printf("incorrect file format");
  }

  levelSprite.setTexture(texture);

  sprite_player.setTexture(texture_player);
  sprite_holywater.setTexture(texture_water);
  sprite_holywater.setPosition(sf::Vector2f(479.f, 152.f));

  sprite_player.setScale(sf::Vector2f(0.80f, 0.80f));

  PlayerActor player = this->logic.getPlayer();
  sprite_player.setPosition(player.getPosition().x, player.getPosition().y);

  this->status = State::RUNNING;

}

//update the running game state depending on logic and input
void GameView::update(sf::Event& Event, float dt){
  inputManager.update(Event, dt);

  //get the latest level texture
  texture = this->levelManager.getLevelTexture();

  //update the level sprite
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
    DialogueBox dialogue = this->logic.getDialogueBox();
    HolyWater water = this->logic.getWater();
    this->App->clear();
    this->App->draw(levelSprite);
    this->App->draw(sprite_player);
    this->App->draw(sprite_player);
    if(!water.obtained()){
      this->App->draw(sprite_holywater);
    }

    this->isDialogue(dialogue);

}


void GameView::isDialogue(DialogueBox& box){
  if (box.tracker%4 != 0){ //toggle the dialogue box, if the  player has some sort of interaction
    this->App->draw(box.dialogueBox);
    this->App->draw(box.message);
  }else if (box.tracker == 0 && this->logic.Etracker != 0){ //for the first interaction with an item of any kind
    this->App->draw(box.dialogueBox);
    this->App->draw(box.message);
  }
}

void GameView::pause(){}

void GameView::unpause(){}
