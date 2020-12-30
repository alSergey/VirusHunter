#include "Sick.h"
#include "ResourcePath.hpp"

Sick::Sick(float x, float y, float dx, float dy, int width, int height)
    : Entity(x, y, width, height),
      alive(false),
      aliveAnimTimer(ALIVE_ANIM_TIME),
      end(false) {
  anim = AnimationManager(resourcePath() + "files/images/ill.png");
  anim.Create("ill", 2, 0, 75, 64, 3, 0.003, 79);
  anim.Create("alive", 1, 71, 90, 64, 3, 0.001, 94);
  anim.Set("ill");
}

void Sick::Update(float time, std::vector<Object> &obj) {
  anim.Tick(time);
  if (alive) {
    --aliveAnimTimer;
    if (aliveAnimTimer == 0) {
      end = true;
    }
  }
}

void Sick::SetAlive() {
  if (!alive) {
    anim.Set("alive");
    alive = true;
  }
}

bool Sick::GetEnd() const {
  return end;
}
