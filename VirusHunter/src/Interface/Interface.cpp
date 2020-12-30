#include "Interface.h"
#include <sstream>
#include <memory>
#include "Level_map.h"
#include "ResourcePath.hpp"
#include "iostream"

sf::Vector2f calculatePlayerPosition(int width,
                                     int height,
                                     int left,
                                     int right,
                                     int top,
                                     int bottom,
                                     float playerX,
                                     float playerY) {
  float x = 0;
  float y = 0;

  if (playerX - width / 2.0 > left && playerX + width / 2.0 < right) {
    x = playerX;
  } else {
    if (playerX - width / 2.0 <= left) {
      x = left + width / 2.0;
    } else {
      x = right - width / 2.0;
    }
  }

  if (playerY - height / 2.0 > top && playerY + height / 2.0 < bottom) {
    y = playerY;
  } else {
    if (playerY - height / 2.0 <= top) {
      y = top + height / 2.0;
    } else {
      y = bottom - height / 2.0;
    }
  }

  return {x, y};
}

void setPrice(std::vector<int> armor, InterfaceLabel &label, int id) {
  std::ostringstream str;
  if (armor[id] * 200 + 200 >= 1000) {
    str << "max";
  } else {
    str << armor[id] * 200 + 200;
  }
  label.SetText(str.str());
}

void setArmLvl(std::vector<int> armor, InterfaceLabel &label, int id) {
  std::ostringstream str;
  str << "LVL:" << armor[id];
  label.SetText(str.str());
}

void buy(std::vector<int> arm_vector, int index) {
  ++arm_vector[index];
  Save::SaveArmor(arm_vector);
}

Interface &Interface::GetInstance(sf::RenderWindow &window) {
  static Interface instance(window);
  return instance;
}

Interface::Interface(sf::RenderWindow &window)
    : height(window.getSize().y),
      width(window.getSize().x),
      buttonSize(window.getSize().y / 25),
      textSize(window.getSize().y / 30),
      headSize(window.getSize().y / 20),
      gameHeight(1600),
      gameWidth(2500),
      gameText(1600 / 30),
      buttonFontPath(resourcePath() + "files/fonts/Inconsolata-Bold.ttf"),
      textFontPath(resourcePath() + "files/fonts/Inconsolata-Bold.ttf") {
}

// Вывод главного меню
void Interface::MainMenu(sf::RenderWindow &window) {
  float left = buttonSize * 2;
  float up = buttonSize * 0.6;
  float dy = buttonSize * 1.4;
  InterfaceButton newGameButton(buttonFontPath, buttonSize, left, up, "New Game");
  up += dy;
  InterfaceButton loadGameButton(buttonFontPath, buttonSize, left, up, "Load Game");
  up += dy;
  InterfaceButton statisticButton(buttonFontPath, buttonSize, left, up, "Statistic");
  up += dy;
  InterfaceButton shopButton(buttonFontPath, buttonSize, left, up, "Shop");
  up += dy;
  InterfaceButton exitButton(buttonFontPath, buttonSize, left, up, "Exit");

  InterfaceButton aboutButton(buttonFontPath, buttonSize, left, height - left, "About");

  InterfaceImage backImageSprite(resourcePath() + "files/menu/back_image.png");
  backImageSprite.SetPosition(statisticButton.GetTextRectSize().x + left + 30, 0);
  backImageSprite.Size(width - backImageSprite.GetTextureRect().left - width / 6, height);

  music.PlayBackgroundMenuMusic();

  ButtonsPressed buttons(3);

  while (window.isOpen()) {
    sf::Event event{};
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }

      if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::A) {
          buttons.SetButton(0, true);
        }

        if (event.key.code == sf::Keyboard::G) {
          buttons.SetButton(1, true);
        }

        if (event.key.code == sf::Keyboard::K) {
          buttons.SetButton(2, true);
        }
      }

      if (event.type == sf::Event::KeyReleased) {
        if (event.key.code == sf::Keyboard::A) {
          buttons.SetButton(0, false);
        }

        if (event.key.code == sf::Keyboard::G) {
          buttons.SetButton(1, false);
        }

        if (event.key.code == sf::Keyboard::K) {
          buttons.SetButton(2, false);
        }
      }
    }

    sf::Vector2i mousePosition = sf::Vector2i(sf::Mouse::getPosition(window));

    if (newGameButton.IsSelect(mousePosition, music)) {
      if (!Save::IsExistLvlFile()) {
        music.StopBackgroundMenuMusic();
        startNewGame(window);
      } else {
        newGameWarningMenu(window);
      }
    }

    if (loadGameButton.IsSelect(mousePosition, music)) {
      if (Save::IsExistLvlFile()) {
        if (Save::LoadLvl() != 0) {
          music.StopBackgroundMenuMusic();
          startNewGame(window);
        } else {
          winMenu(window, true);
        }
      }
    }

    if (statisticButton.IsSelect(mousePosition, music)) {
      music.PlayOnButtonSound();
      statisticMenu(window);
    }

    if (shopButton.IsSelect(mousePosition, music)) {
      shopMenu(window);
    }

    if (exitButton.IsSelect(mousePosition, music)) {
      window.close();
    }

    if (aboutButton.IsSelect(mousePosition, music)) {
      aboutMenu(window);
    }

    if (buttons.isPressed()) {
      configMenu(window);
    }

    window.clear(sf::Color(68, 101, 219));

    backImageSprite.Draw(window);
    newGameButton.Draw(window);
    loadGameButton.Draw(window);
    statisticButton.Draw(window);
    shopButton.Draw(window);
    exitButton.Draw(window);
    aboutButton.Draw(window);

    window.display();
  }
}

