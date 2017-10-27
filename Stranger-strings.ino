#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN D4
#define NUM_LEDS 100
#define BRIGHTNESS 100
int count = 1;
int ledNum;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRBW + NEO_KHZ800);

byte neopix_gamma[] = {
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,
    1,  1,  1,  1,  1,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,
    2,  3,  3,  3,  3,  3,  3,  3,  4,  4,  4,  4,  4,  5,  5,  5,
    5,  6,  6,  6,  6,  7,  7,  7,  7,  8,  8,  8,  9,  9,  9, 10,
   10, 10, 11, 11, 11, 12, 12, 13, 13, 13, 14, 14, 15, 15, 16, 16,
   17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 24, 24, 25,
   25, 26, 27, 27, 28, 29, 29, 30, 31, 32, 32, 33, 34, 35, 35, 36,
   37, 38, 39, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 50,
   51, 52, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 66, 67, 68,
   69, 70, 72, 73, 74, 75, 77, 78, 79, 81, 82, 83, 85, 86, 87, 89,
   90, 92, 93, 95, 96, 98, 99,101,102,104,105,107,109,110,112,114,
  115,117,119,120,122,124,126,127,129,131,133,135,137,138,140,142,
  144,146,148,150,152,154,156,158,160,162,164,167,169,171,173,175,
  177,180,182,184,186,189,191,193,196,198,200,203,205,208,210,213,
  215,218,220,223,225,228,231,233,236,239,241,244,247,249,252,255 
};

void setup() {
  strip.setBrightness(BRIGHTNESS);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  Serial.begin(115200);
  Serial.setTimeout(2000);
}

void loop() {

  // Wait for first byte
  while(!Serial.available());
      
  // Store input val
  int serialVal = Serial.read();

  // Wait for an input
  if (serialVal > 0) {

    // Check if it's a reset command
    if ( checkForReset(serialVal) ) {

      Serial.println("RESET");
      reset();

    // If not, light it up
    } else {

      Serial.print("Key: ");
      Serial.println(serialVal);

      letter(serialVal);

    }

  }

}

void letter(int val) {

  // Turn off all LEDs
  allOff();

  // Map key number to LED
  switch(val) {
    case 65: // a
      ledNum = 73;
      Serial.println("Selected LED: a");
      break;
    case 66: // b
      ledNum = 70;
      Serial.println("Selected LED: b");
      break;
    case 67: // c
      ledNum = 67;
      Serial.println("Selected LED: c");
      break;
    case 68: // d
      ledNum = 65;
      Serial.println("Selected LED: d");
      break;
    case 69: // e
      ledNum = 62;
      Serial.println("Selected LED: e");
      break;
    case 70: // f
      ledNum = 59;
      Serial.println("Selected LED: f");
      break;
    case 71: // g
      ledNum = 57;
      Serial.println("Selected LED: g");
      break;
    case 72: // h
      ledNum = 54;
      Serial.println("Selected LED: h");
      break;
    case 73: // i
      ledNum = 29;
      Serial.println("Selected LED: i");
      break;
    case 74: // j
      ledNum = 32;
      Serial.println("Selected LED: j");
      break;
    case 75: // k
      ledNum = 35;
      Serial.println("Selected LED: k");
      break;
    case 76: // l
      ledNum = 37;
      Serial.println("Selected LED: l");
      break;
    case 77: // m
      ledNum = 39;
      Serial.println("Selected LED: m");
      break;
    case 78: // n
      ledNum = 42;
      Serial.println("Selected LED: n");
      break;
    case 79: // o
      ledNum = 44;
      Serial.println("Selected LED: o");
      break;
    case 80: // p
      ledNum = 47;
      Serial.println("Selected LED: p");
      break;
    case 81: // q
      ledNum = 49;
      Serial.println("Selected LED: q");
      break;
    case 82: // r
      ledNum = 22;
      Serial.println("Selected LED: r");
      break;
    case 83: // s
      ledNum = 19;
      Serial.println("Selected LED: s");
      break;
    case 84: // t
      ledNum = 16;
      Serial.println("Selected LED: t");
      break;
    case 85: // u
      ledNum = 14;
      Serial.println("Selected LED: u");
      break;
    case 86: // v
      ledNum = 11;
      Serial.println("Selected LED: v");
      break;
    case 87: // w
      ledNum = 8;
      Serial.println("Selected LED: w");
      break;
    case 88: // x
      ledNum = 6;
      Serial.println("Selected LED: x");
      break;
    case 89: // y
      ledNum = 4;
      Serial.println("Selected LED: y");
      break;
    case 90: // z
      ledNum = 1;
      Serial.println("Selected LED: z");
      break;
    default: 
      // if nothing matches, do nothing
      ledNum = 0;
      Serial.println("No Match");
      break;
  }
  
  // If an LED has been selected
  if (ledNum != 0) {
    Serial.println("Lighting up LED number: ");
    Serial.println(ledNum);
    // Select LED and Colour
    if ( count == 1 ) {
      strip.setPixelColor(ledNum, strip.Color(255,0,0,0));
    } else if ( count == 2 ) {
      strip.setPixelColor(ledNum, strip.Color(0,255,0,0));
    } else if ( count == 3 ) {
      strip.setPixelColor(ledNum, strip.Color(0,0,255,0));
    } else {
      strip.setPixelColor(ledNum, strip.Color(0,0,0,255));
      count = 0;
    }
  }

  // Light it up + increment
  strip.show();
  count++;

}

void allOff() {
  // Set all to black
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(0,0,0,0));
  }
  // Execute
  strip.show();
}

bool checkForReset(int val) { // Key press 9
  if (val == 57) {
    return 1;
  } else {
    return 0;
  }
}

void reset() {
  colorWipe(strip.Color(255, 0, 0), 50); // Red
  colorWipe(strip.Color(0, 255, 0), 50); // Green
  colorWipe(strip.Color(0, 0, 255), 50); // Blue
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}
