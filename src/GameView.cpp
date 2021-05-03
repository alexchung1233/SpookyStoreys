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
  this->audioManager = &audioManager;
  this->status = State::UNINIT;

}

void GameView::init(){
  this->levelManager.init();
  this->logic.setup();
  this->logic.setLevelManager(levelManager);
  this->scriptManager.readInScript("Intro_Script");
  this->transitionRectangleAlphaChannel = 255;

  inputManager(*App, logic);

  //get current level texture
  texture = this->levelManager.getLevelTexture();

  levelSprite.setTexture(texture);


  PlayerActor player = this->logic.getPlayer();
  sprite_player.setPosition(player.getPosition().x, player.getPosition().y);

  sprite_player.setPosition(sf::Vector2f(400.f, 300.f));
  string animate_sprite_file = "../data/Protag_Spritesheet.png";

  if(!player_sprite_sheet.loadFromFile(animate_sprite_file)){
    printf("incorrect file format");
  }



  string counter_file = "../data/counter.png";
  if(!texture_counter.loadFromFile(counter_file)){
    printf("incorrect file format");
  }
  sprite_counter.setTexture(texture_counter);
  sprite_counter.setPosition(732, 0);


  setCounterText();


  makeBox(sf::Vector2f(this->logic.getDialogueBox().position.x, this->logic.getDialogueBox().position.y), sf::Color::Black);

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


  std::string str;
  ifstream infile;
  infile.open ("../data/itemImageFiles.txt");
  while(!infile.eof())
  {
    std::getline(infile, str);
    std::string filepath = "../data/" + str + ".png";

    if(filepath != "../data/.png"){
      itemTextureMapping[str] = new sf::Texture;
      if(!itemTextureMapping[str]->loadFromFile(filepath)) {
        printf("incorrect file format");
        }
    }
  }
  infile.close();


  //sound->playPlayingMusic();
  this->status = State::RUNNING;

}

void GameView::setCounterText(){
  if (!font.loadFromFile("../data/courier.ttf")){
      std::cout << "incorrect font";
  }
  this->counterText.setString("0");
  this->counterText.setCharacterSize(50);
  this->counterText.setFillColor(sf::Color::White);
  this->counterText.setFont(font);
  this->counterText.setPosition(sf::Vector2f(752, 62));
}

//update the running game state depending on logic and input
void GameView::update(sf::Event& Event, float dt){
  this->dt = dt;

  itemSprites.clear();

  inputManager.update(Event, dt);
  //get the latest level texture
  texture = this->levelManager.getLevelTexture();


  //update the level sprite
  levelSprite.setTexture(texture);

  PlayerActor player = this->logic.getPlayer();
  sprite_player.setPosition(player.getPosition().x, player.getPosition().y);
  this->counterText.setString(to_string(player.getHolyWaterCount()));

  updatePlayerAnimation(dt);


  loadItemSprites();
  this->setText(logic.getDialogueBoxText());

  if(inputManager.getPlayState() == 1){
    this->status = State::SUCCESS;
    childState = new GameOver(*App, "You Win!", *audioManager);
  }
  else if(inputManager.getPlayState() == 2){
    this->status = State::SUCCESS;
    childState = new GameOver(*App, "You Lose...", *audioManager);
  }



  //run test script
  executeScript();

  //test script
  //fadeIn(16.f, 0, 0, 0);

  //THIS CODE IS TO SEARCH FOR HITBOXES, DON'T DELETE UNTIL WE TURN IN
  // int size = levelManager.getCurrentRoom().getObstacles().size();
  // for(int i = 0; i < size; i++){
  //   sf::IntRect checkMe = levelManager.getCurrentRoom().getObstacles().at(i);
  //   sf::RectangleShape rectangle(sf::Vector2f(checkMe.width,checkMe.height));
  //   rectangle.setPosition(sf::Vector2f(checkMe.left,checkMe.top));
  //   rectangle.setOutlineThickness(-3);
  //   rectangle.setOutlineColor(sf::Color(250, 150, 100));
  //   rectangle.setFillColor(sf::Color::Transparent);
  //   this->App->draw(rectangle);
  // }



}


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
    this->App->draw(sprite_monster);
    this->App->draw(sprite_counter);
    this->App->draw(counterText);
    this->App->draw(transitionRectangle);

    isDialogue();

}


