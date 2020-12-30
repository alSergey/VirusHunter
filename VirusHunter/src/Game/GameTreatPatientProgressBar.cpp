#include "GameTreatPatientProgressBar.h"

GameTreatPatientProgressBar::GameTreatPatientProgressBar()
    : status(0) {
  bar.setOutlineThickness(1);
  bar.setOutlineColor(sf::Color::Black);
  bar.setFillColor(sf::Color::Transparent);
  progress.setFillColor(sf::Color::White);
}

void GameTreatPatientProgressBar::Draw(sf::RenderWindow &window, bool isDraw) {
  if (isDraw) {
    float progressHeight = window.getView().getSize().y / 50;
    float progressWidth = window.getView().getSize().x / 5;

    sf::Vector2f center = window.getView().getCenter();
    sf::Vector2f size = window.getView().getSize();

    float xPosition = center.x - size.x / 2;
    float yPosition = center.y - size.y / 2;

    if (isDraw) {
      status += progressWidth / TREAT_TIME;
      if (status >= progressWidth) {
        status = progressWidth;
      }
    }

    progress.setPosition(xPosition + (window.getView().getSize().x - progressWidth) / 2,
                         yPosition + 20 + window.getView().getSize().y / 70);
    bar.setPosition(xPosition + (window.getView().getSize().x - progressWidth) / 2,
                    yPosition + 20 + window.getView().getSize().y / 70);
    progress.setSize(sf::Vector2f(status, progressHeight));
    bar.setSize(sf::Vector2f(progressWidth, progressHeight));

    window.draw(progress);
    window.draw(bar);
  } else {
    status = 0;
  }
}
