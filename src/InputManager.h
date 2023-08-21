#ifndef INPUT_MANAGER
#define INPUT_MANAGER

#include <functional>
#include <Keypad.h>
#include "SettingsState.h"
#include "views/UIView.h"
#include "views/IdleUIView.h"
#include "views/SetFrequencyUIView.h"

class InputManager {
public:
    InputManager(SettingsState &settingsState) : 
        settingsState(&settingsState),
        idleUIView(IdleUIView(settingsState)),
        setFrequencyUIView(SetFrequencyUIView(settingsState)),
        currentView(&idleUIView) {};
    
    void update(void);
    void setup(void);
    
private:
    SettingsState *settingsState;
    
    UIView *currentView;

    IdleUIView idleUIView;
    SetFrequencyUIView setFrequencyUIView;    
};


#endif