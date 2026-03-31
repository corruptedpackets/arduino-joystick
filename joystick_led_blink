const int VRX = A0;
const int VRY = A1;
const int LED = LED_BUILTIN;

const int CENTER = 512;
const int THRESHOLD = 150;

void setup() {
  Serial.begin(9600);
  delay(2000);
  pinMode(LED, OUTPUT);
  Serial.println("Joystick LED ready!");
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
}
