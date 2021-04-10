#include <string>
#include <iostream>
#include "PlayerActor.h"

class GameLogic{

  private:
    PlayerActor player;

  public:
    GameLogic();

    void setup();

    //creates player object
    void createPlayer();

    //reutrns player object
    PlayerActor getPlayer();

    //Function for when the Up key is pressed
    void UpPressed();

}
