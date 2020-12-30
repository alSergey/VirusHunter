#include "GameLabel.h"
#include "ResourcePath.hpp"

GameLabel::GameLabel(unsigned int getSize)
    : size(getSize),
      x(0),
      y(0),
      width(0),
      height(0) {
  font.loadFromFile(resourcePath() + "files/fonts/Inconsolata-Bold.ttf");

  text.setFont(font);
  text.setCharacterSize(size);
  text.setStyle(sf::Text::Bold);
  text.setFillColor(sf::Color::White);
}

GameLabel::GameLabel(unsigned int getSize, sf::Color color)
    : GameLabel(getSize) {
  text.setFillColor(color);
}

GameLabel::GameLabel(unsigned int getSize, const std::string &getStr)
    : GameLabel(getSize) {
  str = getStr;
  text.setString(str);
  getLocalSize();
}

GameLabel::GameLabel(unsigned int getSize, const std::string &getStr, sf::Color color)
    : GameLabel(getSize, getStr) {
  text.setFillColor(color);
}

void GameLabel::SetText(const std::string &getStr) {
  str = getStr;
  text.setString(str);
  getLocalSize();
}

void GameLabel::SetPosition(float getX, float getY) {
  x = getX;
  y = getY;

  text.setPosition(x, y);
}

sf::Vector2f GameLabel::GetTextRectSize() const {
  return {width, height};
}

void GameLabel::Draw(sf::RenderWindow &window) {
  window.draw(text);
}

void GameLabel::getLocalSize() {
  const sf::String textStr = text.getString() + '\n';

  float maxLineWidth = 0.f;
  float lineWidth = 0.f;
  unsigned int lines = 0;

  for (unsigned int itr : textStr) {
    if (itr == '\n') {
      ++lines;
      maxLineWidth = std::max(maxLineWidth, lineWidth);
      lineWidth = 0.f;
    } else {
      lineWidth += text.getFont()->getGlyph(itr, text.getCharacterSize(), text.getStyle() & sf::Text::Bold).advance;
    }
  }

  const auto lineHeight = static_cast<float>(text.getFont()->getLineSpacing(text.getCharacterSize()));

  height = lines * lineHeight;
  width = maxLineWidth;
}
