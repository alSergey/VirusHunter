#pragma once

#include <vector>
#include <string>
#include "ResourcePath.hpp"

#define MAPS_PATH resourcePath() + "files/maps/"
#define LVL_FILE appContainerPath() + "/Documents/save_lvl.txt"
#define POINTS_FILE appContainerPath() + "/Documents/save_points.txt"
#define ARMOR_FILE appContainerPath() + "/Documents/save_armor.txt"
#define STAT_FILE appContainerPath() + "/Documents/save_stat.txt"
#define CONFIG_FILE appContainerPath() + "/Documents/save_config.txt"
#define CONFIG_DEFAULT_FILE resourcePath() + "files/saves/save_config_default.txt"

class Save {
 public:
  void NextLvl();
  void LastLvl();
  void SetEndGame();
  int GetLvl() const;
    
  std::string GetLvlName();
  bool CheckEndGame() const;
  void SaveGame(int points) const;

  static bool IsExistLvlFile();
  static void RemoveGameSaves();
  static void RemoveConfig();

  static int LoadLvl();
  static void SaveLvl(int lvl);

  static int LoadPoints();
  static void SavePoints(int points);

  static std::vector<int> LoadArmors();
  static void SaveArmor(const std::vector<int> &arm);

  static std::vector<int> LoadStat();
  static void SaveStat(const std::vector<int> &stat);

  static std::vector<int> LoadConfig();
  static void SaveConfig(const std::vector<int> &config);

 private:
  int lvl;
};