// Экран штраф от полицейского
void Interface::PenaltyPolice(sf::RenderWindow &window) {
  sf::View view(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
  view.setCenter(width / 2, height / 2);
  window.setView(view);

  InterfaceTable penaltyTable;
  penaltyTable.SetCenterLabel(std::make_shared<InterfaceLabel>(textFontPath, headSize, "You were caught and fined"));
  penaltyTable.SetCenterButton(std::make_shared<InterfaceButton>(buttonFontPath, buttonSize, "Continue"));

  penaltyTable.CalculateTablePosition();
  penaltyTable.SetPosition(height, width);

  while (window.isOpen()) {
    sf::Event event{};
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    auto mousePosition = sf::Vector2i(sf::Mouse::getPosition(window));

    if (penaltyTable.GetCenterButtons()[0]->IsSelect(mousePosition, music)) {
      break;
    }

    window.clear(sf::Color(68, 101, 219));
    penaltyTable.Draw(window);
    window.display();
  }
}

// Экран умер от полицейского
void Interface::DiedPolice(sf::RenderWindow &window) {
  sf::View view(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
  view.setCenter(width / 2, height / 2);
  window.setView(view);

  InterfaceTable diedTable;
  diedTable.SetCenterLabel(std::make_shared<InterfaceLabel>(textFontPath,
                                                            headSize,
                                                            "You were caught and brought back"));
  diedTable.SetCenterButton(std::make_shared<InterfaceButton>(buttonFontPath, buttonSize, "Continue"));

  diedTable.CalculateTablePosition();
  diedTable.SetPosition(height, width);

  while (window.isOpen()) {
    sf::Event event{};
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    auto mousePosition = sf::Vector2i(sf::Mouse::getPosition(window));

    if (diedTable.GetCenterButtons()[0]->IsSelect(mousePosition, music)) {
      break;
    }

    window.clear(sf::Color(68, 101, 219));
    diedTable.Draw(window);
    window.display();
  }
}

// Предупреждение о сбросе данных
void Interface::newGameWarningMenu(sf::RenderWindow &window) {
  InterfaceTable newGameWarningTable;
  newGameWarningTable.SetCenterLabel(std::make_shared<InterfaceButton>(textFontPath,
                                                                       textSize,
                                                                       "Are you sure you want to start a new game?"));
  newGameWarningTable.SetCenterLabel(std::make_shared<InterfaceButton>(textFontPath,
                                                                       textSize,
                                                                       "All your saves will be lost"));
  newGameWarningTable.SetLeftButton(std::make_shared<InterfaceButton>(buttonFontPath, buttonSize, "Yes"));
  newGameWarningTable.SetRightButton(std::make_shared<InterfaceButton>(buttonFontPath, buttonSize, "No"));

  newGameWarningTable.CalculateTablePosition();
  newGameWarningTable.SetPosition(height, width);

  while (window.isOpen()) {
    sf::Event event{};
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    sf::Vector2i mousePosition = sf::Vector2i(sf::Mouse::getPosition(window));

    if (newGameWarningTable.GetLeftButtons()[0]->IsSelect(mousePosition, music)) {
      Save::RemoveGameSaves();
      music.StopBackgroundMenuMusic();
      startNewGame(window);
      break;
    }

    if (newGameWarningTable.GetRightButtons()[0]->IsSelect(mousePosition, music)) {
      break;
    }

    window.clear(sf::Color(68, 101, 219));
    newGameWarningTable.Draw(window);
    window.display();
  }
}

// Старт новой игры
void Interface::startNewGame(sf::RenderWindow &window) {
  bool isRepeat = true;

  Save save;

  while (isRepeat) {
    music.PlayBackgroundGameMusic();

    ButtonsPressed next(4);
    ButtonsPressed last(4);

    sf::View menuView(sf::FloatRect(0, 0, width, height));
    sf::View gameView(sf::FloatRect(0, 0, gameWidth, gameHeight));

    Level lvl;
    lvl.LoadFromFile(save.GetLvlName());
    GameManager
        game(lvl, gameText, music, Save::LoadArmors(), Save::LoadPoints(), Save::LoadStat(), Save::LoadConfig());

    int left = lvl.GetObject("left").rect.left;
    int right = lvl.GetObject("right").rect.left + lvl.GetObject("right").rect.width;
    int top = lvl.GetObject("top").rect.top;
    int bottom = lvl.GetObject("bottom").rect.top + lvl.GetObject("bottom").rect.height;

    sf::Clock clock;
    while (window.isOpen()) {

      bool isBreak = false;
      sf::Event event{};
      while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
          isRepeat = false;
          window.close();
        }

        if (event.type == sf::Event::KeyPressed) {
          if (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::Left) {
            game.GetPlayer().SetKey("L", true);
          }

          if (event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right) {
            game.GetPlayer().SetKey("R", true);
          }

          if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up) {
            game.GetPlayer().SetKey("UP", true);
          }

          if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down) {
            game.GetPlayer().SetKey("DOWN", true);
          }

          if (event.key.code == sf::Keyboard::N) {
            next.SetButton(0, true);
          }

          if (event.key.code == sf::Keyboard::E) {
            next.SetButton(1, true);
          }

          if (event.key.code == sf::Keyboard::X) {
            next.SetButton(2, true);
          }

          if (event.key.code == sf::Keyboard::T) {
            next.SetButton(3, true);
          }

          if (event.key.code == sf::Keyboard::L) {
            last.SetButton(0, true);
          }

          if (event.key.code == sf::Keyboard::A) {
            last.SetButton(1, true);
          }

          if (event.key.code == sf::Keyboard::S) {
            last.SetButton(2, true);
          }

          if (event.key.code == sf::Keyboard::T) {
            last.SetButton(3, true);
          }

          if (event.key.code == sf::Keyboard::Space) {
            game.Fire();
          }

          if (event.key.code == sf::Keyboard::E) {
            game.TakeTransport();
          }

          if (event.key.code == sf::Keyboard::Escape) {
            music.StopBackgroundGameMusic();

            window.setView(menuView);

            if (!gameMenu(window, game.GetPlayer().GetMainData())) {
              isRepeat = false;
              isBreak = true;
              break;
            }

            music.PlayBackgroundGameMusic();
          }
        }

        if (event.type == sf::Event::KeyReleased) {
          if (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::Left) {
            game.GetPlayer().SetKey("L", false);
          }

          if (event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right) {
            game.GetPlayer().SetKey("R", false);
          }

          if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up) {
            game.GetPlayer().SetKey("UP", false);
          }

          if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down) {
            game.GetPlayer().SetKey("DOWN", false);
          }

          if (event.key.code == sf::Keyboard::N) {
            next.SetButton(0, false);
          }

          if (event.key.code == sf::Keyboard::E) {
            next.SetButton(1, false);
          }

          if (event.key.code == sf::Keyboard::X) {
            next.SetButton(2, false);
          }

          if (event.key.code == sf::Keyboard::T) {
            next.SetButton(3, false);
          }

          if (event.key.code == sf::Keyboard::L) {
            last.SetButton(0, false);
          }

          if (event.key.code == sf::Keyboard::A) {
            last.SetButton(1, false);
          }

          if (event.key.code == sf::Keyboard::S) {
            last.SetButton(2, false);
          }

          if (event.key.code == sf::Keyboard::T) {
            last.SetButton(3, false);
          }
        }
      }

      if (isBreak) {
        break;
      }

      if (game.GetPlayer().GetHp() <= 0) {
        music.StopBackgroundGameMusic();
        music.StopAllMusic();
        music.PlayDiedPlayerSound();

        window.setView(menuView);

        isRepeat = diedMenu(window);
        break;
      }

      if (game.GetPlayer().GetFinish()) {
        music.StopBackgroundGameMusic();

        window.setView(menuView);

        if (save.CheckEndGame()) {
          save.SetEndGame();
          isRepeat = winMenu(window, false);

        } else {
          save.NextLvl();
          isRepeat = nextLvlMenu(window);
        }

        save.SaveGame(game.GetPlayer().GetPoints());
        break;
      }

      if (next.isPressed()) {
        if (save.CheckEndGame()) {
          save.SetEndGame();
          isRepeat = false;
          window.setView(menuView);
          music.StopBackgroundGameMusic();
          music.PlayBackgroundMenuMusic();
        } else {
          save.NextLvl();
        }

        save.SaveGame(game.GetPlayer().GetPoints());
        break;
      }

      if (last.isPressed()) {
        save.LastLvl();

        if (save.GetLvl() == 0) {
          isRepeat = false;
          window.setView(menuView);
          music.StopBackgroundGameMusic();
          music.PlayBackgroundMenuMusic();
        }

        save.SaveGame(game.GetPlayer().GetPoints());
        break;
      }

      float time = clock.getElapsedTime().asMicroseconds();
      clock.restart();
      time = time / 400;
      if (time > 70) {
        time = 70;
      }

      game.Update(time);
      auto playerPosition = calculatePlayerPosition(gameWidth, gameHeight,
                                                    left, right, top, bottom,
                                                    game.GetPlayer().GetRect().left, game.GetPlayer().GetRect().top);

      window.clear(sf::Color(0, 0, 0));
      lvl.Draw(window, gameHeight, gameWidth, playerPosition.x, playerPosition.y);
      game.Draw(window, playerPosition.x, playerPosition.y, gameWidth, gameHeight);
      gameView.setCenter(playerPosition.x, playerPosition.y);
      window.setView(gameView);
      window.display();
    }

    Save::SaveStat(game.GetStat());
  }
}

