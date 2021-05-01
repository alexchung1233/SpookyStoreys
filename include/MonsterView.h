#include <string>
#include <iostream>
#include "MonsterActor.h"
#include "Room.h"
#include "LevelManager.h"

class MonsterView{

  private:
    MonsterActor monster;
    Room myRoom;

    void createMonster();

    bool hitsDoor(sf::IntRect possiblePlayerPosition);


  public:
    MonsterView() { };

    void setup();

    LevelManager* levelManager;

    //reutrns player object
    MonsterActor getMonster();

    bool detectCollisionUp(float dt);
    bool detectCollisionDown(float dt);
    bool detectCollisionLeft(float dt);
    bool detectCollisionRight(float dt);

    void setLevelManager(LevelManager &LM);
    sf::Vector2f getRandomDoor();

    float newDoorX;
    float newDoorY;

    //Function for when the Up key is pressed
    void upPressed(float dt);

    //Function for when the Down key is pressed
    void downPressed(float dt);

    //Function for when the Left key is pressed
    void leftPressed(float dt);

    //Function for when the Right key is pressed
    void rightPressed(float dt);

    void setRoom(Room room);
    Room getRoom();


};