void GameView::isDialogue(){
  if (logic.isDialogueBoxUsed()){
     //toggle the dialogue box, if the  player has some sort of interaction
    this->App->draw(dialogueBox);
    this->App->draw(message);
  }
}


//create function to initalize command
//create states for each command to indicate if finished or not

void GameView::executeScript(){

    ScriptCommand* currentCommand = this->scriptManager.scriptQueue.front();

    if(!this->scriptManager.scriptQueue.empty()){
      //if uninitalized, initalize

      //if finished, pop off

      if(currentCommand->getStatus() == ScriptCommand::UNINIT){
        this->initScriptCommand(*currentCommand);
        currentCommand->setStatus(ScriptCommand::RUNNING);
      }
      else if(currentCommand->getStatus() == ScriptCommand::RUNNING){
        this->updateScriptCommand(*currentCommand);
      }

      else if(currentCommand->getStatus() == ScriptCommand::SUCCESS){
        this->scriptManager.scriptQueue.pop();
      }



    }

}


//initalizes the script command based on a base data
void GameView::initScriptCommand(ScriptCommand& command){
  vector<string> data = command.getData();

  switch(command.getCommandType()){

    case ScriptCommand::FADE_IN:
      command.setStatus(ScriptCommand::RUNNING);
      break;

    case ScriptCommand::WAIT:
      clockFilter.restart();
      break;

    case ScriptCommand::PLAY_SOUND:
      audioManager->setGeneralBuffer(data.at(1));
      audioManager->playGeneralBuffer();
      break;

    case ScriptCommand::SHOW_DIALOGUE:
      logic.setDialogueBoxStatus(true);
      logic.setDialogueBoxText(data.at(1));
      break;


  }


}

void GameView::updateScriptCommand(ScriptCommand& command){
  vector<string> data = command.getData();

  switch(command.getCommandType()){

    //matches the command to the type
    case ScriptCommand::FADE_IN:
      fadeIn(
        stof(data.at(1)),stof(data.at(2)), stof(data.at(3)), stof(data.at(4)));
      //finish condition
      if(transitionRectangleAlphaChannel <= 0){
        command.setStatus(ScriptCommand::SUCCESS);
        transitionRectangleAlphaChannel = 255;
      }
      break;

    //move player up based on distance and delayed timer(how slowly it walks)
    case ScriptCommand::MOVE_PLAYER_UP:
      {
        float timer = clockFilter.getElapsedTime().asSeconds() * 100;

        if (timer > 6.f){
          this->logic.upPressed(this->dt);
          clockFilter.restart();
        }
      }
      break;

    //pauses based on seconds
    case ScriptCommand::WAIT:
      {
        float timer = stof(data.at(1));
        if(timer <= clockFilter.getElapsedTime().asSeconds()){
          clockFilter.restart();
          command.setStatus(ScriptCommand::SUCCESS);
        }
      }
      break;

    case ScriptCommand::PLAY_SOUND:
      if(audioManager->getStatusGeneral() == sf::SoundSource::Status::Stopped)
        command.setStatus(ScriptCommand::SUCCESS);
      break;

    case ScriptCommand::SHOW_DIALOGUE:
      if(!logic.getDialogueBoxUsingState()){
        command.setStatus(ScriptCommand::SUCCESS);
        }
      break;



  }
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

//load the itemsprites from the current room
void GameView::loadItemSprites(){

  Room tempRoom = levelManager.getCurrentRoom();
  for(int i = 0; i < tempRoom.getItems().size(); i++) {
    ItemActor* item = tempRoom.getItems().at(i);
    if(item->getActiveStatus()){

      itemSprites.push_back(new sf::Sprite);

      itemSprites.back()->setTexture(*itemTextureMapping[item->getItemName()]);
      itemSprites.back()->setPosition(item->getPosition().x, item->getPosition().y);
    }
  }

}


void GameView::setLogic(GameView& logic){}


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
