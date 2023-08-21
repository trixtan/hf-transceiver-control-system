#include "UIView.h"

int UIView::update(void) {
    int outcome = doInput();
    doOutput();
    return this->getId() != outcome ? outcome : this->getId();
}

int UIView::doInput(void) {
    // Fills kpd.key[ ] array with up-to 10 active keys.
    // Returns true if there are ANY active keys.
    int outcome = -1;
    if (keypad.getKeys())
    {
        for (int i=0; i<LIST_MAX; i++)   // Scan the whole key list.
        {
            if ( keypad.key[i].stateChanged )   // Only find keys that have changed state.
            {
                switch (keypad.key[i].kstate) {  // Report active key state : IDLE, PRESSED, HOLD, or RELEASED
                case PRESSED:
                    outcome = this->onKeyPressed(keypad.key[i]);
                    if(outcome != this->getId()) {
                        //Move to the next view
                        return outcome;
                    }
                    break;
                case HOLD:
                case RELEASED:
                case IDLE:
                  break;
                }
            }
        }
    }
    return this->getId(); //Stay in this view;
};
