#include "Breaker.h"
#include "ResourcePath.hpp"

Breaker::Breaker(float x, float y, int width, int height, int hp, int dmg, const std::string &name)
    : Enemy(x, y, width, height, hp, dmg, name) {
  anim = AnimationManager(resourcePath() + "files/images/breaker.png");
  anim.Create("move", 4, 4, 64, 64, 6, 0.002, 72);
  anim.Create("fire", 68, 72, 64, 64, 2, 0.004, 72);
  anim.Create("dead", 4, 148, 64, 64, 3, 0.002, 72);
  anim.Set("move");
}