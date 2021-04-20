#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <iostream>
#include <string>
#include "GameView.h"
#include "GameManager.h"


using namespace std;

int main(int argc, char** argv)
{

  GameManager game;
  game.runGame();

  // Done.
  return 0;
}
