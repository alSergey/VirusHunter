#include "GameLabelManager.h"

void GameLabelManager::SetLabel(const std::string &mapStr,
                                const std::shared_ptr<GameLabel> &label,
                                PositionSettings labelPosition) {
  gameLabel.insert(make_pair(mapStr, label));
  labelPositionSettings.insert(make_pair(mapStr, labelPosition));
}

void GameLabelManager::SetText(const std::string &mapStr, const std::string &getStr) {
  gameLabel[mapStr]->SetText(getStr);
}

void GameLabelManager::Draw(const std::string &mapStr, sf::RenderWindow &window) {
  int height = window.getView().getSize().y;
  int width = window.getView().getSize().x;

  sf::Vector2f center = window.getView().getCenter();
  sf::Vector2f size = window.getView().getSize();

  float xPosition = center.x - size.x / 2;
  float yPosition = center.y - size.y / 2;

  auto pos = labelPositionSettings[mapStr];
  float x = 0;
  float y = 0;

  switch (pos) {
    case LEFT_UP: {
      x = SHIFT;
      y = SHIFT;
      break;
    }

    case CENTER_UP: {
      x = (width - gameLabel[mapStr]->GetTextRectSize().x) / 2;
      y = SHIFT;
      break;
    }

    case RIGHT_UP: {
      x = width - gameLabel[mapStr]->GetTextRectSize().x - SHIFT;
      y = SHIFT;
      break;
    }

    case LEFT_DOWN: {
      x = SHIFT;
      y = height - gameLabel[mapStr]->GetTextRectSize().y - SHIFT;
      break;
    }

    case RIGHT_DOWN: {
      x = width - gameLabel[mapStr]->GetTextRectSize().x - SHIFT;
      y = height - gameLabel[mapStr]->GetTextRectSize().y - SHIFT;
      break;
    }

    case PLAYER_POSITION:break;
    case CUSTOM_POSITION:break;
  }

  gameLabel[mapStr]->SetPosition(xPosition + x, yPosition + y);
  gameLabel[mapStr]->Draw(window);
}

void GameLabelManager::Draw(const std::string &mapStr, sf::RenderWindow &window, float x, float y) {
  if (labelPositionSettings[mapStr] == PLAYER_POSITION) {
    gameLabel[mapStr]->SetPosition(x + SHIFT * 3, y - SHIFT * 3);
    gameLabel[mapStr]->Draw(window);
  }

  if (labelPositionSettings[mapStr] == CUSTOM_POSITION) {
    gameLabel[mapStr]->SetPosition(x, y);
    gameLabel[mapStr]->Draw(window);
  }
}
