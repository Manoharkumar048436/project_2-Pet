#include <Servo.h>

Servo myServo;  // Create a servo object

int servoPin = 5;  // Define the pin connected to the servo

void setup() {
  myServo.attach(servoPin);  // Attach the servo to the pin
  
  // You might need to calibrate these values based on your servo and requirements
  myServo.write(90);  // Set the initial position of the servo to 90 degrees
  delay(1000);  // Wait for the servo to reach the initial position
}

void loop() {
  // Move the servo to different positions
  myServo.write(0);    // Move to 0 degrees
  delay(1000);
  
  myServo.write(90);   // Move to 90 degrees
  delay(1000);
  
  myServo.write(180);  // Move to 180 degrees
  delay(1000);
}
