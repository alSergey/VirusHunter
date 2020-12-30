#pragma once

#include <string>
#include "Enemy.h"

class Breaker : public Enemy {
 public:
  explicit Breaker(float x, float y, int width, int height, int hp, int dmg, const std::string &name);
};
