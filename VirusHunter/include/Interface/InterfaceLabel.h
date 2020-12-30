#pragma once

#include <string>
#include <SFML/Graphics.hpp>

class InterfaceLabel {
 public:
  explicit InterfaceLabel(const std::string &fontPath, unsigned int getSize);
  explicit InterfaceLabel(const std::string &fontPath, unsigned int getSize, const std::string &str);
  explicit InterfaceLabel(const std::string &fontPath, unsigned int getSize, float getX, float getY);
  explicit InterfaceLabel(const std::string &fontPath, unsigned int getSize, float getX, float getY, const std::string &str);
  void SetText(const std::string &getStr);
  void SetPosition(float getX, float getY);
  sf::Vector2f GetTextRectSize() const;
  void Draw(sf::RenderWindow &window);

 protected:
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
