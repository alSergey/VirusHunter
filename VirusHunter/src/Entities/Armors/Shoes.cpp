#include "Shoes.h"
#include "ResourcePath.hpp"

Shoes::Shoes(float x, float y, int width, int height, int lvl)
    : Armor(x, y, width, height, lvl) {
  sf::Texture player_t;
  switch (lvl) {
    case 0: {
      player_t.loadFromFile(resourcePath() + "files/images/free.png");
      arm = 0;
      break;
    }

    case 1: {
      player_t.loadFromFile(resourcePath() + "files/images/shoes_1.png");
      arm = 1;
      break;
    }

    case 2: {
      player_t.loadFromFile(resourcePath() + "files/images/shoes_2.png");
      arm = 2;
      break;
    }

    case 3: {
      player_t.loadFromFile(resourcePath() + "files/images/shoes_3.png");
      arm = 3;
      break;
    }

    case 4: {
      player_t.loadFromFile(resourcePath() + "files/images/shoes_4.png");
      arm = 4;
      break;
    }

    default: {
      player_t.loadFromFile(resourcePath() + "files/images/free.png");
      arm = 0;
      break;
    }
  }

  anim = AnimationManager(player_t);
  anim.Create("walk", 76, 76, 64, 64, 7, 0.005, 72);
  anim.Create("stay", 4, 4, 64, 64, 8, 0.0005, 72);
  anim.Create("jump", 4, 295, 64, 64, 7, 0.007, 72);
  anim.Create("lay", 152, 362, 64, 64, 1, 0.000, 0);
  anim.Create("walklay", 4, 507, 64, 64, 6, 0.005, 72);
  anim.Create("dmg", 4, 435, 64, 64, 2, 0.004, 72);
  anim.Create("fire", 4, 147, 64, 64, 3, 0.007, 72);
  anim.Create("die", 4, 219, 64, 64, 4, 0.004, 72);
  anim.Create("treat", 4, 651, 64, 64, 5, 0.002, 72);
  anim.Create("win", 0, 744, 33, 76, 4, 0.0045, 38);
  anim.Set("stay");
}
