// RECEIVER //
// To be used with radio_test
#include "SPI.h"
#include "radio.h"
#include "Wire.h"
#include "wiring_private.h"
#include "SERCOM.h"

#define NETWORKID 1 //must be same for both radios
#define MYNODEID 2 //node id for my radio
#define ENCRYPT true
#define E_KEY "testing"
#define FREQUENCY RF69_915MHZ

SPIClass mySPI(&sercom1, 12, 13, 11, SPI_PAD_0_SCK_1, SERCOM_RX_PAD_3); //set up SPI line
RFM69 radio(10, 2, true, &mySPI);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //mySPI.begin();

  radio.initialize(FREQUENCY, MYNODEID, NETWORKID);

  pinPeripheral(12, PIO_SERCOM);
  pinPeripheral(13, PIO_SERCOM);
  pinPeripheral(11, PIO_SERCOM);
  
  radio.setHighPower();
  radio.encrypt(E_KEY);
  
}

void loop() {
    if(radio.receiveDone()){
      Serial.print("received from node ");
      Serial.print(radio.SENDERID, DEC);
      Serial.print(", message [");

      //RECEIVE BYTES INDEVIDUALLY
      for (byte i = 0; i < radio.DATALEN; i++)
        Serial.print((char)radio.DATA[i]);
     
      Serial.println("]"); 
     
      if (radio.ACKRequested()){
        radio.sendACK();
        Serial.println("ACK sent");
      }
    }

}
