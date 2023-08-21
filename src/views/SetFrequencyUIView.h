#ifndef SET_FREQUENCY_UI_VIEW_H
#define SET_FREQUENCY_UI_VIEW_H

#include "FrequencyUIView.h"

class SetFrequencyUIView : public FrequencyUIView {

    public:
    static constexpr int ID = 2;
    int getId(void) const override { return ID; };
    
    SetFrequencyUIView(SettingsState &state): FrequencyUIView(state) {};

    
    unsigned long getFrequencyInHz(void) const override;

    protected:
    bool storeFrequencyDigit(Key &k) override;
    int onKeyPressed(Key &k) override;

    void printBands(void) override;
    void printFrequency() override;

};

#endif