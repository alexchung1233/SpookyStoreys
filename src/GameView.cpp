#include "GameView.h"
#include <string>
#include <iostream>
#include <math.h>
#include "InputManager.h"
#include "Animation.h"

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
  inputManager(*App, logic);
  this->status = State::UNINIT;
  this->audioManager = &audioManager;
}

void GameView::init(){
  if (!font.loadFromFile("../data/courier.ttf")){
    std::cout << "incorrect font";
  }
  this->levelManager.init();
  this->logic.setLevelManager(levelManager);

  this->monsterLevelManager.init();
  this->monsterLevelManager.setRoom("BASEMENT");
  this->logic.setMonsterLevelManager(monsterLevelManager);

  this->logic.setup();

  inputManager(*App, logic);
  
  //get current level texture
  texture = this->levelManager.getLevelTexture();

  levelSprite.setTexture(texture);

  PlayerActor player = logic.getPlayer();
  sprite_player.setPosition(player.getPosition().x, player.getPosition().y);

  sprite_player.setPosition(sf::Vector2f(400.f, 300.f));
  string animate_sprite_file = "../data/Protag_Spritesheet.png";

  if(!player_sprite_sheet.loadFromFile(animate_sprite_file)){
    printf("incorrect file format");
  }

  loadItemTextures();

  setUpInventoyDisplay();

  makeBox(sf::Vector2f(logic.getDialogueBox().position.x, logic.getDialogueBox().position.y), sf::Color::Black);

  player_anim_down = Animation(player_sprite_sheet, sprite_player, 48, 107, 96, 0, 0, 0);
  player_anim_up = Animation(player_sprite_sheet, sprite_player, 48, 107, 96, 0, 0, 107);
  player_anim_left = Animation(player_sprite_sheet, sprite_player, 48, 107, 96, 0, 0, 214);
  player_anim_right = Animation(player_sprite_sheet, sprite_player, 48, 107, 96, 0, 0, 321);

  string monster_file = "../data/Monster.png";
  if(!texture_monster.loadFromFile(monster_file)){
    printf("incorrect file format");
  }

  MonsterActor monster = this->logic.getMonsterActor();

  sprite_monster.setTexture(texture_monster);
  sprite_monster.setPosition(monster.getPosition().x - 200, monster.getPosition().y - 70);
  sprite_monster.setScale(sf::Vector2f(1.00f, 1.00f));

  //sound->playPlayingMusic();
  this->status = State::RUNNING;

}

void GameView::loadItemTextures(){
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
}

void GameView::setUpInventoyDisplay(){
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

  PlayerActor player = this->logic.getPlayer();
  MonsterActor monster = this->logic.getMonsterActor();
  
  logic.updateAI(dt);

  bool inSameRoom = (monsterLevelManager.getCurrentRoom().getRoomTitle() == levelManager.getCurrentRoom().getRoomTitle());

  logic.monsterAI.isPaused(logic.isDialogueBoxUsed());
  logic.monsterAI.calculateMove(player, dt, levelManager.getCurrentRoom().getRoomTitle(), inSameRoom, this->logic.getHolyWaterUsed());

  float distance;
  float distX;
  float distY;
  if(inSameRoom){
    distX = pow(monster.getPosition().x - player.getPosition().x, 2);
    distY = pow(monster.getPosition().y - player.getPosition().y, 2);
    distance = sqrt(distX + distY);
  }
  else
    distance = 1000;

  if (inSameRoom) {
    distX = pow(monster.getPosition().x - player.getPosition().x, 2);
    distY = pow(monster.getPosition().y - player.getPosition().y, 2);

    if (sqrt(distX + distY) < 70){
      this->status = State::SUCCESS;
      audioManager->stopNextRoom();
      audioManager->stopInRoom();
      childState = new GameOver(*App, "You Lose...", *audioManager);
    }
  }

  inputManager.update(Event, dt, distance);
  //get the latest level texture
  texture = this->levelManager.getLevelTexture();

  //update the level sprite
  levelSprite.setTexture(texture);

  sprite_player.setPosition(player.getPosition().x, player.getPosition().y);
  this->holyWaterCounter_text.setString(to_string(player.getInventory()->getHolyWaterCount()));
  this->noteCounter_text.setString(to_string(player.getInventory()->numNotesFound()));
  this->keyCounter_text.setString(to_string(player.getInventory()->getKeyCount()));

  updatePlayerAnimation(dt);

  sprite_monster.setPosition(monster.getPosition().x - 60, monster.getPosition().y - 30);

  if(inputManager.getPlayState() == 1){
    this->status = State::SUCCESS;
    childState = new GameOver(*App, "You Win!", *audioManager);
  }
  else if(inputManager.getPlayState() == 2){
    this->status = State::SUCCESS;
    childState = new GameOver(*App, "You Lose...", *audioManager);
  }

  loadItemSprites();
  this->setText(logic.getDialogueBox().dialogue);

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

    default:
      //do nothing
     break;
  }
  this->logic.setMovementState(MovementStates::IDLE);
}

