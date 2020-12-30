#pragma once

#include <string>
#include "Enemy.h"

class Delivery : public Enemy {
 public:
  explicit Delivery(float x, float y, int width, int height, int hp, int dmg, const std::string &name);
};
