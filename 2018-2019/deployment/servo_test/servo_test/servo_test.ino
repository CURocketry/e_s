#include <Servo.h>
<<<<<<< Updated upstream
//#include <servo_test.h>

Servo myServo;
=======

Servo myservo;

void setup() {
  // put your setup code here, to run once:
  myservo.attach(8);
  myservo.write(90);
>>>>>>> Stashed changes

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
