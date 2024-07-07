#ifndef __MY_LEDS_H
#define __MY_LEDS_H

#include <FastLED.h>


#define NUM_LEDS 27
#define DATA_PIN 5
#define FADE 10
#define FADE_SLOW 1
#define FADE_FAST 80

inline CRGB    leds[NUM_LEDS];
inline CRGBSet ledsSet(leds, NUM_LEDS);
inline CRGBSet ledsSetStar(ledsSet(0, 16));
inline CRGBSet ledsSetBonus(ledsSet(17, 24));
inline CRGBSet ledsSetArrow(ledsSet(25, 26));

// Star definition
#define STAR_BEAMS 4
#define STAR_WAVES 5
#define STAR_CENTER 0

enum star_motion { to_center, from_center, ssinus };

// Bonus blocks definition
#define BONUS_BLOCKS 8
enum bonus_motion { to_right, to_left, bsinus };


// Arrow definition
#define ARROW_LEFT 0
#define ARROW_RIGHT 1


void runStarWave( int bpm, star_motion motion = ssinus, uint8_t fade = FADE_FAST );

//
// Light Star by beam
//

void runStarBeam( int beamNr );
void runStarBeamCircle( int bpm );
void runStarBeamWaver( int bpm );
void runStarBlinker( int bpm, int low = 0, int high = 255 );

//
// Light Star by beam
//

//
//  Light bonus block
//
void runBonusBlock( int block );
void runBonusBlocks( int bpm, bonus_motion motion = bsinus, int offset = 0, uint8_t fade = FADE_FAST );
void runBonusBlockBlinker( int bpm );

//
//  Light bonus block
//


//
//  Light arrow block
//

void runArrowBlinker( int bpm );
void runArrow(int arrow);
void runArrowKit( int bpm, int offset = 0 );

//
//  Light arrow block
//

#endif