// Предупреждение о сбросе данных
bool Interface::endGameWarningMenu(sf::RenderWindow &window) {
  InterfaceTable endGameWarningTable;
  endGameWarningTable.SetCenterLabel(std::make_shared<InterfaceButton>(textFontPath,
                                                                       textSize,
                                                                       "Are you sure you want to end game?"));
  endGameWarningTable.SetCenterLabel(std::make_shared<InterfaceButton>(textFontPath,
                                                                       textSize,
                                                                       "All your progress will be lost"));
  endGameWarningTable.SetLeftButton(std::make_shared<InterfaceButton>(buttonFontPath, buttonSize, "Yes"));
  endGameWarningTable.SetRightButton(std::make_shared<InterfaceButton>(buttonFontPath, buttonSize, "No"));

  endGameWarningTable.CalculateTablePosition();
  endGameWarningTable.SetPosition(height, width);

  while (window.isOpen()) {
    sf::Event event{};
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    sf::Vector2i mousePosition = sf::Vector2i(sf::Mouse::getPosition(window));

    if (endGameWarningTable.GetLeftButtons()[0]->IsSelect(mousePosition, music)) {
      return false;
    }

    if (endGameWarningTable.GetRightButtons()[0]->IsSelect(mousePosition, music)) {
      return true;
    }

    window.clear(sf::Color(68, 101, 219));
    endGameWarningTable.Draw(window);
    window.display();
  }

  return true;
}

