#include "Transport.h"

Transport::Transport(float x, float y, int wight, int height, std::string name)
    : Entity(x, y, wight, height),
      name(std::move(name)),
      isDrive(false),
      isHitWall(false),
      dir(false) {
}

void Transport::SetDrive() {
  if (isDrive && isHitWall) {
    dir = !dir;
    isHitWall = false;
  }

  isDrive = !isDrive;
}

bool Transport::IsDrive() const {
  return isDrive;
}

bool Transport::GetDir() const {
  return dir;
}

std::string Transport::GetName() {
  return name;
}
