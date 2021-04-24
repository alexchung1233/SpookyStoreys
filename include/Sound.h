#ifndef SOUND_H // include guard
#define SOUND_H
#include <SFML/Audio.hpp>


//represents a view state
class Sound
{
protected:
  sf::SoundBuffer menuBuffer;
  sf::SoundBuffer playBuffer;
  sf::SoundBuffer nextRoomBuffer;
  sf::SoundBuffer inRoomBuffer;
  sf::Sound menuMusic;
  sf::Sound playMusic;
  sf::Sound nextRoom;
  sf::Sound inRoom;

public:
  Sound();
  void init();
  void operator()();
  void playMenuMusic();
  void playPlayingMusic();
  void playNextRoom();
  void playInRoom();

  void stopMenuMusic();
  void stopPlayingMusic();
  void stopNextRoom();
  void stopInRoom();
};
#endif
