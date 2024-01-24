#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "Keyboard.h"

//#define OLED_SDA 2
//#define OLED_SCL 3
#define OLED_RESET -1
#define SCREEN_ADRESS 0x3C
Adafruit_SSD1306 display(128, 64, &Wire, OLED_RESET);

#define ROWS 3
#define COLS 4

const int rowPins[ROWS] = {15, 14, 16};  // Adjust pins as per your connections
const int colPins[COLS] = {4, 5, 6, 7};     // Adjust pins as per your connections
const int encoder1PinA = 21;
const int encoder1PinB = 20;
const int encoder2PinA = 19;
const int encoder2PinB = 18;

void setup() {
  Serial.begin(9600);

  // Setup OLED display
  //Wire.begin();
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;
  }
  //display.begin(0x3C, OLED_SDA, OLED_SCL);
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
  int lastEncoder1State = 0;
  int lastEncoder2State = 0;

  // Handle switches
  for (int col = 0; col < COLS; col++) {
    digitalWrite(colPins[col], LOW);

    for (int row = 0; row < ROWS; row++) {
      if (digitalRead(rowPins[row]) == LOW) {

        //case to identify key
        switch (row * COLS + col) {
          case 0:
            // Key in the first column, first row
            // Perform your action here
            Keyboard.write('A');
            break;
          case 1:
            // Key in the first column, second row
            // Perform your action here
            Keyboard.write('B');
            break;
          case 2:
            break;
          case 3:
            break;
          case 4:
            break;
          case 5:
            break;
          case 6:
            break;
          case 7:
            break;
          case 8:
            break;
          case 9:
            break;
          case 10:
            break;
          case 11:
            break;
        }
          // Add more cases for other keys as needed

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

  //display.setRotation(2);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("Blender \n1) copy 2) paste \n3) X 4) y 5) z");
  display.display();
}
