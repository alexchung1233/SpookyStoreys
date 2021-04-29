#ifndef AUDIO_MANAGER_H // include guard
#define AUDIO_MANAGER_H
#include <SFML/Audio.hpp>


//represents a view state
class AudioManager
{
protected:
  sf::SoundBuffer generalBuffer;
  sf::Sound generalSound;

  sf::Music menuMusic;
  sf::Music playMusic;
  sf::Music nextRoom;
  sf::Music inRoom;


public:
  AudioManager();
  void init();
  void setGeneralBuffer(std::string);

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


};
#endif
