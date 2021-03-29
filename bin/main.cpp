#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <iostream>
#include <string>


using namespace std;

int main(int argc, char** argv)
{
  // set the random time seed for logic
  srand(time(0));

  // create clock object
  sf::Clock clock = sf::Clock();

  // create main window
  sf::RenderWindow App(sf::VideoMode(800,600,32), "Hello World - SFML", sf::Style::Close);


  // adaptive game loop
  while(App.isOpen())
  {

    // display
    App.display();

  }

  // Done.
  return 0;
}
