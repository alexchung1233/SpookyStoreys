#ifndef ANIMATION_H // include guard
#define ANIMATION_H
#include <SFML/Graphics.hpp>


class Animation
{
  private:
    sf::Texture* textureSheet;
    sf::Sprite* sprite;
    sf::IntRect rectSourceSprite;
    float timer=0;
    float width;
    float height;
    float endX;
    float endY;
    float startTop;
    float startLeft;
    float timeLimit;
  public:
    Animation(){}
    Animation(
      sf::Texture& textureSheet, sf::Sprite& sprite, float width, float height,
      float endX, float endY, float startLeft, float startTop,float timeLimit);
    void play(float dt);

};

#endif /* MY_CLASS_H */
