#include <FS.h>
#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>

void wifiInit(void) {
  WiFiManager wifiManager;

  // set a callback to be called if we enter WiFi setup mode
  wifiManager.setAPCallback(wifiConfigModeCallback);

  // if we're not configured within 5 minutes, give up and show the error display.
  wifiManager.setConfigPortalTimeout(300);

  // initialize the WiFi
  oledUpdateWifiStatus("Connecting...");
  Serial.println("Connecting to WiFi SSID ");
  if(!wifiManager.autoConnect("ABC Occupancy System Setup"))
    fatal(" WIFI CONNECT FAILED\n\n  Reset unit to try\n  connecting again.");
  Serial.print("Connected to SSID ");
  Serial.print(WiFi.SSID());
  Serial.print(" with IP ");
  Serial.println(WiFi.localIP());
  oledUpdateWifiStatus("Connected");
  oledUpdateWifiSignalStrength(WiFi.RSSI());
  oledUpdateIP(WiFi.localIP().toString());
}

void wifiConfigModeCallback (WiFiManager *myWiFiManager) {
  Serial.println("Entered setup mode.\n");
  Serial.print("SSID: ");
  Serial.println(myWiFiManager->getConfigPortalSSID());
  Serial.print("IP: ");
  Serial.println(WiFi.softAPIP());
  pixelsError(pixelsColour(16, 16, 0));
  oledDrawError(" WIFI CONNECT FAILED\n\nConnect to setup SSID\nto update WiFi config");
  Serial.println("Ready for setup.");
}


byte wifiSendOccupancyUpdate(bool occupied) {
  char url[72];
  
  // build the URL to dweet the occupancy status
  strcpy(url, "http://dweet.io/dweet/for/abcspace-occupancy?occupied=");
  Serial.print("Sending occupancy update: ");
  if(occupied == 1) {
    Serial.println(" occupied");
    strcat(url, "1");
  } else {
    Serial.println(" empty");
    strcat(url, "0");
  }

  // send the dweet
  return wifiSendUpdate(url);
}

byte wifiSendDoorUpdate(bool doorOpen) {
  char url[72];
  
  // build the URL to dweet the door status
  strcpy(url, "http://dweet.io/dweet/for/abcspace-door?open=");
  Serial.print("Sending door update: ");
  if(doorOpen == 1) {
    Serial.print(" open ");
    strcat(url, "1");
  } else {
    Serial.println(" closed ");
    strcat(url, "0");
  }

  // send the dweet
  return wifiSendUpdate(url);
}

byte wifiSendUpdate(char *url) {
  HTTPClient http;

  http.begin(url);
  int httpCode = http.GET();

  // httpCode will be negative on error
  if(httpCode > 0) {
      // HTTP header has been send and Server response header has been handled
      Serial.print("HTTP request returned code ");
      Serial.println(httpCode, DEC);
  } else {
      Serial.print("HTTP request failed, error: ");
      Serial.println(http.errorToString(httpCode).c_str());
  }
  http.end();
  if(httpCode == 200) return true;
  return false;
}

void wifiUpdateSignalStrength(void) {
  oledUpdateWifiSignalStrength(WiFi.RSSI());
}

