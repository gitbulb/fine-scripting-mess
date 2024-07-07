#include "my_leds.hpp"

constexpr uint8_t starBeams[STAR_BEAMS][STAR_WAVES] {
  {STAR_CENTER, 1, 2, 3, 4},
  {STAR_CENTER, 5, 6, 7, 8},
  {STAR_CENTER, 9, 10, 11, 12},
  {STAR_CENTER, 13, 14, 15, 16},
};

// Arrow definition
#define ARROW_LEFT 0
#define ARROW_RIGHT 1

void runStarWave( int bpm, star_motion motion, uint8_t fade ){
  uint8_t pixel;

  switch(motion){
    case ssinus:
      pixel = beatsin8(bpm, 0, STAR_WAVES-1, 0, 0);
      break;
    case to_center:
      pixel = map( beat8(bpm,0) , 0,255, STAR_WAVES-1,-1);
      break;
    case from_center:
      pixel = map( beat8(bpm,0) , 0,255, 0,STAR_WAVES);
      break;
  }

  if( pixel > STAR_WAVES-1 ) pixel = STAR_WAVES-1;
  if( pixel < 0 ) pixel = 0;

  for( int i=0; i<STAR_BEAMS; i++){
    leds[starBeams[i][pixel]] = CRGB::White;
  }
  ledsSetStar.fadeToBlackBy(fade);
}
//
// Light Star by beam
//
void runStarBeam( int beamNr ){
  // Light one (sinbeat) entire star beam
  if( beamNr >= 0 &&  beamNr < STAR_BEAMS ){ // ignore higher "invisible" beams
    for( int i=0; i<STAR_WAVES; i++){
      leds[starBeams[beamNr][i]] = CRGB::White;
    }
  }
  leds[STAR_CENTER] = CRGB::White; // Center allways shines!
  ledsSetStar.fadeToBlackBy(FADE_FAST);
}

void runStarBeamCircle( int bpm ){
  uint8_t beatStarBeamCircle =  map( beat8(bpm,0) , 0,255, 0,((STAR_BEAMS-1)*4)-1);

  runStarBeam(beatStarBeamCircle);
}

void runStarBeamWaver( int bpm ){
  uint8_t beatStarBeam = beatsin8(bpm, 0, STAR_BEAMS-1, 0, 0);

  runStarBeam(beatStarBeam);
}

void runStarBlinker( int bpm, int low, int high ){
  uint8_t brightness = beatsin8(bpm, low, high, 0, 0);

  ledsSetStar =  CHSV( 0, 0, brightness);
}
//
// Light Star by beam
//

//
//  Light bonus block
//
void runBonusBlock( int block ){

  if ( block >= 0 && block < BONUS_BLOCKS ){ // ignore higher "invisible" blocks
    ledsSetBonus[block]  = CRGB::White;
      // Serial.println("Current led: " + String(block));
  }
  ledsSetBonus.fadeToBlackBy(FADE);
  // Serial.println("Current led: " + String(block));
}

void runBonusBlocks( int bpm, bonus_motion motion, int offset, uint8_t fade ){
  uint8_t block;
  switch(motion){
    case bsinus:
      block = beatsin8(bpm,  0, BONUS_BLOCKS-1, 0, offset);
      break;
    case to_right:
      block = map( beat8(bpm,0) , 0,255, BONUS_BLOCKS-1,0);
      break;
    case to_left:
      block = map( beat8(bpm,0) , 0,255, 0,BONUS_BLOCKS-1);
      break;

  }
  runBonusBlock( block);
}

void runBonusBlockBlinker( int bpm ){
  uint8_t brightness = beatsin8(bpm, 0, 255, 0, 0);

  ledsSetBonus =  CHSV( 0, 0, brightness);
}
//
//  Light bonus block
//


//
//  Light arrow block
//
void runArrowBlinker( int bpm ){
  uint8_t brightness = beatsin8(bpm, 0, 255, 0, 0);

  ledsSetArrow =  CHSV( 0, 0, brightness);

}

void runArrow(int arrow){
  ledsSetArrow[arrow] = CRGB::White;
  ledsSetArrow.fadeToBlackBy(FADE);
}

void runArrowKit( int bpm, int offset){
  uint8_t arrow = beatsin8(bpm,  0, 1, 0, offset);

  runArrow(arrow);
}
//
//  Light arrow block
//
