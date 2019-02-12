#ifndef ALT_TEST_H
#define ALT_TEST_H

#include <Wire.h>
#include "wiring_private.h"
#include "SERCOM.h"
#include "variant.h"

#define ALT_SDA 11  // sercom1[0]
#define ALT_SCL 13  // sercom1[1]
#define ALT_ADDR 0x60

void alt_setup(TwoWire * sensor, uint8_t offset);

#endif

