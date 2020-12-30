#pragma once

#include <vector>
#include <string>
#include "Transport.h"

#define HP_TIME_LOSS 2000
#define BUS_DX 0.3
#define METRO_DX 0.4

class UnSafeTransport : public Transport {
 public:
  explicit UnSafeTransport(float x, float y, int width, int height, const std::string &name, std::vector<int> config);
  void Update(float time, std::vector<Object> &obj) override;
  int GetDmg();

 private:
  int dmg{};
  float timerHit;
  void setBus(int getDmg);
  void setMetro(int getDmg);
};
