#pragma once

#include <string>
#include <SFML/Graphics.hpp>

class GameLabel {
 public:
  explicit GameLabel(unsigned int getSize);
  explicit GameLabel(unsigned int getSize, sf::Color color);
  explicit GameLabel(unsigned int getSize, const std::string &getStr);
  explicit GameLabel(unsigned int getSize, const std::string &getStr, sf::Color color);
  void SetText(const std::string &getStr);
  void SetPosition(float getX, float getY);
  sf::Vector2f GetTextRectSize() const;
  void Draw(sf::RenderWindow &window);

 private:
  void getLocalSize();

  float x;
  float y;
  unsigned int size;
  float height;
  float width;
  std::string str;
  sf::Font font;
  sf::Text text;
};
