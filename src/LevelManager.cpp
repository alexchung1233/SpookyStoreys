#include <iostream>
#include <fstream>
#include "LevelManager.h"

using namespace std;

LevelManager::LevelManager(sf::Texture& levelTexture){
  this->levelTexture = &levelTexture;
}

//read in the level mapping data and store into assoctiative mapping
void LevelManager::init(){
  string myText;

  ifstream levelMappingsFile();

  levelMappingsFile.open("level_mapping.txt");
  
  while (getline (MyReadFile, myText)) {
    cout << myText;
  }

  MyReadFile.close();

}
