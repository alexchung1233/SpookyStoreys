#ifndef MONSTER_AI_H // include guard
#define MONSTER_AI_H


class MonsterAI
{
  public:
    float positionX;
    float positionY;
    MonsterAI();
    void setPosition(float x, float y);
    void calculateMove(float playerX, float playerY);
  };

#endif /* MY_CLASS_H */
