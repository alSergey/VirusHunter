#pragma once

#include <vector>
#include <string>
#include "Entity.h"

#define ENEMY_HIT_TIME 1500

class Enemy : public Entity {
 public:
  explicit Enemy(float x, float y, int width, int height, int hp, int dmg, std::string name);
  void Update(float time, std::vector<Object> &obj) override;
  int GetDmg() const;
  void TakeDmg(int getDmg);
  float GetTimer() const;
  void ResetTimer();
  void SetFire(bool getFire);
  void SetDir(bool getDir);
  bool GetDieSound() const;
  void SetDieSound();
  std::string GetName();

 protected:
  std::string name;
  int hp;
  int dmg;
  bool dir;
  bool fire;
  float timerHit;
  bool dieSound;
};
