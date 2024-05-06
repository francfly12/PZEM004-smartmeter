# PZEM004-smartmeter
Power meter display using PWM004 and lilygo TDisplay

This is a smartmeter designed to display power values of a circuit. 
Example: solar power production.
It uses a PZEM004T module easily found on internet.
Display using the lilygo T-display module.
Easy to make.

## You need:
- PZEM004 module with its current transformer. The original plastic case is removed and it is integrated into a new box with all other components.
- Lilygo T-Display : ESP32 module with ESP32 . Includes display and the 2 buttons.
- Power supply module. Standard 5V/1A supply.
ALL STL files are given to make the new box. Fits into Standard module.

## 4 display modes (screens) are provided: 
- Basic power display
- detailed information
- Graphic, over 24 hours
- Graphic, over 10 days
- reset power value

##  Wiring: Very simple. Power supply (5V) for PZEM and lilygo Tdisplay
- PZEM004T connected to pin GPIO26 (TX) and pin GPIO27 (RX) of lilygo
- AC wiring: see PZEM004T wiring: 2 wires for AC power(230V mains) and 2 wires for AC transformer (coil, over measured circuit)

## Programmed using Arduino IDE 2.3.2
- select boar ESP32 Dev Module
- Serial monitor 115200 bds
- libraries & fonts to install:
- //Librairies
#include <PZEM004Tv30.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>
#include <Fonts/FreeSans18pt7b.h>

## Improvements: There is A LOT OF ROOM for improvement...
  I wrote this software. Not being an expert means it can be greatly improved, but it is also very easy to do so and change things such as text, graphics, etc...
  I am so short of time !
  
## What would be nice to do:
  Improve some of the graphics to increase response time and clear a few glitches.
  Make it power-off safe. No data loss at power off, by writing data every few moments.
  Send data through MQTT ...
  Reprogram using OTA.
  
  

