/**
* Collection of programs for different sets of leds and display
*/
#ifndef __COMPOSITE_PROGRAMS_H
#define __COMPOSITE_PROGRAMS_H

#include "my_leds.hpp"
#include "my_display.hpp"
#include "my_wifi.hpp"

/**
 * Runs a minimal program that alternates between showing the time and temperature.
 */
void minimalRun(){
  static bool oneOrOther = false;

  uint8_t brightness = beatsin8(20, 100, 200, 0, 0);

  ledsSetStar  = CHSV( 0, 0, brightness);
  ledsSetBonus = CHSV( 0, 0, brightness+50);
  ledsSetArrow = CHSV( 0, 0, brightness+20);


  EVERY_N_MILLISECONDS(2000){
    oneOrOther = seconds16()%8 <6 ? true : false;
  }

  if(oneOrOther){
    showTime();
  } else {
    showTemp();
  }

}

/**
 * Simply set all leds to bright white, and display "done" on the display
 */
void noRun(){
  ledsSet = CHSV( 0, 0, 255);
  display.setSegments(done,4,0);
}

/*
* Show each led, while displaying the current led number on the display
*/
void showEachLed(uint8_t bpm=4){
  // Arduino map() should map (here) 0-255 to 0-"last led" (NUM_LEDS-1),
  // but that would only assign 255 to the last led, lighting it very shortly
  // Mapping onto an "extra" led, give the actual last led a fair share.
  // But don't actually us the "extra" led!
  uint8_t currentLed = map( beat8(bpm,0) , 0,255, 0,NUM_LEDS);

  // Don't act on the extra led
  if( currentLed < NUM_LEDS) {
    ledsSet[currentLed] = CRGB::White;
    display.showNumberDec(currentLed, true);
    Serial.println("Current led: " + String(currentLed));

    ledsSet.fadeToBlackBy(FADE_FAST);
  }
}

/*
* Blink all led sets
*/
void runBlinker( int bpm ){
  runBonusBlockBlinker(bpm);
  runStarBlinker(bpm);
  runArrowBlinker(bpm);
}

void showMany(){
  #define NUM_MANY_PROGRAMS 5
  static int currentProgram = 0;
  EVERY_N_SECONDS(8){
    currentProgram = (currentProgram+1) % (NUM_MANY_PROGRAMS+1);

    ledsSet = CRGB::Black;
    runStarBeam(currentProgram%4); // max 4 (0-3) beams
    runBonusBlock(BONUS_BLOCKS-1 - currentProgram);
    FastLED.show();
    display.showNumberDec(currentProgram);
    delay(500);
    displayResetStatics();
    Serial.println("Current program: " + String(currentProgram));
  }

  switch (currentProgram) {

    case 0:
      runStarBeamWaver(40);
      runBonusBlocks(40, bsinus, 128);
      runArrowKit(40);

      showTime();
      break;

    case 1:
      runStarWave(40);
      runBonusBlocks(40, bsinus);
      runArrowKit(40, 128);

      showLocations(40);
      break;

    case 2:
      runStarBlinker(40);
      runBonusBlocks(20, to_right);
      runArrowKit(80);

      showTemp();
      break;

    case 3:
      runStarWave(120, to_center);
      runBonusBlocks(80, to_right);
      runArrow(ARROW_LEFT);

      displayCounter();
      break;

    case 4:
      runStarWave(120, from_center);
      runBonusBlocks(80, to_left);
      runArrow(ARROW_RIGHT);

      // Reversed counter
      displayCounter(false, true);
      break;

    case 5:
      runBlinker(40);

      showText();
      break;

    default:
      break;
  }
}


#endif
