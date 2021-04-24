#include "Animation.h"
#include <SFML/Graphics.hpp>

Animation::Animation(
  sf::Texture& textureSheet, sf::Sprite& sprite, float width, float height,
  float endX, float endY, float startLeft, float startTop){

  this-> startLeft = startLeft;
  this-> startTop = startTop;
  this->endX = endX;
  this->endY = endY;
  this->width = width;
  this->height = height;
  this->textureSheet = &textureSheet;
  this->sprite = &sprite;

  //resets the sprite texture
  this->sprite->setTexture(textureSheet,true);
  rectSourceSprite = sf::IntRect(this->startLeft, this->startTop, this->width, this->height);

  //sets the texture rectangle
  this->sprite->setTextureRect(this->rectSourceSprite);

}

//plays the animation based on the delta time
void Animation::play(float dt){
  this->timer += dt*100.0;
  if(timer >10.5f){
    timer =0.f;
    if(rectSourceSprite.left < endX){
      rectSourceSprite.left+= width;
    }
    else{
      rectSourceSprite.left=startLeft;
    }
    this->sprite->setTextureRect(this->rectSourceSprite);
  }



}
