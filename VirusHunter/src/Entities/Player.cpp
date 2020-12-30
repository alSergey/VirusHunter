#include "Player.h"
#include "ResourcePath.hpp"

Player::Player(const sf::FloatRect &position, int hp, int dmg, int points, std::vector<int> armors)
    : Entity(position.left, position.top, 64, 64),
      startPlayerPosition(position),
      hp(hp),
      dmg(dmg),
      points(points),
      dir(false),
      finish(false),
      isFinishPosition(false),
      vaccine(false),
      max_jump(0),
      arm(0),
      isGround(true),
      STATE(STAY),
      treat(false),
      treatC(0),
      alive(false),
      tookDmg(false),
      dmgC(0),
      fire(false),
      fireC(0),
      isDrive(false),
      playFinishMusic(0),
      bathrobe(position.left, position.top, 64, 64, armors[2]),
      shoes(position.left, position.top, 64, 64, armors[1]),
      cap(position.left, position.top, 64, 64, armors[0]) {
  anim = AnimationManager(resourcePath() + "files/images/doctor.png");

  anim.Create("walk", 76, 76, 64, 64, 7, 0.005, 72);
  anim.Create("stay", 4, 4, 64, 64, 8, 0.0005, 72);
  anim.Create("jump", 4, 295, 64, 64, 7, 0.007, 72);
  anim.Create("lay", 152, 362, 64, 64, 1, 0.000, 0);
  anim.Create("walklay", 4, 507, 64, 64, 6, 0.005, 72);
  anim.Create("dmg", 4, 435, 64, 64, 2, 0.004, 72);
  anim.Create("fire", 4, 147, 64, 64, 3, 0.007, 72);
  anim.Create("die", 4, 219, 64, 64, 4, 0.004, 72);
  anim.Create("win", 0, 744, 33, 76, 4, 0.0045, 38);
  anim.Create("treat", 4, 651, 64, 64, 5, 0.002, 72);

  arm = bathrobe.GetArm() + shoes.GetArm() + cap.GetArm();
}

void Player::keyCheck() {
    if (!(key["L"] || key["R"])) {
      dx = 0;
      if (STATE == RUN) {
        STATE = STAY;
      }
    }

  if (key["L"]) {
    dir = true;
    if (STATE == STAY) {
      STATE = RUN;
      dx = -PLAYER_DX;
      treat = false;
    }

      if (STATE == JUMP) {
          STATE = JUMP;
          dx = -PLAYER_DX;
          treat = false;
      }
  }

  if (key["R"]) {
    dir = false;
    if (STATE == STAY) {
      STATE = RUN;
      dx = PLAYER_DX;
      treat = false;
    }

      if (STATE == JUMP) {
          STATE = JUMP;
          dx = PLAYER_DX;
          treat = false;
      }
  }

  if (key["UP"]) {
    if (STATE == STAY || STATE == RUN) {
      dy = -PLAYER_DY;
      STATE = JUMP;
      treat = false;
    }
  }

  if (key["DOWN"]) {
    if (STATE != JUMP) {
      if (STATE == RUN) {
        STATE = WALKLAY;
      } else {
        STATE = LAY;
      }
      treat = false;
    }
  }

  if (!key["UP"]) {
    if (STATE == JUMP) {
      dy = PLAYER_DY;
    }
  }

  if (key["SPACE"]) {
    fireC = PLAYER_FIRE_ANIM_TIME;
    fire = true;
  }

  key["SPACE"] = false;
}

int Player::GetDmg() const {
  return dmg;
}

void Player::Update(float time, std::vector<Object> &obj) {
  keyCheck();

  if (STATE == STAY) {
    setAnim("stay");
  }

  if (STATE == RUN) {
    setAnim("walk");
  }

  if (STATE == JUMP) {
    setAnim("jump");
  }

  if (STATE == LAY) {
    setAnim("lay");
  }

  if (STATE == WALKLAY) {
    setAnim("walklay");
  }

  if (hp > 0) {
    rect.left += dx * time;
  }

  if (tookDmg) {
    setAnim("dmg");
    --dmgC;

    if (dmgC == 0) {
      tookDmg = false;
    }
  }

  collision(0, obj);

  if (fire) {
    setAnim("fire");
    --fireC;
    if (fireC == 0) {
      fire = false;
    }
  }

  setDir();

  if (STATE != JUMP) {
    if ((STATE == STAY || STATE == RUN || STATE == LAY) && !isGround) {
      setAnim("jump");
    }

    dy = PLAYER_DY;
  }

  if (STATE == JUMP) {
    max_jump += PLAYER_DY * time;
    if (max_jump > PLAYER_MAX_JUMP_TIME) {
      dy = PLAYER_DY;
    }
  }

  rect.top += dy * time;
  isGround = false;
  collision(1, obj);

  if (hp <= 0) {
    setAnim("die");
  }

  if (treat && !alive) {
    if (playFinishMusic == 2) {
      playFinishMusic = 3;
    }

    if (playFinishMusic == 1) {
      playFinishMusic = 2;
    }

    setAnim("treat");
    --treatC;
    if (treatC <= 0) {
      alive = true;
      treat = false;
    }
  }

  anim.Tick(time);
  obj[0].rect = rect;
  bathrobe.Update(time, obj);
  shoes.Update(time, obj);
  cap.Update(time, obj);
}

