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

int lastEncoder1State = 0;
int lastEncoder2State = 0;

const char* macros[16] = {
  "String 1",
  "String 2",
  "String 3",
  "String 4",
  "String 5",
  "String 6",
  "String 7",
  "String 8",
  "String 9",
  "String 10",
  "String 11",
  "String 12",
  "String 13",
  "String 14",
  "String 15",
  "String 16"
};


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

  // Handle switches
  for (int col = 0; col < COLS; col++) {
    digitalWrite(colPins[col], LOW);

    for (int row = 0; row < ROWS; row++) {
      if (digitalRead(rowPins[row]) == LOW) {
        int key = row * COLS + col;
        executeMacro(macros[key]);
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
      executeMacro(macros[12]);
    } else {
      // Encoder 1 rotated counterclockwise
      // Perform your action here
      executeMacro(macros[13]);
    }
  }
  lastEncoder1State = encoder1State;

  int encoder2State = digitalRead(encoder2PinA);
  if (encoder2State != lastEncoder2State) {
    if (digitalRead(encoder2PinB) != encoder2State) {
      // Encoder 2 rotated clockwise
      // Perform your action here
      executeMacro(macros[14]);
    } else {
      // Encoder 2 rotated counterclockwise
      // Perform your action here
      executeMacro(macros[15]);
    }
  }
  lastEncoder2State = encoder2State;

  display.setRotation(2);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("");
  display.display();
}

void executeMacro(const char* macro) {
  int len = strlen(macro);

  for (int i = 0; i < len; i++) {
    if (macro[i] == '[') {
      // Find the end of the command (closing bracket)
      int endPos = i + 1;
      while (endPos < len && macro[endPos] != ']') {
        endPos++;
      }

      // Extract the command and process it
      if (endPos < len) {
        processCommand(&macro[i + 1], endPos - i - 1);
        i = endPos; // Skip the processed command
      }
    } else {
      // Send regular ASCII key
      Keyboard.write(macro[i]);
    }

    delay(10); // Delay to ensure proper keypress recognition
  }

  // Release all keys at the end
  Keyboard.releaseAll();
}

void processCommand(const char* command, int length) {
  // Handle different commands here
  if (strncmp(command, "CTRL", 4) == 0) {
    Keyboard.press(KEY_LEFT_CTRL);
  } else if (strncmp(command, "/CTRL", 5) == 0) {
    Keyboard.release(KEY_LEFT_CTRL);
  } else if (strncmp(command, "ALT", 3) == 0) {
    Keyboard.press(KEY_LEFT_ALT);
  } else if (strncmp(command, "/ALT", 4) == 0) {
    Keyboard.release(KEY_LEFT_ALT);
  } else if (strncmp(command, "WIN", 3) == 0) {
    Keyboard.press(KEY_LEFT_GUI);
  } else if (strncmp(command, "/WIN", 4) == 0) {
    Keyboard.release(KEY_LEFT_GUI);
  } else if (strncmp(command, "F", 1) == 0 && length > 1) {
    int functionKey = atoi(&command[1]);
    if (functionKey >= 1 && functionKey <= 12) {
      Keyboard.press(KEY_F1 + functionKey - 1);
    }
  } else if (strncmp(command, "MEDIA", 5) == 0) {
    int mediaKey = atoi(&command[5]);
    if (mediaKey >= 1 && mediaKey <= 12) {
      //Keyboard.press(KEY_MEDIA_VOLUME_UP + mediaKey - 1);
    }
  }

  // Add more commands as needed
}