bool Interface::winMenu(sf::RenderWindow &window, bool isLoadFromMenu) {
  if (!isLoadFromMenu) {
    music.PlayBackgroundMenuMusic();
  }

  InterfaceTable winTable;
  winTable.SetCenterLabel(std::make_shared<InterfaceLabel>(textFontPath, headSize, "Congratulations!"));
  winTable.SetCenterLabel(std::make_shared<InterfaceLabel>(textFontPath,
                                                           textSize,
                                                           "You have collected all the vaccines and were able to"));
  winTable.SetCenterLabel(std::make_shared<InterfaceLabel>(textFontPath,
                                                           textSize,
                                                           "save the world from the fucking coronavirus"));
  winTable.SetCenterButton(std::make_shared<InterfaceButton>(buttonFontPath, buttonSize, "Menu"));

  winTable.CalculateTablePosition();
  winTable.SetPosition(height, width);

  while (window.isOpen()) {
    sf::Event event{};
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    auto mousePosition = sf::Vector2i(sf::Mouse::getPosition(window));

    if (winTable.GetCenterButtons()[0]->IsSelect(mousePosition, music)) {
      if (!isLoadFromMenu) {
        music.StopBackgroundMenuMusic();
      }

      return false;;
    }

    window.clear(sf::Color(68, 101, 219));
    winTable.Draw(window);
    window.display();
  }

  return false;
}

bool Interface::nextLvlMenu(sf::RenderWindow &window) {
  music.PlayBackgroundMenuMusic();

  InterfaceTable nextMissionTable;
  nextMissionTable.SetCenterLabel(std::make_shared<InterfaceLabel>(textFontPath, headSize, "Mission completed"));
  nextMissionTable.SetCenterButton(std::make_shared<InterfaceButton>(buttonFontPath, buttonSize, "Next mission"));
  nextMissionTable.SetCenterButton(std::make_shared<InterfaceButton>(buttonFontPath, buttonSize, "Menu"));

  nextMissionTable.CalculateTablePosition();
  nextMissionTable.SetPosition(height, width);

  while (window.isOpen()) {
    sf::Event event{};
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    sf::Vector2i mousePosition = sf::Vector2i(sf::Mouse::getPosition(window));

    if (nextMissionTable.GetCenterButtons()[0]->IsSelect(mousePosition, music)) {
      music.StopBackgroundMenuMusic();
      return true;
    }

    if (nextMissionTable.GetCenterButtons()[1]->IsSelect(mousePosition, music)) {
      return false;
    }

    window.clear(sf::Color(68, 101, 219));
    nextMissionTable.Draw(window);
    window.display();
  }

  return false;
}

// Экран смерти
bool Interface::diedMenu(sf::RenderWindow &window) {
  music.PlayBackgroundMenuMusic();

  InterfaceTable diedTable;
  diedTable.SetCenterLabel(std::make_shared<InterfaceLabel>(textFontPath, headSize, "Mission failed"));
  diedTable.SetCenterButton(std::make_shared<InterfaceButton>(buttonFontPath, buttonSize, "Restart"));
  diedTable.SetCenterButton(std::make_shared<InterfaceButton>(buttonFontPath, buttonSize, "Menu"));

  diedTable.CalculateTablePosition();
  diedTable.SetPosition(height, width);

  while (window.isOpen()) {
    sf::Event event{};
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    sf::Vector2i mousePosition = sf::Vector2i(sf::Mouse::getPosition(window));

    if (diedTable.GetCenterButtons()[0]->IsSelect(mousePosition, music)) {
      music.StopBackgroundMenuMusic();
      return true;
    }

    if (diedTable.GetCenterButtons()[1]->IsSelect(mousePosition, music)) {
      return false;
    }

    window.clear(sf::Color(68, 101, 219));
    diedTable.Draw(window);
    window.display();
  }

  return false;
}

