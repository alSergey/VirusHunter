#include "Enemy.h"

Enemy::Enemy(float x, float y, int width, int height, int hp, int dmg, std::string name)
    : Entity(x, y, width, height),
      name(std::move(name)),
      hp(hp),
      dmg(dmg),
      dir(false),
      fire(false),
      timerHit(std::rand() % ENEMY_HIT_TIME),
      dieSound(false) {
}

void Enemy::Update(float time, std::vector<Object> &obj) {
  timerHit += time;
    
  if (fire) {
    anim.Set("fire");
  } else {
    anim.Set("move");
  }

  if (!isLife) {
    anim.Set("dead");
  }

  if (hp < 0 && isLife) {
    dx = 0;
    dy = 0;
    anim.Set("dead");
    isLife = false;
    dieSound = true;
  }

  anim.Flip(dir);
  anim.Tick(time);
}

float Enemy::GetTimer() const {
  return timerHit;
}

void Enemy::ResetTimer() {
  timerHit = 0;
}

int Enemy::GetDmg() const {
  return dmg;
}

void Enemy::TakeDmg(int takeDmg) {
  hp -= takeDmg;
}

void Enemy::SetFire(bool getFire) {
  this->fire = getFire;
}

void Enemy::SetDir(bool getDir) {
  this->dir = getDir;
}

bool Enemy::GetDieSound() const {
  return dieSound;
}

void Enemy::SetDieSound() {
  dieSound = false;
}

std::string Enemy::GetName() {
  return name;
}

