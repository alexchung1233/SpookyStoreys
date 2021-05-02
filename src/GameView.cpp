#include "GameView.h"
#include <string>
#include <iostream>
#include <math.h>
#include "InputManager.h"
#include "Animation.h"
#include "MonsterAI.h"

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


GameView::GameView(sf::RenderWindow& app, AudioManager& audioManager){
  //TODO make this extend off a Process class.
  this->App = &app;
  GameLogic myLogic;
  this->logic = myLogic;
  inputManager(*App, logic);
  this->status = State::UNINIT;
  this->audioManager = &audioManager;
}

void GameView::init(){
  if (!font.loadFromFile("../data/courier.ttf")){
    std::cout << "incorrect font";
  }

  this->levelManager.init();
  this->logic.setup();
  this->logic.setLevelManager(levelManager);

  inputManager(*App, logic);

  //get current level texture
  texture = this->levelManager.getLevelTexture();

  levelSprite.setTexture(texture);


  PlayerActor player = this->inputManager.logic->getPlayer();
  sprite_player.setPosition(player.getPosition().x, player.getPosition().y);

  sprite_player.setPosition(sf::Vector2f(400.f, 300.f));
  string animate_sprite_file = "../data/Protag_Spritesheet.png";

  if(!player_sprite_sheet.loadFromFile(animate_sprite_file)){
    printf("incorrect file format");
  }

  std::string str; 
  ifstream infile;
  infile.open ("../data/itemImageFiles.txt");
  while(!infile.eof())
  {
    std::getline(infile, str);
    std::string filepath = "../data/itemSprites/" + str + ".png";

    itemTextures[str] = new sf::Texture;

    if(!itemTextures[str]->loadFromFile(filepath)) {
      printf("incorrect file format");
    }
  }
  infile.close(); 


  string inventoryDisplay_file = "../data/inventory_display.png";
  if(!texture_inventoryDisplay.loadFromFile(inventoryDisplay_file)){
    printf("incorrect file format");
  }
  sprite_inventoryDisplay.setTexture(texture_inventoryDisplay);
  sprite_inventoryDisplay.setPosition(800, 150);
  sprite_inventoryDisplay.setScale(sf::Vector2f(0.50f, 0.50f));

  setCounterText(holyWaterCounter_text,165);
  setCounterText(noteCounter_text, 265);
  setCounterText(keyCounter_text, 365);

  //sprite_player.setScale(sf::Vector2f(0.80f, 0.80f));


  player_anim_down = Animation(player_sprite_sheet, sprite_player, 48, 107, 96, 0, 0, 0);
  player_anim_up = Animation(player_sprite_sheet, sprite_player, 48, 107, 96, 0, 0, 107);
  player_anim_left = Animation(player_sprite_sheet, sprite_player, 48, 107, 96, 0, 0, 214);
  player_anim_right = Animation(player_sprite_sheet, sprite_player, 48, 107, 96, 0, 0, 321);

  string monster_file = "../data/Monster.png";
  if(!texture_monster.loadFromFile(monster_file)){
    printf("incorrect file format");
  }

  //MonsterAI monsterAI;
  monsterAI.setPosition(400, 360);
  sprite_monster.setTexture(texture_monster);
  sprite_monster.setPosition(400, 360);
  sprite_monster.setScale(sf::Vector2f(-1.00f, 1.00f));

  //sound->playPlayingMusic();
  this->status = State::RUNNING;

}

void GameView::setCounterText(sf::Text& myText, float yPos){
  myText.setString("0");
  myText.setCharacterSize(50);
  myText.setFillColor(sf::Color(200, 200, 200));
  myText.setFont(font);
  myText.setPosition(sf::Vector2f(860, yPos));
}

