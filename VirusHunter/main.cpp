#include "Interface.h"
#include "SaveGame.h"

int main() {
  sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "VirusHunter", sf::Style::Fullscreen);
  window.setFramerateLimit(120);
  window.setVerticalSyncEnabled(true);
  Interface& interface = Interface::GetInstance(window);
  interface.MainMenu(window);
  return 0;
} 