void Player::setAnim(const std::string &str) {
  anim.Set(str);
  bathrobe.SetAnim(str);
  shoes.SetAnim(str);
  cap.SetAnim(str);
}

void Player::setDir() {
  anim.Flip(dir);
  bathrobe.FlipAnim(dir);
  shoes.FlipAnim(dir);
  cap.FlipAnim(dir);
}

bool Player::GetFinish() const {
  return finish;
}

void Player::collision(int num, std::vector<Object> &objs) {
  for (auto &obj : objs) {
    if (rect.intersects(obj.rect)) {
      if (obj.name == "wall") {
        if (dy > 0 && num == 1) {
          rect.top = obj.rect.top - rect.height;
          dy = 0;
          isGround = true;
          max_jump = PLAYER_MAX_JUMP_TIME;
          if (STATE == JUMP) {
            max_jump = 0;
          }
          STATE = STAY;
        }

        if (dy < 0 && num == 1) {
          rect.top = obj.rect.top + obj.rect.height;
          dy = 0;
          max_jump = PLAYER_MAX_JUMP_TIME;
        }

        if (dx > 0 && num == 0) {
          rect.left = obj.rect.left - rect.width;
        }

        if (dx < 0 && num == 0) {
          rect.left = obj.rect.left + obj.rect.width;
        }
      }

      if (obj.name == "death" && obj.rect.intersects(rect)) {
          GoToStart();
      }

      finish = false;
      isFinishPosition = false;
      if (obj.name == "finish") {
        isFinishPosition = true;
        if (vaccine && !treat) {
          playFinishMusic = 1;
          treat = true;
          treatC = PLAYER_TREAT_ANIM_TIME;
        }
      }
    }
  }

  if (!isFinishPosition) {
    playFinishMusic = 0;
  }
}

void Player::DrawObjs(sf::RenderWindow &window) {
  Draw(window);
  bathrobe.Draw(window);
  shoes.Draw(window);
  cap.Draw(window);
}

void Player::TakeDamage(int getDmg) {
  if (hp > 0 && getDmg != 0) {
    if (GetArm() >= getDmg) {
      --hp;
    } else {
      hp += arm - getDmg;
    }
    dmgC = PLAYER_DAMAGED_ANIM_TIME;
    tookDmg = true;
  }
}

int Player::GetHp() const {
  return hp;
}

int Player::GetArm() const {
  return arm;
}

bool Player::GetDir() const {
  return dir;
}

void Player::SetKey(const std::string &name, bool value) {
  key[name] = value;
}

void Player::ChangePoints(int getPoints) {
  points += getPoints;
}

int Player::GetPoints() const {
  return points;
}

bool Player::GetVaccine() const {
  return vaccine;
}

void Player::SetVaccine(bool value) {
  vaccine = value;
}

void Player::GoToStart() {
    rect.left = startPlayerPosition.left;
    rect.top = startPlayerPosition.top;
}

void Player::SetPosition(float x, float y) {
  rect.left = x;
  rect.top = y;
}

std::vector<int> Player::GetMainData() {
  std::vector<int> data;
  data.push_back(hp);
  data.push_back(points);
  data.push_back(arm);
  data.push_back(shoes.Getlvl());
  data.push_back(cap.Getlvl());
  data.push_back(bathrobe.Getlvl());
  data.push_back(vaccine);

  return data;
}

void Player::SetDrive() {
  isDrive = !isDrive;
}

bool Player::IsDrive() const {
  return isDrive;
}

bool Player::IsFinishPosition() const {
  if (treat || alive) {
    return false;
  }

  return isFinishPosition;
}

bool Player::DrawProgressBar() const {
  if (treat || alive) {
    return true;
  } else {
    return false;
  }
}

bool Player::GetAlive() const {
  return alive;
}

void Player::SetFinish(bool getFinish) {
  this->finish = getFinish;
}

int Player::PlayFinishMusic() const {
  return playFinishMusic;
}

void Player::SetStay() {
    STATE = STAY;
    key["L"] = key["DOWN"] = key["R"] = key["SPACE"] = key["UP"] = false;
}
