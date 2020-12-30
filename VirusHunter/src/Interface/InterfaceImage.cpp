#include "InterfaceImage.h"

InterfaceImage::InterfaceImage(const std::string &texturePath) {
  texture.loadFromFile(texturePath);
  sprite.setTexture(texture);
}

InterfaceImage::InterfaceImage(const std::string &texturePath, float x, float y)
    : InterfaceImage(texturePath) {

  sprite.setPosition(x, y);
}

InterfaceImage::InterfaceImage(const std::string &texturePath, float getX, float getY, float getWidth, float getHeight)
    : InterfaceImage(texturePath) {

  sprite.setPosition(getX, getY);

  width = getWidth;
  height = getHeight;

  sprite.setScale(width / sprite.getLocalBounds().width, height / sprite.getLocalBounds().height);
}

void InterfaceImage::SetColor(sf::Color color) {
  sprite.setColor(color);
}

sf::Rect<int> InterfaceImage::GetTextureRect() {
  return sprite.getTextureRect();
}

sf::Vector2f InterfaceImage::GetSpriteRect() {
  return sprite.getPosition();
}

sf::Vector2<double> InterfaceImage::GetSize() const {
  return {width, height};
}

void InterfaceImage::Size(float w, float h) {
  sf::Vector2f targetSize(w, h);
  width = w;
  height = h;

  sprite.setScale(
      targetSize.x / sprite.getLocalBounds().width,
      targetSize.y / sprite.getLocalBounds().height);
}

void InterfaceImage::SetTextureRect(sf::Rect<int> rect) {
  sprite.setTextureRect(rect);
}

void InterfaceImage::SetPosition(float x, float y) {
  sprite.setPosition(x, y);
}

void InterfaceImage::Draw(sf::RenderWindow &window) {
  window.draw(sprite);
}
