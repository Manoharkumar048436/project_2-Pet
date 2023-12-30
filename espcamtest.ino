
// ledPin refers to ESP32-CAM GPIO 4 (flashlight)
const int ledPin = 4;

void setup() {
  // initialize digital pin ledPin as an output
  pinMode(ledPin, OUTPUT);
  pinMode(33, OUTPUT);
}

void loop() {
  digitalWrite(ledPin, HIGH);
   digitalWrite(33, HIGH);
  delay(2000);
  digitalWrite(ledPin, LOW);
    digitalWrite(33, LOW);
  delay(2000);
}