void Interface::statisticMenu(sf::RenderWindow &window) {
  InterfaceLabel statisticHeadText(textFontPath, headSize, "Statistic menu");
  statisticHeadText.SetPosition((width - statisticHeadText.GetTextRectSize().x) / 2, headSize);

  InterfaceTable statisticTable;
  std::vector<int> stat = Save::LoadStat();

  std::ostringstream ssPatient;
  ssPatient << "Player win time: " << stat[0];
  statisticTable.SetLeftLabel(std::make_shared<InterfaceLabel>(textFontPath, textSize, ssPatient.str()));

  std::ostringstream ssDied;
  ssDied << "Player lose time: " << stat[1];
  statisticTable.SetRightLabel(std::make_shared<InterfaceLabel>(textFontPath, textSize, ssDied.str()));

  std::ostringstream ssVaccine;
  ssVaccine << "Vaccine collected: " << stat[2];
  statisticTable.SetLeftLabel(std::make_shared<InterfaceLabel>(textFontPath, textSize, ssVaccine.str()));

  std::ostringstream ssAntigen;
  ssAntigen << "Antigen collected: " << stat[3];
  statisticTable.SetRightLabel(std::make_shared<InterfaceLabel>(textFontPath, textSize, ssAntigen.str()));

  std::ostringstream ssPolice;
  ssPolice << "Police cured: " << stat[4];
  statisticTable.SetLeftLabel(std::make_shared<InterfaceLabel>(textFontPath, textSize, ssPolice.str()));

  std::ostringstream ssBreaker;
  ssBreaker << "Breaker cured: " << stat[5];
  statisticTable.SetRightLabel(std::make_shared<InterfaceLabel>(textFontPath, textSize, ssBreaker.str()));

  std::ostringstream ssDelivery;
  ssDelivery << "Delivery cured: " << stat[6];
  statisticTable.SetLeftLabel(std::make_shared<InterfaceLabel>(textFontPath, textSize, ssDelivery.str()));

  std::ostringstream ssVirus;
  ssVirus << "Virus cured: " << stat[7];
  statisticTable.SetRightLabel(std::make_shared<InterfaceLabel>(textFontPath, textSize, ssVirus.str()));

  std::ostringstream ssAuto;
  ssAuto << "Ambulance trips: " << stat[8];
  statisticTable.SetLeftLabel(std::make_shared<InterfaceLabel>(textFontPath, textSize, ssAuto.str()));

  std::ostringstream ssMonorail;
  ssMonorail << "Monorail trips: " << stat[9];
  statisticTable.SetRightLabel(std::make_shared<InterfaceLabel>(textFontPath, textSize, ssMonorail.str()));

  std::ostringstream ssBus;
  ssBus << "Bus trips: " << stat[10];
  statisticTable.SetLeftLabel(std::make_shared<InterfaceLabel>(textFontPath, textSize, ssBus.str()));

  std::ostringstream ssMetro;
  ssMetro << "Metro trips: " << stat[11];
  statisticTable.SetRightLabel(std::make_shared<InterfaceLabel>(textFontPath, textSize, ssMetro.str()));

  std::ostringstream ssPenalty;
  ssPenalty << "Police penalty time: " << stat[12];
  statisticTable.SetLeftLabel(std::make_shared<InterfaceLabel>(textFontPath, textSize, ssPenalty.str()));

  std::ostringstream ssCaught;
  ssCaught << "Police back time: " << stat[13];
  statisticTable.SetRightLabel(std::make_shared<InterfaceLabel>(textFontPath, textSize, ssCaught.str()));

  statisticTable.CalculateTablePosition();
  statisticTable.SetPosition(height, width);

  InterfaceButton backButton(buttonFontPath, buttonSize, 30, height - buttonSize - 30, "Back");

  while (window.isOpen()) {
    sf::Event event{};
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    auto mousePosition = sf::Vector2i(sf::Mouse::getPosition(window));

    if (backButton.IsSelect(mousePosition, music)) {
      break;
    }

    window.clear(sf::Color(68, 101, 219));
    statisticHeadText.Draw(window);
    statisticTable.Draw(window);
    backButton.Draw(window);
    window.display();
  }
}

