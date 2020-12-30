#include "Entity.h"

Entity::Entity(float x, float y, int width, int height)
    : dx(0),
      dy(0),
      isLife(true),
      rect(x, y, width, height) {
}

Entity::Entity(float x, float y, float dx, float dy, int width, int height)
    : Entity(x, y, width, height) {
  this->dx = dx;
  this->dy = dy;
}

sf::FloatRect Entity::GetRect() {
  return rect;
}

void Entity::Draw(sf::RenderWindow &window) {
  anim.Draw(window, rect.left, rect.top + rect.height);
}

bool Entity::IsLife() const {
  return isLife;
}
