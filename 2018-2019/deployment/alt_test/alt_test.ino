#include "alt_test.h"
#include "SparkFunMPL3115A2.h"

#define ALT2_SDA 4 // sercom0[0]
#define ALT2_SCL 3 // sercom0[1]


TwoWire myWire(&sercom1, 11, 13); // set up i2c line
TwoWire alt2(&sercom0, ALT2_SDA, ALT2_SCL);

void setup() {
  
  Serial.begin(115200);
  myWire.begin();                 // address optional for master
  alt2.begin();
  
  pinPeripheral(11, PIO_SERCOM);
  pinPeripheral(13, PIO_SERCOM);
  pinPeripheral(ALT2_SDA, PIO_SERCOM);
  pinPeripheral(ALT2_SCL, PIO_SERCOM);

  // In ithaca, read 123 meters or around 404 ft.
  alt_setup(&myWire, (uint8_t) 0x1E); // should be 30
  alt_setup(&alt2, (uint8_t) 0x17); // should be 23
  
}

void loop() {
  float altitude1 = get_alt(&myWire);
  float altitude2 = get_alt(&alt2);
  Serial.print("Alt1: ");
  Serial.print(altitude1);
  Serial.print("\tAlt2: ");
  Serial.println(altitude2);
  delay(500);
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


