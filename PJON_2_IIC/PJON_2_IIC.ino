#define I2C_NUM 1 // no of IIC channels on branch.

#include "global.h"
#include "macros.h"
#include "utils.h"
#include "pJon.h"

void setup() {
  DBEGIN(9600);
    bus.set_receiver(receiver_handler); // link PJON to receiver
    bus.strategy.set_pin(12); // Set PJON pin
    bus.begin(); // 
    Wire.begin();
}

void loop() {
  bus.update(); // update the PJON
  bus.receive(5000); // receive for a while
}
