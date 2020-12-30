#include "Antibodies.h"
#include "ResourcePath.hpp"

Antibodies::Antibodies(float x, float y, int width, int height, const std::string &name)
    : Entity(x, y, width, height),
      name(name) {
  if (name == "antigen") {
    setAntigen();
  }

  if (name == "vaccine") {
    setVaccine();
  }
}

void Antibodies::Update(sf::FloatRect playerRect) {
  anim.Tick(0.05);
  if (rect.intersects(playerRect)) {
    isLife = false;
  }
}

void Antibodies::Update(float time, std::vector<Object> &obj) {
}

std::string Antibodies::GetName() {
  return name;
}

void Antibodies::setAntigen() {
  anim = AnimationManager(resourcePath() + "files/images/antitel.png");
  anim.Create("stay", 4, 4, 32, 32, 3, 1, 34);
  anim.Set("stay");
}

void Antibodies::setVaccine() {
  anim = AnimationManager(resourcePath() + "files/images/vaccine.png");
  anim.Create("stay", 4, 4, 32, 32, 3, 1, 34);
  anim.Set("stay");
}
