#pragma once

#include <list>
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include "Level_map.h"
#include "Player.h"
#include "MusicManager.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Antibodies.h"
#include "GameLabelManager.h"
#include "GameLabel.h"
#include "Breaker.h"
#include "Delivery.h"
#include "Police.h"
#include "Virus.h"
#include "SafeTransport.h"
#include "UnSafeTransport.h"
#include "Sick.h"
#include "GameTreatPatientProgressBar.h"

#define FIRE_TIME 1000

class GameManager {
 public:
  explicit GameManager(Level &lvl,
                       int textSize,
                       MusicManager &music,
                       const std::vector<int> &arms,
                       int points,
                       std::vector<int> stat,
                       const std::vector<int> &config);

  // Обновление всех классов
  void Update(float time);
  // Вывод всех классов на экран
  void Draw(sf::RenderWindow &window, float x, float y, int height, int width);
  // Получение игрока
  Player &GetPlayer();
  // Огонь игроком
  void Fire();
  // Садится в транспорт
  void TakeTransport();
  // Получение статистики
  std::vector<int> GetStat();

 private:
  MusicManager &music;
//  GameFPS fps;

  std::vector<int> stat;
  int antigenPoints;

  std::vector<Object> obj;
  Player player;
  float fireTimer;
  std::shared_ptr<Sick> sick;

  GameLabelManager labelManager;
  GameTreatPatientProgressBar progressBar;
  void drawPlayerData(sf::RenderWindow &window);
//  void drawFPS(sf::RenderWindow &window);

  // Методы работы с классом Bullet
  std::list<Bullet> playerBullets;
  std::list<Bullet>::iterator playerBulletsIt;
  std::list<Bullet> enemyBullets;
  std::list<Bullet>::iterator enemyBulletsIt;
  void updateBullet(float time);
  void drawBullet(sf::RenderWindow &window);
  void checkHitEnemy();
  void checkHitPlayer();
  void bulletPlayer();

  // Методы работы с классом Enemy
  std::list<std::shared_ptr<Enemy>> enemies;
  std::list<std::shared_ptr<Enemy>>::iterator enemiesIt;
  void updateEnemy(float time);
  void drawEnemy(sf::RenderWindow &window, sf::FloatRect screenRect);

  // Методы работы с классом Antibodies
  std::list<Antibodies> antibodies;
  std::list<Antibodies>::iterator antibodiesIt;
  void drawAntibodies(sf::RenderWindow &window, sf::FloatRect screenRect);
  void updateAntibodies();

  // Методы работы с классом Transport
  std::list<SafeTransport> safeTransports;
  std::list<SafeTransport>::iterator safeTransportsIt;
  std::list<UnSafeTransport> unSafeTransports;
  std::list<UnSafeTransport>::iterator unSafeTransportsIt;
  void updateTransport(float time);
  void updateSafeTransport(float time);
  void updateUnSafeTransport(float time);
  void drawTransport(sf::RenderWindow &window, sf::FloatRect screenRect);
  void drawSafeTransport(sf::RenderWindow &window, sf::FloatRect screenRect);
  void drawUnSafeTransport(sf::RenderWindow &window, sf::FloatRect screenRect);
};
