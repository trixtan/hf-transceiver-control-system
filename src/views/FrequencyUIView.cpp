#include "FrequencyUIView.h"

void FrequencyUIView::setup() {

    //Serial1.begin(115200);

  // Initialise FS
  if (!FileSys.begin()) {
    //Serial1.println("LittleFS initialisation failed!");
    while (1) yield(); // Stay here twiddling thumbs waiting
  }

  // Initialise the TFT
  tft.begin();
  tft.fillScreen(BACKGROUND_COLOR);
  tft.setRotation(1);

  bool font_missing = false;
  if (LittleFS.exists("/DSEG7Modern-Regular56.vlw")    == false) font_missing = true;
  if (font_missing)
  {
    //Serial.println("\nFont missing in Flash FS, did you upload it?");
    while(1) yield();
  }
  //else Serial.println("\nFonts found OK.");

  tft.loadFont(AA_FONT_LARGE, LittleFS); // Load another different font

  //Serial1.println("\r\nInitialisation done.");

  //Create sprites
  numberBox(mt40, 40);
  numberBox(mt30, 30);
  numberBox(mt20, 20);
  numberBox(mt17, 17);
  numberBox(mt15, 15);
  numberBox(mt12, 12);
  numberBox(mt10, 10);
  
  hiddenBands.setColorDepth(1);
  hiddenBands.createSprite(BANDS_BOX_WIDTH*7, BANDS_BOX_HEIGHT);
  hiddenBands.setBitmapColor(TEXT_COLOR, BACKGROUND_COLOR);
  hiddenBands.fillSprite(TFT_BLACK);
}

void FrequencyUIView::doOutput(void) {
    //Update blink
    if(sinceCheck >= BLINK_INTERVAL_MS) {
        sinceCheck = 0;
        this->blink = !this->blink;
    }

    printFrequency();
    printBands();
}

void FrequencyUIView::clearFrequency() {
    tft.setTextColor(BACKGROUND_COLOR, BACKGROUND_COLOR, true);
	tft.setCursor(FREQUENCY_POSITION_X, FREQUENCY_POSITION_Y);
    tft.print("88.888.888");
}

void FrequencyUIView::printBands() {
    std::optional<Band> currentBand = this->getBandForFrequency(getFrequencyInHz());
    BandId band = currentBand.has_value() ? currentBand.value().getBandId() : NONE;
    
    int i=0;
    mt40.setBitmapColor(band == M_40 ? BACKGROUND_COLOR: TEXT_COLOR, band == M_40 ? TEXT_COLOR : BACKGROUND_COLOR);
    mt40.pushSprite(BANDS_POSITION_X + (i++ * BANDS_BOX_WIDTH), BANDS_POSITION_Y);
    mt30.setBitmapColor(band == M_30 ? BACKGROUND_COLOR: TEXT_COLOR, band == M_30 ? TEXT_COLOR : BACKGROUND_COLOR);
    mt30.pushSprite(BANDS_POSITION_X + (i++ * BANDS_BOX_WIDTH), BANDS_POSITION_Y);
    mt20.setBitmapColor(band == M_20 ? BACKGROUND_COLOR: TEXT_COLOR, band == M_20 ? TEXT_COLOR : BACKGROUND_COLOR);
    mt20.pushSprite(BANDS_POSITION_X + (i++ * BANDS_BOX_WIDTH), BANDS_POSITION_Y);
    mt17.setBitmapColor(band == M_17 ? BACKGROUND_COLOR: TEXT_COLOR, band == M_17 ? TEXT_COLOR : BACKGROUND_COLOR);
    mt17.pushSprite(BANDS_POSITION_X + (i++ * BANDS_BOX_WIDTH), BANDS_POSITION_Y);
    mt15.setBitmapColor(band == M_15 ? BACKGROUND_COLOR: TEXT_COLOR, band == M_15 ? TEXT_COLOR : BACKGROUND_COLOR);
    mt15.pushSprite(BANDS_POSITION_X + (i++ * BANDS_BOX_WIDTH), BANDS_POSITION_Y);
    mt12.setBitmapColor(band == M_12 ? BACKGROUND_COLOR: TEXT_COLOR, band == M_12 ? TEXT_COLOR : BACKGROUND_COLOR);
    mt12.pushSprite(BANDS_POSITION_X + (i++ * BANDS_BOX_WIDTH), BANDS_POSITION_Y);
    mt10.setBitmapColor(band == M_10 ? BACKGROUND_COLOR: TEXT_COLOR, band == M_10 ? TEXT_COLOR : BACKGROUND_COLOR);
    mt10.pushSprite(BANDS_POSITION_X + (i++ * BANDS_BOX_WIDTH), BANDS_POSITION_Y);
}

