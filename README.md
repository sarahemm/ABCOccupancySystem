# ABCOccupancySystem
Occupancy reporting system for Adventure Box Collective space.
Connects a switch to wifi (which members flip when arriving/leaving) and reports whether the switch is on or off to dweet.io, which then feeds into a Freeboard dashboard.

Runs on an Adafruit Feather system with:
- Feather Doubler - Allows OLED and NeoPixel display to be side by side.
- Feather HUZZAH ESP8266 - Overall control and WiFi communication.
- Feather OLED - Reporting detailed status information.
- Feather NeoPixel - Reporting current status in easy-to-read form.
