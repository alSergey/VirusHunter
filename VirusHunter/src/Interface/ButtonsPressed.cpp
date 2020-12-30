#include "ButtonsPressed.h"

ButtonsPressed::ButtonsPressed(int buttonsCount)
: button(buttonsCount) {
}

void ButtonsPressed::SetButton(int num, bool value) {
    button[num] = value;
}

bool ButtonsPressed::isPressed() {
    for (int i = 0; i < button.size(); i++) {
        if (!button[i]) {
            return false;
        }
    }
    
    for (int i = 0; i < button.size(); i++) {
        button[i] = false;
    }
    
    return true;
}
