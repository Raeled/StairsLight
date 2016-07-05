#include <Adafruit_NeoPixel.h>
#include <Adafruit_CAP1188.h>

byte neopixelPin = 6;
byte steps[] = {24, 24, 24, 23, 26};


void setStepColor(byte step, uint32_t color);
int getStartLed(byte step);
int getLedCount();



Adafruit_NeoPixel strip = Adafruit_NeoPixel(getLedCount(), neopixelPin, NEO_GRB + NEO_KHZ800);
Adafruit_CAP1188 cap = Adafruit_CAP1188();


void setup() {
  cap.begin();

  uint8_t reg = cap.readRegister( 0x1f ) & 0x0f;
cap.writeRegister( 0x1f, reg | 0x00 );
  
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {

  
rainbow(20);

  //strip.clear();
  //uint8_t touched = cap.touched();

  //for (uint8_t i=0; i<5; i++) {
  //  if (touched & (1 << i)) {
  //    setStepColor(i, strip.Color(0,0,64));
  //  }
  //}

  //strip.show();
/*
  
  for (byte i = 0; i<sizeof(steps); i++) {
    strip.clear();
    setStepColor(i, strip.Color(0,0,64));
    strip.show();
    delay(1000);
    
  }

  for (byte i = 0; i<sizeof(steps); i++) {
    strip.clear();
    setStepColor(i, strip.Color(0,64,0));
    strip.show();
    delay(1000);
    
  }

  for (byte i = 0; i<sizeof(steps); i++) {
    strip.clear();
    setStepColor(i, strip.Color(64,0,0));
    strip.show();
    delay(1000);
    
  }*/
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for (byte i = 0; i<sizeof(steps); i++) {
      setStepColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

void setStepColor(byte step, uint32_t color) {
  int startLed = getStartLed(step);
  int ledCount = steps[step];
  for (byte i = 0; i<ledCount; i++) {
    strip.setPixelColor(startLed+i, color);
  }
}

int getStartLed(byte step) {
  int result = 0;
  for (byte i = 0; i<step; i++) {
    result += steps[i];
  }
  return result;
}

int getLedCount() {
  int result = 0;
  for (byte i = 0; i<sizeof(steps); i++) {
    result += steps[i];
  }
  return result;
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else if(WheelPos < 170) {
    WheelPos -= 85;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
}
