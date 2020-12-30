#include "SafeTransport.h"
#include "ResourcePath.hpp"

SafeTransport::SafeTransport(float x, float y, int width, int height, const std::string &name, std::vector<int> config)
    : Transport(x, y, width, height, name) {
  if (name == "auto") {
    setAuto(config[11]);
  }

  if (name == "monorail") {
    setMonorail(config[12]);
  }
}

void SafeTransport::Update(float time, std::vector<Object> &obj) {
  if (isDrive && !isHitWall && fuel > 0) {
    if (!dir) {
      rect.left += dx * time;
    } else {
      rect.left -= dx * time;
    }

    fuel -= FUEL_LOSS;
  }

  for (auto &i : obj) {
    if (i.rect.intersects(this->rect) && i.name == "wall" && isDrive) {
      isHitWall = true;
    }

    if (i.rect.intersects(this->rect) && (i.name == "auto" || i.name == "monorail")) {
      i.rect = this->rect;
    }
  }

  anim.Flip(dir);
  anim.Tick(time);
}

void SafeTransport::setAuto(int getFuel) {
  dx = AUTO_DX;
  fuel = getFuel;

  anim = AnimationManager(resourcePath() + "files/images/safe.png");
  anim.Create("move", 4, 5, 200, 100, 2, 0.005, 204);
  anim.Set("move");
}

void SafeTransport::setMonorail(int getFuel) {
  dx = MONORAIL_DX;
  fuel = getFuel;

  anim = AnimationManager(resourcePath() + "files/images/mono.png");
  anim.Create("move", 39, 2, 976, 140, 2, 0.002, 986);
  anim.Set("move");
}

int SafeTransport::GetFuel() const {
  return fuel;
}
