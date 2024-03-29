#include <FastLED.h>
#include <LiquidCrystal.h>
 
#define DATA_PIN 8
#define NUM_LEDS 30

LiquidCrystal lcd(1, 2, 4, 5, 6, 7); // Creates an LC object. Parameters: (rs, enable, d4, d5, d6, d7) 
 
CRGB leds[NUM_LEDS];

// could make this array smaller by storing an offset and only indexing up to 25.
int letter_positions[122];

CHSV mycolors[4];

void setup() { 
  // map letters to LEDs in the string of LEDs
  setupLetterPositions();

  // setup the LCD screen with two rows of 16 characters
  lcd.begin(16,2);

  mycolors[0] = CHSV( 160, 200, 10);  // pale blue
  mycolors[1] = CHSV( 42,  255, 10);  // yellow
  mycolors[2] = CHSV( 0,   200, 10);  // red
  mycolors[3] = CHSV( 85,   200, 10);  // green
 
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  Serial.begin(115200);

  showReadyMessage();
 }
 
void loop() {
  writeWord("happy halloween run away in fear");
  FastLED.clear();
  FastLED.show();
  lcd.clear();
  delay(1000);
}

void writeWord(String word) {
  word.toLowerCase();
  Serial.print(F("Hello There"));
  Serial.println(word);
  
  lcd.clear();
  
  for (int i=0; i < word.length(); i++) {
    int lcdCursorPosition = i;
    char letter = word.charAt(i);

    lcd.clear();
    lcd.print("Lighting LEDs...");
    // don't scroll off the screen. Just continue to use the last position for long strings
    if (lcdCursorPosition > 15 ) { lcdCursorPosition = 15; } 
    lcd.setCursor(lcdCursorPosition,2);
    lcd.print(letter);
    
    FastLED.clear();
    FastLED.show();
    // need to pause for a short time so that words with double letters appear to have some space in between them
    delay(200);

    // if this is a space or another character we don't recognize, just continue
    if ( (int) letter < 97 || (int) letter > 122) {
      continue;
    }
    
    Serial.print(F("looping. Will turn on ")); Serial.print(letter); Serial.print(F(", index:")); Serial.println(letter_positions[(int) letter]);
    //leds[ letters[i] ] = CRGB::Red;
    //fadeLED_on( letter_positions[(int) letter]);
    turnLED_on( letter_positions[(int) letter]);
    delay(1500);
  }
}

void turnLED_on(int ledindex) {
  CHSV thisColor = mycolors[random(0,4)];
  leds[ ledindex ] = thisColor;

  for (int i=0; i < 255; i = i + 5) {
    thisColor.value = i;
    leds[ ledindex ] = thisColor;
    FastLED.show();
    //delay(1);
  }
}

void fadeLED_on(int ledindex) {
  for (int i=0; i < 255; i++) {
    leds[ ledindex ].red = i;
    FastLED.show();
    delay(1);
  }
}

void setupLetterPositions() {
  // this maps ascii codes to led position on the string of addressable LEDs
  letter_positions[97]  = 39;  // a
  letter_positions[98]  = 41;  // b
  letter_positions[99]  = 42;  // c
  letter_positions[100] = 43;  // d
  letter_positions[101] = 45;  // e
  letter_positions[102] = 46;  // f
  letter_positions[103] = 47;  // g
  letter_positions[104] = 49;  // h
  letter_positions[105] = 33;  // i
  letter_positions[106] = 31;  // j
  letter_positions[107] = 29;  // k
  letter_positions[108] = 28;  // l
  letter_positions[109] = 26;  // m
  letter_positions[110] = 24;  // n
  letter_positions[111] = 22;  // o
  letter_positions[112] = 21;  // p
  letter_positions[113] = 19;  // q
  letter_positions[114] = 2;  // r
  letter_positions[115] = 3;  // s
  letter_positions[116] = 5;  // t
  letter_positions[117] = 6;  // u
  letter_positions[118] = 8;  // v
  letter_positions[119] = 9;  // w
  letter_positions[120] = 11;  // x
  letter_positions[121] = 13;  // y
  letter_positions[122] = 14;  // z
}

void showReadyMessage() {
  lcd.print("Starting up...");
  
  // test all the LEDs, then spell out R-E-A-D-Y
  for (int i=0; i<NUM_LEDS; i++) {
    FastLED.clear();
    leds[i].red = 150;
    FastLED.show();
    delay(15);
  }
  for (int i=NUM_LEDS; i>=0; i--) {
    FastLED.clear();
    leds[i].green = 150;
    FastLED.show();
    delay(15);
  }
  for (int i=0; i<NUM_LEDS; i++) {
    FastLED.clear();
    leds[i].blue = 150;
    FastLED.show();
    delay(15);
  }
  
  char msg[] = {'r', 'e', 'a', 'd', 'y'};
  for (int i=0; i<5; i++) {
    FastLED.clear();
    FastLED.show();
    leds[ letter_positions[(int) msg[i]] ].green = 150;
    FastLED.show();
    delay(300);
  }

  FastLED.clear();
  FastLED.show();

  lcd.clear();
}

void setupLetterPositionsTest() {
  // this maps ascii codes to led position on the string of addressable LEDs
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
}
