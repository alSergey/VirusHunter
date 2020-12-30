#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "AnimationManager.h"
#include "Level_map.h"

class Entity {
 public:
  explicit Entity(float x, float y, int width, int height);
  explicit Entity(float x, float y, float dx, float dy, int width, int height);
  sf::FloatRect GetRect();
  virtual void Update(float time, std::vector<Object> &obj) = 0;
  void Draw(sf::RenderWindow &window);
  bool IsLife() const;

 protected:
  bool isLife;
  float dx;
  float dy;
  sf::FloatRect rect;
  AnimationManager anim;
};
