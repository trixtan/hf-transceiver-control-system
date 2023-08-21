#include <Arduino.h>
#include <Keypad.h>
#include <ctype.h>
#include "InputManager.h"

void InputManager::setup(void) {
  this->idleUIView.setup();
  this->setFrequencyUIView.setup();
}

void InputManager::update(void) { 

  int outcome = currentView->update();
  switch(outcome) {
    case IdleUIView::ID:
      currentView = &idleUIView;
      break;
    case SetFrequencyUIView::ID:
      currentView = &setFrequencyUIView;
      break;
  }
}

/*
    DisplayView view;
    view.frequency(getFrequencyInHz());
    view.frequencyShow(true);

    switch(this->state) {
      case IDLE:
        view.frequencyBlink(false);
        view.frequencyPrintUpTo(HZ);
        view.bandShow(true);
        break;
      case SETTING_FREQUENCY:
        view.frequencyBlink(true);
        view.frequencyPrintUpTo(Band::getFrequencyUnitFromTenExponent(MAX_TEN_EXP_FOR_FREQUENCY-this->nextFrequencyKeyPos+1));
        view.bandShow(false);
    }
    
    
    std::optional<Band> currentBand = this->getBandForFrequency(view.frequency());
    if(currentBand.has_value())
      view.band(currentBand.value().getBandId());
    else
      view.band(NONE);

    this->displayManager.update(view);
*/


