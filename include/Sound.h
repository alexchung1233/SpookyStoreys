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
  sf::SoundBuffer generalBuffer;
  sf::Sound menuMusic;
  sf::Sound playMusic;
  sf::Sound nextRoom;
  sf::Sound inRoom;
  sf::Sound generalSound;

public:
  Sound();
  void init();
  void operator()();
  void playMenuMusic();
  void playPlayingMusic();
  void playNextRoom();
  void playInRoom();
  void playGeneralBuffer();

  void stopMenuMusic();
  void stopPlayingMusic();
  void stopNextRoom();
  void stopInRoom();
  void stopGeneralBuffer();

  sf::SoundSource::Status getStatusMenu();
  sf::SoundSource::Status getStatusPlaying();
  sf::SoundSource::Status getStatusNextRoom();
  sf::SoundSource::Status getStatusInRoom();
  sf::SoundSource::Status getStatusGeneral();

  void setGeneralBuffer(std::string);

};
#endif
