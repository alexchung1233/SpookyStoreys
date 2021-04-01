#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <iostream>
#include <string>
#include "GameView.h"


using namespace std;

int main(int argc, char** argv)
{
  // set the random time seed for logic
  srand(time(0));

  // create clock object
  sf::Clock clock = sf::Clock();
  // create game view

  // create main window
  sf::RenderWindow App(sf::VideoMode(800,600,32), "Spooky Storeys", sf::Style::Close);

  GameView gameView = GameView(App);

  // adaptive game loop
  while(App.isOpen())
  {
    
    sf::Event Event;
    while(App.pollEvent(Event))
    {
      // Exit
      if(Event.type == sf::Event::Closed)
        App.close();

      if(Event.type == sf::Event::KeyPressed){
        gameView.update(Event);
      }
    }

    gameView.setup();

    // display
    App.display();

  }

  // Done.
  return 0;
}