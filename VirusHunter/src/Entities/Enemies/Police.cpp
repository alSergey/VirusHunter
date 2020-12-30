#include "Police.h"
#include "ResourcePath.hpp"

Police::Police(float x, float y, int width, int height, int hp, int dmg, int penalty, const std::string &name)
    : Enemy(x, y, width, height, hp, dmg, name),
      penalty(penalty),
      isMetUser(false),
      drawPenaltyMenu(false),
      drawDiedMenu(false) {

  anim = AnimationManager(resourcePath() + "files/images/policemen.png");
  anim.Create("move", 4, 4, 64, 64, 3, 0.002, 72);
  anim.Create("fire", 4, 147, 64, 64, 3, 0.004, 72);
  anim.Create("dead", 4, 363, 64, 64, 3, 0.002, 72);
  anim.Set("move");
}

int Police::Penatly() {
  isMetUser = true;
  auto rand = std::rand() % 4;

  if (rand != 0) {
    rand = penalty;
    drawPenaltyMenu = true;

  } else {
    rand = 0;
    drawDiedMenu = true;
  }

  return rand;
}

bool Police::IsDrawPenaltyMenu() {
  if (drawPenaltyMenu) {
    drawPenaltyMenu = false;
    return true;
  }

  return false;
}

bool Police::ISDrawDiedMenu() {
  if (drawDiedMenu) {
    drawDiedMenu = false;
    return true;
  }

  return false;
}

bool Police::ISMetUser() const {
  return isMetUser;
}
