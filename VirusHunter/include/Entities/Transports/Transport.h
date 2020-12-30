#pragma once

#include <string>
#include "Entity.h"

class Transport : public Entity {
 public:
  explicit Transport(float x, float y, int width, int height, std::string name);
  void SetDrive();
  bool IsDrive() const;
  bool GetDir() const;
  std::string GetName();

 protected:
  std::string name;
  bool dir;
  bool isDrive;
  bool isHitWall;
};
