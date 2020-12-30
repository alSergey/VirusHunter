#pragma once

#include <vector>
#include <string>
#include "Entity.h"

class Armor : public Entity {
 public:
  Armor(float x, float y, int width, int height, int lvl);
  void Update(float time, std::vector<Object> &obj) override;
  void SetAnim(const std::string &name);
  void FlipAnim(bool value);
  int GetArm() const;
  int Getlvl() const;

 protected:
  int arm;
  int lvl;
};

