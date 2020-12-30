#pragma once

#include <string>
#include "InterfaceLabel.h"
#include "MusicManager.h"

class InterfaceButton : public InterfaceLabel {
 public:
  InterfaceButton(const std::string &fontPath, unsigned int getSize, const std::string &str);
  InterfaceButton(const std::string &fontPath, unsigned int getSize, float getX, float getY, const std::string &str);
  bool IsSelect(sf::Vector2i mouse, MusicManager &music);

 private:
  bool isOnButton;
};
