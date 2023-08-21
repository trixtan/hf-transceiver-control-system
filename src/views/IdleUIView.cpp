#include "IdleUIView.h"
#include "SetFrequencyUIView.h"

bool IdleUIView::storeFrequencyDigit(Key &k) {
  if(!isdigit(k.kchar)) return false; //Ignore non digit keys

  if(this->nextFrequencyKeyPos == 0) {
    switch(k.kchar) {  
      case '0':
        //We are at the very beginning. There is only one band which can accept 0 as the first position.
        //We are in the 40 meters band,the only valid next value is 7, we can add it
        this->nextFrequencyKeys[this->nextFrequencyKeyPos++] = k.kchar;
        this->nextFrequencyKeys[this->nextFrequencyKeyPos++] = '7';
        return true;
      case '1':
      case '2':
        this->nextFrequencyKeys[this->nextFrequencyKeyPos++] = k.kchar;
        return true;
      case '7':
        //Let's assume the user wants to enter the 40 meters without digiting the first 0.
        this->nextFrequencyKeys[this->nextFrequencyKeyPos++] = '0';
        this->nextFrequencyKeys[this->nextFrequencyKeyPos++] = k.kchar;
        return true;
      default:
        //All other digits are invalid at this point
        return false;
    }
  }
  return false;
}

unsigned long IdleUIView::getFrequencyInHz(void) const {
    return this->settingsState->getCurrentFrequencyRxHz();  
}

int IdleUIView::onKeyPressed(Key &k) {
    if(isdigit(k.kchar) && storeFrequencyDigit(k))
        return SetFrequencyUIView::ID;
    return this->getId();
};