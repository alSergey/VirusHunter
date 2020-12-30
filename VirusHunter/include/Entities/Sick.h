#pragma once

#include <vector>
#include "Entity.h"

#define ALIVE_ANIM_TIME 100

class Sick : public Entity {
 public:
  explicit Sick(float x, float y, float dx, float dy, int width, int height);
  void Update(float time, std::vector<Object> &obj) override;
  void SetAlive();
  bool GetEnd() const;

 private:
  int aliveAnimTimer;
  bool alive;
  bool end;
};
