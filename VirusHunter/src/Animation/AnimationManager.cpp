#include "AnimationManager.h"

AnimationManager::AnimationManager(sf::Texture &texture)
    : texture(texture) {
}

AnimationManager::AnimationManager(const std::string &str) {
    texture.loadFromFile(str);
}

void AnimationManager::Create(const std::string &name, int x, int y, int w, int h, int count, float speed, int step) {
  animList[name] = Animation(texture, x, y, w, h, count, speed, step);
  currentAnim = name;
}

void AnimationManager::Draw(sf::RenderWindow &window, int x, int y) {
  animList[currentAnim].SetSpritePosition(x, y);
  window.draw(animList[currentAnim].GetSprite());
}

void AnimationManager::Set(const std::string &name) {
  currentAnim = name;
}

void AnimationManager::Flip(bool b) {
  animList[currentAnim].SetFlip(b);
}

void AnimationManager::Tick(float time) {
  animList[currentAnim].Tick(time);
}

void AnimationManager::Pause() {
  animList[currentAnim].SetPlay(false);
}

int AnimationManager::GetCurrentFrame() {
  return animList[currentAnim].GetCurrentFrame();
}
