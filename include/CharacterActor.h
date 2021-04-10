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
      virtual void setVelocity(sf::Vector2f vel) = 0;
      virtual void setVelocity(float x, float y) = 0;
      virtual void move() = 0;
      
   protected:
      sf::Vector2f myVelocity;

   private:
};

#endif /* MY_CLASS_H */
