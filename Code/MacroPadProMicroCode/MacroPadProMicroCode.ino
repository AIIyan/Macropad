#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "Keyboard.h"

#define OLED_SDA 2
#define OLED_SCL 3
Adafruit_SSD1306 display(128, 32, &Wire, OLED_SDA, OLED_SCL);

#define ROWS 4
#define COLS 3

const int rowPins[ROWS] = {15, 14, 16};  // Adjust pins as per your connections
const int colPins[COLS] = {4, 5, 6, 7};     // Adjust pins as per your connections

const int encoder1PinA = 21;
const int encoder1PinB = 20;
const int encoder2PinA = 19;
const int encoder2PinB = 18;

void setup() {
  Serial.begin(9600);

  // Setup OLED display
  Wire.begin();
  display.begin(SSD1306_I2C_ADDRESS, OLED_SDA, OLED_SCL);
  display.display();

  // Setup switches
  for (int i = 0; i < ROWS; i++) {
    pinMode(rowPins[i], INPUT_PULLUP);
  }

  for (int i = 0; i < COLS; i++) {
    pinMode(colPins[i], OUTPUT);
    digitalWrite(colPins[i], HIGH);
  }

  // Setup encoders
  pinMode(encoder1PinA, INPUT_PULLUP);
  pinMode(encoder1PinB, INPUT_PULLUP);
  pinMode(encoder2PinA, INPUT_PULLUP);
  pinMode(encoder2PinB, INPUT_PULLUP);
}

void loop() {
  // Your main loop code here

  // Handle switches
  for (int col = 0; col < COLS; col++) {
    digitalWrite(colPins[col], LOW);

    for (int row = 0; row < ROWS; row++) {
      if (digitalRead(rowPins[row]) == LOW) {
        // Key pressed, you can use a switch-case statement to identify the key
        // For example, use Keyboard.write('a') to send the letter 'a'
      }
    }

    digitalWrite(colPins[col], HIGH);
  }

  // Handle encoders
  int encoder1State = digitalRead(encoder1PinA);
  if (encoder1State != lastEncoder1State) {
    if (digitalRead(encoder1PinB) != encoder1State) {
      // Encoder 1 rotated clockwise
      // Perform your action here
    } else {
      // Encoder 1 rotated counterclockwise
      // Perform your action here
    }
  }
  lastEncoder1State = encoder1State;

  int encoder2State = digitalRead(encoder2PinA);
  if (encoder2State != lastEncoder2State) {
    if (digitalRead(encoder2PinB) != encoder2State) {
      // Encoder 2 rotated clockwise
      // Perform your action here
    } else {
      // Encoder 2 rotated counterclockwise
      // Perform your action here
    }
  }
  lastEncoder2State = encoder2State;

  // Additional code for OLED display updates can be added here
}
