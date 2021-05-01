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

  levelSprite.setTexture(texture);

  sprite_player.setTexture(texture_player);

  sprite_player.setScale(sf::Vector2f(0.80f, 0.80f));

  PlayerActor player = this->inputManager.logic->getPlayer();
  sprite_player.setPosition(player.getPosition().x, player.getPosition().y);

  this->status = State::RUNNING;

}

//update the running game state depending on logic and input
void GameView::update(sf::Event& Event, float dt){
  itemSprites.clear();
  itemTextures.clear();
  inputManager.update(Event, dt);

  //get the latest level texture
  texture = this->levelManager.getLevelTexture();


  //update the level sprite
  levelSprite.setTexture(texture);

  PlayerActor player = this->inputManager.logic->getPlayer();
  sprite_player.setPosition(player.getPosition().x, player.getPosition().y);


  if(inputManager.getPlayState() == 1){
    this->status = State::SUCCESS;
    childState = new GameOver(*App, "You Win!");
  }
  else if(inputManager.getPlayState() == 2){
    this->status = State::SUCCESS;
    childState = new GameOver(*App, "You Lose...");
  }

  Room tempRoom = levelManager.getCurrentRoom();

  for(int i = 0; i < tempRoom.getItems().size(); i++) {

    ItemActor* item = tempRoom.getItems().at(i);

    itemTextures.push_back(new sf::Texture);

    if(!itemTextures.back()->loadFromFile(item->getSpriteFile())){
      printf("incorrect file format");
    }

    itemSprites.push_back(new sf::Sprite);

    texture_item = itemTextures.back();
    itemSprites.back()->setTexture(*texture_item);
    itemSprites.back()->setPosition(item->getPosition().x, item->getPosition().y);

    inputManager.logic->setUpDialogueBox(item, dialoguebox, i);
    
  }

  if(!dialoguebox.getUsingState()){
    inputManager.logic->Etracker = 0; //reset Etracker
  }

  //THIS CODE IS TO SEARCH FOR HITBOXES, DON'T DELETE UNTIL WE TURN IN
  // sf::RectangleShape rectangle(sf::Vector2f(540,385));
  // rectangle.setPosition(sf::Vector2f(170,175));
  // rectangle.setOutlineThickness(-3);
  // rectangle.setOutlineColor(sf::Color(250, 150, 100));
  // rectangle.setFillColor(sf::Color::Transparent);
  // this->App->draw(rectangle);
  isDialogue();


}

void GameView::setLogic(GameView& logic){}

//renders the running game
void GameView::render(){
    this->App->clear();
    this->App->draw(levelSprite);
    
    Room tempRoom = levelManager.getCurrentRoom();
    for (int i = 0; i < tempRoom.getItems().size(); i++){
      sf::Sprite* drawMe = itemSprites.at(i);
      this->App->draw(*drawMe);
    }

    this->App->draw(sprite_player);

}


void GameView::isDialogue(){
  if (dialoguebox.tracker <= dialoguebox.getDialogueLimit() && dialoguebox.getUsingState()){ //toggle the dialogue box, if the  player has some sort of interaction
    this->App->draw(dialoguebox.dialogueBox);
    this->App->draw(dialoguebox.message);
  }else if (dialoguebox.tracker == 0 && this->inputManager.logic->Etracker != 0){ //for the first interaction with an item of any kind
    this->App->draw(dialoguebox.dialogueBox);
    this->App->draw(dialoguebox.message);
  }else{
    //cout << "N0";
  }
}


void GameView::pause(){}

void GameView::unpause(){}
