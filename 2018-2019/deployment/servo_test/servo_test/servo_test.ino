#include <Servo.h>
//#include <servo_test.h>

Servo myServo;

void setup() {
  myServo.attach(8);
  myServo.write(0);
}

void loop() {
  myServo.write(90);
  delay(1000);
  myServo.write(180);
  delay(1000);
  myServo.write(0);
  delay(1000);
}
