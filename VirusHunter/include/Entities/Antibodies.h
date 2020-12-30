#pragma once

#include <vector>
#include <string>
#include "Entity.h"

class Antibodies : public Entity {
 public:
  Antibodies(float x, float y, int width, int height, const std::string &name);
  void Update(sf::FloatRect playerRect);
  void Update(float time, std::vector<Object> &obj) override;
  std::string GetName();

 private:
  std::string name;
  void setAntigen();
  void setVaccine();
};
