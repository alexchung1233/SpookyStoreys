#include "MonsterAI.h"


MonsterAI::MonsterAI() {
  positionX = 0;
  positionY = 0;
}

void MonsterAI::setPosition(float x, float y) {
  positionX = x;
  positionY = y;
}

void MonsterAI::calculateMove(float playerX, float playerY) {
  if (positionX < playerX){
    positionX += .05;
  }
  else {
    positionX -= .05;
  }

  if (positionY < playerY){
    positionY += .05;
  }
  else {
    positionY -= .05;
  }
}
