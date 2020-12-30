#pragma once

#include <vector>
#include <string>
#include "Transport.h"

#define FUEL_LOSS 0.1
#define AUTO_DX 0.3
#define MONORAIL_DX 0.4

class SafeTransport : public Transport {
 public:
  explicit SafeTransport(float x, float y, int width, int height, const std::string &name, std::vector<int> config);
  void Update(float time, std::vector<Object> &obj) override;
  int GetFuel() const;

 private:
  float fuel{};
  void setAuto(int getFuel);
  void setMonorail(int getFuel);
};