//update the running game state depending on logic and input
void GameView::update(sf::Event& Event, float dt){
  itemSprites.clear();
  inputManager.update(Event, dt);

  //get the latest level texture
  texture = this->levelManager.getLevelTexture();


  //update the level sprite
  levelSprite.setTexture(texture);

  PlayerActor player = this->inputManager.logic->getPlayer();
  sprite_player.setPosition(player.getPosition().x, player.getPosition().y);
  this->holyWaterCounter_text.setString(to_string(player.getInventory()->getHolyWaterCount()));
  this->noteCounter_text.setString(to_string(player.getInventory()->numNotesFound()));
  this->keyCounter_text.setString(to_string(player.getInventory()->getKeyCount()));

  updatePlayerAnimation(dt);
  //this->logic.update(dt);

/*

All monster AI stuff

  monsterAI.calculateMove(player.getPosition().x, player.getPosition().y, dt);
  sprite_monster.setPosition(monsterAI.positionX, monsterAI.positionY);


  float distX = pow(monsterAI.positionX - player.getPosition().x-125, 2);
  float distY = pow(monsterAI.positionY - player.getPosition().y+20, 2);


  if (sqrt(distX + distY) < 70){
    this->status = State::SUCCESS;
    childState = new GameOver(*App, "You Lose...", sound);
  }
  */

  loadItemsandDialogueBox();


  if(inputManager.getPlayState() == 1){
    this->status = State::SUCCESS;
    childState = new GameOver(*App, "You Win!", *audioManager);
  }
  else if(inputManager.getPlayState() == 2){
    this->status = State::SUCCESS;
    childState = new GameOver(*App, "You Lose...", *audioManager);
  }

  //THIS CODE IS TO SEARCH FOR HITBOXES, DON'T DELETE UNTIL WE TURN IN
  // sf::IntRect checkMe = levelManager.getCurrentRoom().getBoundaries();
  // sf::RectangleShape rectangle(sf::Vector2f(checkMe.width,checkMe.height));
  // rectangle.setPosition(sf::Vector2f(checkMe.left,checkMe.top));
  // rectangle.setOutlineThickness(-3);
  // rectangle.setOutlineColor(sf::Color(250, 150, 100));
  // rectangle.setFillColor(sf::Color::Transparent);
  // this->App->draw(rectangle);

  // int size = levelManager.getCurrentRoom().getObstacles().size();
  // for(int i = 0; i < size; i++){
  //   checkMe = levelManager.getCurrentRoom().getObstacles().at(i);
  //   sf::RectangleShape rectangle2(sf::Vector2f(checkMe.width,checkMe.height));
  //   rectangle2.setPosition(sf::Vector2f(checkMe.left,checkMe.top));
  //   rectangle2.setOutlineThickness(-3);
  //   rectangle2.setOutlineColor(sf::Color(250, 150, 100));
  //   rectangle2.setFillColor(sf::Color::Transparent);
  //   this->App->draw(rectangle2);
  // }

  isDialogue();

}


//temporary function to update direction of player
void GameView::updatePlayerAnimation(float dt){
  PlayerActor player = this->logic.getPlayer();
  switch(player.getMovementState()){

    case MovementStates::MOVING_LEFT:
      this->player_anim_left.play(gameClock);
      break;

    case MovementStates::MOVING_RIGHT:
      this->player_anim_right.play(gameClock);
      break;


    case MovementStates::MOVING_UP:
      this->player_anim_up.play(gameClock);
      break;

    case MovementStates::MOVING_DOWN:
      this->player_anim_down.play(gameClock);
      break;

      }
    this->logic.setMovementState(MovementStates::IDLE);
}

void GameView::loadItemsandDialogueBox(){
  //work on streamlining this
  Room tempRoom = levelManager.getCurrentRoom();

  for(int i = 0; i < tempRoom.getItems().size(); i++) {

    ItemActor* item = tempRoom.getItems().at(i);

    itemSprites.push_back(new sf::Sprite);

    texture_item = itemTextures[item->getItemName()];
    itemSprites.back()->setTexture(*texture_item);
    itemSprites.back()->setPosition(item->getPosition().x, item->getPosition().y);

    inputManager.logic->setUpDialogueBox(item, dialoguebox, i);
    
  }

  if(!dialoguebox.getUsingState()){
    inputManager.logic->Etracker = 0; //reset Etracker
  }

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
    this->App->draw(sprite_monster);
    this->App->draw(sprite_inventoryDisplay);
    this->App->draw(holyWaterCounter_text);
    this->App->draw(noteCounter_text);
    this->App->draw(keyCounter_text);
    // this->App->draw(dialoguebox.dialogueBox);
    // this->App->draw(dialoguebox.message);

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
