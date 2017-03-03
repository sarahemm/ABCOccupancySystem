#define ANIMATE_BRIGHTNESS  8
#define STATIC_BRIGHTNESS   2

#define DOOR_OPEN   1
#define DOOR_CLOSED 0

bool lastDoor, lastOccupancy;

void ioInit(void) {
  pinMode(OCCUPANCY_PIN, INPUT_PULLUP);
  pinMode(DOOR_PIN, INPUT_PULLUP);
}

bool ioCheckAndUpdateStatus(void) {
  bool thisDoor, thisOccupancy, change;
  
  change = false;
  thisDoor = digitalRead(DOOR_PIN) == HIGH ? false : true;
  thisOccupancy = digitalRead(OCCUPANCY_PIN) == HIGH ? false : true;
  if(thisDoor != lastDoor) {
    if(!wifiSendDoorUpdate(thisDoor)) {
      // failed to update the occupancy system
      pixelsErrorFlash(pixelsColour(16, 16, 0));
      lastDoor = thisDoor;
      return true;
    }
    lastDoor = thisDoor;
    change = true;
  }
  if(thisOccupancy != lastOccupancy) {
    oledDim(false);
    if(!wifiSendOccupancyUpdate(thisOccupancy)) {
      // failed to update the occupancy system
      oledUpdateSpaceStatus("UPD FAIL");
      pixelsErrorFlash(pixelsColour(16, 16, 0));
      lastOccupancy = thisOccupancy;
      return true;
    }
    if(thisOccupancy) {
      oledUpdateSpaceStatus("Occupied");
      pixelsAnimateCheckerboard(pixelsColour(0, 0, ANIMATE_BRIGHTNESS), 150, 3);
      pixelsFillAll(pixelsColour(0, 0, STATIC_BRIGHTNESS));
    } else {
      oledUpdateSpaceStatus("Empty");
      pixelsAnimateCheckerboard(pixelsColour(ANIMATE_BRIGHTNESS, 0, 0), 150, 3);
      pixelsFillAll(pixelsColour(STATIC_BRIGHTNESS, 0, 0));
    }
    lastOccupancy = thisOccupancy;
    change = true;
  }
  return change;
}

