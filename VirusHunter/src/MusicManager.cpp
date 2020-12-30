#include "MusicManager.h"
#include "ResourcePath.hpp"

MusicManager::MusicManager()
    : isDriveMetro(false),
      isDriveCar(false) {
  backgroundMenuMusic.openFromFile(resourcePath() + "files/music/menuBack.wav");
  backgroundMenuMusic.setLoop(true);
  backgroundMenuMusic.setVolume(BACK_MENU);

  onButtonBuffer.loadFromFile(resourcePath() + "files/music/onButton.wav");
  onButtonSound.setBuffer(onButtonBuffer);
  onButtonSound.setVolume(ON_BUTTON);

  selectButtonBuffer.loadFromFile(resourcePath() + "files/music/selectButton.wav");
  selectButtonSound.setBuffer(selectButtonBuffer);
  selectButtonSound.setVolume(SELECT_BUTTON);

  backgroundGameMusic.openFromFile(resourcePath() + "files/music/gameBack.wav");
  backgroundGameMusic.setLoop(true);
  backgroundGameMusic.setVolume(BACK_GAME);

  hitPlayerBuffer.loadFromFile(resourcePath() + "files/music/playerHit.wav");
  hitPlayerSound.setBuffer(hitPlayerBuffer);
  hitPlayerSound.setVolume(HIT_PLAYER);

  hitEnemyBuffer.loadFromFile(resourcePath() + "files/music/enemyHit.wav");
  hitEnemySound.setBuffer(hitEnemyBuffer);
  hitEnemySound.setVolume(HIT_ENEMY);

  diedEnemyBuffer.loadFromFile(resourcePath() + "files/music/enemyDie.wav");
  diedEnemySound.setBuffer(diedEnemyBuffer);
  diedEnemySound.setVolume(DIED_ENEMY);

  diedPlayerBuffer.loadFromFile(resourcePath() + "files/music/playerDie.wav");
  diedPlayerSound.setBuffer(diedPlayerBuffer);
  diedPlayerSound.setVolume(DIED_PLAYER);

  metroBuffer.loadFromFile(resourcePath() + "files/music/metroSound.wav");
  metroSound.setBuffer(metroBuffer);
  metroSound.setLoop(true);
  metroSound.setVolume(METRO);

  carBuffer.loadFromFile(resourcePath() + "files/music/carSound.wav");
  carSound.setBuffer(carBuffer);
  carSound.setLoop(true);
  carSound.setVolume(CAR);

  getAntibodiesBuffer.loadFromFile(resourcePath() + "files/music/getAntibodies.wav");
  getAntibodiesSound.setBuffer(getAntibodiesBuffer);
  getAntibodiesSound.setVolume(ANTIBODIES);

  getVaccineBuffer.loadFromFile(resourcePath() + "files/music/getVaccine.wav");
  getVaccineSound.setBuffer(getVaccineBuffer);
  getVaccineSound.setVolume(VACCINE);

  treatPatientBuffer.loadFromFile(resourcePath() + "files/music/treatPatient.wav");
  treatPatientSound.setBuffer(treatPatientBuffer);
  treatPatientSound.setVolume(TREAT_PATIENT);
}

void MusicManager::PlayBackgroundMenuMusic() {
  backgroundMenuMusic.play();
}

void MusicManager::StopBackgroundMenuMusic() {
  backgroundMenuMusic.stop();
}

void MusicManager::PlayOnButtonSound() {
  onButtonSound.play();
}

void MusicManager::PlaySelectButtonSound() {
  selectButtonSound.play();
}

void MusicManager::PlayBackgroundGameMusic() {
  backgroundGameMusic.play();
}

void MusicManager::StopBackgroundGameMusic() {
  backgroundGameMusic.stop();
}

void MusicManager::PlayHitPlayerSound() {
  hitPlayerSound.play();
}

void MusicManager::PlayHitEnemySound() {
  hitEnemySound.play();
}

void MusicManager::PlayDiedEnemySound() {
  diedEnemySound.play();
}

void MusicManager::PlayDiedPlayerSound() {
  diedPlayerSound.play();
}

void MusicManager::PlayMetroSound() {
  isDriveMetro = !isDriveMetro;

  if (isDriveMetro) {
    metroSound.play();
  } else {
    metroSound.stop();
  }
}

void MusicManager::PlayCarSound() {
  isDriveCar = !isDriveCar;

  if (isDriveCar) {
    carSound.play();
  } else {
    carSound.stop();
  }
}

void MusicManager::StopCarSound() {
  carSound.stop();
}

void MusicManager::PlayGetAntibodiesSound() {
  getAntibodiesSound.play();
}

void MusicManager::PlayGetVaccineSound() {
  getVaccineSound.play();
}

void MusicManager::PlayTreatPatientSound() {
  treatPatientSound.play();
}

void MusicManager::StopTreatPatientSound() {
  treatPatientSound.stop();
}

void MusicManager::StopAllMusic() {
  metroSound.stop();
  carSound.stop();
}
