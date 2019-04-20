#include "alt_test.h"
#include "SparkFunMPL3115A2.h"


TwoWire myWire(&sercom2, 22, 38); // set up i2c line, SDA THEN SCL
//pa22 - sda
// pa23 - scl
//MPL3115A2 alt;
TwoWire testWire(&sercom3, 20, 21);
void setup() {
  myWire.begin();
  Serial.begin(9600);
  pinPeripheral(22, PIO_SERCOM);
  pinPeripheral(38, PIO_SERCOM);
  pinPeripheral(20, PIO_SERCOM);
  pinPeripheral(21, PIO_SERCOM);

//  // In ithaca, read 123 meters or around 404 ft.
  alt_setup(&myWire, (uint8_t) 0x1E); // should be 30
  alt_setup(&testWire, (uint8_t) 0x1E);
  pinMode(9, OUTPUT);
  digitalWrite(9, LOW);
  pinMode(8, OUTPUT);
  digitalWrite(8, LOW);
//  //alt_setup(&alt2, (uint8_t) 0x17); // should be 23
  
}

void loop() {
  delay(1000);
  float altitude1 = get_alt(&myWire);//alt.readAltitudeFt();
  float alt2 = get_alt(&testWire);
  Serial.println(altitude1);
  if(altitude1 < 10000 && altitude1 > 0){
    digitalWrite(9, HIGH);
    Serial.println(altitude1);
//    digitalWrite(8, HIGH);
//    digitalWrite(17, HIGH);
//    digitalWrite(18, HIGH);
  }
  if(alt2 < 10000){
    digitalWrite(8, HIGH);
    Serial.print("Alt2: ");
    Serial.println(alt2);
  }
//  digitalWrite(9, HIGH);
//  digitalWrite(8, HIGH);
//  digitalWrite(17, HIGH);
//  digitalWrite(18, HIGH);
  //while(1);
}

void alt_setup(TwoWire * sensor, uint8_t offset){
  sensor->beginTransmission(ALT_ADDR); // set up altimeter measurement
  sensor->write(0x26); // Control register
  sensor->write(0xB8);
  sensor->endTransmission();

  sensor->beginTransmission(ALT_ADDR);
  sensor->write(0x13); // data config
  sensor->write(0x07); // setting flags
  sensor->endTransmission();

  sensor->beginTransmission(ALT_ADDR);
  sensor->write(0x26);
  sensor->write(0xB9); // set altimeter active
  sensor->endTransmission();

  sensor->beginTransmission(ALT_ADDR);
  sensor->write(0x2D);
  sensor->write(offset); // set altimeter active
  sensor->endTransmission();

}

float get_alt(TwoWire * sensor) {
  float altitude = 50000;
  sensor->beginTransmission(ALT_ADDR);
  sensor->write(OUT_P_MSB);
  sensor->endTransmission(false);
  if(sensor->requestFrom(ALT_ADDR, 3) != 3){
    Serial.println("did not work");
  } else {
    byte msb, csb, lsb;
    msb = sensor->read();
    csb = sensor->read();
    lsb = sensor->read();

    float tempcsb = (lsb>>4)/16.0;
    altitude = (float)((msb << 8)|csb) + tempcsb;
    //Serial.println(3.28*altitude); 
  }
  return 3.28*altitude;
}


