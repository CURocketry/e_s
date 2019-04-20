#include <Servo.h>

Servo servo1;
Servo servo2;

void setup() {
  // put your setup code here, to run once:
  servo1.attach(13);
  servo2.attach(12);

  // final position
  servo1.write(75);
  servo2.write(180);

  // second position
  delay(10000);
  servo1.write(123);
  servo2.write(120);

  // start position
  delay(30000);
  servo1.write(180); 
  servo2.write(56);
}

void loop() {
  //while(1);
  delay(10000);
  servo1.write(123); // 80
  servo2.write(120);
  delay(10000);
  servo1.write(75);
  servo2.write(180);
  while(1);
}
