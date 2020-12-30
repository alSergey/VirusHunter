#pragma once

#include "SFML/Audio.hpp"

#define BACK_MENU 15
#define ON_BUTTON 10
#define SELECT_BUTTON 20
#define BACK_GAME 5
#define HIT_PLAYER 20
#define HIT_ENEMY 15
#define DIED_ENEMY 25
#define DIED_PLAYER 35
#define METRO 35
#define CAR 35
#define ANTIBODIES 40
#define VACCINE 40
#define TREAT_PATIENT 25

class MusicManager {
 public:
  MusicManager();
  void PlayBackgroundMenuMusic();
  void StopBackgroundMenuMusic();
  void PlayOnButtonSound();
  void PlaySelectButtonSound();

  void PlayBackgroundGameMusic();
  void StopBackgroundGameMusic();
  void PlayHitPlayerSound();
  void PlayHitEnemySound();
  void PlayDiedEnemySound();
  void PlayDiedPlayerSound();
  void PlayMetroSound();
  void PlayCarSound();
  void StopCarSound();
  void PlayGetAntibodiesSound();
  void PlayGetVaccineSound();
  void PlayTreatPatientSound();
  void StopTreatPatientSound();

  void StopAllMusic();

 private:
  // Звук меню
  sf::Music backgroundMenuMusic;

  // Наведение на кнопку
  sf::SoundBuffer onButtonBuffer;
  sf::Sound onButtonSound;

  // Выбор кнопки
  sf::SoundBuffer selectButtonBuffer;
  sf::Sound selectButtonSound;

  // Звук игры
  sf::Music backgroundGameMusic;

  // Стрельба игроком
  sf::SoundBuffer hitPlayerBuffer;
  sf::Sound hitPlayerSound;

  // Стрельба врагом
  sf::SoundBuffer hitEnemyBuffer;
  sf::Sound hitEnemySound;

  // Смерть врага
  sf::SoundBuffer diedEnemyBuffer;
  sf::Sound diedEnemySound;

  // Смерть игрока
  sf::SoundBuffer diedPlayerBuffer;
  sf::Sound diedPlayerSound;

  // Движение поезда
  sf::SoundBuffer metroBuffer;
  sf::Sound metroSound;
  bool isDriveMetro;

  // Движение машин
  sf::SoundBuffer carBuffer;
  sf::Sound carSound;
  bool isDriveCar;

  // Получение антител
  sf::SoundBuffer getAntibodiesBuffer;
  sf::Sound getAntibodiesSound;

  // Получение вацины
  sf::SoundBuffer getVaccineBuffer;
  sf::Sound getVaccineSound;

  // Лечение пациена
  sf::SoundBuffer treatPatientBuffer;
  sf::Sound treatPatientSound;
};
