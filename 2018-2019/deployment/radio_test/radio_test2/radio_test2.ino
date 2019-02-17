#include "SPI.h"
#include "RFM69.h"
#include "Wire.h"

#define NETWORKID 1 //must be same for both radios
#define MYNODEID 2 //node id for my radio
#define ENCRYPT true
#define E_KEY "testing"
#define FREQUENCY RF60_915MHZ

RFM69 radio(10, 2, true);

SPIClass mySPI(&sercom1, 12, 13, 11, SPI_PAD_0_SCK_1, SERCOM_RX_PAD_3); //set up SPI line

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  mySPI.begin();

  pinPeripheral(12, PIO_SERCOM);
  pinPeripheral(13, PIO_SERCOM);
  pinPeripheral(11, PIO_SERCOM);


  
  //radio.initialize(FREQUENCY, MYNODEID, NETWORKID);
  

}

void loop() {
  // put your main code here, to run repeatedly:

}
