#ifndef FREQUENCY_UI_VIEW_H
#define FREQUENCY_UI_VIEW_H

#include <optional>
#include <LittleFS.h>
#include "UIView.h"

#include "SettingsState.h"
#include "elapsedMillis.h"

#define FileSys LittleFS

#define AA_FONT_LARGE "DSEG7Modern-Regular56"

#define FREQUENCY_POSITION_X 20 
#define FREQUENCY_POSITION_Y 132

#define BANDS_POSITION_X 0
#define BANDS_POSITION_Y 285
#define BANDS_BOX_HEIGHT 35
#define BANDS_BOX_WIDTH 40

#define BLINK_INTERVAL_MS 200
 
#define BACKGROUND_COLOR 0xB6CF
#define TEXT_COLOR TFT_BLACK

class FrequencyUIView: public UIView {

public:
    FrequencyUIView(SettingsState &state) : 
        UIView(state),
        mt40(TFT_eSprite(&tft)),
        mt30(TFT_eSprite(&tft)),
        mt20(TFT_eSprite(&tft)),
        mt17(TFT_eSprite(&tft)),
        mt15(TFT_eSprite(&tft)),
        mt12(TFT_eSprite(&tft)),
        mt10(TFT_eSprite(&tft)),
        hiddenBands(TFT_eSprite(&tft)) {};

    void setup() override;

    std::optional<Band> getBandForFrequency(unsigned int frequencyInHz) const;

    virtual unsigned long getFrequencyInHz(void) const = 0;

    protected:
    char nextFrequencyKeys[8];
    byte nextFrequencyKeyPos; //Position of the next frequency digit to be received.

    void doOutput(void) override;
    virtual bool storeFrequencyDigit(Key &k) = 0;

    /*
    * Get the currently saved next frequency
    */
    unsigned int getNextFrequencyHz() const;

    /*
    * Get the frequency obtained from the currently saved,
    * plus a not yet saved additional key
    */
    unsigned int getNextFrequencyHz(std::optional<Key> k) const;
    void resetNextFrequency();
    std::optional<Band> getNextBand() const;

    char frequencyBuf1[11];
    char frequencyBuf2[11];
    elapsedMillis sinceCheck;
    bool blink;

    /* Sprites */
    TFT_eSprite mt40;
    TFT_eSprite mt30;
    TFT_eSprite mt20;
    TFT_eSprite mt17;
    TFT_eSprite mt15;
    TFT_eSprite mt12;
    TFT_eSprite mt10;
    TFT_eSprite hiddenBands;

    // UI    
    void clearFrequency();
    virtual void printFrequency();
    void numberBox(TFT_eSprite &img, unsigned int num);
    virtual void printBands();


};

#endif