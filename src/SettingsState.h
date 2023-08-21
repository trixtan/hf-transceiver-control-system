#ifndef SETTINGS_STATE_H
#define SETTINGS_STATE_H

#include <list>
#include "Band.h"


class SettingsState {

public:
    SettingsState(): curModulation(USB), curFrequencyRxHz(14200000), curFrequencyTxHz(14200000) {};
    
    const std::list<Band> supportedBands = {
        Band(M_40, M_40_MIN_FREQ, M_40_MAX_FREQ),
        Band(M_30, M_30_MIN_FREQ, M_30_MAX_FREQ),
        Band(M_20, M_20_MIN_FREQ, M_20_MAX_FREQ),
        Band(M_17, M_17_MIN_FREQ, M_17_MAX_FREQ),
        Band(M_15, M_15_MIN_FREQ, M_15_MAX_FREQ),
        Band(M_12, M_12_MIN_FREQ, M_12_MAX_FREQ),
        Band(M_10, M_10_MIN_FREQ, M_10_MAX_FREQ)
    };

    unsigned long getCurrentFrequencyRxHz() const;
    unsigned long getCurrentFrequencyTxHz() const;
    void setCurrentFrequencyRxHz(unsigned long freqInHz);
    void setCurrentFrequencyTxHz(unsigned long freqInHz);

private:
    Modulation curModulation;
    unsigned long curFrequencyTxHz;
    unsigned long curFrequencyRxHz;

};

#endif