void Interface::configMenu(sf::RenderWindow &window) {
  InterfaceLabel configurationHeadText(textFontPath, headSize, "Configuration menu");
  configurationHeadText.SetPosition((width - configurationHeadText.GetTextRectSize().x) / 2, headSize);

  InterfaceTable configurationTable;
  int lvl = Save::LoadLvl();
  int points = Save::LoadPoints();
  std::vector<int> armors = Save::LoadArmors();
  std::vector<int> config = Save::LoadConfig();

  std::ostringstream ssCurrentLvl;
  ssCurrentLvl << "Current lvl: " << lvl;
  configurationTable.SetLeftLabel(std::make_shared<InterfaceLabel>(textFontPath, textSize, ssCurrentLvl.str()));

  std::ostringstream ssPlayerHp;
  ssPlayerHp << "Player hp: " << config[0];
  configurationTable.SetRightLabel(std::make_shared<InterfaceLabel>(textFontPath, textSize, ssPlayerHp.str()));

  std::ostringstream ssCurrentPoints;
  ssCurrentPoints << "Current points: " << points;
  configurationTable.SetLeftLabel(std::make_shared<InterfaceLabel>(textFontPath, textSize, ssCurrentPoints.str()));

  std::ostringstream ssAntigenPoints;
  ssAntigenPoints << "Antigen Points: " << config[1];
  configurationTable.SetRightLabel(std::make_shared<InterfaceLabel>(textFontPath, textSize, ssAntigenPoints.str()));

  std::ostringstream ssCapLvl;
  ssCapLvl << "Cap lvl: " << armors[0];
  configurationTable.SetLeftLabel(std::make_shared<InterfaceLabel>(textFontPath, textSize, ssCapLvl.str()));

  std::ostringstream ssShoesLvl;
  ssShoesLvl << "Shoes lvl: " << armors[1];
  configurationTable.SetRightLabel(std::make_shared<InterfaceLabel>(textFontPath, textSize, ssShoesLvl.str()));

  std::ostringstream ssRobeLvl;
  ssRobeLvl << "Robe lvl: " << armors[2];
  configurationTable.SetLeftLabel(std::make_shared<InterfaceLabel>(textFontPath, textSize, ssRobeLvl.str()));

  std::ostringstream ssPoliceHp;
  ssPoliceHp << "Police hp: " << config[2];
  configurationTable.SetRightLabel(std::make_shared<InterfaceLabel>(textFontPath, textSize, ssPoliceHp.str()));

  std::ostringstream ssPoliceDmg;
  ssPoliceDmg << "Police dmg: " << config[3];
  configurationTable.SetLeftLabel(std::make_shared<InterfaceLabel>(textFontPath, textSize, ssPoliceDmg.str()));

  std::ostringstream ssPolicePenalty;
  ssPolicePenalty << "Police penalty: " << config[4];
  configurationTable.SetRightLabel(std::make_shared<InterfaceLabel>(textFontPath, textSize, ssPolicePenalty.str()));

  std::ostringstream ssBreakerHp;
  ssBreakerHp << "Breaker hp: " << config[5];
  configurationTable.SetLeftLabel(std::make_shared<InterfaceLabel>(textFontPath, textSize, ssBreakerHp.str()));

  std::ostringstream ssBreakerDmg;
  ssBreakerDmg << "Breaker dmg: " << config[6];
  configurationTable.SetRightLabel(std::make_shared<InterfaceLabel>(textFontPath, textSize, ssBreakerDmg.str()));

  std::ostringstream ssDeliveryHp;
  ssDeliveryHp << "Delivery hp: " << config[7];
  configurationTable.SetLeftLabel(std::make_shared<InterfaceLabel>(textFontPath, textSize, ssDeliveryHp.str()));

  std::ostringstream ssDeliveryDmg;
  ssDeliveryDmg << "Delivery dmg: " << config[8];
  configurationTable.SetRightLabel(std::make_shared<InterfaceLabel>(textFontPath, textSize, ssDeliveryDmg.str()));

  std::ostringstream ssVirusHp;
  ssVirusHp << "Virus hp: " << config[9];
  configurationTable.SetLeftLabel(std::make_shared<InterfaceLabel>(textFontPath, textSize, ssVirusHp.str()));

  std::ostringstream ssVirusDmg;
  ssVirusDmg << "Virus dmg: " << config[10];
  configurationTable.SetRightLabel(std::make_shared<InterfaceLabel>(textFontPath, textSize, ssVirusDmg.str()));

  std::ostringstream ssAutoFuel;
  ssAutoFuel << "Ambulance fuel: " << config[11];
  configurationTable.SetLeftLabel(std::make_shared<InterfaceLabel>(textFontPath, textSize, ssAutoFuel.str()));

  std::ostringstream ssMonorailFuel;
  ssMonorailFuel << "Monorail fuel: " << config[12];
  configurationTable.SetRightLabel(std::make_shared<InterfaceLabel>(textFontPath, textSize, ssMonorailFuel.str()));

  std::ostringstream ssBusDmg;
  ssBusDmg << "Bus dmg: " << config[13];
  configurationTable.SetLeftLabel(std::make_shared<InterfaceLabel>(textFontPath, textSize, ssBusDmg.str()));

  std::ostringstream ssMetroDmg;
  ssMetroDmg << "Metro dmg: " << config[14];
  configurationTable.SetRightLabel(std::make_shared<InterfaceLabel>(textFontPath, textSize, ssMetroDmg.str()));

  configurationTable.CalculateTablePosition();
  configurationTable.SetPosition(height, width);

  InterfaceButton backButton(buttonFontPath, buttonSize, 30, height - buttonSize - 30, "Back");
  InterfaceButton defaultButton(buttonFontPath, buttonSize, "Default");
  defaultButton.SetPosition(width - defaultButton.GetTextRectSize().x - 30, height - buttonSize - 30);

  while (window.isOpen()) {
    sf::Event event{};
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    sf::Vector2i mousePosition = sf::Vector2i(sf::Mouse::getPosition(window));

    if (backButton.IsSelect(mousePosition, music)) {
      break;
    }

    if (defaultButton.IsSelect(mousePosition, music)) {
      Save::RemoveConfig();
    }

    window.clear(sf::Color(68, 101, 219));
    configurationHeadText.Draw(window);
    configurationTable.Draw(window);
    backButton.Draw(window);
    defaultButton.Draw(window);
    window.display();
  }
}

