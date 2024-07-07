#include <FastLED.h>
// FastLED by Daniel Garcia


#include <TM1637Display.h>
// TM1637 by Avishay Orpaz

#include <Arduino_JSON.h>
// Arduino_JSON by Arduino

#include "my_display.hpp"
#include "my_leds.hpp"
#include "pins_arduino.h"
#include "my_wifi.hpp"
#include "my_time.hpp"
#include "my_weather.hpp"
#include "my_programs.hpp"

#define BUTTONPIN 4

#define NUM_PROGRAMS 3

void printImageCompileInfo(){
  // Add compile info for imgage startup.
  // Helps me locate and identify source of (running) images.
  // Or verify during development that a new (compiled) image IS (uploaded and) running.
  Serial.println(""); Serial.flush();

  Serial.println("Compile info: " __DATE__ " " __TIME__ " " __FILE__);
  Serial.flush();
}

void setup() {
    // Initialize display and display "Wof" for WiFi not connected (yet).
  display.setBrightness(7);

  Serial.begin(115200);

  delay(3000);

  printImageCompileInfo();

  // Initialize button
  pinMode(BUTTONPIN, INPUT);

  // Initialize LEDs, and turn them all on
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  FastLED.clear();
  ledsSet = CHSV( 0, 0, 200);
  FastLED.show();


  display.setSegments(wof,4,0);

  // Configure NTP
  configTime(MY_TZ, MY_NTP_SERVER);

  //  Connect to WiFi
  wifiSetup();

}

// Main loop
void loop() {
  static int program = 0;
  // static int buttonState = LOW;


  int buttonState = digitalRead(BUTTONPIN);

  if (buttonState == HIGH) {
    FastLED.clear();

    // Next program
    program = (program+1)% NUM_PROGRAMS ;
    // Show program number in "beams", display and serial output
    runStarBeam(program);
    FastLED.show();
    display.showNumberDec(program, true);
    Serial.print("Select program "); Serial.println(program);

    // Delay to catch "release" of button as single button press
    delay(1000);
  } else {

    // Run designated program
    switch (program) {

      case 0:
        minimalRun();
        break;

      case 1:
        showEachLed();
        break;

      case 2:
        showMany();
        break;

      default:
        break;
    }

    FastLED.show();
  }
}
