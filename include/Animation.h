#ifndef ANIMATION_H // include guard
#define ANIMATION_H
#include <SFML/Graphics.hpp>


class Animation
{
  private:
    sf::Texture* textureSheet;
    sf::Sprite* sprite;
    sf::IntRect rectSourceSprite;
    float timer;

  public:
    Animation(){}
    Animation(sf::Texture& textureSheet, sf::Sprite& sprite);
    void play(float dt);

};

#endif /* MY_CLASS_H */
