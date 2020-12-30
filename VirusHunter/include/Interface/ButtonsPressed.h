#pragma once

#include <vector>

class ButtonsPressed {
public:
    ButtonsPressed(int buttonsCount);
    void SetButton(int num, bool value);
    bool isPressed();
    
private:
    std::vector<bool> button;
};
