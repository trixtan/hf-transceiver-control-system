#include "SettingsState.h"


    unsigned long SettingsState::getCurrentFrequencyRxHz() const {
        return this->curFrequencyRxHz;
    }

    unsigned long SettingsState::getCurrentFrequencyTxHz() const {
        return this->curFrequencyTxHz;
    }

    void SettingsState::setCurrentFrequencyRxHz(unsigned long freqInHz) {
        this->curFrequencyRxHz = freqInHz;
    }

    void SettingsState::setCurrentFrequencyTxHz(unsigned long freqInHz) {
        this->curFrequencyTxHz = freqInHz;
    }