#ifndef UI_VIEW_H
#define UI_VIEW_H

#include <Arduino.h>
#include <Keypad.h>
#include <ctype.h>

#include "SPI.h"
#include <TFT_eSPI.h>

#include "config/PinMap.h"
#include "SettingsState.h"

#define ROWS 4
#define COLS 4

class UIView {
    
    public:
    static constexpr int ID = 0;
    virtual int getId(void) const {return UIView::ID; };

    UIView(SettingsState &state) : 
        settingsState(&state), 
        tft(TFT_eSPI()),
        keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS) {
        rowPins[0] = KEYPAD_ROW1_PIN;
        rowPins[1] = KEYPAD_ROW2_PIN;
        rowPins[2] = KEYPAD_ROW3_PIN;
        rowPins[3] = KEYPAD_ROW4_PIN;

        colPins[0] = KEYPAD_COL1_PIN;
        colPins[1] = KEYPAD_COL2_PIN;
        colPins[2] = KEYPAD_COL3_PIN;
        colPins[3] = KEYPAD_COL4_PIN;
    };

    virtual void setup(void) = 0;
    virtual int update(void);

    protected:
        TFT_eSPI tft;
        SettingsState *settingsState;

        virtual int doInput(void);
        virtual void doOutput(void) = 0;
        virtual int onKeyPressed(Key &k) = 0;

    private:
        char keys[ROWS][COLS] = {
            {'1','2','3','A'},
            {'4','5','6','B'},
            {'7','8','9','C'},
            {'*','0','#','D'}
        };

        Keypad keypad;
        byte rowPins[ROWS];
        byte colPins[COLS];
    
};

#endif