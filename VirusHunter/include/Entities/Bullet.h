#pragma once

#include <vector>
#include "Entity.h"

#define BULLET_TIME_DIE 400
#define ENEMY_BULLET_DX 0.20
#define PLAYER_BULLET_DX 0.25

class Bullet : public Entity {
 public:
  explicit Bullet(float x, float y, float dx, float dy, int dmg, bool player);
  void Update(float time, std::vector<Object> &obj) override;
  int GetDmg() const;
  bool IsDie();

 private:
  int dmg;
  bool isDie;
  float timerDie;
};