bool Interface::shopMenu(sf::RenderWindow &window) {
  InterfaceButton backButton(buttonFontPath, buttonSize, 30, height - buttonSize - 30, "Back");

  InterfaceImage armorListSprite(resourcePath() + "files/menu/armor_list.png",
                                 width / 2 - (width / 1.6) / 2, height / 2 - (width / 1.9) / 2,
                                 width / 1.6, width / 1.9);

  InterfaceImage armorShoesSprite(resourcePath() + "files/menu/armors.png",
                                  width / 1.57, height / 14,
                                  width / 1.0, width / 1.7);

  InterfaceImage armorCapSprite(resourcePath() + "files/menu/armors.png",
                                width / 4.9, height / 6,
                                width / 1.3, width / 2);

  InterfaceImage armorRobeSprite(resourcePath() + "files/menu/armors.png",
                                 width / 2.32, height / 1.45,
                                 width / 1.3, width / 2.2);

  InterfaceImage buyShoesSprite(resourcePath() + "files/menu/upgrade.png",
                                width / 1.215, height / 7,
                                width / 15, width / 15);

  InterfaceImage buyCapSprite(resourcePath() + "files/menu/upgrade.png",
                              width / 10, height / 7,
                              width / 15, width / 15);

  InterfaceImage buyRobeSprite(resourcePath() + "files/menu/upgrade.png",
                               width / 1.67, height / 1.4,
                               width / 15, width / 15);

  InterfaceLabel lvlShoesText(textFontPath, textSize, width / 1.42, height / 3.5);
  InterfaceLabel lvlCapText(textFontPath, textSize, width / 4.0, height / 3.5);
  InterfaceLabel lvlRobeText(textFontPath, textSize, width / 2.10, height / 1.18);
  InterfaceLabel costShoesText(textFontPath, textSize, width / 1.19, height / 4);
  InterfaceLabel costCapText(textFontPath, textSize, width / 8.6, height / 4);
  InterfaceLabel costRobeText(textFontPath, textSize, width / 1.62, height / 1.22);

  std::ostringstream ssPoints;
  int money = Save::LoadPoints();
  ssPoints << "Points: " << money;
  InterfaceLabel pointsLabel(textFontPath, textSize, ssPoints.str());
  pointsLabel.SetPosition(width - pointsLabel.GetTextRectSize().x - 30, 13);

  std::vector<int> arm_vector = Save::LoadArmors();
  std::ostringstream ssArm;
  ssArm << "ARM: " << arm_vector[0] + arm_vector[1] + arm_vector[2];
  InterfaceLabel armText(textFontPath, textSize, 30, 13, ssArm.str());

  setArmLvl(arm_vector, lvlCapText, 0);
  setArmLvl(arm_vector, lvlShoesText, 1);
  setArmLvl(arm_vector, lvlRobeText, 2);

  setPrice(arm_vector, costCapText, 0);
  setPrice(arm_vector, costShoesText, 1);
  setPrice(arm_vector, costRobeText, 2);

  armorCapSprite.SetTextureRect(sf::Rect<int>(204 * arm_vector[0], 41, 196, 85));
  armorShoesSprite.SetTextureRect(sf::Rect<int>(204 * arm_vector[1], 352, 196, 169));
  armorRobeSprite.SetTextureRect(sf::Rect<int>(204 * arm_vector[2], 200, 195, 165));

  while (window.isOpen()) {
    buyShoesSprite.SetColor(sf::Color::White);
    buyCapSprite.SetColor(sf::Color::White);
    buyRobeSprite.SetColor(sf::Color::White);

    int menuNum = -1;

    if (sf::IntRect(buyCapSprite.GetSpriteRect().x,
                    buyCapSprite.GetSpriteRect().y,
                    buyCapSprite.GetSize().x,
                    buyCapSprite.GetSize().y).
        contains(sf::Mouse::getPosition(window))) {
      buyCapSprite.SetColor(sf::Color::Black);
      menuNum = 0;
    }

    if (sf::IntRect(buyShoesSprite.GetSpriteRect().x,
                    buyShoesSprite.GetSpriteRect().y,
                    buyShoesSprite.GetSize().x,
                    buyShoesSprite.GetSize().y).
        contains(sf::Mouse::getPosition(window))) {
      buyShoesSprite.SetColor(sf::Color::Black);
      menuNum = 1;
    }
    if (sf::IntRect(buyRobeSprite.GetSpriteRect().x,
                    buyRobeSprite.GetSpriteRect().y,
                    buyRobeSprite.GetSize().x,
                    buyRobeSprite.GetSize().y).
        contains(sf::Mouse::getPosition(window))) {
      buyRobeSprite.SetColor(sf::Color::Black);
      menuNum = 2;
    }

    auto mousePosition = sf::Vector2i(sf::Mouse::getPosition(window));

    if (backButton.IsSelect(mousePosition, music)) {
      break;
    }

    sf::Event event{};
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
      if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
          if (menuNum == 0 || menuNum == 1 || menuNum == 2) {
            if (arm_vector[menuNum] < 4) {
              int cost = arm_vector[menuNum] * 200 + 200;
              if (cost <= money) {
                buy(arm_vector, menuNum);
                Save::SavePoints(money - cost);
                ssPoints.str("");
                money = Save::LoadPoints();
                ssPoints << "Points: " << money;
                pointsLabel.SetText(ssPoints.str());
                arm_vector = Save::LoadArmors();
                ssArm.str("");
                ssArm << "ARM: " << arm_vector[0] + arm_vector[1] + arm_vector[2];
                armText.SetText(ssArm.str());
                armText.SetPosition(+30, +13);
                setArmLvl(arm_vector, lvlCapText, 0);
                setArmLvl(arm_vector, lvlShoesText, 1);
                setArmLvl(arm_vector, lvlRobeText, 2);
                setPrice(arm_vector, costCapText, 0);
                setPrice(arm_vector, costShoesText, 1);
                setPrice(arm_vector, costRobeText, 2);
                armorCapSprite.SetTextureRect(sf::Rect<int>(204 * arm_vector[0], 41, 196, 85));
                armorShoesSprite.SetTextureRect(sf::Rect<int>(204 * arm_vector[1], 352, 196, 169));
                armorRobeSprite.SetTextureRect(sf::Rect<int>(204 * arm_vector[2], 200, 195, 165));
              }
            }
          }
        }
      }
    }

    window.clear(sf::Color(68, 101, 219));

    armorListSprite.Draw(window);
    armorShoesSprite.Draw(window);
    armorCapSprite.Draw(window);
    armorRobeSprite.Draw(window);
    buyShoesSprite.Draw(window);
    buyCapSprite.Draw(window);
    buyRobeSprite.Draw(window);

    backButton.Draw(window);

    pointsLabel.Draw(window);
    armText.Draw(window);
    lvlShoesText.Draw(window);
    lvlCapText.Draw(window);
    lvlRobeText.Draw(window);
    costShoesText.Draw(window);
    costCapText.Draw(window);
    costRobeText.Draw(window);

    window.display();
  }

  return true;
}

