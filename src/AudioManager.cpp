#include <iostream>
#include "AudioManager.h"

AudioManager::AudioManager(){

}

void AudioManager::init(){
  if (!nextRoom.openFromFile("../data/NextRoom.wav"))
    {
      printf("error, file unabled to be opened");
    }
  if (!menuMusic.openFromFile("../data/MenuMusic.wav"))
    {
    printf("error, file unabled to be opened");
    }
  if (!playMusic.openFromFile("../data/PlayMusic.wav"))
    {
    printf("error, file unabled to be opened");
    }
  if (!inRoom.openFromFile("../data/InRoom.wav"))
    {
    printf("error, file unabled to be opened");
    }
  if (!monsterScream.openFromFile("../data/MonsterScream.wav"))
    {
      printf("error, file unabled to be opened");
    }

  monsterScream.setVolume(70);
  menuMusic.setVolume(75.f);
  menuMusic.setLoop(true);
  playMusic.setLoop(true);
  nextRoom.setLoop(true);
  inRoom.setLoop(true);
}


//general buffer to handle any wav sounds
void AudioManager::setGeneralBuffer(std::string fileLoc){
  if (!generalBuffer.loadFromFile(fileLoc))
    printf("error, file unable to be opened");
  generalSound.setBuffer(generalBuffer);
}




void AudioManager::playMenuMusic(){
  menuMusic.play();
}

void AudioManager::playPlayingMusic(){
  playMusic.play();
}

void AudioManager::playNextRoom(){
  nextRoom.play();
}

void AudioManager::playInRoom(){
  inRoom.play();
}

void AudioManager::playMonsterScream(){
  monsterScream.play();
}

void AudioManager::playGeneralBuffer(){
  generalSound.play();
}




void AudioManager::stopMenuMusic(){
  menuMusic.stop();
}

void AudioManager::stopPlayingMusic(){
  playMusic.stop();
}

void AudioManager::stopNextRoom(){
  nextRoom.stop();
}

void AudioManager::stopInRoom(){
  inRoom.stop();
}

void AudioManager::stopMonsterScream(){
  monsterScream.stop();
}

void AudioManager::stopGeneralBuffer(){
  generalSound.stop();
}

sf::SoundSource::Status AudioManager::getStatusMenu(){
  return (menuMusic.getStatus());
}

sf::SoundSource::Status AudioManager::getStatusPlaying(){
  return (playMusic.getStatus());
}

sf::SoundSource::Status AudioManager::getStatusNextRoom(){
  return (nextRoom.getStatus());
}

sf::SoundSource::Status AudioManager::getStatusInRoom(){
  return (inRoom.getStatus());
}

sf::SoundSource::Status AudioManager::getStatusGeneral(){
  return (generalSound.getStatus());
}
