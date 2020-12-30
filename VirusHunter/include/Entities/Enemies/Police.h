#pragma once

#include <string>
#include "Enemy.h"

class Police : public Enemy {
 public:
  explicit Police(float x, float y, int width, int height, int hp, int dmg, int penalty, const std::string &name);
  int Penatly();
  bool IsDrawPenaltyMenu();
  bool ISDrawDiedMenu();
  bool ISMetUser() const;

 private:
  int penalty;
  bool drawPenaltyMenu;
  bool drawDiedMenu;
  bool isMetUser;
};
