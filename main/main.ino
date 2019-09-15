#include <FastLED.h>
 
#define DATA_PIN 6
#define NUM_LEDS 30
 
CRGB leds[NUM_LEDS];

int letter_positions[255];

void setup() { 
  // map letters to LEDs in the string of LEDs
  letter_positions[97]  =  0;  // a
  letter_positions[98]  =  1;  // b
  letter_positions[99]  =  2;  // c
  letter_positions[100] =  3;  // d
  letter_positions[101] =  4;  // e
  letter_positions[102] =  5;  // f
  letter_positions[103] =  6;  // g
  letter_positions[104] =  7;  // h
  letter_positions[105] =  8;  // i
  letter_positions[106] =  9;  // j
  letter_positions[107] = 10;  // k
  letter_positions[108] = 11;  // l
  letter_positions[109] = 12;  // m
  letter_positions[110] = 13;  // n
  letter_positions[111] = 14;  // o
  letter_positions[112] = 15;  // p
  letter_positions[113] = 16;  // q
  letter_positions[114] = 17;  // r
  letter_positions[115] = 18;  // s
  letter_positions[116] = 19;  // t
  letter_positions[117] = 20;  // u
  letter_positions[118] = 21;  // v
  letter_positions[119] = 22;  // w
  letter_positions[120] = 23;  // x
  letter_positions[121] = 24;  // y
  letter_positions[122] = 25;  // z
 
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  Serial.begin(115200);
  int sanityCheck = 0;
  while (!Serial && sanityCheck < 1000) {
    // wait for serial port to be ready. Add sanity check in case it never becomes ready
    delay(2);
    sanityCheck++;
  }
  
  Serial.print(F("Program started. Took "));
  Serial.print(sanityCheck);
  Serial.println(F(" counts for serial port to become ready."));
 }
 
void loop() {
  int numArray[] = {3, 8, 4, 12, 17, 25};
  writeWord("hello");
  FastLED.clear();
  FastLED.show();
  delay(1000);
}

void writeWord(String word) {
  Serial.print(F("writeWord called with "));
  Serial.println(word);
  
  for (int i=0; i < word.length(); i++) {
    char letter = word.charAt(i);
    FastLED.clear();
    FastLED.show();
    // need to pause for a short time so that words with double letters appear to have some space in between them
    delay(200);
    Serial.print(F("looping. Will turn on ")); Serial.print(letter); Serial.print(F(", index:")); Serial.println(letter_positions[(int) letter]);
    //leds[ letters[i] ] = CRGB::Red;
    fadeLED_on( letter_positions[(int) letter], 500 );
    delay(2000);
  }
}

void fadeLED_on(int ledindex, int wait) {
  for (int i=0; i < 255; i++) {
    leds[ ledindex ].red = i;
    FastLED.show();
    delay(1);
  }
}
