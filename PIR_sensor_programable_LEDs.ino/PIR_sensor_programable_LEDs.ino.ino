/*

   A PIR sensor triggers a individually programmable LED strip (type WS2811, waterproof).
   The LED strip flashes randomly.
*/

#include "FastLED.h" //can be found in Arduino 1.8.5 library manager
// How many leds in your strip?
#define NUM_LEDS 50
// LED datawire connected to digital pin:
#define DATA_PIN 5
// Define the array of leds
CRGB leds[NUM_LEDS];

// PIR sensor recieves 5V. PIR sensor connected to digital pin:
int pirSensor = 4;

// for loop without delay() command:
long previousMillis = 0;
long startInterval = 10000;
long interval = 10000; //10000 is about 10 seconds


void setup() {
  Serial.begin(9600);
  pinMode(pirSensor, INPUT);
  pinMode(13, OUTPUT); //build in LED
  FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);

}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis > interval) { //when time run the code below
    randomBlink();
    previousMillis = currentMillis;
    interval = random(1, 5) * startInterval;
  }
  int sensorValue = digitalRead(pirSensor);
  Serial.println(sensorValue);

  if (sensorValue == 1) {
    digitalWrite(13, HIGH);
    for (int i = 0; i < 50; i++) {
      leds[i] = CRGB::Green; // select LED number and color
      FastLED.show();      // Turn the LED on
      delay(35);
    }
    previousMillis = currentMillis; // reset loop
  }
  if (sensorValue == 0) {
    digitalWrite(13, LOW);
    for (int i = 0; i < 50; i++) {
      leds[i] = CRGB::Black;
      // Turn the LED on
      FastLED.show();
      delay(10);
    }
  }
}

void randomBlink () {
  int LED = random(50);
  int blinks = random(5, 15);
  for (int i = 0; i < blinks; i++) {
    int delayTime = random(200);
    leds[LED] = CRGB::Red; // select LED number and color
    FastLED.show();      // Turn the LED on
    delay(delayTime);
    leds[LED] = CRGB::Black; // select LED number and color
    FastLED.show();      // Turn the LED on
    delay(delayTime);
  }
  //interval = random(1,5)*10000; //
}

