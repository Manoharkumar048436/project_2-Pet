const int flowSensorPin = 2; // Change this to your actual pin number

volatile int pulseCount = 0;
unsigned long previousMillis = 0;
const unsigned long interval = 1000; // Interval to calculate flow rate (1 second in this case)
float calibrationFactor = 1.0; // Adjust this for calibration

void setup() {
  Serial.begin(9600);
  pinMode(flowSensorPin, INPUT);
    pinMode(6, OUTPUT);
    digitalWrite(6, HIGH);
    delay(100);
     digitalWrite(6, LOW);
  attachInterrupt(digitalPinToInterrupt(flowSensorPin), countPulse, RISING);
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    float flowRate = pulseCount * calibrationFactor / (interval / 1000.0); // Calculate flow rate (pulses per second)
    float volume = flowRate * interval / calibrationFactor; // Approximate volume based on flow rate

    Serial.print("Pulse Count: ");
    Serial.println(pulseCount);
    Serial.print("Flow Rate (pulses/s): ");
    Serial.println(flowRate);
    Serial.print("Approximate Volume (ml): ");
    Serial.println(volume);

    pulseCount = 0; // Reset pulse count
    previousMillis = currentMillis;
  }

  // You can add other logic or functionality here
  // Ensure the loop doesn't contain time-consuming tasks
  // delay(100); // Avoid long delays in actual use
}

void countPulse() {
  pulseCount++;
}
