#include "Animation.h"
#include <SFML/Graphics.hpp>

Animation::Animation(sf::Texture& textureSheet, sf::Sprite& sprite){
  float left = 3;
  float top = 3;
  float width = 74;
  float height = 68;
  this->textureSheet = &textureSheet;
  this->sprite = &sprite;
  //resets the sprite texture
  this->sprite->setTexture(textureSheet,true);
  rectSourceSprite = sf::IntRect(left, top, width, height);
  //sets the texture rectangle
  this->sprite->setTextureRect(this->rectSourceSprite);

}

//plays the animation based on the delta time
void Animation::play(float dt){
  this->timer += dt*100.0;
  if(timer >4.f){
    timer =0.f;
    if(rectSourceSprite.left < 400){
      rectSourceSprite.left+= 74;
    }
    else{
      rectSourceSprite.left=0;
      /*
      if(rectSourceSprite.top < 200){
        rectSourceSprite.top+= 68;
      }
      else{
        rectSourceSprite.top=0;
      }
      */


    }
    this->sprite->setTextureRect(this->rectSourceSprite);
  }



}
