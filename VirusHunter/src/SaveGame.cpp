#include "SaveGame.h"
#include <fstream>
#include <sstream>

void Save::NextLvl() {
  lvl += 1;
}

void Save::LastLvl() {
  lvl -= 1;
}

void Save::SetEndGame() {
  lvl = 0;
}

int Save::GetLvl() const {
  return lvl;
}

std::string Save::GetLvlName() {
  lvl = LoadLvl();

  std::ifstream saveStatFile(STAT_FILE);

  if (saveStatFile.is_open()) {
    int statlvl;
    saveStatFile >> statlvl;

    if (statlvl != 0 && lvl == 1) {
      NextLvl();
    }
  }

  return (MAPS_PATH + std::to_string(lvl) + ".tmx");
}

void Save::SaveGame(int points) const {
  SaveLvl(lvl);
  SavePoints(points);
}

bool Save::CheckEndGame() const {
  std::ifstream nextMap(MAPS_PATH + std::to_string(lvl + 1) + ".tmx");
  bool exist = nextMap.is_open();
  nextMap.close();
  return !exist;
}

bool Save::IsExistLvlFile() {
  std::fstream saveLvlFile(LVL_FILE);
  bool exist = saveLvlFile.is_open();
  saveLvlFile.close();
  return exist;
}

void Save::RemoveGameSaves() {
    std::ostringstream ssLvl;
    ssLvl << LVL_FILE;
    remove(ssLvl.str().c_str());

    std::ostringstream ssArmor;
    ssArmor << ARMOR_FILE;
    remove(ssArmor.str().c_str());

    std::ostringstream ssPoints;
    ssPoints << POINTS_FILE;
    remove(ssPoints.str().c_str());
}

void Save::RemoveConfig() {
    std::ostringstream ssConfig;
    ssConfig << CONFIG_FILE;
    remove(ssConfig.str().c_str());
}

int Save::LoadLvl() {
  std::ifstream saveLvlFile(LVL_FILE);
  if (!saveLvlFile.is_open()) {
    return 1;
  }

  int lvl;
  saveLvlFile >> lvl;
    
  saveLvlFile.close();
  return lvl;
}

void Save::SaveLvl(int lvl) {
  std::ofstream save_file(LVL_FILE);
  save_file << lvl;
  save_file.close();
}

int Save::LoadPoints() {
  std::ifstream savePointsFile(POINTS_FILE);
  if (!savePointsFile.is_open()) {
    return 0;
  }

  int points;
  savePointsFile >> points;
    
  savePointsFile.close();
  return points;
}

void Save::SavePoints(int points) {
  std::ofstream save_file(POINTS_FILE);
  save_file << points;
  save_file.close();
}

std::vector<int> Save::LoadArmors() {
  std::ifstream saveArmorsFile(ARMOR_FILE);
  std::vector<int> armors;
  armors.resize(3, 0);

  if (!saveArmorsFile.is_open()) {
    return armors;
  }

  for (int &i : armors) {
    saveArmorsFile >> i;
  }

  saveArmorsFile.close();
  return armors;
}

void Save::SaveArmor(const std::vector<int> &arm) {
  std::ofstream saveArmorsFile(ARMOR_FILE);

  for (int armor : arm) {
    saveArmorsFile << armor << std::endl;
  }

  saveArmorsFile.close();
}

std::vector<int> Save::LoadStat() {
  std::ifstream saveStatFile(STAT_FILE);
  std::vector<int> stat;
  stat.resize(14, 0);

  if (!saveStatFile.is_open()) {
    return stat;
  }
    
  for (int &i : stat) {
    saveStatFile >> i;
  }

  saveStatFile.close();
  return stat;
}

void Save::SaveStat(const std::vector<int> &stat) {
  std::ofstream saveStatFile(STAT_FILE);

  for (int i : stat) {
    saveStatFile << i << std::endl;
  }

  saveStatFile.close();
}

std::vector<int> Save::LoadConfig() {
  std::ifstream saveConfigFile;
  std::vector<int> config;
  config.resize(15, 0);

  std::fstream saveConfig(CONFIG_FILE);
  if (saveConfig.is_open()) {
    saveConfigFile.open(CONFIG_FILE);
  } else {
    saveConfigFile.open(CONFIG_DEFAULT_FILE);
  }
  saveConfig.close();

  for (int &i : config) {
    saveConfigFile >> i;
  }

  saveConfigFile.close();
  return config;
}

void Save::SaveConfig(const std::vector<int> &config) {
  std::ofstream saveConfigFile(CONFIG_FILE);

  for (int i : config) {
    saveConfigFile << i << std::endl;
  }

  saveConfigFile.close();
}


