#ifndef __MY_DISPLAY_H
#define __MY_DISPLAY_H

#include <TM1637Display.h>
#include <FastLED.h>

// Define the connections pins:

#define CLK 12
#define DIO 13

inline TM1637Display display = TM1637Display(CLK, DIO);


// Create display object of type TM1637Display:

// Create array that turns all segments on:
constexpr uint8_t data[] = {0xff, 0xff, 0xff, 0xff};

// Create array that turns all segments off:
constexpr uint8_t blank[] = {0x00, 0x00, 0x00, 0x00};

constexpr uint8_t na[] = {
  SEG_G,   // -
  SEG_G   // -
};

constexpr uint8_t done[] = {
  SEG_B | SEG_C | SEG_D | SEG_E | SEG_G,           // d
  SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,   // O
  SEG_C | SEG_E | SEG_G,                           // n
  SEG_A | SEG_D | SEG_E | SEG_F | SEG_G            // E
};

// Won
constexpr uint8_t won[] = {
  SEG_C | SEG_D | SEG_E | SEG_F,   // W, left half
  SEG_B | SEG_C | SEG_D | SEG_E,   // W, right half
  SEG_C | SEG_D | SEG_E | SEG_G,   // o
  SEG_C | SEG_E | SEG_G,           // n
};

// WoF
constexpr uint8_t wof[] = {
  SEG_C | SEG_D | SEG_E | SEG_F,   // W, left half
  SEG_B | SEG_C | SEG_D | SEG_E,   // W, right half
  SEG_C | SEG_D | SEG_E | SEG_G,   // o
  SEG_A | SEG_E | SEG_F | SEG_G    // F
};



// Create degree Celsius symbol:
constexpr uint8_t celsius[] = {
  SEG_A | SEG_B | SEG_F | SEG_G,  // Circle
  SEG_A | SEG_D | SEG_E | SEG_F   // C
};


void displayCounter( bool reset = false, bool reverse = false );
void displayResetStatics();
void showBrightness();
void showLocations(uint8_t bpm);
void showTemp();
void showTime();
void showText();
#endif
