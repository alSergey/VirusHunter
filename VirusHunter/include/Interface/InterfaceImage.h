#pragma once

#include <string>
#include <SFML/Graphics.hpp>

class InterfaceImage {
 public:
  explicit InterfaceImage(const std::string &texturePath, float getX, float getY);
  explicit InterfaceImage(const std::string &texturePath, float getX, float getY, float getWidth, float getHeight);
  explicit InterfaceImage(const std::string &texturePath);
  void SetColor(sf::Color color);
  sf::Rect<int> GetTextureRect();
  sf::Vector2f GetSpriteRect();
  void Size(float w, float h);
  sf::Vector2<double> GetSize() const;
  void SetTextureRect(sf::Rect<int> rect);
  void SetPosition(float x, float y);
  void Draw(sf::RenderWindow &window);

 private:
  sf::Texture texture;
  sf::Sprite sprite;
  float width;
  float height;
};
