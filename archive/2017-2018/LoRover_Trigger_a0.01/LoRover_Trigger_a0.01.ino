//Libraries
#include <RFM69.h>
#include <SPI.h>
 

//Node Identifiers
#define NETWORKID     1   // Must be the same for all nodes
#define MYNODEID      2   // My node ID
#define TONODEID      1   // Destination node ID

//Frequency
#define FREQUENCY RF69_915MHZ

// AES encryption (or not):

#define ENCRYPT       true // Set to "true" to use encryption
#define ENCRYPTKEY    "TeamCornell2014" // Use the same 16-byte key on all nodes

// Use ACKnowledge when sending messages (or not):

#define USEACK        true // Request ACKs or not

// Packet sent/received indicator LED (optional):

#define LED 3



RFM69 radio;

void setup()
{
  //INITIALIZE SERIAL
  Serial.begin(9600);
  Serial.print("WIRECOMM MODULE: ");
  Serial.print(MYNODEID,DEC);
  Serial.print(" ready");

  //INITIALIZE LED
  pinMode(LED,OUTPUT);
  digitalWrite(LED,LOW);


  // INITIALIZE THE RFM69HCW
  radio.initialize(FREQUENCY, MYNODEID, NETWORKID);

  //INITIALIZE ENCRYPTION
  if (ENCRYPT) radio.encrypt(ENCRYPTKEY);
}

void loop()
{
  if (radio.receiveDone())
  {
    //radio.sendACK();
    //Serial.println("ACK sent");
    //SERIAL COMM FOR TESTING
    Serial.print("received from node ");
    Serial.print(radio.SENDERID, DEC);
    Serial.print(", message [");

    //RECEIVE BYTES INDEVIDUALLY
    for (byte i = 0; i < radio.DATALEN; i++)
      Serial.print((char)radio.DATA[i]);

    //PRINT RSSI FOR TESTING
    Serial.print("], RSSI ");
    Serial.println(radio.RSSI);
    
    if (radio.ACKRequested())
    {
      radio.sendACK();
      Serial.println("ACK sent");
    }
    
    char str[] = "ACTIVATE";
    if (strcmp(radio.DATA, (str)) == 0){
      
        digitalWrite(LED,HIGH);
        delay(100000);
        digitalWrite(LED,LOW);

        if (USEACK)
        {
          char return_str[] = "RECIEVED ROVER DEPLOYMENT TRIGGERED";
          int  return_length = 35;
          
          if (radio.sendWithRetry(TONODEID,return_str,return_length))
            Serial.println("LV RECIEVED CONFIRMATION");
            
          else
            Serial.println("LV DID NOT RECIEVE CONFIRMATION");
        }

        
    }

    //
  }
}

