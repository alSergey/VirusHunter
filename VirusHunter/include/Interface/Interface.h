#pragma once

#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "GameManager.h"
#include "SaveGame.h"
#include "MusicManager.h"
#include "InterfaceLabel.h"
#include "InterfaceImage.h"
#include "InterfaceButton.h"
#include "InterfaceTable.h"
#include "ButtonsPressed.h"

class Interface {
 public:
  static Interface &GetInstance(sf::RenderWindow &window);
  void MainMenu(sf::RenderWindow &window);
  void PenaltyPolice(sf::RenderWindow &window);
  void DiedPolice(sf::RenderWindow &window);

 private:
  explicit Interface(sf::RenderWindow &window);
  ~Interface() = default;
  Interface(const Interface &);
  Interface &operator=(const Interface &);

  void newGameWarningMenu(sf::RenderWindow &window);
  void startNewGame(sf::RenderWindow &window);
  bool endGameWarningMenu(sf::RenderWindow &window);
  bool winMenu(sf::RenderWindow &window, bool isLoadFromMenu);
  bool nextLvlMenu(sf::RenderWindow &window);
  bool diedMenu(sf::RenderWindow &window);

  void statisticMenu(sf::RenderWindow &window);
  void configMenu(sf::RenderWindow &window);

  bool gameMenu(sf::RenderWindow &window, std::vector<int> data);
  bool shopMenu(sf::RenderWindow &window);

  void aboutMenu(sf::RenderWindow &window);

  MusicManager music;
  std::string buttonFontPath;
  std::string textFontPath;
  int height;
  int width;
  int buttonSize;
  int textSize;
  int headSize;
  int gameHeight;
  int gameWidth;
  int gameText;
};
