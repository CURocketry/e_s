#include "SPI.h"
//#include "RFM69.h"
#include "radio.h"

#define FREQ      RF69_915MHZ
#define ENCRYPT   true
#define E_KEY     "testing"
#define NODEID    1
#define NETWORKID 1


SPIClass mySPI(&sercom1, 12, 13, 11,SPI_PAD_0_SCK_1, SERCOM_RX_PAD_3);

void setup() {
  Serial.begin(9600);
  //mySPI.begin();    // should be called by radio
  RFM69 radio((uint8_t)10, (uint8_t)2, true, &mySPI);
  radio.initialize(FREQ, NODEID, NETWORKID);
  radio.setHighPower();
  radio.encrypt(E_KEY);

}

void loop() {
  // put your main code here, to run repeatedly:

}
