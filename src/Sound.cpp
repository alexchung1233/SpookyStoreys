#include <iostream>
#include "Sound.h"

Sound::Sound(){

}

void Sound::init(){
  nextRoomBuffer.loadFromFile("../data/NextRoom.wav");
  inRoomBuffer.loadFromFile("../data/InRoom.wav");
  playBuffer.loadFromFile("../data/PlayMusic.wav");
  menuBuffer.loadFromFile("../data/MenuMusic.wav");

  menuMusic.setLoop(true);
  playMusic.setLoop(true);
  nextRoom.setLoop(true);
  inRoom.setLoop(true);
}
/*
void operator()(){
  nextRoomBuffer.loadFromFile("../data/NextRoom.wav");
  inRoomBuffer.loadFromFile("../data/InRoom.wav");
  playBuffer.loadFromFile("../data/PlayMusic.wav");
  menuBuffer.loadFromFile("../data/MenuMusic.wav");

  menuMusic.setLoop(true);
  playMusic.setLoop(true);
  nextRoom.setLoop(true);
  inRoom.setLoop(true);
}
*/


void Sound::setGeneralBuffer(std::string fileLoc){
  generalBuffer.loadFromFile(fileLoc);
}




void Sound::playMenuMusic(){
  menuMusic.setBuffer(menuBuffer);
  menuMusic.play();
}

void Sound::playPlayingMusic(){
  playMusic.setBuffer(playBuffer);
  playMusic.play();
}

void Sound::playNextRoom(){
  nextRoom.setBuffer(nextRoomBuffer);
  nextRoom.play();
}

void Sound::playInRoom(){
  inRoom.setBuffer(inRoomBuffer);
  inRoom.play();
}

void Sound::playGeneralBuffer(){
  generalSound.setBuffer(generalBuffer);
  generalSound.play();
}




void Sound::stopMenuMusic(){
  menuMusic.stop();
}

void Sound::stopPlayingMusic(){
  playMusic.stop();
}

void Sound::stopNextRoom(){
  nextRoom.stop();
}

void Sound::stopInRoom(){
  inRoom.stop();
}

void Sound::stopGeneralBuffer(){
  generalSound.stop();
}

sf::SoundSource::Status Sound::getStatusMenu(){
  return (menuMusic.getStatus());
}

sf::SoundSource::Status Sound::getStatusPlaying(){
  return (playMusic.getStatus());
}

sf::SoundSource::Status Sound::getStatusNextRoom(){
  return (nextRoom.getStatus());
}

sf::SoundSource::Status Sound::getStatusInRoom(){
  return (inRoom.getStatus());
}

sf::SoundSource::Status Sound::getStatusGeneral(){
  return (generalSound.getStatus());
}
