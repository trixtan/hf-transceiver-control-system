#include "SetFrequencyUIView.h"
#include "IdleUIView.h"

bool SetFrequencyUIView::storeFrequencyDigit(Key &k) {
  if(!isdigit(k.kchar)) return false; //Ignore non digit keys

  //Check if the digit is valid by testing if the new frequency would be legal.
  unsigned int nextFreqWithThisKey = getNextFrequencyHz(std::optional(k));
  for(const Band& band: this->settingsState->supportedBands) {
    if(band.frequencyInBand(nextFreqWithThisKey, Band::getFrequencyUnitFromTenExponent(MAX_TEN_EXP_FOR_FREQUENCY-this->nextFrequencyKeyPos))) {
      this->nextFrequencyKeys[this->nextFrequencyKeyPos++] = k.kchar;
      return true;
    } 
  }
  return false;
}

unsigned long SetFrequencyUIView::getFrequencyInHz(void) const {
    return this->getNextFrequencyHz();
}

int SetFrequencyUIView::onKeyPressed(Key &k) {
    if(isdigit(k.kchar))
      storeFrequencyDigit(k);
    else if(k.kchar=='A') {
      //Accept frequency if is valid.
      if(getNextBand().has_value()) {
        this->settingsState->setCurrentFrequencyRxHz(getNextFrequencyHz());
        this->settingsState->setCurrentFrequencyTxHz(getNextFrequencyHz());
        this->resetNextFrequency();
        return IdleUIView::ID;
      }
    }
    else if(k.kchar=='D') {
      //Discard everything and go back
      this->resetNextFrequency();
      return IdleUIView::ID;
    }
    return this->getId();
};

void SetFrequencyUIView::printBands(void) {
  this->hiddenBands.pushSprite(BANDS_POSITION_X, BANDS_POSITION_Y);
};

void SetFrequencyUIView::printFrequency(void) {
    bool show = this->blink;

    if(!show) {
        clearFrequency();
        return;
    }

    FrequencyUIView::printFrequency();
}