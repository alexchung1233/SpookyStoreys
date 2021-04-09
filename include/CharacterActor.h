#ifndef CHARACTER_ACTOR_H // include guard
#define CHARACTER_ACTOR_H
#include <SFML/Graphics.hpp>
#include "Position.h"
#include "Actor.h"

class CharacterActor : public Actor {
   public:
      // pure virtual function
      virtual Position getPosition() = 0;
      virtual sf::Vector2f getVelocity() = 0;
      virtual void move() = 0;
      
   private:
      Position myPosition;
      sf::Vector2f myVelocity;
};

#endif /* MY_CLASS_H */