void FrequencyUIView::printFrequency() {
  
	tft.setTextColor(TEXT_COLOR, BACKGROUND_COLOR, true);
	tft.setCursor(FREQUENCY_POSITION_X, FREQUENCY_POSITION_Y);
	
    sprintf(this->frequencyBuf1, "%8u", getNextFrequencyHz());
  
    //Replace spaces with 0
    for(unsigned char i = 0; i < 10; i++) {
        this->frequencyBuf1[i] = this->frequencyBuf1[i] == ' ' ? '0' : this->frequencyBuf1[i];
    }

    this->frequencyBuf2[10];
    FrequencyUnit frequencyPrintUpTo = Band::getFrequencyUnitFromTenExponent(MAX_TEN_EXP_FOR_FREQUENCY-this->nextFrequencyKeyPos+1);
    switch(frequencyPrintUpTo) {
        case HZ:
            sprintf(this->frequencyBuf2, "%.*s.%.*s.%.*s", 2, this->frequencyBuf1, 3, this->frequencyBuf1+2, 3, this->frequencyBuf1+5);
            break;
        case DECA_HZ:
            sprintf(this->frequencyBuf2, "%.*s.%.*s.%.*s", 2, this->frequencyBuf1, 3, this->frequencyBuf1+2, 2, this->frequencyBuf1+5);
            break;
        case HECTO_HZ:
            sprintf(this->frequencyBuf2, "%.*s.%.*s.%.*s", 2, this->frequencyBuf1, 3, this->frequencyBuf1+2, 1, this->frequencyBuf1+5);
            break;
        case KILO_HZ:
            sprintf(this->frequencyBuf2, "%.*s.%.*s", 2, this->frequencyBuf1, 3, this->frequencyBuf1+2);
            break;
        case MYRIA_HZ:
            sprintf(this->frequencyBuf2, "%.*s.%.*s", 2, this->frequencyBuf1, 2, this->frequencyBuf1+2);
            break;
        case HECTOKILO_HZ:
            sprintf(this->frequencyBuf2, "%.*s.%.*s", 2, this->frequencyBuf1, 1, this->frequencyBuf1+2);
            break;
        case MEGA_HZ:
            sprintf(this->frequencyBuf2, "%.*s", 2, this->frequencyBuf1);
            break;
        case HEBDO_HZ:
            sprintf(this->frequencyBuf2, "%.*s", 1, this->frequencyBuf1);
    }

	tft.print(this->frequencyBuf2);
};


// #########################################################################
// Draw a number in a rounded rectangle with some transparent pixels
// #########################################################################
void FrequencyUIView::numberBox(TFT_eSprite &img, unsigned int num)
{
  // Size of sprite
  #define IWIDTH  BANDS_BOX_WIDTH
  #define IHEIGHT BANDS_BOX_HEIGHT

  // Create a 1 bit sprite 80 pixels wide, 35 high (350 bytes of RAM needed @ 1 bit color depth)
  img.setColorDepth(1);
  img.createSprite(IWIDTH, IHEIGHT);
  img.setBitmapColor(TEXT_COLOR, BACKGROUND_COLOR);

  // Draw a background for the numbers
  //img.fillRect(0, 0,  40, 35, TFT_BLACK);
  img.drawRect(0, 0,  40, 35, TFT_WHITE);

  // Set the font parameters
  img.setTextSize(1);           // Font size scaling is x1
  img.setTextColor(TFT_WHITE);  // White text, no background colour

  // Set text coordinate datum to middle center
  img.setTextDatum(MC_DATUM);

  img.drawNumber(num, 20, 20, 4);
}

unsigned int FrequencyUIView::getNextFrequencyHz() const {
  return getNextFrequencyHz(std::nullopt);
}

unsigned int FrequencyUIView::getNextFrequencyHz(std::optional<Key> k) const {
  if(this->nextFrequencyKeyPos == 0 && !k.has_value()) return 0;
  unsigned int toRet = 0;
  for(byte b=0; b<DIGITS_IN_FREQUENCY; b++) {
    //Subtract from a char representation of a digit the value of '0' to get the numeric value of the char
    //(See ASCII table)
    toRet += (this->nextFrequencyKeys[b] - '0') * Band::getFrequencyUnitFromTenExponent(MAX_TEN_EXP_FOR_FREQUENCY-b);
  }
  if(k.has_value())
    toRet += (k.value().kchar - '0') * Band::getFrequencyUnitFromTenExponent(MAX_TEN_EXP_FOR_FREQUENCY-this->nextFrequencyKeyPos);
  return toRet;
}

void FrequencyUIView::resetNextFrequency() {
  this->nextFrequencyKeyPos = 0;
  for(byte b=0; b<DIGITS_IN_FREQUENCY; b++) {
    this->nextFrequencyKeys[b] = '0';
  }
}

std::optional<Band> FrequencyUIView::getNextBand() const {
  unsigned int nextFreq = this->getNextFrequencyHz();

  return getBandForFrequency(nextFreq);
}

std::optional<Band> FrequencyUIView::getBandForFrequency(unsigned int frequencyInHz) const {
  const Band *toRet;

  int i=0;
  for(const Band& band: this->settingsState->supportedBands) {
    if(band.frequencyInBand(frequencyInHz, HZ)) {
      toRet = &band;
      i++;
    }
  }
  if(i == 1) {
    return std::optional(*toRet);
  }
  return std::nullopt;
}
