#include "Adafruit_VL53L0X.h"
#include <Servo.h>
#include "SPI.h"
#include "RFM69.h"


//LoRa address setup (On the LSM = Node 1)
#define NETWORKID     1 // must be the same for LSM & Rover
#define MYNODEID      2 // node ID for LSM
#define TONODEID      1 // node ID for Rover

//LoRa Frequency setup
#define FREQUENCY     RF69_915MHZ

//LoRa Encryption
#define ENCRYPT       true // will have encryption
#define ENCRYPTKEY    "TeamCornell2014" //use the same key on all LoRa modules

//Use ACKnowledge
#define USEACK        true // request ACK

Servo left;
Servo right;


Adafruit_VL53L0X sensor1 = Adafruit_VL53L0X();

int leftMotor = 5;
int rightMotor = 6;
int heading = 0;
int xcoord = 0;
int ycoord = 0;
int phase = 0;
bool done = false;
VL53L0X_RangingMeasurementData_t measure1;
RFM69 radio;


void setup() {
  radio.initialize(FREQUENCY, MYNODEID, NETWORKID);
  radio.encrypt(ENCRYPTKEY); //setup encryption
  left.attach(leftMotor);
  right.attach(rightMotor);
  Serial.begin(9600);
  right.write(90);
  left.write(90);
  if (!sensor1.begin()) {
    digitalWrite(3, HIGH);
  }
  //setting the addresses
  //pinMode(xleftSensor, OUTPUT);
  //pinMode(xrightSensor, OUTPUT);
  //digitalWrite(xleftSensor, LOW);
  //digitalWrite(xrightSensor, LOW);
  //delay(10);
  //digitalWrite(xleftSensor, HIGH);
  //digitalWrite(xrightSensor, HIGH);
  //digitalWrite(xrightSensor, LOW);
  //sensor1.begin(0x30);
  //digitalWrite(xrightSensor, HIGH);
  //sensor2.begin(0x31);
}

void loop() {
  if (radio.receiveDone()) {
    radio.sendACK();
    if ((char)radio.DATA[0] == 'c') {
      turnRight();
      delay(500);
      forward();
      delay(10000);
  
  while (!done) {
    delay(500);
    sensor1.rangingTest(&measure1, false);  
    Serial.println(measure1.RangeMilliMeter);
      if (measure1.RangeMilliMeter < 300) {
        digitalWrite(3,HIGH);
        if (phase == 0) {
          if (heading == 0) {
            turnLeft();
            heading = 1; 
          }
          else if (heading == 1) {
            turnAround();
            heading = 2;
            while (xcoord != 0) {
              forward();
              xcoord += 1;
            }
          }
          else if (heading == 2) {
            turnRight();
            heading = 3;
            phase = 1;
          }
          
        }
        else if (phase == 1) {
          if (heading == 2) {
            turnRight();
            heading = 3;
          }
          else if (heading == 3) {
            turnRight();
            heading = 1; 
            phase = 3;
          }
        }
        else if (phase == 3) {
          if (heading == 3) {
            turnRight();
            heading = 1;
          }
          else if (heading == 1) {
            turnRight();
            heading = 0;
            phase = 2; 
          }
          
        }
        else if (phase == 2) {
          if (heading == 1) {
            turnRight();
            heading = 0;
          }
          else if (heading == 1) {
            turnRight();
            heading = 0;
            phase = 0; 
          }
      }
    } else {
      Serial.println(phase);
      Serial.println(heading);
      forward();
      if (heading == 0) {
        ycoord += 1;
        if (phase == 1) {
          Serial.println("hello");
          turnRight();
          heading = 2;
        }
        else if (phase == 2) {
          turnLeft();
          heading = 1;
        }
        else if (phase == 3) {
          turnAround();
          heading = 3;
        }
     }
     else if (heading == 1) {
        xcoord -= 1;
        if (phase == 0) {
          Serial.println("hello1");
          turnRight();
          heading = 0;
        }
        else if (phase == 1) {
          turnAround();
          heading = 2;
        }
        else if (phase == 3) {
          turnLeft();
          heading = 3;
        } 
      }
      else if (heading == 2) {
        xcoord += 1;
        if (phase == 0) {
          turnLeft();
          heading = 0;
        }
        else if (phase == 2) {
          turnAround();
          heading = 1;
        }
        else if (phase == 3) {
          Serial.println("hello2");
          turnRight();
          heading = 3;
        } 
      }
      else {
        ycoord -= 1;
        if (phase == 0) {
          turnAround;
          heading = 0;
        }
        else if (phase == 1) {
          turnLeft();
          heading = 2;
        }
        else if (phase == 2) {
          Serial.println("hello3");
          turnRight();
          heading = 1;
        } 
      }
    }
   if (xcoord > 6 || xcoord < -6 || ycoord > 6 || ycoord < -6) {
    forward();
    done = true; 
    right.write(90);
    left.write(90);
    }

  }
  }
  }
}

void turnRight() {
  Serial.println("turn right");
  //to be completed
  right.write(70);
  left.write(70);
  delay(600);
  slowDown();
}
void turnLeft() {
  //to be completed
  Serial.println("turn left");
  right.write(110);
  left.write(110);
  delay(600);
  slowDown();
}

void forward() {
  //to be completed
  //one foot per second
  Serial.println("forward");
  right.write(110);
  left.write(70);
  delay(800);
  slowDown();
}

void reverse() {
  //to be completed
  //one foot per second
  Serial.println("forward");
  right.write(70);
  left.write(110);
  delay(1000);
  slowDown();
}

void turnAround() {
  Serial.println("turnaround");
  right.write(110);
  left.write(90);
  delay(2000);
  slowDown();
}

void deploySolarPanels() {
  digitalWrite(7, HIGH);
  delay(10000);
}

void slowDown() {
  for (int i = 110; i != 95; i--) {
    right.write(i);
    left.write(180-i); 
    delay(20);
  }
}
//void sendACKLSM(){
//  char sendBuffer[] = {'R', 'E', 'C', 'E', 'I', 'V', 'E'};
//  int sendLength = 7;
//  radio.send(TONODEID, sendBuffer, sendLength);
//}



