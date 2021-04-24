#include <string>
#include <iostream>
#include "PlayerActor.h"
#include "Room.h"
#include "LevelManager.h"

class GameLogic{

  private:
    PlayerActor player;
    Room myRoom;


    void setup();

    //creates player object
    void createPlayer();

    bool hitsDoor(sf::IntRect possiblePlayerPosition);


  public:
    GameLogic();

    LevelManager* levelManager;

    //reutrns player object
    PlayerActor getPlayer();

    bool detectCollisionUp(float dt);
    bool detectCollisionDown(float dt);
    bool detectCollisionLeft(float dt);
    bool detectCollisionRight(float dt);

    void setLevelManager(LevelManager &LM);


    //Function for when the Up key is pressed
    void upPressed(float dt);

    //Function for when the Down key is pressed
    void downPressed(float dt);

    //Function for when the Left key is pressed
    void leftPressed(float dt);

    //Function for when the Right key is pressed
    void rightPressed(float dt);

    void setRoom(Room room);


};
