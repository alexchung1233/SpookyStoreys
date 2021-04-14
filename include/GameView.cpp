/**
    Pong Game View: Renders graphical interface for pong logic
    using sfml
    @file GameView.cpp
    @author Alex Chung
*/
#include "GameView.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <iostream>
#include "PongLogic.h"
#include "PlayerState.h"
#include "BallState.h"

using namespace std;


//constructor takes in App
GameView::GameView(sf::RenderWindow &app){
  this->App = &app;
  }

/**
 *  Setup for the gameview. Used before game loop.
 * Initalizes all the states, sfml objects, and positions.
 */
void GameView::setup(){
  font_file = "../data/Lato-Bold.ttf";
  if (!font.loadFromFile(font_file))
  {
      cout << "No font found. ";
  }


  PlayerState userPlayerState = logic->getUserPlayer();
  PlayerState aiPlayerState = logic->getAIPlayer();
  BallState ballState = logic->getBall();

  userPlayer = sf::RectangleShape(
    sf::Vector2f(userPlayerState.getWidth(),userPlayerState.getHeight()));

  aiPlayer = sf::RectangleShape(
      sf::Vector2f(aiPlayerState.getWidth(),aiPlayerState.getHeight()));

  ball = sf::RectangleShape(
    sf::Vector2f(ballState.getBallSize(),ballState.getBallSize()));

  score.setFont(font);
  score.setCharacterSize(20);
  score.setStyle(sf::Text::Regular);
  score.setString("Score");
  score.setPosition(355,20);

  //set score properties for user and ai
  userScoreText.setFont(font);
  aiScoreText.setFont(font);
  userScoreText.setCharacterSize(20);
  aiScoreText.setCharacterSize(20);
  userScoreText.setStyle(sf::Text::Regular);
  aiScoreText.setStyle(sf::Text::Regular);
  userScoreText.setPosition(400,40);
  aiScoreText.setPosition(350,40);
}


/**
 *  Render pong game. This is called in the adaptive game loop. The app objects
 * draws whatever happens.
 */
void GameView::renderGamePlaying(){

  // collision detection
  aiScoreText.setString(to_string(logic->getAIScore()));
  userScoreText.setString(to_string(logic->getUserScore()));

  userPlayer.setPosition(
    logic->getUserPosition().x, logic->getUserPosition().y);

  aiPlayer.setPosition(
    logic->getAIPosition().x, logic->getAIPosition().y);

  ball.setPosition(logic->getBallPosition().x, logic->getBallPosition().y);

  //draw the app and entities
  App->clear(sf::Color::Black);
  App->draw(score);
  App->draw(aiScoreText);
  App->draw(userScoreText);
  App->draw(userPlayer);
  App->draw(aiPlayer);
  App->draw(ball);
}

/**
 *  Render winner screen. Menu shows for restarting or quitting
 */
void GameView::renderWinnerScreen(){

  sf::Event Event;
  while(App->pollEvent(Event))
  {
    // Exit
    if(Event.type == sf::Event::Closed)
      App->close();
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
      logic->start();
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
      App->close();

  }


  winner.setFont(font);;
  winner.setCharacterSize(50);
  winner.setStyle(sf::Text::Regular);

  winner.setPosition(270,200);

  winnerSplash.setFont(font);
  winnerSplash.setCharacterSize(50);
  winnerSplash.setStyle(sf::Text::Regular);
  winnerSplash.setString("Winner");
  winnerSplash.setPosition(300,20);

  //options whether ot quit or restart
  winnerOptions.setFont(font);
  winnerOptions.setCharacterSize(35);
  winnerOptions.setStyle(sf::Text::Regular);
  winnerOptions.setString("Press 1 to restart\nPress 2 to quit");
  winnerOptions.setPosition(300,300);

  if(logic->gameWinner() == -1){
    winner.setString("AI player wins");
  }
  else if(logic->gameWinner() == 1){
    winner.setString("User player wins");
  }
  App->clear(sf::Color::Black);
  App->draw(winnerSplash);
  App->draw(winner);
  App->draw(winnerOptions);
}

/**
 * Handles input of the key
 * @return 1 to represent moving up
 * @return -1 to represent moving down
 * @return 0 to no action
 */
int GameView::inputHandler(bool playing){
  while(App->pollEvent(Event))
  {
    //manages user input
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
      return 1;
    }

    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
      return -1;
    }
    // Exit
    else if(Event.type == sf::Event::Closed)
      App->close();
  }
  return 0;
}

/**
 * Set the logic object used for calculating pong game states.
 */
void GameView::setLogic(PongLogic &log){
  logic = &log;

}

/**
 * Plays sound when paddle hits. Currently NOT working.
 */
void GameView::playPaddleSound(){
  soundfile = "../data/paddle.wav";
  if (!buffer.loadFromFile(soundfile))
      cout << "No sound file found";

  sf::Sound sound;
  sound.setBuffer(buffer);
  sound.play();
}
