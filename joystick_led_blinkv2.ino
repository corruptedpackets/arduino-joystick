const int VRX = A0;
const int VRY = A1;
const int LED = LED_BUILTIN;

const int CENTER = 512;
const int THRESHOLD = 150;

void setup() {
  Serial.begin(9600);
  delay(2000);
  pinMode(LED, OUTPUT);
}

void loop() {
  int xVal = analogRead(VRX);
  int yVal = analogRead(VRY);

  bool moved = abs(xVal - CENTER) > THRESHOLD ||
               abs(yVal - CENTER) > THRESHOLD;

  if (moved) {
    digitalWrite(LED, HIGH);
  } else {
    digitalWrite(LED, LOW);
  }

  delay(50);
}#include "Arduino_LED_Matrix.h"

ArduinoLEDMatrix matrix;

const int VRX = A0;
const int VRY = A1;
const int SW  = 2;

const int CENTER = 512;
const int THRESHOLD = 150;

uint8_t frame[8][12];

void clearFrame() {
  for (int r = 0; r < 8; r++)
    for (int c = 0; c < 12; c++)
      frame[r][c] = 0;
}

void showDot() {
  clearFrame();
  frame[3][5] = 1;
  frame[3][6] = 1;
  frame[4][5] = 1;
  frame[4][6] = 1;
}

void showUp() {
  clearFrame();
  frame[1][5] = 1; frame[1][6] = 1;
  frame[2][4] = 1; frame[2][7] = 1;
  frame[3][3] = 1; frame[3][8] = 1;
  frame[4][5] = 1; frame[4][6] = 1;
  frame[5][5] = 1; frame[5][6] = 1;
  frame[6][5] = 1; frame[6][6] = 1;
}

void showDown() {
  clearFrame();
  frame[1][5] = 1; frame[1][6] = 1;
  frame[2][5] = 1; frame[2][6] = 1;
  frame[3][5] = 1; frame[3][6] = 1;
  frame[4][3] = 1; frame[4][8] = 1;
  frame[5][4] = 1; frame[5][7] = 1;
  frame[6][5] = 1; frame[6][6] = 1;
}

void showLeft() {
  clearFrame();
  frame[3][2] = 1;
  frame[2][3] = 1; frame[3][3] = 1; frame[4][3] = 1;
  frame[1][4] = 1; frame[3][4] = 1; frame[5][4] = 1;
  frame[3][5] = 1;
  frame[3][6] = 1;
  frame[3][7] = 1;
  frame[3][8] = 1;
}

void showRight() {
  clearFrame();
  frame[3][3] = 1;
  frame[3][4] = 1;
  frame[3][5] = 1;
  frame[3][6] = 1;
  frame[1][7] = 1; frame[3][7] = 1; frame[5][7] = 1;
  frame[2][8] = 1; frame[3][8] = 1; frame[4][8] = 1;
  frame[3][9] = 1;
}

void showPress() {
  clearFrame();
  for (int r = 0; r < 8; r++)
    for (int c = 0; c < 12; c++)
      frame[r][c] = 1;
}

void setup() {
  Serial.begin(9600);
  delay(2000);
  pinMode(SW, INPUT_PULLUP);
  matrix.begin();
  Serial.println("Joystick matrix ready!");
}

void loop() {
  int xVal = analogRead(VRX);
  int yVal = analogRead(VRY);
  int btn  = digitalRead(SW);

  if (btn == LOW) {
    showPress();
  } else if (yVal < CENTER - THRESHOLD) {
    showUp();
  } else if (yVal > CENTER + THRESHOLD) {
    showDown();
  } else if (xVal < CENTER - THRESHOLD) {
    showLeft();
  } else if (xVal > CENTER + THRESHOLD) {
    showRight();
  } else {
    showDot();
  }

  matrix.renderBitmap(frame, 8, 12);
  delay(50);
}
