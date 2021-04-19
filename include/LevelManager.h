#ifndef LEVEL_MANAGER_H
#define LEVEL_MANAGER_H

#include <SFML/Graphics.hpp>
#include <map>
#include <string>


class LevelManager {

private:
  sf::Texture* levelTexture;
  std::map<std::string, std::string> levelFileMapping;
public:
  LevelManager(sf::Texture& levelTexture);
  void init();
  void changeLevelTexture(std::string textureName);
  const sf::Texture getLevelTexture();



};

#endif
