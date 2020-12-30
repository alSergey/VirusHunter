#pragma once

#include <vector>
#include <string>
#include <map>
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Robe.h"
#include "Shoes.h"
#include "Cap.h"

#define PLAYER_DX 0.13
#define PLAYER_DY 0.2
#define PLAYER_MAX_JUMP_TIME 300
#define PLAYER_FIRE_ANIM_TIME 20
#define PLAYER_TREAT_ANIM_TIME 200
#define PLAYER_WIN_ANIM_TIME 100
#define PLAYER_DAMAGED_ANIM_TIME 30

class Player : public Entity {
 public:
  explicit Player(const sf::FloatRect &position, int hp, int dmg, int points, std::vector<int> armors);
  void Update(float time, std::vector<Object> &obj) override;
  void SetKey(const std::string &name, bool value = true);
  bool GetDir() const;
  int GetHp() const;
  int GetArm() const;
  void TakeDamage(int getDmg);
  int GetDmg() const;
  void ChangePoints(int getPoints);
  int GetPoints() const;
  bool GetVaccine() const;
  void SetVaccine(bool value);
  void DrawObjs(sf::RenderWindow &window);
  void GoToStart();
  bool GetFinish() const;
  void SetPosition(float x, float y);
  std::vector<int> GetMainData();
  void SetDrive();
  bool IsDrive() const;
  bool IsFinishPosition() const;
  bool DrawProgressBar() const;
  bool GetAlive() const;
  void SetFinish(bool getFinish = true);
  int PlayFinishMusic() const;
  void SetStay();
    
 private:
  void keyCheck();
  void collision(int num, std::vector<Object> &objs);
  void setAnim(const std::string &str);
  void setDir();

  enum {
    STAY,
    RUN,
    JUMP,
    LAY,
    WALKLAY,
  } STATE;

  std::map<std::string, bool> key;
  sf::FloatRect startPlayerPosition;
  int dmgC;
  int fireC;
  int treatC;
  bool treat;
  bool finish;
  bool alive;
  bool dir;
  bool fire;
  int dmg;
  int hp;
  int arm;
  float max_jump;
  int points;
  bool isGround;
  bool tookDmg;
  bool vaccine;
  Robe bathrobe;
  Shoes shoes;
  Cap cap;
  int playFinishMusic;
  bool isDrive;
  bool isFinishPosition;
};
