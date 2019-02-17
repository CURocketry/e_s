#include "SPI.h"
#include "RFM69.h"

#define FREQ      RF69_915MHZ
#define ENCRYPT   true
#define E_KEY     "testing"
#define NODEID    1
#define NETWORKID 1

RFM69 radio(10, 2, true);
SPIClass mySPI(&sercom1, 12, 13, 11,SPI_PAD_0_SCK_1, SERCOM_RX_PAD_3); );
void setup() {
  Serial.begin(9600);
  mySPI.begin();
  
  // rip
  radio.initialize(FREQ, NODEID, NETWORKID);
  radio.setHighPower();;
  radio.encrypt(E_KEY)

}

void loop() {
  // put your main code here, to run repeatedly:

}
