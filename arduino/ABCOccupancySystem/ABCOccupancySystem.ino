// this should go in the WiFi file really but Arduino's automatic prototype generation fails if it is
#include <WiFiManager.h>

#define NEOPIXEL_PIN  15
#define NEOPIXEL_ROWS 4
#define NEOPIXEL_COLS 8

#define OCCUPANCY_PIN 13
#define DOOR_PIN      2  // FIXME: determine the actual pins

#define xy_to_pixel(x, y) (y * NEOPIXEL_COLS + x)

void setup() {
  Serial.begin(115200);
  
  Serial.println("Booting...");
  
  // initialize the NeoPixel display
  pixelsInit();

  // initialize the OLED display
  oledInit();

  // WiFi needs some time to be ready
  delay(2000);

  // set up the pin directions and such
  ioInit();

  // connect to the configured SSID or enter WiFi setup mode to get one configured
  wifiInit();

  // in case we had a warning while booting, clear the pixel display
  pixelsClearDisplay();
}

long lastUpdatedTime = 0;
void loop() {
  // dim the display after 30 seconds idle
  oledDim(millis() - lastUpdatedTime > 30000);
  // clear the display after 5m idle
  if((millis() - lastUpdatedTime) / 1000 < 60*5) {
    oledDrawDisplay();
  } else {
    oledClear();
  }
  // gets the latest signal strength to put on the display
  wifiUpdateSignalStrength();
  // check our I/Os and update occupancy/door status based on them
  if(ioCheckAndUpdateStatus())
    lastUpdatedTime = millis();
  delay(1000);
}

void fatal(char *msg) {
  Serial.print("FATAL: ");
  Serial.println(msg);
  pixelsError(pixelsColour(16, 0, 0));
  oledDrawError(msg);
  while(1) {
    // needed to reset the WDT
    delay(1000);
  }
}



