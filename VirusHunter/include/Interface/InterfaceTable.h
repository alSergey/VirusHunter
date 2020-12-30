#pragma once

#include <memory>
#include <vector>
#include "InterfaceLabel.h"
#include "InterfaceButton.h"

class InterfaceTable {
 public:
  InterfaceTable() = default;

  void SetCenterLabel(const std::shared_ptr<InterfaceLabel> &label);
  void SetLeftLabel(const std::shared_ptr<InterfaceLabel> &label);
  void SetRightLabel(const std::shared_ptr<InterfaceLabel> &label);

  void SetCenterButton(const std::shared_ptr<InterfaceButton> &button);
  void SetLeftButton(const std::shared_ptr<InterfaceButton> &button);
  void SetRightButton(const std::shared_ptr<InterfaceButton> &button);

  std::vector<std::shared_ptr<InterfaceButton>> GetCenterButtons();
  std::vector<std::shared_ptr<InterfaceButton>> GetLeftButtons();
  std::vector<std::shared_ptr<InterfaceButton>> GetRightButtons();

  void CalculateTablePosition();
  void SetPosition(unsigned int height, unsigned int width);
  void Draw(sf::RenderWindow &window);

 private:
  void calculateCenterLabel();
  void calculateCenterButton();
  void calculateLeftRightLabel();
  void calculateLeftRightButton();

  std::vector<std::shared_ptr<InterfaceLabel>> centerLabel;
  std::vector<sf::Vector2i> centerLabelPosition;
  float centerLabelMaxWidth = 0;
  float centerLabelHeight = 0;

  std::vector<std::shared_ptr<InterfaceButton>> centerButton;
  std::vector<sf::Vector2f> centerButtonPosition;
  float centerButtonMaxWidth = 0;
  float centerButtonHeight = 0;

  std::vector<std::shared_ptr<InterfaceLabel>> leftLabel;
  std::vector<std::shared_ptr<InterfaceLabel>> rightLabel;
  std::vector<sf::Vector2f> leftLabelPosition;
  std::vector<sf::Vector2f> rightLabelPosition;
  float leftLabelMaxWidth = 0;
  float rightLabelMaxWidth = 0;
  float leftLabelHeight = 0;
  float rightLabelHeight = 0;

  std::vector<std::shared_ptr<InterfaceButton>> leftButton;
  std::vector<std::shared_ptr<InterfaceButton>> rightButton;
  std::vector<sf::Vector2f> leftButtonPosition;
  std::vector<sf::Vector2f> rightButtonPosition;
  float leftButtonMaxWidth = 0;
  float rightButtonMaxWidth = 0;
  float leftButtonHeight = 0;
  float rightButtonHeight = 0;
};
