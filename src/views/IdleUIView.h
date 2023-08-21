#ifndef IDLE_UI_VIEW_H
#define IDLE_UI_VIEW_H

#include "FrequencyUIView.h"

class IdleUIView : public FrequencyUIView {

    public:
    static constexpr int ID = 1;
    int getId(void) const override { return ID; };

    IdleUIView(SettingsState &state): FrequencyUIView(state) {};
    unsigned long getFrequencyInHz(void) const override;
    
    protected:
    int onKeyPressed(Key &k) override;
    bool storeFrequencyDigit(Key &k) override;

};

#endif