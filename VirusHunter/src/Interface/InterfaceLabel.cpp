#include "InterfaceLabel.h"

InterfaceLabel::InterfaceLabel(const std::string &fontPath, unsigned int getSize)
    : size(getSize),
      x(0),
      y(0),
      width(0),
      height(0) {

  font.loadFromFile(fontPath);

  text.setFont(font);
  text.setCharacterSize(size);
  text.setStyle(sf::Text::Bold);
  text.setFillColor(sf::Color::White);
}

InterfaceLabel::InterfaceLabel(const std::string &fontPath, unsigned int getSize, const std::string &str)
    : InterfaceLabel(fontPath, getSize) {

  this->str = str;
  text.setString(str);
  getLocalSize();
}

InterfaceLabel::InterfaceLabel(const std::string &fontPath, unsigned int getSize, float getX, float getY)
    : InterfaceLabel(fontPath, getSize) {

  x = getX;
  y = getY;

  text.setPosition(x, y);
}

InterfaceLabel::InterfaceLabel(const std::string &fontPath, unsigned int getSize, float getX, float getY, const std::string &str)
    : InterfaceLabel(fontPath, getSize, getX, getY) {

  this->str = str;
  text.setString(str);
  getLocalSize();
}

void InterfaceLabel::SetText(const std::string &getStr) {
  str = getStr;
  text.setString(str);
  getLocalSize();
}

void InterfaceLabel::SetPosition(float getX, float getY) {
  x = getX;
  y = getY;

  text.setPosition(x, y);
}

sf::Vector2f InterfaceLabel::GetTextRectSize() const {
  return {width, height};
}

void InterfaceLabel::Draw(sf::RenderWindow &window) {
  window.draw(text);
}

void InterfaceLabel::getLocalSize() {
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

