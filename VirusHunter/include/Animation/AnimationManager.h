#pragma once

#include <map>
#include <string>
#include "Animation.h"

class AnimationManager {
 public:
  AnimationManager() = default;
  explicit AnimationManager(sf::Texture &texture);
  explicit AnimationManager(const std::string &str);
  void Create(const std::string &name, int x, int y, int w, int h, int count, float speed, int step = 0);
  void Draw(sf::RenderWindow &window, int x = 0, int y = 0);
  void Set(const std::string &name);
  void Flip(bool b = true);
  void Tick(float time);
  void Pause();
  int GetCurrentFrame();

 private:
  std::map<sf::String, Animation> animList;
  sf::String currentAnim;
  sf::Texture texture;
};
