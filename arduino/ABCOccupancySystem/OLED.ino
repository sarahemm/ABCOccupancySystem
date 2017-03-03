#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display = Adafruit_SSD1306();

char wifiStatus[10] = "Unknown";
long wifiSignalStrength = 0;
char spaceStatus[10] = "Unknown";
char ipAddress[17] = "Waiting...";
char lastUpdatedBuf[10] = "";

void oledInit(void) {
  // Activate the display using the internal boost regulator and the default address of 0x3C
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  // show the splash screen (which is in the buffer by default, and required for license compliance)
  display.display();

  // clear the screen buffer
  display.clearDisplay();

  // set our default text parameters
  display.setTextSize(1);
  display.setTextColor(WHITE);
}

void oledClear(void) {
  display.clearDisplay();
  display.display();
}

void oledDrawError(char *error) {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println(error);
  display.display();
}

void oledDrawDisplay(void) {
  display.clearDisplay();
  display.setCursor(0, 0);
  
  display.print("WiFi ");
  display.print(wifiStatus);
  if(wifiSignalStrength != 0) {
    display.print(" ");
    display.print(wifiSignalStrength, DEC);
    display.println("dBm");
  } else {
    display.println("");
  }
  display.print("IP is ");
  display.println(ipAddress);
  
  display.print("Space is ");
  display.println(spaceStatus);

  display.print("Last Update ");
  oledSecsAgoToString((millis() - lastUpdatedTime) / 1000, lastUpdatedBuf);
  display.print(lastUpdatedBuf);
  display.println(" ago");
  
  display.display();
}

void oledUpdateWifiStatus(char *newWifiStatus) {
  strcpy(wifiStatus, newWifiStatus);
  oledDrawDisplay();
}

void oledUpdateWifiSignalStrength(long newWifiSignalStrength) {
  wifiSignalStrength = newWifiSignalStrength;
}

void oledUpdateSpaceStatus(char *newSpaceStatus) {
  strcpy(spaceStatus, newSpaceStatus);
  oledDrawDisplay();
}

void oledUpdateIP(String newIP) {
  newIP.toCharArray(ipAddress, 17);
  oledDrawDisplay();
}

void oledSecsAgoToString(long secsAgo, char *buf) {
  if(secsAgo < 60) {
    sprintf(buf, "%ds", secsAgo);
  } else if(secsAgo < 60*60) {
    sprintf(buf, "%dm%ds", secsAgo / 60, secsAgo % 60);
  } else if(secsAgo < 60*60*24) {
    sprintf(buf, "%dh", secsAgo / (60*60));
  } else {
    strcpy(buf, "ages");
  }
}

void oledDim(bool dim) {
  display.dim(dim);
}

