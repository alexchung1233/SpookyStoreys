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

  PlayerActor player = this->logic.getPlayer();
  sprite_player.setPosition(player.getPosition().x, player.getPosition().y);

  this->status = State::RUNNING;

}

void GameView::createDialogueBox(){
	int sampleLimit = 2;
	dialoguebox = DialogueBox(sampleLimit);
	dialoguebox.init();
}

/*void GameView::createHolyWater(){
  water = HolyWater();
  water.init();
}

HolyWater GameView::getHolyWater(){
  return water;
}*/

//update the running game state depending on logic and input
void GameView::update(sf::Event& Event, float dt){
  itemSprites.clear();
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

  Room tempRoom = levelManager.getCurrentRoom();

  for(int i = 0; i < tempRoom.getItems().size(); i++) {


    ItemActor* item = tempRoom.getItems().at(i);
    //std::cout << item->getDialogue() << endl;


    if(!texture_item.loadFromFile(item->getSpriteFile())){
      printf("incorrect file format");
    }

    sprite_item.setTexture(texture_item);
    sprite_item.setPosition(item->getPosition().x, item->getPosition().y);

    itemSprites.push_back(sprite_item);    


    if(logic.Etracker == 2 
    && item->nextToPlayer(player)
    && !dialoguebox.getUsingState()){
      createDialogueBox();
      item->interact(player);
      dialoguebox.setText(item->getDialogue());
      dialoguebox.tracker++;
      dialoguebox.setUsingState(true);
      levelManager.itemToDestroy(i);

      //TODO fix to allow for only one interaction per holywater
    }

    else if (logic.Etracker == 4 //to handle dialogue tracker to only have the dialogue box come up after the first interaction 
      && dialoguebox.getUsingState())
    { //else if statement does not work
      //dialoguebox.tracker++;
      dialoguebox.setUsingState(false);
      levelManager.destroyItem();

      //std::cout << "SCREAAMS" << endl;
    } 
    
  }

  if(!dialoguebox.getUsingState()){
    logic.Etracker = 0; //reset Etracker
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
        //if(!this->room.getWaters().at(i).obtained()){
          
          this->App->draw(itemSprites.at(i));
       // }
      //}
    }
    this->App->draw(sprite_player);

      


}


void GameView::isDialogue(){
  if (dialoguebox.tracker <= dialoguebox.getDialogueLimit() && dialoguebox.getUsingState()){ //toggle the dialogue box, if the  player has some sort of interaction
    this->App->draw(dialoguebox.dialogueBox);
    this->App->draw(dialoguebox.message);
  }else if (dialoguebox.tracker == 0 && this->logic.Etracker != 0){ //for the first interaction with an item of any kind
    this->App->draw(dialoguebox.dialogueBox);
    this->App->draw(dialoguebox.message);
  }else{
    //cout << "N0";
  }
}



void GameView::pause(){}

void GameView::unpause(){}