bool Interface::gameMenu(sf::RenderWindow &window, std::vector<int> data) {
  music.PlayBackgroundMenuMusic();

  InterfaceButton continueButton(buttonFontPath, buttonSize, 30, height - buttonSize - 30, "Continue");
  InterfaceButton menuButton(buttonFontPath, buttonSize, "Menu");
  menuButton.SetPosition(width - menuButton.GetTextRectSize().x - 30, height - menuButton.GetTextRectSize().y - 30);

  InterfaceImage armorListImage(resourcePath() + "files/menu/armor_list.png",
                                width / 2 - (width / 1.6) / 2, height / 2 - (width / 1.9) / 2,
                                width / 1.6, width / 1.9);

  InterfaceImage armorCapImage(resourcePath() + "files/menu/armors.png",
                               width / 4.9, height / 6,
                               width / 1.3, width / 2);

  InterfaceImage armorShoesImage(resourcePath() + "files/menu/armors.png",
                                 width / 1.57, height / 14,
                                 width / 1.0, width / 1.7);

  InterfaceImage armorRobeImage(resourcePath() + "files/menu/armors.png",
                                width / 2.32, height / 1.45,
                                width / 1.3, width / 2.2);

  armorShoesImage.SetTextureRect(sf::Rect<int>(204 * data[3], 352, 196, 169));
  armorCapImage.SetTextureRect(sf::Rect<int>(204 * data[4], 41, 196, 85));
  armorRobeImage.SetTextureRect(sf::Rect<int>(204 * data[5], 200, 195, 165));

  std::ostringstream ssData;
  ssData << "HP: " << data[0] << "%" << " ARM: " << data[2] << " Vaccine: " << data[6];
  InterfaceLabel playerDataLabel(textFontPath, textSize, 20, 20, ssData.str());

  std::ostringstream ssPoints;
  ssPoints << "Points: " << data[1];
  InterfaceLabel pointsLabel(textFontPath, textSize, ssPoints.str());
  pointsLabel.SetPosition(width - pointsLabel.GetTextRectSize().x - 20, 20);

  std::ostringstream ssShoes;
  ssShoes << "LVL:" << data[3];
  InterfaceLabel lvlShoesLabel(textFontPath, textSize, width / 1.46, height / 3.5, ssShoes.str());

  std::ostringstream ssCap;
  ssCap << "LVL:" << data[4];
  InterfaceLabel lvlCapLabel(textFontPath, textSize, width / 4.2, height / 3.5, ssCap.str());

  std::ostringstream ssRobe;
  ssRobe << "LVL:" << data[5];
  InterfaceLabel lvlRobeLabel(textFontPath, textSize, width / 2.15, height / 1.18, ssRobe.str());

  while (window.isOpen()) {
    sf::Event event{};
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }

      if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) {
          music.StopBackgroundMenuMusic();
          return true;
        }
      }
    }

    sf::Vector2i mousePosition = sf::Vector2i(sf::Mouse::getPosition(window));

    if (menuButton.IsSelect(mousePosition, music)) {
      return endGameWarningMenu(window);
    }

    if (continueButton.IsSelect(mousePosition, music)) {
      music.StopBackgroundMenuMusic();
      return true;
    }

    window.clear(sf::Color(68, 101, 219));

    menuButton.Draw(window);
    continueButton.Draw(window);

    armorListImage.Draw(window);
    armorShoesImage.Draw(window);
    armorCapImage.Draw(window);
    armorRobeImage.Draw(window);

    playerDataLabel.Draw(window);
    pointsLabel.Draw(window);
    lvlCapLabel.Draw(window);
    lvlShoesLabel.Draw(window);
    lvlRobeLabel.Draw(window);

    window.display();
  }

  return true;
}

void Interface::aboutMenu(sf::RenderWindow &window) {
  InterfaceLabel aboutGameHead(textFontPath, headSize, "About game");
  aboutGameHead.SetPosition((width - aboutGameHead.GetTextRectSize().x) / 2, headSize);

  InterfaceTable aboutTable;
  aboutTable.SetCenterLabel(std::make_shared<InterfaceLabel>(textFontPath, textSize, "This game was developed by"));
  aboutTable.SetCenterLabel(std::make_shared<InterfaceLabel>(textFontPath,
                                                             textSize,
                                                             "Alekhin Sergey, Gorshkov Ivan, Kalinin Ilya"));
  aboutTable.SetLeftLabel(std::make_shared<InterfaceLabel>(textFontPath, textSize, "Sound expert:"));
  aboutTable.SetRightLabel(std::make_shared<InterfaceLabel>(textFontPath, textSize, "Akhverdiev Valery"));
  aboutTable.SetLeftLabel(std::make_shared<InterfaceLabel>(textFontPath, textSize, "Designer:"));
  aboutTable.SetRightLabel(std::make_shared<InterfaceLabel>(textFontPath, textSize, "Fedor Surovtsev"));
  aboutTable.SetLeftLabel(std::make_shared<InterfaceLabel>(textFontPath, textSize, "Assistance:"));
  aboutTable.SetRightLabel(std::make_shared<InterfaceLabel>(textFontPath, textSize, "Poznyak Anastasia"));

  aboutTable.CalculateTablePosition();
  aboutTable.SetPosition(height, width);

  InterfaceLabel gameData(textFontPath, textSize, "August 2020 version: 1.0");
  gameData.SetPosition((width - gameData.GetTextRectSize().x) / 2, height - textSize - 30);

  InterfaceButton backButton(buttonFontPath, buttonSize, 30, height - buttonSize - 30, "Back");

  while (window.isOpen()) {
    sf::Event event{};
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    auto mousePosition = sf::Vector2i(sf::Mouse::getPosition(window));

    if (backButton.IsSelect(mousePosition, music)) {
      break;
    }

    window.clear(sf::Color(68, 101, 219));
    aboutGameHead.Draw(window);
    aboutTable.Draw(window);
    gameData.Draw(window);
    backButton.Draw(window);
    window.display();
  }
}
