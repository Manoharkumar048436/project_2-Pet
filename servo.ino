#include <Servo.h>
Servo servo1;
int servoPin = 9;

void setup(){
  servo1.attach(servoPin);
}

void loop(){
  servo1.write(0);
  delay(2000);
  //while(1){}
 /*  servo1.write(45);
  delay(1000);
 
   servo1.write(135);
  delay(1000);
   servo1.write(90);
  delay(1000);*/
  servo1.write(150);
  delay(2000);
}
