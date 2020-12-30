#pragma once

#include <map>
#include <memory>
#include <string>
#include "GameLabel.h"

#define SHIFT 20

enum PositionSettings {
  LEFT_UP,
  CENTER_UP,
  RIGHT_UP,
  LEFT_DOWN,
  RIGHT_DOWN,
  PLAYER_POSITION,
  CUSTOM_POSITION
};

class GameLabelManager {
 public:
  GameLabelManager() = default;
  void SetLabel(const std::string &mapStr, const std::shared_ptr<GameLabel> &label, PositionSettings labelPosition);
  void SetText(const std::string &mapStr, const std::string &getStr);
  void Draw(const std::string &mapStr, sf::RenderWindow &window);
  void Draw(const std::string &mapStr, sf::RenderWindow &window, float x, float y);

 private:
  std::map<std::string, PositionSettings> labelPositionSettings;
  std::map<std::string, std::shared_ptr<GameLabel>> gameLabel;
};