//load the itemsprites from the current room
void GameView::loadItemSprites(){
  Room tempRoom = levelManager.getCurrentRoom();
  for(int i = 0; i < tempRoom.getItems().size(); i++) {

    ItemActor* item = tempRoom.getItems().at(i);
    if(item->getActiveStatus()){
      itemSprites.push_back(new sf::Sprite);

      texture_item = itemTextures[item->getItemName()];
      itemSprites.back()->setTexture(*texture_item);
      itemSprites.back()->setPosition(item->getPosition().x, item->getPosition().y);
    }

  }
}


void GameView::setLogic(GameView& logic){}

//renders the running game
void GameView::render(){
    this->App->clear();
    this->App->draw(levelSprite);
    Room tempRoom = levelManager.getCurrentRoom();

    for (int i = 0; i < itemSprites.size(); i++){
      sf::Sprite* drawMe = itemSprites.at(i);
      this->App->draw(*drawMe);
    }


    this->App->draw(sprite_player);

    //If the monster is in the same room a the player
    if (monsterLevelManager.getCurrentRoom().getRoomTitle() == levelManager.getCurrentRoom().getRoomTitle()) {
      //If the in room sound isnt already playing
      if (!inRoomLastTime){
        audioManager->playInRoom();
      }
      //Draw monster
      inRoomLastTime = true;
      this->App->draw(sprite_monster);
    }
    else {
      //If they aren't in the same room stop in room sound
      inRoomLastTime = false;
      audioManager->stopInRoom();
    }

    //Get title of current monster room and list of doors from player room
    string monsterRoom = monsterLevelManager.getCurrentRoom().getRoomTitle();
    std::vector<Door> doorList = levelManager.getCurrentRoom().getDoors();
    bool inNextRoom = false;
    bool holdLastTime;
    //Iterate through list of player doors
    for (int i = 0; i < doorList.size(); i++) {
      //If they are equal mark as true
      if (doorList.at(i).getNextRoom() == monsterRoom) {
        inNextRoom = true;
        holdLastTime = true;
      }
    }
    //If the monster is in the next room and sound isnt already playing, play next room sound
    if (inNextRoom) {
      if (!nextRoomLastTime){
        audioManager->playNextRoom();
      }
    }
    //Else stop playing next room sound
    else {
      holdLastTime = false;
      audioManager->stopNextRoom();
    }

    nextRoomLastTime = holdLastTime;

    sf::RectangleShape monsterRect = sf::RectangleShape(logic.getMonsterActor().getSize());
    monsterRect.setPosition(logic.getMonsterActor().getPosition().x, logic.getMonsterActor().getPosition().y);
    this->App->draw(monsterRect);


    sf::CircleShape doorCenter = sf::CircleShape(1);
    doorCenter.setPosition(logic.getMonsterView().newDoorX, logic.getMonsterView().newDoorY);
    this->App->draw(doorCenter);
    
    this->App->draw(sprite_inventoryDisplay);
    this->App->draw(holyWaterCounter_text);
    this->App->draw(noteCounter_text);
    this->App->draw(keyCounter_text);

    isDialogue();

}


void GameView::isDialogue(){
  if (logic.isDialogueBoxUsed()){ //toggle the dialogue box, if the  player has some sort of interaction
    this->App->draw(dialogueBox);
    this->App->draw(message);
  }
}

//creat the box and position of box
void GameView::makeBox(sf::Vector2f position, sf::Color color){
    this->dialogueBox.setFillColor(color);
    this->dialogueBox.setSize(sf::Vector2f(790, 40));
    this->dialogueBox.setOutlineColor(sf::Color::White);
    this->dialogueBox.setOutlineThickness(2);

    sf::Vector2f myPos = sf::Vector2f(position.x - this->dialogueBox.getSize().x/2, 550);

    dialogueBox.setPosition(myPos);
}

//set the text for the dialoguebox
void GameView::setText(std::string words){
  this->message.setString(words);
  this->message.setCharacterSize(15);
  this->message.setFillColor(sf::Color::Red);
  this->message.setFont(font);

  sf::FloatRect boxBounds = this->dialogueBox.getGlobalBounds();
  sf::FloatRect textBounds = this->message.getLocalBounds();

  sf::Vector2f myPos = sf::Vector2f(boxBounds.left + boxBounds.width/2 - textBounds.width/2,
    boxBounds.top + boxBounds.height/2.7 - textBounds.height/2);

  this->message.setPosition(myPos);

}

void GameView::pause(){}

void GameView::unpause(){}
