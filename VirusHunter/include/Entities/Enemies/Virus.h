#pragma once

#include <string>
#include "Enemy.h"

class Virus : public Enemy {
 public:
  explicit Virus(float x, float y, int width, int height, int hp, int dmg, const std::string &name);
};
