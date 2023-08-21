
// This example if for processors with LittleFS capability (e.g. RP2040,
// ESP32, ESP8266). It renders a png file that is stored in LittleFS
// using the PNGdec library (available via library manager).

// The test image is in the sketch "data" folder (press Ctrl+K to see it).
// You must upload the image to LittleFS using the Arduino IDE Tools Data
// Upload menu option (you may need to install extra tools for that).

// Don't forget to use the Arduino IDE Tools menu to allocate a LittleFS
// memory partition before uploading the sketch and data!



#include "SettingsState.h"
#include "InputManager.h"

SettingsState gSettingsState = SettingsState();

InputManager inputManager = InputManager(gSettingsState);

//====================================================================================
//                                    Setup
//====================================================================================
void setup() {
	inputManager.setup();
}

void setup1()
{
  
}

//====================================================================================
//                                    Loop
//====================================================================================
void loop(){
  inputManager.update();
}

void loop1() 
{
	
  
}
