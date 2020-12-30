#pragma once

#include <SFML/Graphics.hpp>

#define TREAT_TIME 300

class GameTreatPatientProgressBar {
 public:
  GameTreatPatientProgressBar();
  void Draw(sf::RenderWindow &window, bool isDraw);

 private:
  float status;
  sf::RectangleShape bar;
  sf::RectangleShape progress;
};
